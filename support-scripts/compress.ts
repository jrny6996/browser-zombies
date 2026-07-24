#!/usr/bin/env -S deno run -A

import { basename, extname, join } from "jsr:@std/path";

const COMPRESSION_RATIOS = [1.0, 0.5, 0.25, 0.1, 0.05];
const DIST_DIR = "dist";

async function compressGlb(inputFile: string) {
  const modelName = basename(inputFile, ".glb");
  const outDir = join(DIST_DIR, modelName);

  await Deno.mkdir(outDir, { recursive: true });

  for (const ratio of COMPRESSION_RATIOS) {
    const percent = Math.round(ratio * 100);
    const outputFile = join(outDir, `${modelName}-${percent}.glb`);

    console.log(`[${percent}%] ${inputFile} -> ${outputFile}`);

    const command = new Deno.Command("gltf-transform", {
      args: [
        "simplify",
        inputFile,
        outputFile,
        "--ratio",
        ratio.toString(),
      ],
      stdout: "inherit",
      stderr: "inherit",
    });

    const { code } = await command.output();

    if (code !== 0) {
      throw new Error(`gltf-transform exited with code ${code}`);
    }
  }
}

async function collectGlbs(dir: string): Promise<string[]> {
  const files: string[] = [];

  for await (const entry of Deno.readDir(dir)) {
    const full = join(dir, entry.name);

    if (entry.isDirectory) {
      files.push(...await collectGlbs(full));
    } else if (
      entry.isFile && extname(entry.name).toLowerCase() === ".glb"
    ) {
      files.push(full);
    }
  }

  return files;
}

async function processPath(path: string) {
  const trailingSlash = path.endsWith("/") || path.endsWith("\\");

  try {
    const stat = await Deno.stat(path);

    if (stat.isDirectory || trailingSlash) {
      const files = await collectGlbs(path);

      if (files.length === 0) {
        console.log("No .glb files found.");
        return;
      }

      for (const file of files) {
        await compressGlb(file);
      }

      return;
    }

    if (stat.isFile && extname(path).toLowerCase() === ".glb") {
      await compressGlb(path);
      return;
    }

    console.error("Path is not a .glb file or directory.");
  } catch {
    console.error(`Path not found: ${path}`);
  }
}

async function main() {
  let input = Deno.args[0];

  if (!input) {
    input = prompt("Enter asset path:") ?? "";
  }

  input = input.trim();

  if (!input) {
    console.error("No path provided.");
    Deno.exit(1);
  }

  await processPath(input);
}

main().catch((err) => {
  console.error(err);
  Deno.exit(1);
});

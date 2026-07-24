#!/usr/bin/env -S deno run -A

import { basename, extname, join } from "jsr:@std/path";

const COMPRESSION_RATIOS = [1.0, 0.5, 0.25, 0.1, 0.05];

const DIST_DIR = "dist";
const TEXTURE_SIZE = 512;

async function runCommand(args: string[]) {
  const command = new Deno.Command("gltf-transform", {
    args,
    stdout: "inherit",
    stderr: "inherit",
  });

  const status = await command.spawn().status;

  if (!status.success) {
    throw new Error(
      `gltf-transform failed: ${args.join(" ")}`,
    );
  }
}

async function compressGlb(inputFile: string) {
  const modelName = basename(inputFile, ".glb");
  const outDir = join(DIST_DIR, modelName);

  await Deno.mkdir(outDir, { recursive: true });

  for (const ratio of COMPRESSION_RATIOS) {
    const percent = Math.round(ratio * 100);

    const tempSimplified = join(
      outDir,
      `${modelName}-${percent}-simplified.glb`,
    );

    const tempResized = join(
      outDir,
      `${modelName}-${percent}-resized.glb`,
    );

    const outputFile = join(
      outDir,
      `${modelName}-${percent}.glb`,
    );

    console.log(
      `\n[${percent}%] Processing ${inputFile}`,
    );

    // 1. Reduce geometry
    await runCommand([
      "simplify",
      inputFile,
      tempSimplified,
      "--ratio",
      ratio.toString(),
    ]);

    // 2. Resize textures
    await runCommand([
      "resize",
      tempSimplified,
      tempResized,
      "--width",
      TEXTURE_SIZE.toString(),
      "--height",
      TEXTURE_SIZE.toString(),
    ]);

    // 3. Draco compression
    await runCommand([
      "draco",
      tempResized,
      outputFile,
    ]);

    console.log(
      `Created: ${outputFile}`,
    );

    // Cleanup intermediates
    await safeRemove(tempSimplified);
    await safeRemove(tempResized);
  }
}

async function safeRemove(file: string) {
  try {
    await Deno.remove(file);
  } catch {
    // ignore missing files
  }
}

async function collectGlbs(dir: string): Promise<string[]> {
  const files: string[] = [];

  for await (const entry of Deno.readDir(dir)) {
    const full = join(dir, entry.name);

    if (entry.isDirectory) {
      files.push(...await collectGlbs(full));
    } else if (
      entry.isFile &&
      extname(entry.name).toLowerCase() === ".glb"
    ) {
      files.push(full);
    }
  }

  return files;
}

async function processPath(path: string) {
  try {
    const stat = await Deno.stat(path);

    if (stat.isDirectory) {
      const files = await collectGlbs(path);

      if (!files.length) {
        console.log("No .glb files found.");
        return;
      }

      for (const file of files) {
        await compressGlb(file);
      }

      return;
    }

    if (
      stat.isFile &&
      extname(path).toLowerCase() === ".glb"
    ) {
      await compressGlb(path);
      return;
    }

    console.error(
      "Path must be a .glb file or directory.",
    );
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

# Supporting scripts (Asset compression only for now)

Install deps

`npm install -g @gltf-transform/cli`

## Run asset compression

on directory

`./support-scripts/compress.ts ./support-scripts/raw/`

or on specific file

`./support-scripts/compress.ts ./support-scripts/raw/somefile.glb`

outputs to `./support-scripts/dist/{modelname}/{modelname-proxypercentage.glb}`

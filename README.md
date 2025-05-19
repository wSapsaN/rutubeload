# rutubeload

This project is designed to download videos from rutube.
At this stage, the program saves the file in ts format.
Plans are to receive mp4 files.

You also need to output timeLine at the time of downloading chunks.

# Build

```bash
mkdir build
cd build

cmake ../
make
```

Launch:
```bash
./rutubeload -h # you receive instruction
./rutubeload <LINK> # if file doesn't define, the application itself creates "file.ts"
./rutubeload <LINK> <FILENAME> # define filename without extension
```
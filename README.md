# Huffman Coding
This is an implementation of the Huffman coding compression algorithm.

## Building and running
The project uses CMake so you can build the project with that by
make a build directory inside the project and then run the comand below to to build the executable.
```bash
cmake ..
make
```


You can (at some point) run the following commands to compress files with the -c flag (omit for now)
```bash
./huffman_coding -c <file to compress>
```

To decompress use the -d flat (not implemented yet)
```bash
./huffman_coding -d <file to decompress>
```

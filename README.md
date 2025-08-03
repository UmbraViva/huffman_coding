# Huffman Coding
This is an implementation of the Huffman coding compression algorithm.

## Building and running
The project uses CMake so you can build the project with that by
make a build directory inside the project and then running
```bash
cmake ..
make
```

to build the executable. You compress files by using the -c flag
```bash
./huffman_coding -c <file to compress>
```

and decompress with -d
```bash
./huffman_coding -d <file to decompress>
```

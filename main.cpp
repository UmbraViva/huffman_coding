#include "Node.h"
#include "huffman.h"
#include <fstream>
#include <iostream>
#include <set>

int main(int argc, char *argv[]) {
    std::ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    // Finds which characters are in the file and adds them to a vector
    char letter;
    std::string letter_string;
    std::set<std::string> letters;
    while (inputFile.get(letter)) {
        letter_string = letter;
        letters.insert(letter_string);
    }
    const std::vector ordered_letters(letters.begin(), letters.end());

    // Generates tree based on queue
    std::priority_queue<std::unique_ptr<Node>,
                        std::vector<std::unique_ptr<Node>>, CompareNode>
        queue = Huffman::generate_queue(ordered_letters, inputFile);

    Huffman::generate_tree(queue);

    // Travereses the tree and stores nodes in a map
    const std::unique_ptr<Node> &root = queue.top();
    std::map<char, int> encoding_map = Huffman::traverse_tree(root);

    Huffman::encode_data(argv[1], encoding_map);

    inputFile.close();
    return 0;
}

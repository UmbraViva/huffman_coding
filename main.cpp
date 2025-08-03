#include <iostream>
#include <set>
#include <fstream>

#include "Node.h"
#include "huffman.h"

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

    std::priority_queue<std::unique_ptr<Node>,
                        std::vector<std::unique_ptr<Node>>, CompareNode>
        queue = Huffman::generate_queue(ordered_letters, inputFile);

    Huffman::generate_tree(queue);

    // Travereses the tree and stores nodes in a map
    // const std::unique_ptr<Node> &root = queue.top();
    // std::unique_ptr<Node> current_node;
    // std::string key = "";
    // std::map<char, std::string> encodeing_key;

    // for (int i = 0; i < root->getCharacter().length(); i++) {
    //     char character = root->getCharacter()[i];

    //    if (root->getLeft() != nullptr || root->getRight() != nullptr) {

    //        if (root->getLeft()->getCharacter().find(character) !=
    //            std::string::npos) {
    //            key.push_back('0');
    //            current_node = std::move(root->getLeft());
    //        }
    //        if (root->getRight()->getCharacter().find(character) !=
    //            std::string::npos) {
    //            key.push_back('1');
    //            current_node = std::move(root->getRight());
    //        }
    //    } else {
    //        key = "";
    //    }
    //}

    return 0;
}

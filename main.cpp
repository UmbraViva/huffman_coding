#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>

#include "Node.h"

int main(int argc, char *argv[]) {
    std::priority_queue<std::unique_ptr<Node>,
                        std::vector<std::unique_ptr<Node>>, CompareNode>
        queue;
    std::ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    // Finds which characters are in the file and adds them to the array
    char letter;
    std::string letter_string;
    std::set<std::string> letters;
    while (inputFile.get(letter)) {
        letter_string = letter;
        letters.insert(letter_string);
    }
    const std::vector ordered_letters(letters.begin(), letters.end());

    // Counts how many times each character appears
    // in the file and then adds them to the queue
    int characterCount = 0;
    for (const std::string &ordered_letter : ordered_letters) {
        // Resets file errors (EOF) and file pointer
        inputFile.clear();
        inputFile.seekg(0);

        // Counts characters and adds them to the queue
        char character;
        while (inputFile.get(character)) {
            letter_string = character;
            if (letter_string == ordered_letter) {
                characterCount++;
            }
        }
        queue.push(std::make_unique<Node>(ordered_letter, characterCount));
        characterCount = 0;
    }

    // Combines nodes into a tree
    while (queue.size() > 1) {

        // Copies the lowest weighted nodes and takes them off the queue
        auto first_character = std::make_unique<Node>(
            queue.top()->getCharacter(), queue.top()->getCount(),
            std::move(queue.top()->getLeft()),
            std::move(queue.top()->getRight()));
        queue.pop();

        auto second_character = std::make_unique<Node>(
            queue.top()->getCharacter(), queue.top()->getCount(),
            std::move(queue.top()->getLeft()),
            std::move(queue.top()->getRight()));
        queue.pop();

        // Makes a new node by concatenating the characters and adding weights
        auto new_node = std::make_unique<Node>(
            first_character->getCharacter() + second_character->getCharacter(),
            first_character->getCount() + second_character->getCount());

        // Makes the children of the new node the lowest weighted nodes that
        // were popped off the queue
        new_node->setLeft(std::make_unique<Node>(
            first_character->getCharacter(), first_character->getCount(),
            std::move(first_character->getLeft()),
            std::move(first_character->getRight())));

        new_node->setRight(std::make_unique<Node>(
            second_character->getCharacter(), second_character->getCount(),
            std::move(second_character->getLeft()),
            std::move(second_character->getRight())));

        // Puts the new node back into the queue
        queue.push(std::move(new_node));
    }

    // Travereses the tree and stores nodes in a map
    const std::unique_ptr<Node> &root = queue.top();
    std::unique_ptr<Node> current_node;
    std::string key = "";
    std::map<char, std::string> encodeing_key;

    for (int i = 0; i < root->getCharacter().length(); i++) {
        char character = root->getCharacter()[i];

        if (root->getLeft() != nullptr || root->getRight() != nullptr) {

            if (root->getLeft()->getCharacter().find(character) !=
                std::string::npos) {
                key.push_back('0');
                current_node = std::move(root->getLeft());
            }
            if (root->getRight()->getCharacter().find(character) !=
                std::string::npos) {
                key.push_back('1');
                current_node = std::move(root->getRight());
            }
        } else {
            key = "";
        }
    }

    return 0;
}

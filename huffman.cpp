#include "huffman.h"
#include <fstream>
#include <map>

std::priority_queue<std::unique_ptr<Node>, std::vector<std::unique_ptr<Node>>,
                    CompareNode>
Huffman::generate_queue(const std::vector<std::string> &letters,
                        std::ifstream &inputFile) {
    std::priority_queue<std::unique_ptr<Node>,
                        std::vector<std::unique_ptr<Node>>, CompareNode>
        queue;
    // Counts how many times each character appears
    // in the file and then adds them to the queue
    std::string letter_string;
    int characterCount = 0;
    for (const std::string &letter : letters) {
        // Resets file errors (EOF) and file pointer
        inputFile.clear();
        inputFile.seekg(0);

        // Counts characters and adds them to the queue
        char character;
        while (inputFile.get(character)) {
            letter_string = character;
            if (letter_string == letter) {
                characterCount++;
            }
        }
        queue.push(std::make_unique<Node>(letter, characterCount));
        characterCount = 0;
    }
    return queue;
}

void Huffman::generate_tree(
    std::priority_queue<std::unique_ptr<Node>,
                        std::vector<std::unique_ptr<Node>>, CompareNode>
        &queue) {
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
}

std::map<char, int>
Huffman::traverse_tree(const std::unique_ptr<Node> &rootNode) {
    std::map<char, int> encoding_map;

    // Helper function to recursively traverse the tree
    std::function<void(const std::unique_ptr<Node> &, int, int)> traverse =
        [&](const std::unique_ptr<Node> &node, int code, int depth) {
            if (!node)
                return;

            // If this is a leaf node (has a single character)
            if (node->getCharacter().length() == 1) {
                encoding_map[node->getCharacter()[0]] = code;
                return;
            }

            // Traverse left (0 bit) and right (1 bit) children
            // Shift code left by 1 bit and add 0 for left, 1 for right
            traverse(node->getLeft(), code << 1, depth + 1);
            traverse(node->getRight(), (code << 1) | 1, depth + 1);
        };

    // Start traversal from root with empty code
    if (rootNode) {
        traverse(rootNode, 0, 0);
    }

    return encoding_map;
}

#pragma once
#include "Node.h"
#include <map>
#include <memory>
#include <queue>

namespace Huffman {

std::priority_queue<std::unique_ptr<Node>, std::vector<std::unique_ptr<Node>>,
                    CompareNode>
generate_queue(const std::vector<std::string> &letters,
               std::ifstream &inputFile);

void generate_tree(std::priority_queue<std::unique_ptr<Node>,
                                       std::vector<std::unique_ptr<Node>>,
                                       CompareNode> &queue);
std::map<char, std::string>
traverse_tree(const std::unique_ptr<Node> &rootNode);
void encode_data(const std::string &inputFile,
                 const std::map<char, std::string> &encoding_map);
} // namespace Huffman

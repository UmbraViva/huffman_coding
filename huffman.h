#pragma once
#include "Node.h"
#include <queue>

namespace Huffman {

std::priority_queue<std::unique_ptr<Node>, std::vector<std::unique_ptr<Node>>,
                    CompareNode>
generate_queue(const std::vector<std::string> &letters,
               std::ifstream &inputFile);

void generate_tree(std::priority_queue<std::unique_ptr<Node>,
                                       std::vector<std::unique_ptr<Node>>,
                                       CompareNode> &queue);
} // namespace Huffman

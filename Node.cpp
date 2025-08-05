#include "Node.h"

Node::Node(const std::string &character, const int count) {
    this->character = character;
    this->count = count;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(const std::string &character, const int count,
           std::unique_ptr<Node> left, std::unique_ptr<Node> right)
    : left(std::move(left)), right(std::move(right)) {
    this->character = character;
    this->count = count;
}

void Node::updateCount() {
    this->count++;
}

[[nodiscard]] int Node::getCount() const {
    return this->count;
}

[[nodiscard]] std::string Node::getCharacter() {
    return this->character;
}

[[nodiscard]] std::unique_ptr<Node> &Node::getLeft() {
    return left;
}

[[nodiscard]] std::unique_ptr<Node> &Node::getRight() {
    return right;
}

void Node::setLeft(std::unique_ptr<Node> left) {
    this->left = std::move(left);
}

void Node::setRight(std::unique_ptr<Node> right) {
    this->right = std::move(right);
}

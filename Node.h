#pragma once
#include <string>

class Node {
    std::string character;
    int count;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

public:
    Node(const std::string &character, int count);
    Node(const std::string &character, int count, std::unique_ptr<Node> left, std::unique_ptr<Node> right);
    void updateCount();
    [[nodiscard]] int getCount() const;
    [[nodiscard]] std::string getCharacter();
    [[nodiscard]] std::unique_ptr<Node>& getLeft();
    [[nodiscard]] std::unique_ptr<Node>& getRight();
    void setLeft(std::unique_ptr<Node> left);
    void setRight(std::unique_ptr<Node> right);
};

struct CompareNode {
    bool operator()(const std::unique_ptr<Node>& a, const std::unique_ptr<Node>& b) const {
        return a->getCount() > b->getCount();
    }
};

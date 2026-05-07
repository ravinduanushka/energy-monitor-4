#include "TreeNode.h"

TreeNode::TreeNode(std::string n, double p) {

    name = n;
    totalPower = p;
}

void TreeNode::addChild(TreeNode* child) {

    children.push_back(child);
}
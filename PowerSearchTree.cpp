#include "PowerSearchTree.h"

PowerSearchTree::PowerSearchTree() : root(nullptr) {}

void PowerSearchTree::insert(BSTNode*& node, Device* d) {
    if (!node) node = new BSTNode(d);
    else if (d->getPower() < node->device->getPower()) insert(node->left, d);
    else insert(node->right, d);
}

void PowerSearchTree::rangeSearch(BSTNode* node, double min, double max) const {
    if (!node) return;
    if (node->device->getPower() > min) rangeSearch(node->left, min, max);
    if (node->device->getPower() >= min && node->device->getPower() <= max)
        std::cout << " - " << node->device->getName() << " (" << node->device->getPower() << "W)\n";
    if (node->device->getPower() < max) rangeSearch(node->right, min, max);
}

void PowerSearchTree::add(Device* d) {
    insert(root, d);
}

void PowerSearchTree::search(double min, double max) const {
    rangeSearch(root, min, max);
}

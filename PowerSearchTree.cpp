#include "PowerSearchTree.h"

PowerSearchTree::PowerSearchTree() : root(nullptr) {}

void PowerSearchTree::insert(BSTNode*& node, Device* d) {
    if (!node) node = new BSTNode(d);
    else if (d->powerRating < node->device->powerRating) insert(node->left, d);
    else insert(node->right, d);
}

void PowerSearchTree::rangeSearch(BSTNode* node, double min, double max) const {
    if (!node) return;
    if (node->device->powerRating > min) rangeSearch(node->left, min, max);
    if (node->device->powerRating >= min && node->device->powerRating <= max)
        std::cout << " - " << node->device->name << " (" << node->device->powerRating << "W)\n";
    if (node->device->powerRating < max) rangeSearch(node->right, min, max);
}

void PowerSearchTree::add(Device* d) {
    insert(root, d);
}

void PowerSearchTree::search(double min, double max) const {
    rangeSearch(root, min, max);
}

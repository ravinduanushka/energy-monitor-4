
#define TREENODE_H

#include <string>
#include <vector>

class TreeNode {

public:
    std::string name;
    double totalPower;

    std::vector<TreeNode*> children;

    TreeNode(std::string n, double p = 0);

    void addChild(TreeNode* child);
};

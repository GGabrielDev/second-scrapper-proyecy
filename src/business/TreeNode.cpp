#include "TreeNode.h"

TreeNode::TreeNode(const std::string& url, bool broken)
    : url(url), isBroken(broken) {}

TreeNode::~TreeNode() {
    for (TreeNode* child : children)
        delete child;
}

void TreeNode::addChild(TreeNode* child) {
    children.push_back(child);
}

const std::string& TreeNode::getUrl() const {
    return url;
}

const std::vector<TreeNode*>& TreeNode::getChildren() const {
    return children;
}

bool TreeNode::getIsBroken() const {
    return isBroken;
}

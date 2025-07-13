#include "CrawlStats.h"
#include "TreeNode.h"

TreeNode::TreeNode(const std::string& url, bool broken, bool external)
    : url(url), isBroken(broken), isExternal(external) {}

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

bool TreeNode::getIsExternal() const {
    return isExternal;
}

CrawlStats TreeNode::getStats() const {
    CrawlStats stats;
    stats.total = 1;
    if (isExternal)
        stats.external++;
    else
        stats.internal++;
    if (isBroken)
        stats.broken++;

    for (TreeNode* child : children) {
        CrawlStats childStats = child->getStats();
        stats.total += childStats.total;
        stats.internal += childStats.internal;
        stats.external += childStats.external;
        stats.broken += childStats.broken;
    }

    return stats;
}

#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <string>
#include <vector>

class TreeNode {
private:
    std::string url;
    bool isBroken;
    bool isExternal;
    std::vector<TreeNode*> children;

public:
    TreeNode(const std::string& url, bool broken = false, bool external = false);
    ~TreeNode();

    void addChild(TreeNode* child);
    const std::string& getUrl() const;
    const std::vector<TreeNode*>& getChildren() const;
    bool getIsBroken() const;
    bool getIsExternal() const;
};

#endif

#ifndef TREE_EXPORTER_H
#define TREE_EXPORTER_H

#include <string>
#include "TreeNode.h"

class TreeExporter {
public:
    static bool exportToHtml(TreeNode* root, const std::string& filename);
};

#endif

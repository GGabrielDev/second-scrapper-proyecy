#include "TreeNode.h"
#include <cassert>
#include <iostream>

int main() {
    TreeNode* root = new TreeNode("https://uneg.edu.ve");
    TreeNode* child1 = new TreeNode("https://uneg.edu.ve/page1");
    TreeNode* child2 = new TreeNode("https://google.com", true);  // enlace roto externo

    root->addChild(child1);
    root->addChild(child2);

    assert(root->getUrl() == "https://uneg.edu.ve");
    assert(root->getChildren().size() == 2);
    assert(!child1->getIsBroken());
    assert(child2->getIsBroken());

    std::cout << "All TreeNode tests passed.\n";

    delete root;
    return 0;
}

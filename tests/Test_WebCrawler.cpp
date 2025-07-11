#include "WebCrawler.h"
#include <iostream>

void printTree(TreeNode* node, int depth = 0) {
    if (!node) return;
    for (int i = 0; i < depth; ++i) std::cout << "  ";
    std::string tag = node->getIsExternal() ? "[E]" : (node->getIsBroken() ? "[X]" : "[✓]");
    std::cout << tag << " " << node->getUrl() << "\n";
    for (TreeNode* child : node->getChildren()) {
        printTree(child, depth + 1);
    }
}

int main() {
    std::cout << "Iniciando prueba de WebCrawler...\n";
    WebCrawler crawler("uneg.edu.ve", true);
    TreeNode* root = crawler.crawl("https://uneg.edu.ve", 1);

    if (root) {
        std::cout << "\nÁrbol generado:\n";
        printTree(root);
        delete root;
    } else {
        std::cout << "Fallo al crear el árbol\n";
    }
    return 0;
}

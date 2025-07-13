#include <iostream>
#include "CrawlStats.h"
#include "WebCrawler.h"

void printTree(TreeNode* node, int depth = 0) {
    if (!node) return;
    for (int i = 0; i < depth; ++i) std::cout << "  ";
    std::string tag = node->getIsExternal() ? "[E]" : (node->getIsBroken() ? "[X]" : "[✓]");
    std::cout << tag << " " << node->getUrl() << "\n";
    for (TreeNode* child : node->getChildren()) {
        printTree(child, depth + 1);
    }
}

void printStats(const CrawlStats& stats) {
    std::cout << "\nEstadísticas:\n";
    std::cout << "  Total de nodos: " << stats.total << "\n";
    std::cout << "  Internos válidos: " << stats.internal << "\n";
    std::cout << "  Enlaces rotos: " << stats.broken << "\n";
    std::cout << "  Enlaces externos: " << stats.external << "\n";
}

int main() {
    std::cout << "Iniciando prueba de WebCrawler...\n";
    WebCrawler crawler("uneg.edu.ve", true);
    TreeNode* root = crawler.crawl("https://uneg.edu.ve/", 5);

    if (root) {
        // Mostrar Arbol
        std::cout << "\nÁrbol generado:\n";
        printTree(root);

        // Mostrar stats
        CrawlStats stats = root->getStats();
        printStats(stats);
        delete root;
    } else {
        std::cout << "Fallo al crear el árbol\n";
    }
    return 0;
}

#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include "TreeExporter.h"
#include "WebCrawler.h"

int main() {
    std::cout << "Iniciando prueba de exportación...\n";

    WebCrawler crawler("uneg.edu.ve", true);
    TreeNode* root = crawler.crawl("https://uneg.edu.ve", 2);
    assert(root != nullptr);

    const std::string filename = "navegacion_exportada.html";
    bool ok = TreeExporter::exportToHtml(root, filename);
    assert(ok);

    std::ifstream file(filename);
    assert(file.is_open());

    std::cout << "\nContenido exportado:\n";
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << "\n";
    }
    file.close();

    if (std::remove(filename.c_str()) == 0)
        std::cout << "\nArchivo eliminado correctamente.\n";
    else
        std::cerr << "\nError al eliminar el archivo.\n";

    delete root;
    return 0;
}

#include <fstream>
#include <iostream>
#include "TreeExporter.h"

static void writeNode(std::ofstream& file, TreeNode* node, int depth) {
    if (!node) return;

    std::string indent(depth * 2, ' ');
    std::string label = node->getUrl();
    std::string cssClass;

    if (node->getIsExternal())
        cssClass = "external";
    else if (node->getIsBroken())
        cssClass = "broken";
    else
        cssClass = "valid";

    file << indent << "<li class=\"" << cssClass << "\">"
         << "<a href=\"" << label << "\">" << label << "</a>";

    const auto& children = node->getChildren();
    if (!children.empty()) {
        file << "\n" << indent << "  <ul>\n";
        for (TreeNode* child : children) {
            writeNode(file, child, depth + 2);
        }
        file << indent << "  </ul>\n";
    }

    file << indent << "</li>\n";
}

bool TreeExporter::exportToHtml(TreeNode* root, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[exportToHtml] Error al abrir el archivo: " << filename << "\n";
        return false;
    }

    file << "<!DOCTYPE html>\n<html>\n<head>\n"
         << "<style>\n"
         << "  ul { list-style-type: none; }\n"
         << "  .valid a { color: green; }\n"
         << "  .broken a { color: red; text-decoration: line-through; }\n"
         << "  .external a { color: blue; }\n"
         << "</style>\n</head>\n<body>\n";

    file << "<ul>\n";
    writeNode(file, root, 1);
    file << "</ul>\n</body>\n</html>\n";

    file.close();
    return true;
}

#include <iostream>

#include "lib/notebook/notebook.h"
#include "lib/notebook/blocks/text.h"

using namespace NotebookBackend;

int main() {
    Notebook n;
    n.setName("new notebook");
    n.addBlock(std::make_shared<Block>(new TextContent("asdf")));
    n.addBlock(std::make_shared<Block>(new TextContent("asdf2")));
    n.addBlock(std::make_shared<Block>(new TextContent("asdf3")));
    std::cout << n.toJSON() << std::endl;
    n.deleteBlock(1);
    std::cout << n.toJSON() << std::endl;
}

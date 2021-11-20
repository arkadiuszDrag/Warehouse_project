#include "Goods.h"
#include "Warehouse.h"
#include "interface.h"
#include "Product.h"
#include <iostream>

#include "iosfwd"
#include <fstream>

std::basic_istream<char> *input;

int main(int argc, char** argv) {

    input = &std::cin;

    if (argc == 2) {
        auto file = new std::ifstream(argv[1], std::ios_base::in);
        input = file;
    } else {
        std::cerr << "Error! There is no input file.";
    }
    interface system;
    system.interfaceStart(input);
}

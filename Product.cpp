#include "Product.h"
#include <string>
#include <iostream>
#include <cstring>

int Product::idGenerator = 0;

void Product::copyString(const char *src, char **dst) {
    *dst = new char[ strlen(src) +1 ];
    strcpy(*dst, src);
}

Product::Product(): ID{idGenerator++} {
    std::cout<<"Products constructor"<<std::endl;
}

Product::~Product() {}
//
// Created by Arkadiusz Drąg on 19/11/2020.
//
#include <iostream>
#include "Goods.h"
#include <string>
#include <cstring>
//function comments are in the looseGoods class because the functions are almost the same

Goods::Goods(const Goods &t): Product(t) { //copy constructor
    copyString(t.name, &this->name);
    this->numOfItems = t.numOfItems;
}

Goods::Goods(const std::string &name): Goods::Goods(name.c_str()) {}

Goods::Goods(const char* name): name{nullptr}, numOfItems{0}, Product() {
    if (name != nullptr) {
        this->name = new char[strlen(name)+1];
        copyString(name, &this->name);
    }
}

std::ostream & operator << (std::ostream &output, const Goods &t) {
    return output << "ID:"<< t.ID << " || Products name: " << t.name <<" || Number of items: "<< t.numOfItems;
}



Product* Goods::divide(int amount) {
    Goods* t = new Goods (*this);
    t->numOfItems = amount;
    return t;
}

Product* Goods::divide(float amount) {
    Goods* t = new Goods (*this);
    t->numOfItems = static_cast<int>(amount);
    return t;
}

void Goods::scal(Product *p) {
    this->numOfItems += p->getAmountInt();
    delete p;
}

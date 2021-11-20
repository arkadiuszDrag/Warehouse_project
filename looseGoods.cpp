//
// Created by Arkadiusz Drąg on 15/12/2020.
//

#include <iostream>
#include "looseGoods.h"
#include <string>
#include "Product.h"
#include <cstring>

looseGoods::looseGoods(const looseGoods &t): Product(t) { //copy constructor
    copyString(t.name, &this->name);
    this->amount_kg = t.amount_kg;
}

looseGoods::looseGoods(const std::string &name): looseGoods::looseGoods(name.c_str()) {}

looseGoods::looseGoods(const char* name): name{nullptr}, amount_kg{0}, Product() {
    if (name != nullptr) {
        this->name = new char[strlen(name)+1];
        copyString(name, &this->name);
    }
}

Product* looseGoods::divide(float amount) {
    looseGoods* t = new looseGoods (*this); //a new pointer to the item to be returned is created
    t->amount_kg = amount;
    return t;
}

Product* looseGoods::divide(int amount) {
    looseGoods* t = new looseGoods (*this);
    t->amount_kg = static_cast<float>(amount);
    return t;
}

void looseGoods::scal(Product *p) {
    this->amount_kg += p->getAmountFloat(); // the amount of the product from the given product is added to the given item
    delete p;
}

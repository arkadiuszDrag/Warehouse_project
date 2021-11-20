//
// Created by Arkadiusz Drąg on 15/12/2020.
//

#include <iostream>
#include "liquidGoods.h"
#include <string>
#include <cstring>


liquidGoods::liquidGoods(const liquidGoods &t): Product(t) { //konstruktor kopiujacy
    copyString(t.name, &this->name);
    this->amount_L = t.amount_L;
}

liquidGoods::liquidGoods(const std::string &name): liquidGoods::liquidGoods(name.c_str()) {}

liquidGoods::liquidGoods(const char* name): name{nullptr}, amount_L{0}, Product() {
    if (name != nullptr) {
        this->name = new char[strlen(name)+1];
        copyString(name, &this->name);
    }
}

Product* liquidGoods::divide(float amount) {
    liquidGoods* t = new liquidGoods (*this);
    t->amount_L = amount;
    return t;
}

Product* liquidGoods::divide(int amount) {
    liquidGoods* t = new liquidGoods (*this);
    t->amount_L = static_cast<float>(amount);
    return t;
}

void liquidGoods::scal(Product *p) {
    this->amount_L += p->getAmountFloat();
    delete p;
}


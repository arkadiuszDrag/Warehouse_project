//
// Created by Arkadiusz Drąg on 15/12/2020.
//
#include <iostream>
#include "Product.h"

#ifndef WAREHOUSE_PROJECT_LIQUIDGOODS_H
#define WAREHOUSE_PROJECT_LIQUIDGOODS_H

class liquidGoods: public Product {
    char *name;
    float amount_L;

public:
    explicit liquidGoods(const liquidGoods &t);

    explicit liquidGoods(const std::string &name);

    explicit liquidGoods(const char *name= nullptr);

    Product& operator+= (float amount) override {
        this->amount_L += amount;
        return *this;
    }

    Product& operator-= (float amount) override {
        this->amount_L -= amount;
        return *this;
    }

    float getAmountFloat() override {return amount_L;}

    void displayProduct() override {
        std::cout << "ID:"<< ID << " || Products name: " << name <<" || amount in liters: "<< amount_L << std::endl;
    }
    void displayAmount() override { std::cout << amount_L << " liters" << std::endl; }
    Product* divide(float amount) override;
    void scal(Product *p) override;
    int getID() override {return ID;}

    Product &operator-=(int amount) override {
        this->amount_L -= amount;
        return *this;
    }
    Product &operator+=(int amount) override {
        this->amount_L += amount;
        return *this;
    }
    int getAmountInt() override {return amount_L;}
    Product* divide (int amount) override;


};

#endif //WAREHOUSE_PROJECT_LIQUIDGOODS_H

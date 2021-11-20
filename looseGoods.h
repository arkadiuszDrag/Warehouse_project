#include <iostream>
#include "Product.h"

#ifndef WAREHOUSE_PROJECT_LOOSEGOODS_H
#define WAREHOUSE_PROJECT_LOOSEGOODS_H

class looseGoods: public Product {
    char *name;
    float amount_kg;

public:
    explicit looseGoods(const looseGoods &t);

    explicit looseGoods(const std::string &name);

    explicit looseGoods(const char *name = nullptr);


    Product& operator+= (float amount) override {
        this->amount_kg += amount;
        return *this;
    }

    Product& operator-= (float amount) override {
        this->amount_kg -= amount;
        return *this;
    }

    float getAmountFloat() override {return amount_kg;}
    void displayProduct() override {
        std::cout << "ID:"<< ID << " || Products name: " << name <<" || amount in kilograms: "<< amount_kg << std::endl;
    }
    void displayAmount() override { std::cout << amount_kg << " kg" << std::endl; }
    Product* divide(float ilosc) override; //allocates a given quantity of goods to the new returned goods
    void scal(Product *p) override; //adds the quantity of goods to the given goods
    int getID() override {return ID;}

    Product &operator-=(int amount) override {
        this->amount_kg -= amount;
        return *this;
    }
    Product &operator+=(int amount) override {
        this->amount_kg += amount;
        return *this;
    }
    int getAmountInt() override {return amount_kg;}
    Product* divide (int amount) override;





};

#endif //WAREHOUSE_PROJECT_LOOSEGOODS_H

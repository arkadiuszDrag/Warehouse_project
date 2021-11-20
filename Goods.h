#include <iostream>
#include "Product.h"


#ifndef WAREHOUSE_PROJECT_GOODS_H
#define WAREHOUSE_PROJECT_GOODS_H


class Goods: public Product{
    char* name;
    int numOfItems;

public:
    explicit Goods(const Goods &t);
    explicit Goods(const std::string &name);
    explicit Goods(const char* name = nullptr);

    Product& operator+= (int amount) override {
        this->numOfItems += amount;
        return *this;
    }

    Produkt& operator-= (int amount) override {
        this->numOfItems -= amount;
        return *this;
    }

    friend std::ostream & operator << (std::ostream &output, const Goods &t);

    int getAmountInt() override { return numOfItems; }//returns the number of items
    void displayProduct() override {
        std::cout << "ID:"<< ID << " || Products name: " << nazwa <<" || Number of items: "<< liczba_sztuk << std::endl;
    }

    void displayAmount() override { std::cout << amount << " pieces" << std::endl; }
    Product* divide(int amount) override;
    void scal(Product *p) override;
    int getID() override {return ID;}

    Product &operator-=(float amount) override {
        this->numOfItems -= amount;
        return *this;
    }
    Product &operator+=(float amount) override {
        this->numOfItems += amount;
        return *this;
    }
    float getAmountFloat() override { return numOfItems; }
    Product* divide(float amount) override;

};


#endif //WAREHOUSE_PROJECT_GOODS_H

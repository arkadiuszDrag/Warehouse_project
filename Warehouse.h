//
// Created by Arkadiusz Drąg on 19/11/2020.
//
#include <iostream>
#include <vector>
#include "Goods.h"
#include "looseGoods.h"
#include "liquidGoods.h"
#include "Product.h"
#include "Jigger.h"
#include <string>
#include <cstdio>

#ifndef WAREHOUSE_PROJECT_WAREHOUSE_H
#define WAREHOUSE_PROJECT_WAREHOUSE_H


class Warehouse {
    std::vector<Product*> t_vec;
    std::string warehouseName;

public:

    explicit Warehouse(const std::string &name);

    Magazyn() = default;
    template<typename T> void handOver(int id, T amount, Jigger &p);

    int getIndexOfID(int id); //extracts a vector element with the given id
    bool idExists(int id);
    void print(); //display the content of the vector
    void addGoods(Produkt *t); //adds an element of item to the warehouse
    void removeGoods(int id); //removes the Item Item from the warehouse
    int getSize() {return t_vec.size();} //returns the size of a vector
    bool isEmpty() {return t_vec.empty();} //checks if the vector is empty
    std::string getName() {return nazwaMagazynu;}
    Produkt* getEle(int id);

    void displayInfo() {
        std::cout  <<warehouseName<< " || number of types of goods in stock: " << t_vec.size() << std::endl;
    }
    void receiptInto(Jigger &p);

    Product* operator[](int el) { return t_vec[el]; }
};




#endif //WAREHOUSE_PROJECT_WAREHOUSE_H

#include "Product.h"
#include <iostream>
#include <vector>
#include "Goods.h"
#include "looseGoods.h"
#include "liquidGoods.h"


#ifndef WAREHOUSE_PROJECT_JIGGER_H
#define WAREHOUSE_PROJECT_JIGGER_H

class Jigger {
    std::vector<Product*> p_vec;
    std::vector<Product*>::iterator it;

    float capacity;
    static float aktualnyUdzwig;

public:
    explicit Jigger(float capacity): capacity{capacity} {}

    bool isEmpty() {return p_vec.empty();}
    int getIndexOfID(int id);
    Product* getEleWithID(int id);
    void addProduct(Produkt *p);
    void removeProduct(int index);
    void print();
    bool increaseCurrentCapacity(float weight);
    int getSize() {return p_vec.size();}
    int getCapacity() {return capacity;}
    float getCurrentCapacity() { return currentCapacity; }
    Product* operator[](int el) { return p_vec[el]; }
    bool idExists(int id);
    void getCurrentCapacity() {currentCapacity = 0;}

};

#endif //WAREHOUSE_PROJECT_JIGGER_H

// Created by Arkadiusz Drąg on 15/12/2020.
#include <iostream>
#include "Exceptions.h"

#ifndef WAREHOUSE_PROJECT_PRODUCT_H
#define WAREHOUSE_PROJECT_PRODUCT_H

//template<typename T>
class Product {
protected:
    int ID;
    static int idGenerator;
    void copyString(const char *src, char **dst);


public:
    Product(const Product &p) : ID(p.ID) {}
    Product();
    virtual ~Product() = 0;

    virtual Product &operator-=(int amount) = 0;
    virtual Product &operator+=(int amount) = 0;
    virtual Product &operator-=(float amount) = 0;
    virtual Product &operator+=(float amount) = 0;

    virtual int getID() = 0;// const {return ID;}
    virtual float pobierzIloscFloat() = 0;
    virtual int pobierzIloscInt() = 0;


    virtual void displayProduct() = 0;
    virtual void displayAmount() = 0;
    virtual Product* divide (int amount) = 0;
    virtual Product* divide(float amount) = 0;

    virtual void scal(Product *p) = 0;




};


#endif //WAREHOUSE_PROJECT_PRODUCT_H

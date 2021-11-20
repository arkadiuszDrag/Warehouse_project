//
// Created by Arkadiusz Drąg on 23/11/2020.
//

#ifndef WAREHOUSE_PROJECT_INTERFACE_H
#define WAREHOUSE_PROJECT_INTERFACE_H
#include "Warehouse.h"
#include "Goods.h"
#include "looseGoods.h"
#include "liquidGoods.h"
#include "Product.h"
#include "Jigger.h"





class interface {
    void interfaceMain(Warehouse &m, std::vector<Warehouse*> &vec, Jigger *p, std::basic_istream<char> *input);
    void interfaceWarehouse(Warehouse &m,std::vector<Warehouse*> &vec, Jigger &p, std::basic_istream<char> *input);
    std::string readString( std::basic_istream<char> *input);
    void addTypeOfGoods(Warehouse &m, std::basic_istream<char> *input); //adds the type of item to the warehouse
    void removeTypeOfGoods(Warehouse &m, std::basic_istream<char> *input); //removes the type of item to the warehouse
    void receiptOfGoodsFromWarehouse(Warehouse &m, std::basic_istream<char> *input); //removes a given quantity of a given item from the warehouse
    void receiptOfGoodsIntoWarehouse(Warehouse &m, std::basic_istream<char> *input); //adds a given quantity of a given item to the warehouse
    void display(Warehouse &m); //displays the contents of the item in stock
    void createWarehouse(std::vector<Warehouse*> &vec, std::basic_istream<char> *input); //creates a warehouse
    void entranceWarehouse(Warehouse *m, std::vector<Warehouse*> &vec, Jigger *p, std::basic_istream<char> *input); //entry to the warehouse on which the indicator is set
    void pickUpFromJigger(Warehouse &m, Jigger &p); //transfers all goods from the jigger to the warehouse
    void TransferToJigger(Warehouse &m, Jigger &p, std::basic_istream<char> *input); //transfers the goods from the warehouse to the jigger
    void displayJigger(Jigger &p); //displays the goods in the jigger
    void ViewWarehouseList(std::vector<Warehouse*> &vec); // displays werehouse list
    template<typename T> T readNumber(std::basic_istream<char> *input);

public:
    interfejs() {}
    void interfaceStart(std::basic_istream<char> *input); //runs the entire interface

};


#endif //WAREHOUSE_PROJECT_INTERFACE_H

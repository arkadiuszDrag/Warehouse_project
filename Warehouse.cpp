//
// Created by Arkadiusz Drąg on 19/11/2020.
//
#include "Warehouse.h"
#include "Exceptions.h"

Warehouse::Warehouse(const std::string &name): warehouseName{name} {}

void Warehouse::addGoods(Goods* t) {
    t_vec.insert(t_vec.begin(), t);
}

void Warehouse::print() {
    for (int i = 0; i < t_vec.size(); i++) {
        t_vec[i]->displayGoods();
    }
}

void Warehouse::removeGoods(int id) {
    int index;
    try {
        index = getIndexOfID(id); //we take the index of the element with the given id
    }
    catch(IDError &ex) {
        std::cerr << "ID Error: " + ex.message  << std::endl;
    }
    t_vec.erase(t_vec.begin() + index); //we delete the element with the index found
}

int Warehouse::getIndexOfID(int id) {
    for ( int i = 0; i < t_vec.size(); i++ ) {
        if (id == t_vec[i]->getID())
            return i; //if the element hit the given element id, I return the index of this element
    }
    throw IDError();
}

template<typename T> void Warehouse::handOver(int id, T amount, Jigger &p) {
    int index;
    try {
        index = getIndexOfID(id);
    }
    catch(IDError &ex) {
        std::cerr << "ID Error: " + ex.message  << std::endl;
    }

    p.addProduct(t_vec[index]->divide(amount));
    *t_vec[index] -= amount;

}

template void Warehouse::handOver<int>(int id, int amount, Jigger &p);
template void Warehouse::handOver<float>(int id, float amount, Jigger &p);



Product* Warehouse::getEle(int id) {
    int index;
    try {
        index = getIndexOfID(id);
    }
    catch(IDError &ex) {
        std::cerr << "ID Error: " + ex.message  << std::endl;
    }
    return t_vec[index];
}

bool Warehouse::idExists(int id) {
    for(int i = 0; i < t_vec.size(); i++) {
        if (id == t_vec[i]->getID()) {
            return true;
        }
    }
    throw IDError();
}

void Warehouse::receiptInto(Jigger &p) {
    for(int i = 0; i < p.getSize(); i++) {
            if (idExists(p[i]->getID())) {
                try {
                    t_vec[getIndexOfID(p[i]->getID())]->scal(p[i]);
                }
                catch (IDError &ex) {
                    std::cerr << "ID Error: " + ex.message << std::endl;
                }

        } else {
            dodajTowar(p[i]);
            try {
                t_vec[getIndexOfID(p[i]->getID())]->scal(p[i]);
            }
            catch(IDError &ex) {
                std::cerr << "ID Error: " + ex.message  << std::endl;
            }
        }
        p.removeProduct(i);
    }
}

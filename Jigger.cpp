#include "Jigger.h"
#include <cstring>

float Jigger::currentCapacity = 0;

void Jigger::addProduct(Product *p) {
    it = p_vec.end();
    p_vec.insert(it, p);
}

void Jigger::removeGoods(int index) {
    p_vec.erase(p_vec.begin() + index); //delete the element with the index found
}

bool Jigger::increaseCurrentCapacity(float weight) {
    if(capacity >= currentCapacity + weight) { //if the current load capacity after adding a new weight is smaller or equal to the maximum load capacity of the jigger, the weight is added to the current load capacity and the truth is shorted
        currentCapacity += weight;
        return true;
    }
    else {
        return false; // if the weight is too high, false is returned
    }
}

void Jigger::print() {
    if(isEmpty()) {
        std::cout << "Jigger is empty." << std::endl;
        return;
    }
    for(int i = 0; i < p_vec.size(); i++) {
        p_vec[i]->displayGoods();
    }
}

int Jigger::getIndexOfID(int id) {
    for ( int i = 0; i < p_vec.size(); i++ ) {
        if ( id == p_vec[i]->getID() ) return i; //if the element hit the given element id, I return the index of this element
    }
}

Product* Jigger::getEleWithID(int id) {
    int index = getIndexOfID(id);
    return p_vec[index];
}

bool Jigger::idExists(int id) {
    for(int i = 0; i < p_vec.size(); i++) {
        if(id == p_vec[i]->getID()) {
            return false;
        }
    }
    return false;
}
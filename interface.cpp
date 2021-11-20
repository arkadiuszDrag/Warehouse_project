#include <regex>
#include "interface.h"
#include "Exceptions.h"


void interface::interfaceStart(std::basic_istream<char> *input) {

    std::vector<Warehouse*> m_vec;
    std::cout << "Enter the capacity in kg: ";
    float capacity = readNumber<float>(input);
    Jigger* p = new Jigger(capacity); //creates a jigger the specified load capacity
    Warehouse* m = nullptr;
    interfaceMain(*m, m_vec, p, input);
}


void interface::interfaceMain(Warehouse &m, std::vector<Warehouse*> &vec, Jigger *p, std::basic_istream<char> *input) {

    int choice;

    do {
        std::cout <<   "______________________________________\n"
                       "|---------====== MENU ======---------|\n"
                       "|                                    |\n"
                       "|0: Exit from the system             |\n"
                       "|1: Create warehouse                 |\n"
                       "|2: Entrance to the warehouse        |\n"
                       "|3: View warehouse list              |\n"
                       "|                                    |\n"
                       "--------------------------------------\n"
                       " Choose option: ";

        try {
            choice = readNumber<int>(input);
        }
        catch(ChooseError &ex) {
            std::cerr << "Choose Error: " + ex.message  << std::endl;
            exit(0); //exit it is used due to the fact that we run the program from the input file and cannot exit the program immediately when an error occurs
        }

        switch (choice) {
            case 0:
                break;
            case 1:
                createWarehouse(vec, input );
                break;
            case 2:
                entranceWarehouse(&m, vec, p, input);
                break;
            case 3:
                ViewWarehouseList(vec);
                break;
            default:
                std::cout << "Incorrect choice" << std::endl;
        }

    } while (choice != 0);
}

void interface::interfaceStart(Warehouse &m, std::vector<Warehouse*> &vec, Jigger &p, std::basic_istream<char> *input) {

    int choice;
    do {
        std::cout <<   "________________________________________\n"
                       "|-----====== WAREHOUSE MENU ======-----|\n"
                       "|"; std::cout <<"WAREHOUSE NAME: " << m.getName() << std::endl;
        std::cout <<   "|                                      |\n"
                       "|0: Go back to main menu               |\n"
                       "|1: Add item type to warehouse         |\n" // adds a book to the selected shelf
                       "|2: Remove an item type from warehouse |\n" // removes the book from the selected shelf
                       "|3: Receipt of goods into the warehouse|\n" // moves a book between two shelves
                       "|4: Receipt of goods from the warehouse|\n" // shows the contents of the selected shelf
                       "|5: Display the contents of the goods  |\n"
                       "|6: Pick up the goods from the jigger  |\n"
                       "|7: Transfer the goods to the jigger   |\n"
                       "|8: View the contents of jigger        |\n"
                       "|                                      |\n"
                       "----------------------------------------\n"
                       " Choose option: ";

        try {
            choice = readNumber<int>(input);
        }
        catch(ChooseError &ex) {
            std::cerr << "Choose Error: " + ex.message  << std::endl;
            exit(0); //exit it is used due to the fact that we run the program from the input file and cannot exit the program immediately when an error occurs
        }

        switch (choice) {
            case 0:
                interfaceMain(m, vec, &p, input);
                break;
            case 1:
                addTypeOfGoods(m, input);
                break;
            case 2:
                removeTypeOfGoods(m, input);
                break;
            case 3:
                receiptOfGoodsIntoWarehouse(m, input);
                break;
            case 4:
                receiptOfGoodsFromWarehouse(m, input);
                break;
            case 5:
                display(m);
                break;
            case 6:
                pickUpFromJigger(m, p );
                break;
            case 7:
                TransferToJigger(m, p, input);
                break;
            case 8:
                displayJigger(p);
                break;
            default:
                std::cout << "Incorrect choice" << std::endl;
        }
    } while (choice != 0);
}


void interface::displayJigger(Jigger &p) {
    p.print();
}


void interface::pickUpFromJigger(Warehouse &m, Jigger &p) {

    if(p.isEmpty()) {
        std::cout << "--------------------------------------\n"
                     "Jigger is empty \n";
        return;
    }

    m.receiptInto(p);
    p.cleanCurrentCapacity();
    std::cout << "The products are collected from the jigger\n";
}



void interface::TransferToJigger(Warehouse &m, Jigger &p, std::basic_istream<char> *input) {


    if(m.isEmpty()) { // if the warehouse is empty, we inform the user that it is not possible to pick up goods from an empty warehouse that does not support any type yet
        std::cout << "--------------------------------------\n"
                     "The goods cannot be loaded onto the jigger because the warehouse does not yet handle any type of goods.\n";
        return;
    }

    std::cout << "--------------------------------------\n"
                 "Enter the id of the goods to be loaded: ";
    int id;
    try {
        id = readNumber<int>(input);
        m.idExists(id);
    }
    catch(ChooseError &ex) {
        std::cerr << "Choose Error: "<< ex.message << std::endl;
        exit(0);
    }

    float weight;

    if ( dynamic_cast<Goods*>(m.getEle(id)) ) { //checking the type of element in the warehouse with the given id
        if(m.getEle(id)->getAmountInt() == 0) {
            std::cout << "--------------------------------------\n"
                         "The goods cannot be loaded. The amount of the given curd in the warehouse is 0.\n";
            return;
        }
        std::cout << "--------------------------------------\n"
                     "Weigh a single item and enter its weight in kilograms: ";
        int numOfItems;
        try {
            weight = readNumber<float>(input);

            std::cout << "--------------------------------------\n"
                         "Enter the number of items to be loaded: ";
            numOfItems = readNumber<int>(input);


            while (numOfItems > m.getEle(id)->getAmountInt()) { // if the number of goods to be removed is greater than the one in stock, we ask the user to enter it again
                std::cout << "--------------------------------------\n"
                             "There are not enough items of the given goods in stock.\n"
                             "The available quantity is: ";
                m.getEle(id)->displayNumItems();
                std::cout << " Enter the number of pieces again: ";
                numOfItems = readNumber<int>(input);
            }
        }
        catch (ChooseError &ex) {
            std::cerr << "Choose Error: "<< ex.message << std::endl;
            exit(0);
        }


        weight *= numOfItems; // the total weight is calculated


        if (!p.increaseCurrentCapacity(weight)) {
            std::cout << "--------------------------------------\n"
                         "The goods weigh too much to be loaded on the jigger.\n"
                         "Current jigger capacity: ";
            std::cout << p.getCurrentCapacity() << std::endl;
            std::cout << "Max current capacity: ";
            std::cout << p.getCapacity() << std::endl;
            return;
        }


        if(p.idExists(id)) {
            *p.getEleWithID(id) += numOfItems;
            *m.getEle(id) -= numOfItems;
        } else {
            m.handOver(id, numOfItems, p);
        }
    }
    else if ( dynamic_cast<looseGoods*>(m.getEle(id)) ) {

        if(m.getEle(id)->getAmountFloat() == 0) {
            std::cout << "--------------------------------------\n"
                         "The goods cannot be loaded. The amount of the given curd in the warehouse is 0.";
            return;
        }

        std::cout << "--------------------------------------\n"
                     "Enter how many kilograms of goods you want to load: ";
        try {
            weight = readNumber<float>(input);
        }
        catch (ChooseError &ex) {
            std::cerr << "Choose Error: "<< ex.message << std::endl;
            exit(0);
        }

        if (!p.increaseCurrentCapacity(weight)) {
            std::cout << "The goods weigh too much to be loaded on the pallet jack.\n";
            return;
        }
        if(p.idExists(id)) {
            *p.getEleWithID(id) += weight;
            *m[id] -= weight;
        } else {
            m.handOver(id, weight, p);
        }
    }
    else {

        if(m.getEle(id)->getAmountFloat() == 0) {
            std::cout << "--------------------------------------\n"
                         "The goods cannot be loaded. The amount of the given curd in the warehouse is 0.";
            return;
        }
        std::cout << "--------------------------------------\n"
                     "Enter how many liters of goods you want to load: ";
        try {
            weight = readNumber<float>(input);
        }
        catch (ChooseError &ex) {
            std::cerr << "Choose Error: "<< ex.message << std::endl;
        }

        if (!p.increaseCurrentCapacity(waga)) {
            std::cout << "The goods weigh too much to be loaded on the jigger.\n";
            return;
        }
        if(p.idExists(id)) {
            *p.getEleWithID(id) += weight;
            *m[id] -= weight;
        } else {
            m.handOver(id, weight, p);
        }
    }
}


void interface::addTypeOfGoods(Warehouse &m, std::basic_istream<char> *input) {

    std::cout << "--------------------------------------\n"
                     "Enter the name of the goods: ";

    std::string name = readString(input);

    std::cout << "--------------------------------------\n"
                 "Choose the form of the product: \n\n"
                 "0. Return to the menu\n"
                 "1. By the piece\n"
                 "2. In liquid form\n"
                 "3. In loose form\n"
                 "--------------------------------------\n"
                 "Choose option: ";
    int c;
    try {
        c = readNumber<int>(input);
    }
    catch(ChooseError &ex) {
        std::cerr << "Choose Error: " + ex.message  << std::endl;
        exit(0);
    }


    switch (c) {
        case 1: {
            Product* t = new Goods(name);
            m.addGoods(t);
            break;
        }
        case 2: {
            Product* t = new liquidGoods(nazwa);
            m.addGoods(t);
            break;
        }
        case 3: {
            Product* t = new looseGoods(nazwa);
            m.addGoods(t);
            break;
        }
        default:
            std::cout << "Incorrect choose" << std::endl;
    }
}


void interface::removeTypeOfGoods(Warehouse &m, std::basic_istream<char> *input) {
    if(m.isEmpty()) { // if the warehouse is empty, it is not possible to delete any kind of goods
        std::cout << "You cannot delete an item type because the warehouse does not yet support any item type." << std::endl;
        return;
    }

    std::cout << "--------------------------------------\n"
                 "Enter the id of the item to be removed: ";

    int id;
    try {
        id = readNumber<int>(input);
        m.getIndexOfID(id);
    }
    catch(ChooseError &ex) {
        std::cerr << "Choose Error: " + ex.message  << std::endl;
        exit(0);
    }

    m.removeGoods(id);
}


void interface::receiptOfGoodsFromWarehouse(Warehouse &m, std::basic_istream<char> *input) {
    if(m.isEmpty()) { // if the warehouse is empty, we inform the user that it is not possible to pick up goods from an empty warehouse that does not support any type yet
        std::cout << "The item cannot be picked up because the warehouse does not yet handle any type of item." << std::endl;
        return;
    }
    std::cout << "--------------------------------------\n"
                 "Enter the ID of the goods to be picked up: ";

    int id;
    try {
        id = readNumber<int>(input);
        m.getIndexOfID(id);
    }
    catch(ChooseError &ex) {
        std::cerr << "Choose Error: " + ex.message  << std::endl;
        exit(0);
    }

    if ( dynamic_cast<Goods*>(m.getEle(id)) ) {
        std::cout << "--------------------------------------\n"
                     "How many pieces of goods do you want to pick up: ";
        int amount;
        try {
            amount = readNumber<int>(input);
        }
        catch(ChooseError &ex) {
            std::cerr << "Choose Error: " + ex.message  << std::endl;
            exit(0);
        }


            while (amount > m.getEle(id)->getAmountInt()) { // if the given number of goods to be removed is greater than the one in stock, we ask the user to enter it again
                std::cout << "--------------------------------------\n"
                             "There are not enough items of the given goods in stock.\n"
                             "The available quantity is: ";
                m.getEle(id)->displayNumItems();
                std::cout << "Enter the number of pieces again: ";
                amount = readNumber<int>(input);
            }

            *m.getEle(id) -= amount;
        }

    else {
        std::cout << "--------------------------------------\n"
                     "How much goods do you want to pick up?: ";
        float amount;
        try {
            amount = readNumber<float>(input);
        }
        catch(ChooseError &ex) {
            std::cerr << "Choose Error: " + ex.message  << std::endl;
            exit(0);
        }

            while (amount > m.getEle(id)->getAmountFloat()) { // if the given number of goods to be removed is greater than the one in stock, we ask the user to enter it again
                std::cout << "--------------------------------------\n"
                             "There are not enough items of the given goods in stock.\n"
                             "The available quantity is: ";
                m[id]->displayNumItems();
                std::cout << "Enter the number of pieces again: ";
                ilosc = readNumber<float>(input);
            }
            *m.getEle(id) -= amount;

    }
}



void interface::receiptOfGoodsIntoWarehouse(Warehouse &m, std::basic_istream<char> *input) {
    if(m.isEmpty()) { // if the warehouse is empty, we inform the user that it is not possible to accept the goods into an empty warehouse that does not support any type yet
        std::cout << "The goods cannot be accepted because the warehouse does not yet handle any type of goods." << std::endl;
        return;
    }
    std::cout << "--------------------------------------\n"
                 "Enter the id of the goods to be accepted: ";

    int id;
    try {
        id = readNumber<int>(input);
        m.getIndexOfID(id);
    }
    catch(ChooseError &ex) {
        std::cerr << "Choose Error: " + ex.message  << std::endl;
        exit(0);
    }

    std::cout << "--------------------------------------\n"
                 "Enter the quantity of goods to be accepted: ";

    if ( dynamic_cast<Towar*>(m.getEle(id)) ) {
        int amount;
        try {
            amount = readNumber<int>(input);
                *m.getEle(id) += amount;
        }
        catch(ChooseError &ex) {
            std::cerr << "Choose Error: " + ex.message  << std::endl;
            exit(0);
        }
    }
    else {
        float amount;
        try {
            amount = readNumber<float>(input);
            *m.getEle(id) += amount;
        }
        catch(ChooseError &ex) {
            std::cerr << "Choose Error: " + ex.message  << std::endl;
            exit(0);
        }
    }
}


void interface::display(Warehouse &m) {
    if(m.isEmpty()) { // if the magazine is empty, we inform the user about it
        std::cout << "The warehouse is empty." << std::endl;
        return;
    }
    std::cout << "--------------------------------------\n"
                 "Magazine content: \n";
    m.print();
}



template<typename T>
T interface::readNumber(std::basic_istream<char> *input) {
    std::string line;
    std::getline(*input, line);

    if(line == "END") {
        exit(0);
    }

    if( !std::regex_match( line, std::regex( ( "((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?" ) ) ))
        throw NotDigitError();

    std::cout << line << std::endl;

    if(line.find('.') != std::string::npos) {
        return atof(line.c_str()); // first we copy our string downloaded from the user, then we convert the copy to intiger and finally we return
    }
    else {
        return atoi(line.c_str());
    }
}

template int interface::readNumber<int>(std::basic_istream<char> *input);
template float interface::readNumber<float>(std::basic_istream<char> *input);


std::string interfejs::readString( std::basic_istream<char> *input) {
    std::string line;
    std::getline(*input, line);
    if(line == "END") {
        exit(0);
    }
    std::cout << line << std::endl;
    return line;
}



void interface::createWarehouse(std::vector<Warehouse*> &vec, std::basic_istream<char> *input) {
    std::cout << "--------------------------------------\n"
                 "Enter the name of the warehouse: \n";
    std::string name = readString(input);
    Warehouse *m = new Warehouse(name);
    vec.insert(vec.begin(), m);
}

void interface::entranceWarehouse(Warehouse *m, std::vector<Warehouse*> &vec, Jigger *p, std::basic_istream<char> *input) {

    if(vec.empty()) {
        std::cout << "--------------------------------------\n"
                     "No warehouse has been created yet.\n";
    }
    ViewWarehouseList(vec);
    std::cout << "--------------------------------------\n"
                 "Enter the warehouse number: ";
    int nr;
    try {
        nr = readNumber<int>(input);
    }
    catch(ChooseError &ex) {
        std::cerr << "Choose Error: " + ex.message  << std::endl;
        exit(0);
    }

    if (nr > vec.size()) {
        std::cout << "--------------------------------------\n"
                     "Warehouse number not supported\n";
        return;
    }

    nr = vec.size() - nr;

    m = vec[nr];

    interfaceWarehouse(*m, vec, *p, input);
}

void interface::ViewWarehouseList(std::vector<Warehouse*> &vec) {
    for(int i = vec.size()-1; i >= 0; i--) {
        std::cout << vec.size()-i << ". " ; vec[i]->displayInfo();
    }
}



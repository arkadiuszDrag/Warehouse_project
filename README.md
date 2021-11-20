# Warehouse project

The project includes seven classes.

The first three classes are Towar, TowarSypki and TowarCiekly, which have the quantity and id inherited from the next class.
The fourth class is a product that is the abstract and base class for the first three classes. It has a product id so that the goods classes cannot have the same id.
The fifth class is Warehouse, you can create any number of them. It stores pointers for products in the vector, thanks to which the same id cannot be duplicated between warehouses, and has the name of the warehouse.
The sixth class is a pallet truck that has its own lifting capacity. You can keep products from different warehouses there.
The third class is the interface that allows you to execute methods operating directly on our storage created in the main.cpp file.

Each of these classes also has the necessary methods to implement the project.

After creating the interface class object, we run and calling functions from the interface class, we run our program.

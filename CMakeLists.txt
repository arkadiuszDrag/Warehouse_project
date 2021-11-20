cmake_minimum_required(VERSION 3.17)
project(Werhouse_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Werhouse_project main.cpp Goods.cpp Goods.h Warehouse.h Warehouse.cpp interface.h interface.cpp looseGoods.h Product.h Product.cpp looseGoods.cpp liquidGoods.h liquidGoods.cpp Jigger.h Jigger.cpp Exceptions.h)

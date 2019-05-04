//
// Created by kdabb on 4/24/2019.
//

#include "Restaurant.h"
#include <ctime>


Restaurant::Restaurant()
{
    resNumber = 0;
    tableNumber = 0;
    patronID = -1;
    patronMealNumber = 0;
    mealTime = {};
}

Restaurant::Restaurant(short _resNumber, short _tableNumber)
{
    resNumber = _resNumber;
    tableNumber = _tableNumber;

    patronID = -1;
    patronMealNumber = 0;

    mealTime = {};

}

void Restaurant::setPatronID(int _patronID)
{
    patronID = _patronID;
}

void Restaurant::setPatronName(std::string &_patronName)
{
    patronName = _patronName;
}

void Restaurant::setPatronMealNumber(short int _patronMealNumber)
{
    patronMealNumber = _patronMealNumber;
}

void Restaurant::setResNumber(short int _resNumber)
{
    resNumber = _resNumber;
}

void Restaurant::setTableNumber(short int _tableNumber)
{
    tableNumber = _tableNumber;
}



short int Restaurant::getResNumber() const
{
    return resNumber;
}

int Restaurant::getPatronID() const
{
    return patronID;
}
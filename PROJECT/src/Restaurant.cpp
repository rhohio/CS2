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

short int Restaurant::getResNumber() const
{
    return resNumber;
}

void Restaurant::setPatronID(int _patronID)
{
    patronID = _patronID;
}

int Restaurant::getPatronID() const
{
    return patronID;
}

void Restaurant::setPatronName(std::string &_patronName)
{
    patronName = _patronName;
}

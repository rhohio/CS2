//
// Created by kdabb on 4/24/2019.
//

#include "Restaurant.h"
#include <ctime>


Restaurant::Restaurant()
{
    resNumber = -1;
    tableNumber = -1;
    patronID = -1;
    patronMealNumber = -1;
    patronName = "";

    time_t now = time(nullptr);
    char* timeOf = ctime(&now);
    timeOf[20] = '\0';

    mealTime = {};

    for(int i = 0; i < 20; i ++)
    {
        mealTime[i] = timeOf[i];
    }
    mealTime[20] = '\0';
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
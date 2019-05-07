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

    mealTime[20] = '\0';

    for(int i = 0; i < 20; i ++)
    {
        mealTime[i] = timeOf[i];
    }
}

Restaurant::Restaurant(const Restaurant &input)
{
    resNumber = input.resNumber;
    tableNumber = input.tableNumber;
    patronID = input.patronID;
    patronMealNumber = input.patronMealNumber;
    patronName = input.patronName;

    time_t now = time(nullptr);
    char* timeOf = ctime(&now);
    timeOf[20] = '\0';

    mealTime[20] = '\0';

    for(int i = 0; i < 20; i ++)
    {
        mealTime[i] = timeOf[i];
    }
}

void Restaurant::setPatronName(std::string &_patronName)
{
    patronName = _patronName;
}

void Restaurant::setPatronMealNumber(short int _patronMealNumber)
{
    patronMealNumber = _patronMealNumber;
}

void Restaurant::setPatronID(int _patronID)
{
    patronID = _patronID;
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

std::string Restaurant::getPatronName() const
{
    return patronName;
}
char* Restaurant::getMealTime()
{
    return mealTime;
}
short int Restaurant::getPatronMealNumber() const
{
    return patronMealNumber;
}
//
// Created by kdabb on 4/24/2019.
//

#include "Restaurant.h"


Restaurant::Restaurant()
{
    resNumber = 0;
    tableNumber = 0;
    patronID = 00000;
    patronMealNumber = 0;

    mealTime = new char[20];

    for(int i = 0; i < 19; ++i)
    {
        mealTime[i] = '0';
    }
    mealTime[20] = '\0';
}

Restaurant::~Restaurant()
{
    delete [] mealTime;
}

void Restaurant::setResNumber(short int _resNumber)
{
    resNumber = _resNumber;
}
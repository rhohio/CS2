//
// Created by kdabb on 4/24/2019.
//

#include "Meals.h"
#include <string>

Meals::Meals()
{
    patronMealName = "";
    calories = -1;
    protein = -1;
    vitamins = -1;
}

Meals::Meals(const std::string &_patronMealName, const int _calories, const short _protein, const short _vitamins)
{
    patronMealName = _patronMealName;
    calories = _calories;
    protein = _protein;
    vitamins = _vitamins;
}

std::string Meals::getPatronMealName()
{
    return patronMealName;
}

int Meals::getCalories()
{
    return calories;
}

short Meals::getProtein()
{
    return protein;
}
short Meals::getVitamins()
{
    return vitamins;
}
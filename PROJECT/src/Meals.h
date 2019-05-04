//
// Created by kdabb on 4/24/2019.
//

#ifndef MY_PROJECT_MEALS_H
#define MY_PROJECT_MEALS_H

#include<string>

class Meals
{
    private:
        std::string patronMealName;
        int calories;
        short protein;
        short vitamins;
    public:

        Meals();
        Meals(const std::string &, int, short, short);

        std::string getPatronMealName();
        int getCalories();
        short getProtein();
        short getVitamins();
};


#endif //MY_PROJECT_MEALS_H

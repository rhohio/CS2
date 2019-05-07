//
// Created by kdabb on 4/24/2019.
//

#ifndef MY_PROJECT_RESTAURANT_H
#define MY_PROJECT_RESTAURANT_H

#include<string>

class Restaurant
{
    private:
        short int resNumber;        //one of the available HFRestaurants
        short int tableNumber;      //next available table number
        int patronID;               //unique ID for the patron
        std::string patronName;     //patron name
        char mealTime[21];             //time of meal
        short int patronMealNumber; //meal number

    public:

        //constructors
        Restaurant();
        //~Restaurant();
        Restaurant(const Restaurant&);

        //setters and getters
        void setPatronID(int);
        void setPatronName(std::string&);
        void setPatronMealNumber(short int);
        void setResNumber(short int);
        void setTableNumber(short int);

        short int getResNumber() const;
        int getPatronID() const;
        std::string getPatronName() const;
        char* getMealTime();
        short int getPatronMealNumber() const;

};


#endif //MY_PROJECT_RESTAURANT_H

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
        char *mealTime;             //time of meal
        short int patronMealNumber; //meal number

    public:

        //constructors
        Restaurant();
        ~Restaurant();
        Restaurant(short, short);
        //setters and getters
        short int getResNumber() const;
        void setPatronID(int);
        int getPatronID() const;
        void setPatronName(std::string&);

};


#endif //MY_PROJECT_RESTAURANT_H

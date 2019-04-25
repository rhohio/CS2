/*
   COPYRIGHT (C) 2018 Student Name (kad145) All rights reserved.
   CS Project
   Author.  Kyle Dabbieri
            kad145@zips.uakron.edu
   Version. 1.01 04.23.2019
   Purpose: Restaurant management Project
*/

#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include "Restaurant.h"
#include "Meals.h"



/*
 *      <globalConstants>
 */

//Number of Restaurants
const int NUMHFCS = 8;

//Number of tables in each restaurant
const int HFCSIZES[NUMHFCS]
    = {19, 15, 24, 33, 61, 17, 55, 37};

//Names of restaurants
const std::string RESTAURANT[NUMHFCS] = {"The Salubrious Bistro", "What the Kale?",
                                         "Lettuce Enjoy", "Vegan Nights",
                                         "Pasta is a Planet", "The Meatless Miracle",
                                         "The Pesky Pescatarian", "The Fine Fettle"};
//Number of meals
const int NUMMEALS = 10;

// Names of meals
const std::string MEALNAMES[NUMMEALS] = {"Mexican Quinoa Salad", " Kale and Eggs",
                                         "Chickpea Vegetable Curry", "Vegetable Pot Pie",
                                         " Eggplant Carbonara", "Butternut Squash Black Bean Chili",
                                         " Seafood Medley", "Sweet Potato Black Bean Enchiladas",
                                         "Pesto Pasta Salad", "Tomato Soup and Salad Supremo"};

// calories (int)
const int CALORIES[NUMMEALS]
    = {202, 119, 304, 398, 215, 157, 222, 341, 143, 233};

// grams of protein (short)
const short int PROTEIN[NUMMEALS]
    = {1, 12, 16, 22, 17, 7, 11, 20, 27, 9};

// milligrams of vitamins (short)
const short int VITAMINS[NUMMEALS]
    = {12,  10, 23, 31, 20, 17, 24, 19, 22, 13};

/*
 *      </globalConstants>
 */


int mainMenu();
void assessMenuAnswer(int, bool&, Restaurant**[]);
void requestTable(Restaurant**[]);
int assignTableNumber(Restaurant*[]);
int generatePatronID(Restaurant**[]);

int main()
{

    Restaurant **restaurants[NUMHFCS];
    for(int i = 0; i < NUMHFCS; ++i)
    {
        for(int j = 0; j < HFCSIZES[i]; ++j)
        {
            restaurants[i][j] = new Restaurant(i, j);
        }
    }

    bool isMainRepeated = true;

    do
    {
        int menuAnswer = mainMenu();
        assessMenuAnswer(menuAnswer, isMainRepeated, restaurants);
    }while(isMainRepeated);

}


int mainMenu()
{
    std::cout << " " << std::setfill('_') << std::setw(50) << " " << std::endl
              << "|" << std::setfill('-') << std::setw(50) << "|" << std::endl
              << "|" << std::setfill(' ') << std::setw(17) << " " << "Kyle Dabbieri's" << std::setw(18) << "|" << std::endl
              << "|" << std::setw(8) << " " << "Healthy Food Choices (HFC) System" << std::setw(9) << "|" << std::endl
              << "|" << std::setfill('_') << std::setw(50) << "|" << std::endl
              << "|" << std::setfill(' ') << std::setw(20) << " " << "MAIN MENU" << std::setw(21) << "|" << std::endl
              << "|" << std::setw(17) << " " << "1) Request Table" << std::setw(17) << "|" << std::endl
              << "|" << std::setw(17) << " " << "2) Free up a Table" << std::setw(15) << "|" << std::endl
              << "|" << std::setw(17) << " " << "3) Find a Patron" << std::setw(17) << "|" << std::endl
              << "|" << std::setw(17) << " " << "4) Display Restaurant Usage" << std::setw(6) << "|" << std::endl
              << "|" << std::setw(17) << " " << "5) Print Transaction Log" << std::setw(9) << "|" << std::endl
              << "|" << std::setw(17) << " " << "6) Quit" << std::setw(26) << "|" << std::endl
              << "|" << std::setfill('_') << std::setw(50) << "|" << std::endl
              << "Please enter a choice from the menu [6 to quit]: ";
    int menuAnswer;
    bool invalidMenuAnswer = false;
    do
    {
        std::cin >> menuAnswer;
        if(menuAnswer > 6 || menuAnswer < 1)
        {
            std::cout << "Please enter a valid number 1-6: ";
            invalidMenuAnswer = true;
        }
    }while(invalidMenuAnswer);
    return menuAnswer;
}

void assessMenuAnswer(int menuAnswer, bool &mainLoopFlag, Restaurant **restaurants[])
{
    switch(menuAnswer)
    {
        case 1:
            requestTable(restaurants);
            break;
        case 2:
            //freeTable();
            break;
        case 3:
            //findPatron();
            break;
        case 4:
            //displayUsage();
            break;
        case 5:
            //displayLog();
            break;
        case 6:
            mainLoopFlag = false;
            break;
        default:
            mainLoopFlag = false;
            break;
    }
    return;
}

void requestTable(Restaurant **restaurant[])
{
    std::cout << "Please enter the restaurant choice from 1 through 8 : ";

    int resAnswer;
    bool invalidRestAnswer = false;
    do
    {
        std::cin >> resAnswer;
        if(resAnswer > NUMHFCS || resAnswer < 1)
        {
            std::cout << "Please enter a valid selection [1-" << NUMHFCS << "]: ";
            invalidRestAnswer = true;
        }
    }while(invalidRestAnswer);

    int tableNumber = assignTableNumber(restaurant[resAnswer]);

    if(tableNumber == -1)
    {
        //TODO QUEUE SHIT
    }
    else
    {
        restaurant[resAnswer][tableNumber]->setPatronID(generatePatronID(restaurant));
        std::cout << "Your table number is " << tableNumber << " and your ID number is " //TODO SETFILL FOR ID
                  <<  restaurant[resAnswer][tableNumber]->getPatronID() << std::endl
                  << "Please enter the name of the Patron: ";

        bool isPatronNameInvalid = false;
        std::string patronName;
        do
        {
            std::cin >> patronName;
            if(patronName.empty())
            {
                std::cout << "Please enter a valid name (Not empty): ";
                isPatronNameInvalid = true;
            }
        }while(isPatronNameInvalid);

        restaurant[resAnswer][tableNumber]->setPatronName(patronName);
        std::cout << "Please enter the meal number from the following choices: ";
        for(int i = 0; i < NUMMEALS; ++i)
        {
            std::cout << i + 1;
            ((i + 1) % 10) ? std::cout << ")   " : std::cout << ")  ";
            std::cout << MEALNAMES[i] << std::endl;
        }

        std::cout << "Meal: ";

        bool isMealNameInvalid = false;
        int mealName;

        do
        {
            std::cin >> mealName;
            if(mealName > NUMMEALS || mealName < 1)
            {
                std::cout << "Please enter a valid selection [1 through " << NUMMEALS << "]: ";
                isMealNameInvalid = true;
            }
        }while(isMealNameInvalid);

        std::cout << "Your choice was the " << MEALNAMES[mealName - 1] << std::endl;
    }

    std::cout << "You have chosen " << RESTAURANT[resAnswer - 1] << std::endl;
    //TODO PULL DATA FROM MAP... ALSO MAKE A MAP
}

int assignTableNumber(Restaurant *restaurant[])
{
    for(int i = 0; i < restaurant[0]->getResNumber(); i++)
    {
        if(restaurant[i]->getPatronID() != -1)
        {
            return i;
        }
    }
    return -1;
}

int generatePatronID(Restaurant **restaurants[])
{

    srand(time(nullptr));
    bool isUnique = true;
    int newID;

    do
    {
        newID = rand() % 100000;
        for(int i = 0; i < NUMHFCS; ++i)
        {
            for(int j = 0; j < HFCSIZES[restaurants[i][0]->getResNumber()]; ++j)
            {
                if(newID != restaurants[i][j]->getPatronID())
                {
                    return newID;
                }
                isUnique = false;
            }
        }
    }while(!isUnique);
    return newID;
}
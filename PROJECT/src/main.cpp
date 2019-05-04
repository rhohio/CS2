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
#include <utility>
#include <queue>
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
const std::string MEALNAMES[NUMMEALS] = {"Mexican Quinoa Salad", "Kale and Eggs",
                                         "Chickpea Vegetable Curry", "Vegetable Pot Pie",
                                         "Eggplant Carbonara", "Butternut Squash Black Bean Chili",
                                         "Seafood Medley", "Sweet Potato Black Bean Enchiladas",
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
void assessMenuAnswer(int, bool&, Restaurant**[], std::map<int, Meals>&, std::queue<Restaurant>&);
void requestTable(Restaurant**[], std::map<int, Meals>&, std::queue<Restaurant>&);
int assignTableNumber(Restaurant*[], short int);
int generatePatronID(Restaurant**[], short int);

int main()
{

    Restaurant **restaurants[NUMHFCS];
    for(int i = 0; i < NUMHFCS; ++i)
    {
        restaurants[i] = new Restaurant *[HFCSIZES[i]];
    }

    /* start of the pain
    for(int i = 0; i < NUMHFCS; ++i)
    {
        Restaurant *restPtr[i];
    }
    */

    std::map<int, Meals> mealMap;
    for(int i = 0; i < NUMMEALS; ++i)
    {
        mealMap.insert(std::make_pair<int, Meals>(int(i), Meals(Meals(MEALNAMES[i], CALORIES[i], PROTEIN[i], VITAMINS[i]))));
    }

    std::queue<Restaurant> waitingList;

    bool isMainRepeated = true;

    do
    {
        int menuAnswer = mainMenu();
        assessMenuAnswer(menuAnswer, isMainRepeated, restaurants, mealMap, waitingList);
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

void assessMenuAnswer(int menuAnswer, bool &mainLoopFlag, Restaurant **restaurants[], std::map<int, Meals> &mealMap, std::queue<Restaurant> &waitingList)
{
    switch(menuAnswer)
    {
        case 1:
            requestTable(restaurants, mealMap, waitingList);
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
}

void requestTable(Restaurant **restaurant[], std::map<int, Meals> &mealMap, std::queue<Restaurant> &waitingList)
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
    std::cout << "You have chosen " << RESTAURANT[resAnswer - 1] << std::endl;

    short int resNumber = resAnswer - 1;

    int tableNumber = assignTableNumber(restaurant[resNumber], resNumber);

    if(tableNumber == -1)
    {
        std::cout << "This restaurant is currently full. You will be placed into the wait list and given a table as soon as possible." << std::endl
                  << "Please enter your name: ";

        //create restaurant obj to hold data from patron until table is avail
        Restaurant patron;

        patron.setResNumber(resNumber);

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

        patron.setPatronID(generatePatronID(restaurant, resNumber));
        patron.setPatronName(patronName);

        std::cout << "Please enter the meal number from the following choices: " << std::endl;
        for(int i = 0; i < NUMMEALS; ++i)
        {
            std::cout << i + 1;
            ((i + 1) % 10) ? std::cout << ")   " : std::cout << ")  ";
            std::cout << MEALNAMES[i] << std::endl;
        }

        std::cout << "Meal: ";
        bool isMealNameInvalid = false;
        short int mealName;
        do
        {
            std::cin >> mealName;
            if(mealName > NUMMEALS || mealName < 1)
            {
                std::cout << "Please enter a valid selection [1 through " << NUMMEALS << "]: ";
                isMealNameInvalid = true;
            }
        }while(isMealNameInvalid);
        patron.setPatronMealNumber(mealName);
        std::cout << "Your choice was the " << mealMap[mealName].getPatronMealName() << std::endl
                  << mealMap[mealName].getCalories() << " calories, "
                  << mealMap[mealName].getProtein()  << " grams of protein, and "
                  << mealMap[mealName].getVitamins() << " milligrams of vitamins" << std::endl;
        std::cout << "Thank you for your patience, you've been added to the wait list." << std::endl;
        waitingList.push(patron);
    }
    else
    {
        restaurant[resNumber][tableNumber] = new Restaurant;
        restaurant[resNumber][tableNumber]->setResNumber(resNumber);
        restaurant[resNumber][tableNumber]->setTableNumber(tableNumber);
        restaurant[resNumber][tableNumber]->setPatronID(generatePatronID(restaurant, resNumber));

        std::cout << "Your table number is " << tableNumber + 1 << " and your ID number is " //TODO SETFILL FOR ID
                  <<  restaurant[resNumber][tableNumber]->getPatronID() << std::endl
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

        restaurant[resNumber][tableNumber]->setPatronName(patronName);

        std::cout << "Please enter the meal number from the following choices: " << std::endl;
        for(int i = 0; i < NUMMEALS; ++i)
        {
            std::cout << i + 1;
            ((i + 1) % 10) ? std::cout << ")   " : std::cout << ")  ";
            std::cout << MEALNAMES[i] << std::endl;
        }

        std::cout << "Meal: ";
        bool isMealNameInvalid = false;
        int mealNameAns;
        do
        {
            std::cin >> mealNameAns;
            if(mealNameAns > NUMMEALS || mealNameAns < 1)
            {
                std::cout << "Please enter a valid selection [1 through " << NUMMEALS << "]: ";
                isMealNameInvalid = true;
            }
        }while(isMealNameInvalid);
        short int mealName = mealNameAns - 1;

        restaurant[resNumber][tableNumber]->setPatronMealNumber(mealName);

        std::cout << "Your choice was the " << mealMap[mealName].getPatronMealName() << std::endl
                  << mealMap[mealName].getCalories() << " calories, "
                  << mealMap[mealName].getProtein()  << " grams of protein, and "
                  << mealMap[mealName].getVitamins() << " milligrams of vitamins" << std::endl;

        std::cout << "Hit enter for next selection" << std::endl;
        std::cin.ignore();
        std::cin.get();

        //TODO WRITE TO LOG FILE [Patron Name, Meal Time, Patron Meal Name, Calories, Protein, Vitamins] in separate function
    }
}

int assignTableNumber(Restaurant *restaurant[], short int resNumber)
{
    for(int i = 0; i < HFCSIZES[resNumber]; i++)
    {
        if(!(restaurant[i]))
        {
            return i;
        }
    }
    return -1;
}

int generatePatronID(Restaurant **restaurants[], short int resNumber)
{

    srand(time(nullptr));
    bool isUnique = true;
    int newID;

    do
    {
        newID = rand() % 100000;
        for(int i = 0; restaurants[i] != nullptr && i < NUMHFCS; ++i)
        {
            for (int j = 0; restaurants[i][j] != nullptr && j < HFCSIZES[i]; ++j)
            {
                if (newID == restaurants[i][j]->getPatronID())
                {
                    isUnique = false;
                }
            }
        }
    }while(!isUnique);
    return newID;
}
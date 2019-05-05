wwwwww/*
   COPYRIGHT (C) 2018 Student Name (kad145) All rights reserved.
   CS Project
   Author.  Kyle Dabbieri
            kad145@zips.uakron.edu
   Version. 1.01 04.23.2019
   Purpose: Restaurant management Project.
*/

#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include <utility>
#include <queue>
#include <fstream>
#include <stack>
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
void assessMenuAnswer(int, bool&, Restaurant **[], std::map<int, Meals>&, std::queue<Restaurant>&, std::fstream&);
void requestTable(Restaurant **[], std::map<int, Meals>&, std::queue<Restaurant>&, std::fstream&);
void freeTable(Restaurant **[], std::queue<Restaurant>&);
int assignTableNumber(Restaurant**[], short int);
int generatePatronID(Restaurant **[]);
void writeToLog(Restaurant &, std::fstream &, std::map<int, Meals>&);

int main()
{

    std::fstream log;
    log.open("log.txt", std::ios::in | std::ios::out | std::ios::app);

    if(!log.is_open())
    {
        std::cerr << "Log file failed to open/generate." << std::endl;
    }

    //makes an array, that points to NUMHFCS arrays, which are arrays of size HFCSIZE[i], that point to rest objs
    Restaurant **restPtr[NUMHFCS];
    for(int i = 0; i < NUMHFCS; ++i)
    {
        restPtr[i] = new Restaurant *[HFCSIZES[i]];
    }

    //TODO: Fix this shit

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
        assessMenuAnswer(menuAnswer, isMainRepeated, restPtr, mealMap, waitingList, log);
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

void assessMenuAnswer(int menuAnswer, bool &mainLoopFlag, Restaurant **restPtr[], std::map<int, Meals> &mealMap, std::queue<Restaurant> &waitingList, std::fstream &log)
{
    switch(menuAnswer)
    {
        case 1:
            requestTable(restPtr, mealMap, waitingList, log);
            break;
        case 2:
            freeTable(restPtr, waitingList);
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

void requestTable(Restaurant **restPtr[], std::map<int, Meals> &mealMap, std::queue<Restaurant> &waitingList, std::fstream &log)
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

    int tableNumber = assignTableNumber(restPtr, resAnswer);

    //restaurant is full
    if(tableNumber == -1)
    {
        std::cout << "This restaurant is currently full. You will be placed into the wait list and given a table as soon as possible." << std::endl
                  << "Please enter your name: ";

        //create restaurant obj to hold data from patron until table is avail
        Restaurant patron;

        patron.setResNumber(resAnswer);

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

        patron.setPatronID(generatePatronID(restPtr));
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

        restPtr[resAnswer][tableNumber] = new Restaurant;
        restPtr[resAnswer][tableNumber]->setResNumber(resAnswer);
        restPtr[resAnswer][tableNumber]->setTableNumber(tableNumber);
        restPtr[resAnswer][tableNumber]->setPatronID(generatePatronID(restPtr));
        std::cout << "Your table number is " << tableNumber + 1 << " and your ID number is " //TODO SETFILL FOR ID
                  <<  restPtr[resAnswer][tableNumber]->getPatronID() << std::endl
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

        restPtr[resAnswer][tableNumber]->setPatronName(patronName);
        std::cout << "Please enter the meal number from the following choices: " << std::endl;
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

        restPtr[resAnswer][tableNumber]->setPatronMealNumber(mealName);

        std::cout << "Your choice was the " << mealMap[mealName].getPatronMealName() << std::endl
                  << mealMap[mealName].getCalories() << " calories, "
                  << mealMap[mealName].getProtein()  << " grams of protein, and "
                  << mealMap[mealName].getVitamins() << " milligrams of vitamins" << std::endl;

        std::cout << "Hit enter for next selection" << std::endl;
        std::cin.ignore();
        std::cin.get();

        writeToLog(*restPtr[resAnswer][tableNumber], log, mealMap);

    }
}

void freeTable(Restaurant **restPtr[], std::queue<Restaurant> &waitingList)
{
    std::cout << "Please enter the restaurant choice, [1 - " << NUMHFCS << "]: ";

    bool isResAnsInvalid = false;
    short int resAnswer;

    do
    {
        std::cin >> resAnswer;

        if(resAnswer < 1 || resAnswer > NUMHFCS)
        {
            std::cout << "Please enter a valid number. [1 - " << NUMHFCS << "]: ";
            isResAnsInvalid = true;
        }
    }while(isResAnsInvalid);
    short int resNum = resAnswer - 1;

    std::cout << "You have chosen " << RESTAURANT[resNum] << std::endl;

    std::cout << "Please enter the table number of the patron: ";

    short int tableAns;
    bool isTableAnsInvalid = false;
    do
    {
        std::cin >> tableAns;

        if(!(restPtr[resNum][tableAns - 1]))
        {
            std::cout << "Could not find patron. Please re-enter the correct table number: ";
            isTableAnsInvalid = true;
        }
    }while(isTableAnsInvalid);

    short int tableNum = tableAns - 1;

    std::cout << restPtr[resNum][tableNum]->getPatronName() << " has enjoyed another meal. Goodbye!" << std::endl;

    delete restPtr[resNum][tableNum];

    //if queue is empty, nothing to do
    if(waitingList.empty())
    {
        return;
    }
    //if the front happens to be the right restaurant, replace old patron, and pop if off the queue
    else if(waitingList.front().getResNumber() == resNum)
    {
        restPtr[resNum][tableNum] = new Restaurant(waitingList.front());
        waitingList.pop();
    }
    //if front isnt the right restaurant
    else
    {
        std::stack<Restaurant> tempRestStack;
        //keep popping off the queue and saving the objs until you find the right restaurant
        while(waitingList.front().getResNumber() != resNum)
        {
            tempRestStack.push(Restaurant(waitingList.front()));
            waitingList.pop();
        }
        //once we've found the right rest, replace old patron, and pop it off
        restPtr[resNum][tableNum] = new Restaurant(waitingList.front());
        waitingList.pop();

        //now place all the obj's on the queue we popped off earlier
        while(!(tempRestStack.empty()))
        {
            waitingList.push(tempRestStack.top());
            tempRestStack.pop();
        }
    }
}

int assignTableNumber(Restaurant **restPtr[], short int restaurant)
{
    for(int i = 0; i < HFCSIZES[restaurant]; ++i)
    {
        if(!(restPtr[restaurant]))
        {
            return i;
        }
    }
    return -1;
}

//TODO: Fix this shit
int generatePatronID(Restaurant **restPtr[])
{

    srand(time(nullptr));
    bool isUnique = true;
    int newID;

    do
    {
        newID = rand() % 100000;
        for(int i = 0; i < NUMHFCS; ++i)
        {
            for (int j = 0; j < HFCSIZES[restPtr[i]->getResNumber()]; ++j)
            {
                if (newID == restPtr[j]->getPatronID())
                {
                    isUnique = false;
                }
            }
        }
    }while(!isUnique);
    return newID;
}

void writeToLog(Restaurant &input, std::fstream &log, std::map<int, Meals> &mealMap)
{
    //TODO WRITE TO LOG FILE [Patron Name, Meal Time, Patron Meal Name, Calories, Protein, Vitamins] in separate function

    log << input.getPatronName() << '\t' << input.getMealTime() << '\t' << MEALNAMES[input.getPatronMealNumber()] << '\t'
        << mealMap[input.getPatronMealNumber()].getCalories() << '\t' << mealMap[input.getPatronMealNumber()].getProtein()
        << '\t' << mealMap[input.getPatronMealNumber()].getVitamins() << std::endl;

}
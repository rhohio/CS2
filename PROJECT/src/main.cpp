/*
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
int generatePatronID(Restaurant **[], short int);
void writeToLog(Restaurant &, std::fstream &, std::map<int, Meals>&);
void findPatron(Restaurant **[], std::fstream&);
short int findMealNumberFromObj(Restaurant **[], std::string&);
std::string findFavoriteMeal(std::fstream&, std::string&, short int);
void displayUsage(Restaurant **[], std::fstream&);
void findFavoriteRestaurants(Restaurant **[], std::fstream&);
void findFavoriteMeals(Restaurant **[], std::fstream&);
void findFavoriteTimes(Restaurant **[], std::fstream&);
short int getMode(std::vector<short int> &);
void displayLog(std::fstream&);

int main()
{

    std::fstream log;
    log.open("log.txt", std::ios::in | std::ios::out | std::ios::app);

    if(!log.is_open())
    {
        std::cerr << "Log file failed to open/generate." << std::endl;
        return -1;
    }

    //makes an array, that points to NUMHFCS arrays, which are arrays of size HFCSIZE[i], that point to rest objs
    Restaurant **restPtr[NUMHFCS];
    for(int i = 0; i < NUMHFCS; ++i)
    {
        restPtr[i] = new Restaurant *[HFCSIZES[i]];
    }

    //create map of meals using parallel arrays
    std::map<int, Meals> mealMap;
    for(int i = 0; i < NUMMEALS; ++i)
    {
        mealMap.insert(std::make_pair<int, Meals>(int(i), Meals(Meals(MEALNAMES[i], CALORIES[i], PROTEIN[i], VITAMINS[i]))));
    }

    //create waiting list queue
    std::queue<Restaurant> waitingList;

    bool isMainRepeated = true;

    do
    {
        //calls main menu display, then assess the answer based on input
        assessMenuAnswer(mainMenu(), isMainRepeated, restPtr, mealMap, waitingList, log);
    }while(isMainRepeated);

}


int mainMenu()
{
    //display main menu
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
    //validate main menu
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
    //based on menu answer, go to appropriate function
    switch(menuAnswer)
    {
        case 1:
            requestTable(restPtr, mealMap, waitingList, log);
            break;
        case 2:
            freeTable(restPtr, waitingList);
            break;
        case 3:
            findPatron(restPtr, log);
            break;
        case 4:
            displayUsage(restPtr, log);
            break;
        case 5:
            displayLog(log);
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

    //get and validate res choice
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

    resAnswer--;

    //assigns table number if possible, if full, assigns -1
    int tableNumber = assignTableNumber(restPtr, resAnswer);

    //restaurant is full
    if(tableNumber == -1)
    {
        std::cout << "This restaurant is currently full. You will be placed into the wait list and given a table as soon as possible." << std::endl
                  << "Please enter your name: ";

        //create restaurant obj to hold data from patron to place into queue
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

        patron.setPatronID(generatePatronID(restPtr, resAnswer));
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

        //push data from patron on the waiting list
        const Restaurant _patron(patron);
        waitingList.push(_patron);
    }
    //restaurant isn't full
    else
    {
        //create new restaurant obj and set values we already know
        restPtr[resAnswer][tableNumber] = new Restaurant;
        restPtr[resAnswer][tableNumber]->setResNumber(resAnswer);
        restPtr[resAnswer][tableNumber]->setTableNumber(tableNumber);
        restPtr[resAnswer][tableNumber]->setPatronID(generatePatronID(restPtr, resAnswer));

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

        //write info from patron into log
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

    //free the memory allocated to the obj it was pointing at
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
    //if front isnt the right restaurant, and the queue isn't empty
    else
    {
        //stack to hold data from the queue we want to keep
        std::stack<Restaurant> tempRestStack;

        //keep popping off the queue and saving the objs until you find the right restaurant
        while(waitingList.front().getResNumber() != resNum)
        {

            const Restaurant currentObj(waitingList.front());
            tempRestStack.push(currentObj);
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
    //iterate through the restuarants tables
    for(int i = 0; i < HFCSIZES[restaurant]; ++i)
    {
        //if there isn't an obj, then there's a free table
        if(!(restPtr[restaurant][i]))
        {
            return i;
        }
    }
    //if no free tables, return -1
    return -1;
}

//TODO: Fix this shit
int generatePatronID(Restaurant **restPtr[], short int restaurant)
{

    srand(time(nullptr));
    bool isUnique = true;
    int newID;

    do
    {
        newID = rand() % 100000;
        for(int i = 0; i < NUMHFCS; ++i)
        {
            for (int j = 0; j < HFCSIZES[restaurant] && restPtr[i][j]; ++j)
            {
                if (newID == restPtr[i][j]->getPatronID())
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
    log << input.getResNumber() << '\t' << input.getPatronName() << '\t' << input.getMealTime() << '\t' << MEALNAMES[input.getPatronMealNumber()] << '\t'
        << mealMap[input.getPatronMealNumber()].getCalories() << '\t' << mealMap[input.getPatronMealNumber()].getProtein()
        << '\t' << mealMap[input.getPatronMealNumber()].getVitamins() << std::endl;
}

void findPatron(Restaurant **restPtr[], std::fstream &log)
{
    std::cout << "Please enter the patron by name: ";
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

    std::string favoriteMeal = findFavoriteMeal(log, patronName, findMealNumberFromObj(restPtr, patronName));

    if(favoriteMeal.empty())
    {
        std::cout << patronName << " has no favorite." << std::endl;
    }
    else
    {
        std::cout << patronName << " likes " << favoriteMeal << std::endl;
    }

    std::cout << "Hit enter for next selection" << std::endl;
    std::cin.ignore();
    std::cin.get();
}

short int findMealNumberFromObj(Restaurant **restPtr[], std::string &patronName)
{
    for(int i = 0; i < NUMHFCS; ++i)
    {
        for(int j = 0; j < HFCSIZES[i]; ++j)
        {
            if(restPtr[i][j]->getPatronName() == patronName)
            {
                return restPtr[i][j]->getPatronMealNumber();
            }
        }
    }
    return -1;
}

//TODO: Finish findFavoriteMeal
std::string findFavoriteMeal(std::fstream &log, std::string &patronName, short int mealNumber)
{
    std::string _patronName;
    std::vector<std::string> mealNames;
    std::string mealName;
    while(!log.eof())
    {
        log.ignore('\t');
        log >> _patronName;
        if(_patronName == patronName)
        {
            log.ignore('\t');
            getline(log, mealName, '\t');
            mealNames.push_back(mealName);
            log.ignore('\n');
        }
    }

    for(auto meal: mealNames)
    {
        if(meal == MEALNAMES[0])
        {

        }
    }
}

void displayUsage(Restaurant **restPtr[], std::fstream &log)
{
    std::cout << "A) Favorite restaurants \nB) Favorite meals \nC)Favorite days and times \n" << std::endl
              << "Pick your favorite report from the list: ";

    char menuAns;
    bool isMenuAnsInvalid = false;
    do
    {
        std::cin >> menuAns;
        if(menuAns != 'a' || menuAns != 'A' || menuAns != 'b' || menuAns != 'B' || menuAns != 'c' || menuAns != 'C')
        {
            std::cout << "Please enter either an A, B, or C: ";
            isMenuAnsInvalid = true;
        }
    }while(isMenuAnsInvalid);

    switch(menuAns)
    {
        case 'a':
        case 'A':
            findFavoriteRestaurants(restPtr, log);
            break;
        case 'b':
        case 'B':
            findFavoriteMeals(restPtr, log);
            break;
        case 'c':
        case 'C':
            findFavoriteTimes(restPtr, log);
            break;
        default:
            return;
    }
}


/*
 * log << input.getPatronName() << '\t' << input.getMealTime() << '\t' << MEALNAMES[input.getPatronMealNumber()] << '\t'
        << mealMap[input.getPatronMealNumber()].getCalories() << '\t' << mealMap[input.getPatronMealNumber()].getProtein()
        << '\t' << mealMap[input.getPatronMealNumber()].getVitamins() << std::endl;

 */

//TODO: THIS
void findFavoriteRestaurants(Restaurant **restPtr[], std::fstream &log)
{
    /*
    std::map<short int, int> favoriteRestaurants;
    int count = 0;
    for(int i = 0; i < NUMHFCS; ++i)
    {
        for(int j = 0; j < HFCSIZES[i]; ++j)
        {
            favoriteRestaurants.insert(std::make_pair(restPtr[i][j]->getResNumber(), count));
        }
    }

    short int resNum;

    while(!log.eof())
    {
        log.ignore('\t');
        log.ignore('\t');
        log >> resNum;
        favoriteRestaurants.push_back(resNum);
        log.ignore('\n');
    }

    getMode(favoriteRestaurants);
     */

}

void findFavoriteMeals(Restaurant **restPtr[], std::fstream &log)
{

}


void findFavoriteTimes(Restaurant **restPtr[], std::fstream &log)
{

}


short int getMode(std::vector<short int> &input)
{
    short int count[input.size()];

}

/*
    log << input.getResNumber() << '\t' << input.getPatronName() << '\t' << input.getMealTime() << MEALNAMES[input.getPatronMealNumber()] << '\t'
        << mealMap[input.getPatronMealNumber()].getCalories() << '\t' << mealMap[input.getPatronMealNumber()].getProtein()
        << '\t' << mealMap[input.getPatronMealNumber()].getVitamins() << std::endl;
*/


void displayLog(std::fstream &log)
{
    std::cout << "Which restaurant would you like to view the log for? [1 - " << NUMHFCS << "]: ";

    short int _resNum;
    bool isResAnsInvalid = false;
    do
    {
        std::cin >> _resNum;
        if(_resNum < 1 || _resNum > NUMHFCS)
        {
            std::cout << "Please enter a valid restaurant number [1 - " << NUMHFCS << "]: ";
            isResAnsInvalid = true;
        }
    }while(isResAnsInvalid);

    _resNum--;

    short int resNum;
    std::string patronName;
    std::string mealTime;
    std::string mealName;
    short int calories;
    short int protein;
    short int vitamins;

    while(!log.eof())
    {
        log >> resNum;
        if(resNum == _resNum)
        {
            log >> patronName;
            log >> mealTime;
            log >> mealName;
            log >> calories;
            log >> protein;
            log >> vitamins;

            std::cout << "Log entries for " << RESTAURANT[resNum] << std::endl
                      << patronName << " had " << mealName << " with "
                      << calories << " calories, " << protein << " grams of protein, and "
                      << vitamins << " mg of vitamins at " << mealTime << std::endl;
        }
    }
}
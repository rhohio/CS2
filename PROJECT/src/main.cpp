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
#include <limits>
#include "Restaurant.h"
#include "Meals.h"

//TODO: commenting
//TODO: Optimise and/or implement error handling w excpetions

/*
 *      <globalConstants>
 */

//Number of Restaurants
const int NUMHFCS = 8;

//Number of tables in each restaurant
const int HFCSIZES[NUMHFCS]
    // 19
    = {2, 15, 24, 33, 61, 17, 55, 37};

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
Restaurant findObjFromPatronName(Restaurant **[], std::string&);
std::string findFavoriteMeal(std::fstream&, Restaurant&);
void displayUsage(Restaurant **[], std::fstream&);
void findFavoriteRestaurants(Restaurant **[], std::fstream&);
void findFavoriteMeals(Restaurant **[], std::fstream&);
void findFavoriteTimes(Restaurant **[], std::fstream&);
void displayLog(std::fstream&);

int main()
{

    //generate-open log file
    std::fstream log("log.txt", std::ios::in | std::ios::out | std::ios::app);

    //if log fails to open, abort
    if(!log.is_open())
    {
        std::cerr << "Log file failed to open/generate." << std::endl;
        return -1;
    }

    //makes an array, that points to NUMHFCS arrays, which are arrays of size HFCSIZE[i], that will point to rest objs
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

    //close log file
    log.close();

    //free up memory from leftover restPtrs
    for(int i = 0; i < NUMHFCS; ++i)
        delete [] restPtr[i];
}

//Pre-Condition : N/A
//Post-condition: Returns answer to a menu of choices
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
    bool invalidMenuAnswer;
    do
    {
        std::cin >> menuAnswer;
        if(menuAnswer > 6 || menuAnswer < 1 || std::cin.fail())
        {
            std::cout << "Please enter a valid number 1-6: ";
            invalidMenuAnswer = true;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            invalidMenuAnswer = false;
        }
    }while(invalidMenuAnswer);

    //return validated menu answer
    return menuAnswer;
}

//Pre-Condition : Main menu answer has been retireved and validated, restPtr's have been init'd, same with the mealMap and waiitingList, and log
//Post-Condition: sends user and data to correct subfunction based on menuanswer
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

//Pre-Condition : restPtrs been init's, mealMap is populated with meals, waitingList is init'd, log is open
//Post-Condition: based on table availablility, either adds patron to wiaitng list or assigns thema table
void requestTable(Restaurant **restPtr[], std::map<int, Meals> &mealMap, std::queue<Restaurant> &waitingList, std::fstream &log)
{
    std::cout << "Please enter the restaurant choice from 1 through "<< NUMHFCS << ": ";

    //get and validate res choice
    int resAnswer;
    bool invalidRestAnswer;
    do
    {
        std::cin >> resAnswer;
        if(resAnswer > NUMHFCS || resAnswer < 1 || std::cin.fail())
        {
            std::cout << "Please enter a valid selection [1-" << NUMHFCS << "]: ";
            invalidRestAnswer = true;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            invalidRestAnswer = false;
        }
    }while(invalidRestAnswer);

    std::cout << "You have chosen " << RESTAURANT[resAnswer - 1] << std::endl;

    //decrement resAnswer to get actual restaurant number
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

        bool isPatronNameInvalid;
        std::string patronName;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        do
        {
            getline(std::cin, patronName);
            if(patronName.empty() || std::cin.fail())
            {
                std::cout << "Please enter a valid name (Not empty): ";
                isPatronNameInvalid = true;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max());
            }
            else
            {
                isPatronNameInvalid = false;
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

        bool isMealNameInvalid;
        short int mealName;
        do
        {
            std::cin >> mealName;
            if(mealName > NUMMEALS || mealName < 1 || std::cin.fail())
            {
                std::cout << "Please enter a valid selection [1 through " << NUMMEALS << "]: ";
                isMealNameInvalid = true;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                isMealNameInvalid = false;
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
        waitingList.push(_patron);//TODO: wait list doesn't work as intended - see next TODO
    }
    //restaurant isn't full
    else
    {
        //create new restaurant obj and set values we already know
        restPtr[resAnswer][tableNumber] = new Restaurant;
        restPtr[resAnswer][tableNumber]->setResNumber(resAnswer);
        restPtr[resAnswer][tableNumber]->setTableNumber(tableNumber);
        restPtr[resAnswer][tableNumber]->setPatronID(generatePatronID(restPtr, resAnswer));

        std::cout << "Your table number is " << tableNumber + 1 << " and your ID number is " << std::setfill('0') << std::setw(5)
                  <<  restPtr[resAnswer][tableNumber]->getPatronID() << std::endl
                  << "Please enter the name of the Patron: ";

        bool isPatronNameInvalid;
        std::string patronName;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        do
        {
            getline(std::cin, patronName);
            if(patronName.empty() || std::cin.fail())
            {
                std::cout << "Please enter a valid name (Not empty): ";
                isPatronNameInvalid = true;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                isPatronNameInvalid = false;
            }
        }while(isPatronNameInvalid);

        std::cin.clear();

        restPtr[resAnswer][tableNumber]->setPatronName(patronName);

        std::cout << "Please enter the meal number from the following choices: " << std::endl;
        for(int i = 0; i < NUMMEALS; ++i)
        {
            std::cout << i + 1;
            ((i + 1) % 10) ? std::cout << ")   " : std::cout << ")  ";
            std::cout << MEALNAMES[i] << std::endl;
        }

        std::cout << "Meal: ";
        bool isMealNameInvalid;
        short int mealNumber;

        do
        {
            std::cin >> mealNumber;
            if(mealNumber > NUMMEALS || mealNumber < 1 || std::cin.fail())
            {
                std::cout << "Please enter a valid selection [1 through " << NUMMEALS << "]: ";
                isMealNameInvalid = true;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                isMealNameInvalid = false;
            }
        }while(isMealNameInvalid);

        mealNumber--;

        restPtr[resAnswer][tableNumber]->setPatronMealNumber(mealNumber);

        std::cout << "Your choice was the " << mealMap[mealNumber].getPatronMealName() << std::endl
                  << mealMap[mealNumber].getCalories() << " calories, "
                  << mealMap[mealNumber].getProtein()  << " grams of protein, and "
                  << mealMap[mealNumber].getVitamins() << " milligrams of vitamins" << std::endl;

        std::cout << "Hit enter for next selection" << std::endl;
        std::cin.ignore();
        std::cin.get();

        //write info from patron into log
        writeToLog(*restPtr[resAnswer][tableNumber], log, mealMap);
    }
}

//Pre-Condition : restPtr is init'd, waitingLIst had been init
//Post-Condition: frees up table from current patron, if waiting list is populated, replaces patron with patron on waiting list
void freeTable(Restaurant **restPtr[], std::queue<Restaurant> &waitingList)
{
    std::cout << "Please enter the restaurant choice, [1 - " << NUMHFCS << "]: ";

    bool isResAnsInvalid;
    short int resAnswer;

    do
    {
        std::cin >> resAnswer;

        if(resAnswer < 1 || resAnswer > NUMHFCS || std::cin.fail())
        {
            std::cout << "Please enter a valid number. [1 - " << NUMHFCS << "]: ";
            isResAnsInvalid = true;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            isResAnsInvalid = false;
        }
    }while(isResAnsInvalid);
    short int resNum = resAnswer - 1;

    std::cout << "You have chosen " << RESTAURANT[resNum] << std::endl;

    std::cout << "Please enter the table number of the patron: ";

    short int tableAns;
    bool isTableAnsInvalid;
    do
    {
        std::cin >> tableAns;

        if(!(restPtr[resNum][tableAns - 1]) || std::cin.fail())
        {
            std::cout << "Could not find patron. Please re-enter the correct table number: ";
            isTableAnsInvalid = true;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            isTableAnsInvalid = false;
        }
    }while(isTableAnsInvalid);

    short int tableNum = tableAns - 1;

    std::cout << restPtr[resNum][tableNum]->getPatronName() << " has enjoyed another meal. Goodbye!" << std::endl;

    //free the memory allocated to the obj it was pointing at
    delete restPtr[resNum][tableNum]; //TODO: Not actually deleting???

    //if queue is empty, nothing to do
    if(waitingList.empty())
    {
        return;
    }
    //if the front happens to be the right restaurant, replace old patron, and pop if off the queue
    else if(waitingList.front().getResNumber() == resNum)
    {
        restPtr[resNum][tableNum] = new Restaurant(waitingList.front());
        restPtr[resNum][tableNum]->setTableNumber(tableNum);
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
        restPtr[resNum][tableNum]->setTableNumber(tableNum);
        waitingList.pop();

        //now place all the obj's on the queue we popped off earlier
        while(!(tempRestStack.empty()))
        {
            waitingList.push(tempRestStack.top());
            tempRestStack.pop();
        }
    }
}

//Pre-Condition : restPtr init, passed current restaurant number
//Post-Condition: returns next available table number, -1 if restuarant is full
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

//Pre-Condition : restptr init, passed current restaurant number
//Post-Condition: returns a unique 5 digit int that doesnt exist in any other restaurant obj
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

//Pre-Condition : input is populated with values, log is open, nealMap is populates with correct values
//Post-Condition: writes info from restaurant obj to log file
void writeToLog(Restaurant &input, std::fstream &log, std::map<int, Meals> &mealMap)
{
    log << input.getResNumber() << ' ' << input.getPatronName() << ',' << input.getMealTime() << ','
        << MEALNAMES[input.getPatronMealNumber()] << ',' << mealMap[input.getPatronMealNumber()].getCalories() << ' '
        << mealMap[input.getPatronMealNumber()].getProtein() << ' '
        << mealMap[input.getPatronMealNumber()].getVitamins() << std::endl;
}

//Pre-Condition : rest ptr init, log is open
//Post-Condition: finds patron by name, outputs patron favorite meal
void findPatron(Restaurant **restPtr[], std::fstream &log)
{
    std::cout << "Please enter the patron by name: ";
    bool isPatronNameInvalid;
    std::string patronName;
    do
    {
        std::cin >> patronName;
        if( patronName.empty() || std::cin.fail())
        {
            std::cout << "Please enter a valid name (Not empty): ";
            isPatronNameInvalid = true;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            isPatronNameInvalid = false;
        }
    }while(isPatronNameInvalid);

    std::string favoriteMeal;

    Restaurant patron = findObjFromPatronName(restPtr, patronName);

    favoriteMeal = findFavoriteMeal(log, patron);


    if(favoriteMeal.empty())
    {
        std::cout << patronName << " has no favorite." << std::endl;
    }
    else
    {
        std::cout << patronName << " likes the " << favoriteMeal << std::endl;
    }

    std::cout << "Hit enter for next selection" << std::endl;
    std::cin.ignore();
    std::cin.get();
}

//Pre-Condition : restPtr init, populated w valies, patronname isnt empty
//Post-Condition: finds address of obj w patronName patronName
Restaurant findObjFromPatronName(Restaurant **restPtr[], std::string &patronName)
{
    for(int i = 0; i < NUMHFCS; ++i)
    {
        for(int j = 0; j < HFCSIZES[i]; ++j)
        {
            if(restPtr[i][j]->getPatronName() == patronName)
            {
                return *restPtr[i][j];
            }
        }
    }
    return Restaurant();
}

//Pre-Condition : log is open and populated, input is populated w values
//Post-Condition: finds most occurring meal of given restaurant obj
std::string findFavoriteMeal(std::fstream &log, Restaurant &input)
{
    std::map<std::string, int> patronsMeals;

    if(!input.getPatronName().empty() && patronsMeals.find(MEALNAMES[input.getPatronMealNumber()]) != patronsMeals.end())
        ++patronsMeals[MEALNAMES[input.getPatronMealNumber()]];
    else if(!input.getPatronName().empty() && patronsMeals.find(MEALNAMES[input.getPatronMealNumber()]) == patronsMeals.end())
        patronsMeals.insert(std::make_pair(MEALNAMES[input.getPatronMealNumber()], 1));

    std::string mealName;
    std::string patronName;
    log.clear();
    log.seekg(std::ios::beg);
    while(!log.eof())
    {
        log.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
        getline(log, patronName);
        log.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        getline(log, mealName, ',');
        if(patronName == input.getPatronName())
        {
            if (patronsMeals.find(mealName) != patronsMeals.end())
                ++patronsMeals[mealName];
            else
                patronsMeals.insert(std::make_pair(mealName, 1));
        }
        log.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    log.clear();
    log.seekg(std::ios::end);

    short int largestValue = 0;
    std::string largestKey;

    for(auto const &item: patronsMeals)
    {
        if(item.second > largestValue)
        {
            largestValue = item.second;
            largestKey = item.first;
        }
    }

    return largestKey;
}

//Pre-Condition : restptr and log are init, populated with some values
//Post-Condition: prompts sub menu to choose which usage to display, sneds user and data to appropriate sub functions
void displayUsage(Restaurant **restPtr[], std::fstream &log)
{
    std::cout << "A) Favorite restaurants \nB) Favorite meals \nC) Favorite days and times \n" << std::endl
              << "Pick your favorite report from the list: ";

    char menuAns;
    bool isMenuAnsInvalid = false;
    do
    {
        std::cin >> menuAns;
        if(!(menuAns == 'a' || menuAns == 'A' || menuAns == 'b' || menuAns == 'B' || menuAns == 'c' || menuAns == 'C'))
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

//Pre-Condition : rest ptr, log are init; populated with some values
//Post-Condition: finds three most occuring resturants from current objs and log file
void findFavoriteRestaurants(Restaurant **restPtr[], std::fstream &log)
{

    std::map<short int, int> favoriteRestaurants;

    //populate map with data from active restaurant objs
    for(short int i = 0; restPtr[i][0] != nullptr; ++i)
    {
        for(int j = 0; restPtr[i][j] != nullptr; j++)
        {
            if(favoriteRestaurants.find(i) != favoriteRestaurants.end())
                ++favoriteRestaurants[i];
            else
                favoriteRestaurants.insert(std::make_pair(i, 1));
        }
    }
    short int resNum;
    //fill map with data from log file
    log.clear();
    log.seekg(std::ios::beg);
    while(log >> resNum)
    {
        if(favoriteRestaurants.find(resNum) != favoriteRestaurants.end())
            ++favoriteRestaurants[resNum];
        else
            favoriteRestaurants.insert(std::make_pair(resNum, 1));
        log.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    log.clear();
    log.seekg(std::ios::end);


    short int largestValue;
    short int largestKey;

    //really inefficient but gets the job done
    for(int i = 0; i < 3; ++i)
    {
        largestValue = 0;
        largestKey = -1;

        for(auto const &item: favoriteRestaurants)
        {
            if(item.second > largestValue)
            {
                largestValue = item.second;
                largestKey = item.first;
            }
        }

        if(largestKey == -1)
        {
            std::cout << "There is no more restaurant data." << std::endl;
        }
        else
        {
            std::cout << "The ";
            switch(i)
            {
                case 0: std::cout << "first";
                    break;
                case 1: std::cout << "second";
                    break;
                case 2: std::cout << "third";
                    break;
                default:
                    break;
            }

            std::cout << " most favorite restaurant is " << RESTAURANT[largestKey] << " with " << favoriteRestaurants[largestKey] << " patrons." << std::endl;
        }
        favoriteRestaurants.erase(largestKey);
    }

}

//Pre-Condition : rest ptr, log are init; populated with some values
//Post-Condition: finds three most occuring meals from current objs and log file
void findFavoriteMeals(Restaurant **restPtr[], std::fstream &log)
{
    std::map<std::string, int> favoriteMeals;

    //fill the map with data from active restuant objs
    for(short int i = 0; restPtr[i][0] != nullptr; ++i)
    {
        for(int j = 0; restPtr[i][j] != nullptr; j++)
        {
            if(favoriteMeals.find(MEALNAMES[restPtr[i][j]->getPatronMealNumber()]) != favoriteMeals.end())
                ++favoriteMeals[MEALNAMES[restPtr[i][j]->getPatronMealNumber()]];
            else
                favoriteMeals.insert(std::make_pair(MEALNAMES[restPtr[i][j]->getPatronMealNumber()], 1));
        }
    }

    std::string mealName;
    log.clear();
    log.seekg(std::ios::beg);
    while(!log.eof())
    {
        log.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        log.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        getline(log, mealName, ',');
        if(favoriteMeals.find(mealName) != favoriteMeals.end())
            ++favoriteMeals[mealName];
        else
            favoriteMeals.insert(std::make_pair(mealName, 1));
        log.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    log.clear();
    log.seekg(std::ios::end);

    short int largestValue;
    std::string largestKey;

    //really inefficient but gets the job done
    for(int i = 0; i < 3; ++i)
    {
        largestValue = 0;
        largestKey = "";

        for(auto const &item: favoriteMeals)
        {
            if(item.second > largestValue)
            {
                largestValue = item.second;
                largestKey = item.first;
            }
        }

        if(largestKey.empty())
        {
            std::cout << "There is no more restaurant data." << std::endl;
        }
        else
        {
            std::cout << "The ";
            switch(i)
            {
                case 0: std::cout << "first";
                    break;
                case 1: std::cout << "second";
                    break;
                case 2: std::cout << "third";
                    break;
                default:
                    break;
            }

            std::cout << " most favorite meal is " << largestKey << " with " << favoriteMeals[largestKey] << " orders." << std::endl;
        }
        favoriteMeals.erase(largestKey);
    }
}

//Pre-Condition : rest ptr, log are init; populated with some values
//Post-Condition: finds three most occuring times and days from current objs and log file
void findFavoriteTimes(Restaurant **restPtr[], std::fstream &log)
{
    std::map<std::string, int> favoriteTimes;
    char timecString[7];
    std::string timeString;
    for(short int i = 0; restPtr[i][0] != nullptr; ++i)
    {
        for(int j = 0; restPtr[i][j] != nullptr; ++j)
        {
            for(int k = 0; k < 3; k++)
            {
                timecString[k] = restPtr[i][j]->getMealTime()[k];//TODO: Fix bug where only records Day and not time
            }
            timecString[3] = ' ';
            for(int l = 0; l < 2; ++l)
            {
                timecString[l + 4] = restPtr[i][j]->getMealTime()[l + 12];
            }
            timecString[6] = '\0';

            timeString = timecString;

            if(favoriteTimes.find(timeString) != favoriteTimes.end())
                ++favoriteTimes[timeString];
            else
                favoriteTimes.insert(std::make_pair(timeString, 1));
        }
    }

    log.clear();
    log.seekg(std::ios::beg);
    std::string mealString;
    std::string mealDay;
    std::string mealTime;
    while(!log.eof())
    {
        log.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        getline(log, mealString, ',');
        if(mealString.length() > 10)
        {
            mealString = mealString.substr(0,3) + " " + mealString.substr(11, 2);
            if(favoriteTimes.find(mealString) != favoriteTimes.end())
                ++favoriteTimes[mealString];
            else
                favoriteTimes.insert(std::make_pair(mealString, 1));
        }
        log.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    log.clear();
    log.seekg((std::ios::end));

    int largestValue;
    std::string largestKey;

    for(int i = 0; i < 3; ++i)
    {
        largestValue = 0;
        largestKey = "";

        for(auto const &item: favoriteTimes)
        {
            if(item.second > largestValue)
            {
                largestValue = item.second;
                largestKey = item.first;
            }
        }
        if(!(largestKey.empty() || largestKey.length() < 6))
        {
            std::cout << "The ";
            switch(i)
            {
                case 0: std::cout << "first";
                    break;
                case 1: std::cout << "second";
                    break;
                case 2: std::cout << "third";
                    break;
                default:
                    break;
            }

            std::cout << " most favorite day and times are " << largestKey.substr(0, 3);
            if(largestKey.at(2) == 'n' || largestKey.at(2) == 'i')
            {
                std::cout << "days between ";
            }
            else if(largestKey.at(2) == 'e')
            {
                std::cout << "sdays between ";
            }
            else if(largestKey.at(2) == 'd')
            {
                std::cout << "nesdays between ";
            }
            else if(largestKey.at(2) == 'u')
            {
                std::cout << "rsdays between ";
            }
            else if(largestKey.at(2) == 't')
            {
                std::cout << "urdays between ";
            }

            mealTime = largestKey.substr(4, 2);
            if(mealTime == "00")
            {
                std::cout << "12 and " << int(mealTime.at(1)) + 1 << " AM" << std::endl;
            }
            else if(mealTime.at(0) == '0')
            {
                std::cout << mealTime.at(1) << " and " << int(mealTime.at(1)) + 1 << " AM" << std::endl;
            }
            else if(mealTime == "12" || mealTime == "11")
            {
                std::cout << mealTime << " and ";
                (mealTime.at(1) == '2') ? std::cout << "1 PM" << std::endl : std::cout << "12 PM" << std::endl;
            }
            else
            {
                std::cout << stoi(mealTime) - 12 << " and " << stoi(mealTime) - 11 << " PM" << std::endl;
            }
        }
        favoriteTimes.erase(largestKey);
    }
}

//Pre-Condition : log is open and has values
//Post-Condition: prints info from log
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

    log.clear();
    log.seekg(0, std::ios::beg);

    std::cout << "Log entries for " << RESTAURANT[_resNum] << ":" << std::endl;

    while(log >> resNum)
    {
        if(resNum == _resNum)
        {
            getline(log, patronName, ',');
            getline(log, mealTime, ',');
            getline(log, mealName, ',');
            log >> calories;
            log >> protein;
            log >> vitamins;

            std::cout << patronName << " had " << mealName << " with "
                      << calories << " calories, " << protein << " grams of protein, and "
                      << vitamins << " mg of vitamins on " << mealTime << std::endl;
            log.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            log.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::cout << "End of log entires for " << RESTAURANT[_resNum] << std::endl;

    log.clear();
    log.seekg(0, std::ios::end);
}
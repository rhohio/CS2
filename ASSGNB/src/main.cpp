/* Author: Kyle Dabbieri
   email : kad145@zips.uakron.edu
   ID    : 4032068
   Prgrm : ASSGNB
   Purpse: Retrieve and store tax payer information in
           a vector of structs containing the information
*/

#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include "taxPayer.hpp"

const int SIZE = 2;

void taxPrint(std::vector<taxPayer> &);
void taxTaker(std::vector<taxPayer> &);
float validateInput(float, float, std::string);

int main()
{
   std::vector<taxPayer> citizens(SIZE);

   taxTaker(citizens);
   taxPrint(citizens);

   return 0;
}

//Pre-Condition : vector of size SIZE and type taxPayer is initiazlied, and has relevant values.
//Post-Condition: prints vectors information
void taxPrint(std::vector<taxPayer> &citizen)
{
   std::cout << "Taxes due for this year: " << std::endl;

   for(int i = 0; i < SIZE; ++i)
   {
      std::cout << "Tax Payer # " << (i + 1) << ": $" << std::fixed << std::setprecision(2) << citizen[i].taxes << std::endl;
   }
   return;
}

//Pre-Condition : vector of size SIZE and type taxPayer is initialized
//Post-Condition: inputs data into vector depending on user input
void taxTaker(std::vector<taxPayer> &citizen)
{
   std::cout << "Please enter the annual income and tax rate for " << SIZE 
             << " tax payers:" << std::endl;
   bool isInvalid = false;
   for(int i = 0; i < SIZE; ++i)
   {
      do
      { 
         std::cout << "Enter this year's income for the tax payer " << (i + 1) << ": ";
         std::cin >> citizen[i].income;
         
         //input validaiton (float, not less than income)
         if(std::cin.fail() || (citizen[i].income < 0))
         {
            std::cout << "Please enter a number greater than 0" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            isInvalid = true;
         }
         else
         {
            isInvalid = false;
         } 
      }while(isInvalid);
      isInvalid = false;
      do
      {
         std::cout << std::endl << "Enter the tax rate for tax payer # " << (i + 1) << ": ";
         std::cin >> citizen[i].taxRate;

         //input validation (float, between 0.01 and 9.9, had some weird rounding errors bc of floats)
         if(std::cin.fail() || (citizen[i].taxRate < 0.0099 || citizen[i].taxRate > 9.901))
         {
            std::cout << "Please enter a number between 0.01 and 9.9." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            isInvalid = true;
         }
         else
         {
            isInvalid = false;
         }
      }while(isInvalid);
      //and finally, compute citizen[i].taxes, the good stuff
      citizen[i].taxes = citizen[i].income * (citizen[i].taxRate / 100);
   }
   return;
}
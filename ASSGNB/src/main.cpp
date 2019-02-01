/* Author: Kyle Dabbieri
   email : kad145@zips.uakron.edu
   ID    : 4032068
   Prgrm : ASSGNB
   Purpse: ...
*/

#include <iostream>
#include <vector>
#include <limits>

const int SIZE = 2;

struct taxPayer{
   float taxRate;
   float income;
   float taxes;
};

std::vector<taxPayer> citizen;


void taxPrint(std::vector<taxPayer> &);
void taxTaker(std::vector<taxPayer> &);
float validateInput(float, float, std::string);



int main()
{
   std::vector<taxPayer> citizens;

   taxTaker(citizens);

   taxPrint(citizens);

   return 0;
}


void taxPrint(std::vector<taxPayer> &citizen)
{
   std::cout << "Taxes due for this year: " << std::endl;

   for(int i = 0; i < SIZE; ++i)
   {
      std::cout << "Tax Payer # " << (i + 1) << ": $" << citizen[i].taxes;
   }


   return;
}


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
         
         if(std::cin.fail() || (citizen[i].income < 0))
         {
            std::cout << "Please enter a number greater than 0" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max());
            isInvalid = true;
         }
      }while(isInvalid);
      isInvalid = false;
      do
      {
         std::cout << std::endl << "Enter the tax rate for tax payer # " << (i + 1) << ": ";
         std::cin >> citizen[i].taxRate;

         if(std::cin.fail() || (citizen[i].taxRate < 0.01 || citizen[i].taxRate > 9.9))
         {
            std::cout << "Please enter a number between 0.01 and 9.9." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max());
            isInvalid = true;
         }
      }while(isInvalid);
      
      citizen[i].taxes = citizen[i].income * citizen[i].taxRate;
   }
   return;
}
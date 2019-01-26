/*
   Author:  Kyle Dabbieri
   email:   kad145@zips.uakron.edu
   ID:      4032068
   Prgram:  ASSGNA
   Purpose: Delete corresposing chars in an array
*/

#include <memory>
#include <iostream>

const short unsigned int SIZE = 10;

std::unique_ptr<char[]> delCorr(char*);

int main()
{
   char originalArray[SIZE];
   originalArray [0] = 'a';
   originalArray [1] = 'b';
   originalArray [2] = 'b';
   originalArray [3] = 'c';
   originalArray [4] = 'a';
   originalArray [5] = 'c';
   originalArray [6] = 'a';
   originalArray [7] = 'c';
   originalArray [8] = 'b';
   originalArray [9] = 'a';

   std::cout << "Before:" << std::endl;
   for(int i = 0; i < SIZE; ++i)
   {
      std::cout << originalArray[i] << std::endl;
   }

   std::unique_ptr<char[]> noRepeats(delCorr(originalArray));
   
   std::cout << "After:" << std::endl;
   int i = 0;
   while(noRepeats[i] != 0)
   {
      std::cout << noRepeats[i] << std::endl;
      ++i;
   }

   return 0;
}

//Precondition : an array of characters with size: SIZE  
//Postcondtiion: returns array without matching corresponding elements
std::unique_ptr<char[]> delCorr(char* origArr)
{
   //the new size of the array w/o corresponding elements
   short unsigned int newSize = 0;

   //gets size of array w/o matching corresponding elements
   for(int i = 0; i < SIZE / 2; ++i)
   {
      if(origArr[i] != origArr[SIZE - (i + 1)])
      {
         newSize += 2;
      }
   }

   std::unique_ptr<char[]> newArr(new char[newSize]);
   
   //index for creating the newArr
   short unsigned int count = 0;
   
   //creates new dynamic array of size newSize, with non matching corresponding elements
   for(int i = 0; i < SIZE / 2; ++i)
   {
      if(origArr[i] != origArr[SIZE - (i + 1)])
      {
         newArr[count] = origArr[i];
         newArr[newSize - (count + 1)] = origArr[SIZE - (i + 1)];
         
         ++count;
      }
   }
   return newArr;
}
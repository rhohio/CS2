/*
   COPYRIGHT (C) 2016 Kyle Dabbieri (kad145) All rights reserved.
   CSII Assignment F
   Author.  Kyle Dabbieri
            zippy@zips.uakron.edu
   Version. 1.01 09.09.2017
   Purpose: This program demonstrates simple operations
            on a linked list.
*/

#include "charList.hpp"
#include  <iostream>

charList::charList()
{
   head = nullptr;
}

//**************************************************
// displayList shows the value                     *
// stored in each node of the linked list          *
// pointed to by head.                             *
// pre: an empty parameter list                    *
// post: standard output of the linked list        *
//**************************************************
void charList::displayList() const
{
   listNode *nodePtr;  // To move through the list

   // Position nodePtr at the head of the list.
   nodePtr = head;
   short count = 0;

   // While nodePtr points to a node, traverse
   // the list.
   while (nodePtr)
   {
      // Display the value in this node.
      std::cout << "[" << nodePtr->value << "] -> ";
      ++count;
      // Move to the next node.
      nodePtr = nodePtr->next;
      if (count % 10 == 0) {
        std::cout << std::endl;
        count = 0;
      }
   }
   std::cout << std::endl;
}

//pre : a valid char input
//post: appends char input to end of linked list
void charList::appendNode(char input)
{
   listNode *newNode;
   listNode *nodePtr;

   newNode = new listNode;
   newNode->value = input;
   newNode->next = nullptr;

   if(!head)
   {
      head = newNode;
   }   
   else
   {
      nodePtr = head;
      while(nodePtr->next)
         nodePtr = nodePtr->next;
      
      nodePtr->next = newNode;
   }
}

//pre : a valid char input
//post: inserts char input to correct spot in linked list,
//      which is in decending alphabetical order
void charList::insertNode(char input)
{
   listNode *newNode;
   listNode *nodePtr;
   listNode *previousNode = nullptr;

   newNode = new listNode;
   newNode->value = input;

   if(!head)
   {
      head = newNode;
      newNode->next = nullptr;
   }
   else
   {
      nodePtr = head;
      previousNode = nullptr;
      while(nodePtr != nullptr && nodePtr->value < input)
      {
         previousNode = nodePtr;
         nodePtr = nodePtr->next;
      }
      if(previousNode == nullptr)
      {
         head = newNode;
         newNode->next = nodePtr;
      }
      else
      {
         previousNode->next = newNode;
         newNode->next = nodePtr;
      }
   }
}

//pre : valid char input that exists in the linked list
//post: deletes noded that contains char input
void charList::deleteNode(char input)
{
   listNode *nodePtr;
   listNode *previousNode;

   if(!head)
   {
      return;
   }
   if(head->value == input)
   {
      nodePtr = head->next;
      delete head;
      head = nodePtr;
   }
   else
   {
      nodePtr = head;
      while(nodePtr != nullptr && nodePtr->value != input)
      {
         previousNode = nodePtr;
         nodePtr = nodePtr->next;
      }
      if(nodePtr)
      {
         previousNode->next = nodePtr->next;
         delete nodePtr;
      }
   }
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
// pre: n/a                                        *
// post: destroyed object                          *
//**************************************************

charList::~charList()
{
   listNode *nodePtr;   // To traverse the list
   listNode *nextNode;  // To point to the next node

   // Position nodePtr at the head of the list.
   nodePtr = head;

   // While nodePtr is not at the end of the list...
   while (nodePtr != nullptr)
   {
      // Save a pointer to the next node.
      nextNode = nodePtr->next;

      // Delete the current node.
      delete nodePtr;

      // Position nodePtr at the next node.
      nodePtr = nextNode;
   }
}

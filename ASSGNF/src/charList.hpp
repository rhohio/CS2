#ifndef CHARLIST_H 
#define CHARLIST_H

class charList{
   private:
      struct listNode{
         char value;
         node *nodePtr;
      };
   public:
      charList();
      ~charList();
   
      void appendNode(char);
      void insertNode(char);
      void deleteNode(char);
      void displayList();



}





#endif
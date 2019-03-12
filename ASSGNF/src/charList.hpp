#ifndef CHARLIST_H 
#define CHARLIST_H

class charList{
   private:
      struct listNode{
         char value;
         listNode *next;
      };

      listNode *head;
   public:
      //constructors & deconstructors
      charList();
      ~charList();

      //member functions
      void appendNode(char);
      void insertNode(char);
      void deleteNode(char);
      void displayList() const;
};

#endif
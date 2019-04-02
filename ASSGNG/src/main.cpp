/*
   Name: Kyle Dabbieri
   Email: kad145@zips.uakron.edu
   Purpose: This program demonstrates the myStack class.
*/

#include <iostream>

template <typename T>
class myStack{
   private:
      T *stackArray;
      int stackSize;
      int top;
   public:
      myStack();
      myStack(int);
      ~myStack();
      
      bool push(T);
      bool pop(T&);
      bool isEmpty();
      void mult();
      void div();
      void add();
      void sub();
      void addAll();
      void multAll();
};



int main()
{
  int catchVar;  // To hold values popped off the stack

  // Create a intstack object.
  myStack<int> intStack(5);
  std::cout << "Starting the demonstration of the greatest stack of all time"
            << std::endl << std::endl;

  // Push 3 and 6 onto the stack.
  std::cout << "Pushing 3\n";
  intStack.push(3);
  std::cout << "Pushing 6\n";
  intStack.push(6);

  // Add the two values.
  intStack.add();

  // Pop the sum off the intStack and display it.
  std::cout << "The sum is ";
  intStack.pop(catchVar);
  std::cout << catchVar << std::endl << std::endl;

  // Push 7 and 10 onto the intStack
  std::cout << "Pushing 7\n";
  intStack.push(7);
  std::cout << "Pushing 10\n";
  intStack.push(10);

  // Subtract
  intStack.sub();

  // Pop the difference off the intStack and display it.
  std::cout << "The difference is ";
  intStack.pop(catchVar);
  std::cout << catchVar << std::endl << std::endl;

  // Push 7 and 10 onto the intStack
  std::cout << "Pushing 7\n";
  intStack.push(7);
  std::cout << "Pushing 10\n";
  intStack.push(10);

  // multiply
  intStack.mult();

  // Pop the difference off the intStack and display it.
  std::cout << "The product is ";
  intStack.pop(catchVar);
  std::cout << catchVar << std::endl << std::endl;

  // Push 7 and 10 onto the intStack
  std::cout << "Pushing 7\n";
  intStack.push(7);
  std::cout << "Pushing 10\n";
  intStack.push(10);

  // divide
  intStack.div();

  // Pop the difference off the intStack and display it.
  std::cout << "The quotient is ";
  intStack.pop(catchVar);
  std::cout << catchVar << std::endl << std::endl;

  //***********************************
  // create a double version of myStack
  //***********************************
  myStack<double> doubleStack(5); // size 5
  double doubleValue = 87.1;
  std::cout << "Pushing elements onto doubleStack\n" << std::endl << std::endl;

  // push 5 doubles onto doubleStack
  while (doubleStack.push(doubleValue))
  {
    std::cout << doubleValue << ' ';
    doubleValue += 6.1;
  } // end while

  std::cout << "\nStack is full. Cannot push " << doubleValue
       << "\n\nPopping elements from doubleStack\n" << std::endl << std::endl;

  // pop elements from doubleStack
  while (doubleStack.pop(doubleValue))
  {
    std::cout << doubleValue << ' ';
  }
  std::cout << "\nStack is empty. Cannot pop\n" << std::endl << std::endl;

  //***********************************
  // create a float version of myStack
  //***********************************
  myStack<float> floatStack(5); // size 5
  float floatValue = 87.1;
  std::cout << "Pushing elements onto floatStack\n" << std::endl << std::endl;

  // push 5 floats onto floatStack
  while (floatStack.push(floatValue))
  {
    std::cout << floatValue << ' ';
    floatValue += 6.1;
  } // end while

  floatStack.addAll();

  // Pop the sum off the floatStack and display it.
  std::cout << "The sum of all is ";
  floatStack.pop(floatValue);
  std::cout << floatValue << std::endl << std::endl;

  floatValue = 87.1;
  // push 5 floats onto floatStack
  while (floatStack.push(floatValue))
  {
    std::cout << floatValue << ' ';
    floatValue += 6.1;
  } // end while

  floatStack.multAll();

  // Pop the sum off the floatStack and display it.
  std::cout << "The product of all is ";
  floatStack.pop(floatValue);
  std::cout << floatValue << std::endl << std::endl;
  std::cout << "Ending the demonstration of the greatest stack of all time"
            << std::endl << std::endl;
  return 0;
}

template <typename T>
myStack<T>::myStack()
{
   stackArray = new T[1];
   stackSize = 1;
   top = -1;
}

template <typename T>
myStack<T>::myStack(int size)
{
   stackArray = new T[size];
   stackSize = size;
   top = -1;
}

template <typename T>
myStack<T>::~myStack()
{
   delete [] stackArray;
   stackArray = nullptr;
}

template <typename T>
bool myStack<T>::push(T input)
{
   if(top == stackSize - 1)
      return false;
   top++;
   stackArray[top] = input;
   // std::cout << input << " input " << " top " << top << std::endl;
   return true;
}

template <typename T>
bool myStack<T>::pop(T &input)
{
   if(isEmpty())
      return false;
   input = stackArray[top];
   top--;
   return true;
}

template <typename T>
bool myStack<T>::isEmpty()
{
   return (top == -1);
}

template <typename T>
void myStack<T>::mult()
{
   T left, right;
   pop(left);
   pop(right);
   push(left * right);
}

template <typename T>
void myStack<T>::div()
{
   T left, right;
   pop(left);
   pop(right);
   push(left / right);
}

template <typename T>
void myStack<T>::add()
{
   T left, right;
   pop(left);
   pop(right);
   push(left + right);
}

template <typename T>
void myStack<T>::sub()
{
   T left, right;
   pop(left);
   pop(right);
   push(left - right);
}

template <typename T>
void myStack<T>::addAll()
{
   T sum = 0;
   T index;
   while(pop(index))
   {
      sum += index;
   }
   push(sum);
}

template <typename T>
void myStack<T>::multAll()
{
   T product = 1;
   T index;
   while(pop(index))
   {
      product *= index;
   }
   push(product);
}
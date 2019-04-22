/*
   COPYRIGHT (C) 2018 Student Name (UANET ID ) All rights reserved.
   CS assignment
   Author.  Kyle Dabbieri
            kad145@zips.uakron.edu
   Version. 1.01 04.22.2019
   Purpose: string vclass test suite
*/


#include <cstring>
#include <iosfwd>
#include <string>
#include <iostream>
#include <cassert>

// yourString implementation here
// implemented as a struct
struct badString
{
   // Defines the npos value. Use for methods.
   static constexpr std::size_t npos = -1;

   //"private" but not actually private variables
   char* str;
   std::size_t size = 0;

   //constructors & destructors
   badString();
   ~badString();
   badString(char*);
   badString(char*, int);
   badString(const badString);

   //operator overloaders
   badString operator=(const &badString);
   badString operator=(const std::string);
   badString operator+=(const &badString);
   bool operator==(const &badString);
   bool operator!=(const &badString);
   bool operator<(const &badString);
   bool operator>(const &badString);
   bool operator<=(const &badString);
   bool operator>=(const &badString);

   //memeber functions
   bool empty();
   std::size_t size();
   char const* data();
   std::size_t find(char);
   badString substr(int, int);

};


// Output
std::ostream& operator<<(std::ostream&, yourString const&);

// Encapsulate all of the String tests.
struct Test_string
{
  void default_ctor()
  {
    // Check the default contructor.
    yourString s;
    assert(s.empty());
  }

  void string_ctor()
  {
    char const* str = "hello";
    yourString s = str;
    assert(s.data() != str);
    assert(strcmp(s.data(), str) == 0);
  }


  void copy_ctor()
  {
    yourString s1 = "hello";
    yourString s2 = s1;
    assert(strcmp(s1.data(), s2.data()) == 0);
  }

  void copy_assign()
  {
    yourString s1 = "hello";
    yourString s2;
    s2 = s1;
    assert(strcmp(s1.data(), s2.data()) == 0);
  }

  void string_assign()
  {
    yourString s;
    s = "hello";
    assert(!strcmp(s.data(), "hello"));
  }

  void self_assign()
  {
    yourString s1 = "hello";
    s1 = s1;
  }

  void empty()
  {
    yourString const s1;
    assert(s1.empty());
    yourString const s2 = "";
    assert(s2.empty());
  }

  void access()
  {
    yourString s1 = "hello";
    s1[0] = 'a';
    assert(s1[0] == 'a');

    yourString const s2 = "test";
    assert(s2[0] == 't');

    assert(s1[-1]);  // initially, you may believe this cannot work
    assert(s2[-1]);  // see the example output message in project and apply that logic
  }

  void find()
  {
    yourString const s1 = "abcdef";
    assert(s1.find('c') == 2);
    assert(s1.find('z') == s1.npos);
  }

  void substr()
  {
    yourString const s1 = "abcdef";
    yourString s2 = s1.substr(0, 3);
    yourString s3 = s1.substr(3, 3);
    assert (s2 == "abc");
    assert (s3 == "def");
  }

  void equality()
  {
    yourString const s1 = "hello";
    yourString const s2 = "goodbye";
    assert(s1 == s1);
    assert(s1 != s2);
  }

  void ordering()
  {
    yourString s1 = "abc";
    yourString s2 = "def";
    assert(s1 < s2);
    assert(s2 > s1);
    assert(s1 <= s1);
    assert(s1 >= s1);
  }

  void concatenation()
  {
    yourString s1 = "abc";
    yourString s2 = "def";
    yourString s3 = s1 + s2;
    yourString s4 = "abcdef";
    assert(s3 == s4);
  }

  void self_concatenation()
  {
    yourString s1 = "abc";
    s1 += s1;
    yourString s2 = "abcabc";
    assert(s1 == s2);
  }

  // The assert test runner for this test class.
  void run()
  {
    default_ctor();
    string_ctor();

    copy_assign();
    string_assign();
    self_assign();
    empty();
    access();
    find();
    substr();
    equality();
    ordering();
    concatenation();
    self_concatenation();
  }
};


int
main()
{
  Test_string test;
  test.run();
  return 0;
}



badString::badString()
{
   str = new char[1];
   str[1] = '\0';
}
~badString();
{
   //destructor here
}

badString::badString(char* input)
{
   str = new char[];
   std::size_t i = 0;
   for(; input[i] == '\0'; ++i)
   {
      str[i] = input[i];
   }
   size = i;
}

badString::badString(char* input, int loc)
{
   std::size_t i = 0;
   for(; i < loc; ++i)
   {
      str[i] = input[i];
   }
   size = i;
}

badString::badString(const badString &right)
{
   //copy constructor
}

   /* Operator Overloaders *
   
   badString operator=(const &badString);
   badString operator=(const std::string);
   badString operator+=(const &badString);
   bool operator==(const &badString);
   bool operator!=(const &badString);
   bool operator<(const &badString);
   bool operator>(const &badString);
   bool operator<=(const &badString);
   bool operator>=(const &badString);

    *                      */

badString::badString operator=(const badString &right)
{
   str = new char[right.size];
   for(int i = 0; i < right.size; ++i)
   {
      str[i] = right.str[i];
   }
   size = right.size;
   str[size + 1] = '\0';
   return *this;
}

badstring::badString
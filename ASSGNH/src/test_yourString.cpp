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
   std::size_t len = 0;

   //constructors & destructors
   badString();
   ~badString();
   badString(const char*);
   badString(char*, int);
   badString(const badString&);

   //operator overloaders
   badString& operator=(const badString&);
   badString& operator=(const char*);
   badString operator+=(const badString&);
   badString operator+(const badString&);
   bool operator==(const badString&) const;
   bool operator!=(const badString&) const;
   bool operator<(const badString&) const;
   bool operator>(const badString&) const;
   bool operator<=(const badString&) const;
   bool operator>=(const badString&) const;
   char operator[](const std::size_t) const;
   char& operator[](const std::size_t);

   //member functions
   bool empty() const;
   std::size_t size() const;
   char const* data();
   std::size_t find(char) const;
   badString substr(int, int) const;

};


// Output
std::ostream& operator<<(std::ostream&, badString const&);

// Encapsulate all of the String tests.
struct Test_string
{
  void default_ctor()
  {
    // Check the default contructor.
    badString s;
    assert(s.empty());
  }

  void string_ctor()
  {
    char const* str = "hello";
    badString s = str;
    assert(s.data() != str);
    assert(strcmp(s.data(), str) == 0);
  }


  void copy_ctor()
  {
    badString s1 = "hello";
    badString s2 = s1;
    assert(strcmp(s1.data(), s2.data()) == 0);
  }

  void copy_assign()
  {
    badString s1 = "hello";
    badString s2;
    s2 = s1;
    assert(strcmp(s1.data(), s2.data()) == 0);
  }

  void string_assign()
  {
    badString s;
    s = "hello";
    assert(!strcmp(s.data(), "hello"));
  }

  void self_assign()
  {
    badString s1 = "hello";
    s1 = s1;
  }

  void empty()
  {
    badString const s1;
    assert(s1.empty());
    badString const s2 = "";
    assert(s2.empty());
  }

  void access()
  {
    badString s1 = "hello";
    s1[0] = 'a';
    assert(s1[0] == 'a');

    badString const s2 = "test";
    assert(s2[0] == 't');

    assert(s1[-1]);  // initially, you may believe this cannot work
    assert(s2[-1]);  // see the example output message in project and apply that logic
  }

  void find()
  {
    badString const s1 = "abcdef";
    assert(s1.find('c') == 2);
    assert(s1.find('z') == s1.npos);
  }

  void substr()
  {
    badString const s1 = "abcdef";
    badString s2 = s1.substr(0, 3);
    badString s3 = s1.substr(3, 3);
    assert (s2 == "abc");
    assert (s3 == "def");
  }

  void equality()
  {
    badString const s1 = "hello";
    badString const s2 = "goodbye";
    assert(s1 == s1);
    assert(s1 != s2);
  }

  void ordering()
  {
    badString s1 = "abc";
    badString s2 = "def";
    assert(s1 < s2);
    assert(s2 > s1);
    assert(s1 <= s1);
    assert(s1 >= s1);
  }

  void concatenation()
  {
    badString s1 = "abc";
    badString s2 = "def";
    badString s3 = s1 + s2;
    badString s4 = "abcdef";
    assert(s3 == s4);
  }

  void self_concatenation()
  {
    badString s1 = "abc";
    s1 += s1;
    badString s2 = "abcabc";
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
   str[0] = '\0';
}

badString::~badString()
{
   delete [] str;
   len = 0;
}

badString::badString(const char* input)
{
   assert(input != nullptr);
   std::size_t length = 0;
   for(; input[length] != '\0'; ++length);
   str = new char[length + 1];
   len = length;
   for(std::size_t i = 0; input[i] != '\0'; ++i)
   {
      str[i] = input[i];
   }
   str[len] = '\0';
}

badString::badString(char* input, int index)
{
    std::size_t _len = 0;
    for(; input[_len] != '\0'; ++_len);
    if(input[0] == '\0' || index > _len)
    {
        std::cerr << "Error: String is null, or less than the length passed." << std::endl;
        return;
    }
    //   assert(input[0] != '\0' && input[index]);
   std::size_t i = 0;
   for(; input[i]; ++i);
   str = new char[i];
   for(i = 0; i < index; ++i)
   {
      str[i] = input[i];
   }
   len = i;
   str[len] = '\0';
}

badString::badString(const badString &right)
{
   std::size_t i = 0;
   for(; right.str[i]; ++i);
   str = new char[i];
   for(i = 0; right.str[i] != '\0'; ++i)
   {
      str[i] = right.str[i];
   }
   len = i;
   str[len] = '\0';
}

// Operator Overloads

badString& badString::operator=(const badString &right)
{
   if(this == &right)
   {
       std::cerr << "Avoiding self assignment." << std::endl;
       return *this;
   }
    delete [] str;
   str = new char[right.len];
   for(int i = 0; i < right.len; ++i)
   {
      str[i] = right.str[i];
   }
   len = right.len;
   str[len] = '\0';
   return *this;
}

badString& badString::operator=(const char *input)
{
   delete [] str;
   std::size_t i = 0;
   for(; input[i] != '\0'; ++i);
   str = new char[i];
   for(i = 0; input[i] != '\0'; ++i)
   {
      str[i] = input[i];
   }
   len = i;
   str[len] = '\0';
   return *this;
}

badString badString::operator+(const badString &right)
{
   std::size_t length = len + right.len;
   char* _str = new char[length];
    int i = 0;
   for(; i < len; ++i)
   {
      _str[i] = str[i];
   }
   for(int j = 0; right.str[j] != '\0'; ++j)
   {
      _str[j + i] = right.str[j];
   }
   _str[length] = '\0';
   return badString(_str);
}


badString badString::operator+=(const badString &right)
{
    *this = *this + right;
    return *this;
}

bool badString::operator==(const badString &right) const
{
   if(right.len != len)
   {
       return false;
   }
    for(int i = 0; right.str[i] != '\0'; ++i)
   {
      if(str[i] != right.str[i])
      {
         return false;
      }
   }
   return true;
}

bool badString::operator!=(const badString &right) const
{
   return !(*this == right);
}

bool badString::operator<(const badString &right) const
{
   for(int i = 0; right.str[i] != '\0'; ++i)
   {
      if(str[i] > right.str[i])
      {
         return false;
      }
   }
   return true;
}

bool badString::operator>(const badString &right) const
{
   return !(*this < right);
}

bool badString::operator<=(const badString &right) const
{
   return ((*this < right) || (*this == right));
}

bool badString::operator>=(const badString &right) const
{
   return ((*this > right) || (*this == right));
}

char badString::operator[](const std::size_t index) const
{
    if((index > len - 1) || (index < 0))
    {
        std::cerr << "Error, given index is larger than max size. Defaulting to first space." << std::endl;
        return str[0];
    }
   return str[index];
}

char& badString::operator[](const std::size_t index)
{
   if((index > len - 1) || (index < 0))
   {
       std::cerr << "Error, given index is larger than max size. Defaulting to first space." << std::endl;
       return str[0];
   }
   return str[index];
}

//Member Functions
bool badString::empty() const
{
   return (str[0] == '\0');
}

std::size_t badString::size() const
{
   return len;
}

char const* badString::data()
{
   return str;
}

std::size_t badString::find(char target) const
{
   assert((target < 0) || (target >= len));
   for(std::size_t i = 0; str[i] != '\0'; ++i)
   {
      if(str[i] == target)
      {
         return i;
      }
   }
   return npos;
}

badString badString::substr(int index, int size) const
{
   assert((index >= 0) && (index <= len - 1));
   return badString(str + index, size);
}
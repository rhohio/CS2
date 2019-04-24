/*
   COPYRIGHT (C) 2018 Student Name (kad145) All rights reserved.
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
    char *str;
    std::size_t len = 0;

    //constructors & destructors
    badString();
    ~badString();
    badString(const char *);
    badString(char *, int);
    badString(const badString &);

    //operator overloaders
    badString &operator=(const badString &);
    badString &operator=(const char *);
    badString operator+=(const badString &);
    badString operator+=(const char *);
    badString operator+(const badString &);
    badString operator+(const char *);
    bool operator==(const badString &) const;
    bool operator==(const char *) const;
    bool operator!=(const badString &) const;
    bool operator!=(const char *) const;
    bool operator<(const badString &) const;
    bool operator<(const char *) const;
    bool operator>(const badString &) const;
    bool operator>(const char *) const;
    bool operator<=(const badString &) const;
    bool operator<=(const char *) const;
    bool operator>=(const badString &) const;
    bool operator>=(const char *) const;
    char operator[](const std::size_t) const;
    char &operator[](const std::size_t);

    //member functions
    bool empty() const;
    std::size_t size() const;
    char const *data();
    std::size_t find(char) const;
    badString substr(int, int) const;
};

// Output
std::ostream &operator<<(std::ostream &, badString const &);

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
        char const *str = "hello";
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

//  Pre-Condition: none
// Post-Condition: creates new badString obj w null c str and len 0
badString::badString()
{
    str = new char[1];
    str[0] = '\0';
    len = 0;
}

//  Pre-Condition: badString obj exists
// Post-Condition: deletes ptr to str and sets len to 0
badString::~badString()
{
    delete [] str;
    len = 0;
}

//  Pre-Condition: consturtor given a string or c string
// Post-Condition: Creates badString object w c str input and len size of input
badString::badString(const char *input)
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

//  Pre-Condition: constructor given a string or c str and int index
// Post-Condition: creates badString object given input c str cut off at index index
badString::badString(char *input, int index)
{
    std::size_t _len = 0;
    for(; input[_len] != '\0'; ++_len);
    if(input[0] == '\0' || index > _len)
    {
        std::cerr << "Error: String is null, or less than the length passed." << std::endl;
        return;
    }
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

//  Pre-Condition: given a badString obj w len > 0
// Post-Condition: creates a copy of given badString obj
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

//  Pre-Condition: given badString obj w len > 0 and not the badString itself
// Post-Condition: copies values from given badString to current badString
badString &badString::operator=(const badString &right)
{
    if(this == &right)
    {
        std::cerr << "Avoiding self assignment." << std::endl;
        return *this;
    }
    delete[] str;
    str = new char[right.len];
    for(int i = 0; i < right.len; ++i)
    {
        str[i] = right.str[i];
    }
    len = right.len;
    str[len] = '\0';
    return *this;
}

//  Pre-Condition: given c str
// Post-Condition: assigns c str to badStrign obj
badString &badString::operator=(const char *input)
{
    delete[] str;
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

//  Pre-Condition: given valid badString obj
// Post-Condition: a new badString is returned which is given badstring w current badstring added together
badString badString::operator+(const badString &right)
{
    std::size_t _len = len + right.len;
    char *_str = new char[_len];
    int i = 0;
    for(; i < len; ++i)
    {
        _str[i] = str[i];
    }
    for(int j = 0; right.str[j] != '\0'; ++j)
    {
        _str[j + i] = right.str[j];
    }
    _str[_len] = '\0';
    return badString(_str);
}

//  Pre-Condition: given valid c str
// Post-Condition: adds c str to the end of given badString
badString badString::operator+(const char *input)
{
    std::size_t _len = 0;
    for(; input[_len] != '\0'; ++_len);
    char *_str = new char[_len];
    int i = 0;
    for(; i < len; ++i)
    {
        _str[i] = str[i];
    }
    for(int j = 0; input[j] != '\0'; ++j)
    {
        _str[j + i] = input[i];
    }
    _str[_len] = '\0';
    return badString(_str);
}

//  Pre-Condition: given valid badString obj
// Post-Condition: sets current badStringobj to the addition of current and given
badString badString::operator+=(const badString &right)
{
    *this = *this + right;
    return *this;
}

//  Pre-Condition: given valid c str
// Post-Condition: sets current badString obj to the addition of the current and given c str
badString badString::operator+=(const char *input)
{
    *this = *this + input;
    return *this;
}

//  Pre-Condition: given valid badString obj
// Post-Condition: if both are lexigraphically equal, returns true
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

//  Pre-Condition: given vlaid c str
// Post-Condition: if both are lexigraphically equal, returns true
bool badString::operator==(const char *input) const
{
    int _len = 0;
    for(; input[_len] != '\0'; ++_len);
    if(len != _len)
    {
        return false;
    }
    for(int i = 0; input[i] != '\0'; ++i)
    {
        if(str[i] != input[i])
        {
            return false;
        }
    }
    return true;
}

    /*
     * <COMPARISON OPERATORS>
     *
     * PRE-CONDITIONS:  GIVEN VALID BADSTRING OBJ OR C STR
     * POST-CONDITIONS: RETURNS IT'S LEXIGRAPHICALLY EQUIVALENT COMAPRISON
     *
     */

bool badString::operator!=(const badString &right) const
{
    return !(*this == right);
}

bool badString::operator!=(const char *input) const
{
    return !(*this == input);
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

bool badString::operator<(const char *input) const
{
    for(int i = 0; input[i] != '\0'; ++i)
    {
        if(str[i] > input[i])
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

bool badString::operator>(const char *input) const
{
    return !(*this < input);
}

bool badString::operator<=(const badString &right) const
{
    return ((*this < right) || (*this == right));
}

bool badString::operator<=(const char *input) const
{
    return ((*this < input) || (*this == input));
}

bool badString::operator>=(const badString &right) const
{
    return ((*this > right) || (*this == right));
}

bool badString::operator>=(const char *input) const
{
    return ((*this > input) || (*this == input));
}

    /*
     *</COMPARISON OPERATORS>
     */

//  Pre-Condition: given valid int index that is within range of badString obj
// Post-Condition: returns value badStrings c str at the index
char badString::operator[](const std::size_t index) const
{
    if((index > len - 1) || (index < 0))
    {
        std::cerr << "Error, given index is larger than max size. Defaulting to first space." << std::endl;
        return str[0];
    }
    return str[index];
}

//  Pre-Condition: given valid int index that is within range of badString obj
// Post-Condition: sets indexed value to given value
char &badString::operator[](const std::size_t index)
{
    if((index > len - 1) || (index < 0))
    {
        std::cerr << "Error, given index is larger than max size. Defaulting to first space." << std::endl;
        return str[0];
    }
    return str[index];
}

    /*
     *  <MEMBER_FUNCIONS>
     */

//  Pre-Condition: none
// Post-Condition: returns true if empty
bool badString::empty() const
{
    return (str[0] == '\0');
}

//  Pre-Condition: none
// Post-Condition: returns len
std::size_t badString::size() const
{
    return len;
}

//  Pre-Condition: none
// Post-Condition: returns address of str
char const *badString::data()
{
    return str;
}

//  Pre-Condition: valid char
// Post-Condition: returns index of char
std::size_t badString::find(char target) const
{
    for(std::size_t i = 0; str[i] != '\0'; ++i)
    {
        if(str[i] == target)
        {
            return i;
        }
    }
    return npos;
}

//  Pre-Condition: valid index and size ints
// Post-Condition: returns badString based on its current value at index with size size
badString badString::substr(int index, int size) const
{
    assert((index >= 0) && (index <= len - 1));
    return badString(str + index, size);
}

    /*
     *  </MEMBER_FUNCTIONS>
     */
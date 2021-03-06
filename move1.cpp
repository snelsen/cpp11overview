// move1.cpp

#include <iostream>

using namespace std;

struct Foo
{
      // Constructor
   Foo(int in_x = 0)
         : x(in_x)
   { cout << "Foo::Foo(" << x << ")" << endl; }
   
      // Destructor
   ~Foo()
   { cout << "Foo::~Foo(" << x << ")" << endl; }
   
      // Copy Constructor
   Foo(const Foo& rhs)
         : x(rhs.x)
   { cout << "Foo::Foo(Foo(" << rhs.x << ")&)" << endl; }
   
      // Copy Assignment Operator
   Foo& operator=(const Foo& rhs)
   {
      cout << "Foo::operator=(Foo(" << rhs.x << ")&)" << endl;
      if(this == &rhs)
         return *this;
      x = rhs.x;
      return *this;
   }
   
      // Move Constructor
   Foo(Foo&& rhs)
         : x(move(rhs.x))
   { cout << "Foo::Foo(Foo(" << rhs.x << ")&&)" << endl; }
   
      // Move Assignment Operator
   Foo& operator=(Foo&& rhs)
   {
      cout << "Foo::operator=(Foo(" << rhs.x << ")&&)" << endl;
      if(this == &rhs)
         return *this;
      swap(x, rhs.x);
      return *this;
   }
   
   int x;
};

int main(int argc, char *argv[])
{
   {
      Foo one(1);           // constructor
      cout << "one.x = " << one.x << endl;
      Foo two(one);         // copy constructor
      cout << "one.x = " << one.x << endl
           << "two.x = " << two.x << endl;
      Foo three(Foo(3));    // move constructor
      cout << "three.x = " << three.x << endl;
      Foo four(move(one));  // move constructor
      cout << "one.x = " << one.x << endl
           << "four.x = " << four.x << endl;
      Foo five;             // constructor
      five = four;          // copy assignment operator
   }
   cout << endl;

   {
      Foo six;              // constructor
      cout << "six.x = " << six.x << endl;
      six = Foo(6);         // move assignment operator
      cout << "six.x = " << six.x << endl;
      Foo seven;	          // constructor
      cout << "seven.x = " << seven.x << endl;
      seven = move(six);    // move assignment operator
      cout << "six.x = " << six.x << endl
           << "seven.x = " << seven.x << endl;
   }

   return 0;
}

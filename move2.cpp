// move2.cpp

#include <iostream>
#include <algorithm>
#include <list>

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
   {
      rhs.x = int();
      cout << "Foo::Foo(Foo(" << rhs.x << ")&&)" << endl;
   }
   
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

template <typename C>
void dumpCont(string prefix, C&& c)
{
   cout << prefix;
   for(const auto& f : c)
      cout << f.x << " ";
   cout << endl;
}

int main(int argc, char *argv[])
{
   using Foos = list<Foo>;
   cout << endl << "Creating someFoo" << endl;
   Foos someFoo({ Foo(), Foo(1), Foo(2) });
   cout << endl << "Creating moreFoo" << endl;
   Foos moreFoo = { Foo(3), Foo(4), Foo(5) };
   Foos yetmoreFoo;
   
   cout << endl << "Copying moreFoo into someFoo:" << endl;
   dumpCont("someFoo = ", someFoo);
   dumpCont("moreFoo = ", moreFoo);
   copy(begin(moreFoo), end(moreFoo), back_inserter(someFoo));
   dumpCont("someFoo = ", someFoo);
   dumpCont("moreFoo = ", moreFoo);
   
   cout << endl << "Moving moreFoo into someFoo:" << endl;
   move(begin(moreFoo), end(moreFoo), back_inserter(someFoo));
   dumpCont("someFoo = ", someFoo);
   dumpCont("moreFoo = ", moreFoo);
   
   cout << endl;
   dumpCont("Moving things into yetmoreFoo: ", yetmoreFoo);
   yetmoreFoo.push_back(Foo(6));
   dumpCont("yetmoreFoo = ", yetmoreFoo);
   yetmoreFoo.emplace_back(7);
   dumpCont("yetmoreFoo = ", yetmoreFoo);
   
   cout << endl;
   dumpCont("Moving yetmoreFoo into dumpCont(): ", move(yetmoreFoo));
   dumpCont("yetmoreFoo = ", yetmoreFoo);
   
   return 0;
}

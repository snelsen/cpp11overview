// auto.cpp

#include <iostream>
#include <typeinfo>

int main(int argc, char *argv[])
{
   int j = 3;
   auto x = 200;
   auto y = j + x;
   auto f = 400.2;
   
   std::cout << "int is a " << typeid(int).name() << std::endl
             << "  3 is a " << typeid(3).name() << std::endl
             << "  j is a " << typeid(j).name() << std::endl
             << "  x is a " << typeid(x).name() << std::endl
             << "  y is a " << typeid(y).name() << std::endl
             << "  f is a " << typeid(f).name() << std::endl;
   
   return 0;
}

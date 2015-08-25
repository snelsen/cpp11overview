// decltype.cpp

#include <iostream>
#include <typeinfo>
#include <vector>

using namespace std;

template<typename Container, typename Index>
auto audibleAccess(Container& c, Index i) -> decltype(c[i])
{
   cout << "Retrieving item " << i << endl;
   return c[i];
}

int main(int argc, char *argv[])
{
//   typedef vector<int> IntVector;
   using IntVector = vector<int>;
   IntVector aVector = {4, 6, 10, 3002};
   auto foo = audibleAccess(aVector, 3);
   
   cout << "foo is a " << typeid(foo).name() << " and is " << foo << endl;
   
   return 0;
}

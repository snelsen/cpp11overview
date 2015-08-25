// lambda.cpp

#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>

using namespace std;

using IntList = list<int>;

void dumpList(const IntList& l)
{
   for(auto i : l)
      cout << i << " ";
   cout << endl;
}

template<typename C, typename L>
void someFunction(const C& c, L& l)
{
   cout << "someFunction: " << endl;
   IntList cList;
   copy_if(begin(c), end(c), back_inserter(cList), l);
   cout << "cList: ";
   dumpList(cList);
}

int main(int argc, char *argv[])
{
   IntList aList = {4,5,6,7,8,9,10};
   IntList bList;
   int minval = 7;
   
   copy_if(begin(aList), end(aList), back_inserter(bList),
           [minval](int val)
           {
              cout << "Checking " << val << " ... is <= " << minval << "? "
                   << (val <= minval ? "YES" : "NO") << endl;
              return val <= minval; 
           });
   
   cout << "aList: ";
   dumpList(aList);
   cout << "bList: ";
   dumpList(bList);
   
   auto lamb = [minval](int val)
      {
         cout << "Checking " << val << " ... is > " << minval << "? "
         << (val > minval ? "YES" : "NO") << endl;
         return val > minval; 
      };
   
   someFunction(aList, lamb);
   
   return 0;
}

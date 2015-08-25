// pointers.cpp

#include <iostream>
#include <memory>

using namespace std;

// make_unique<T> is not available in C++11, so here's something like it.
template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params)
{
   return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

struct Foo
{
   Foo(int in_x=0)
         : x(in_x)
   { cout << "Foo(" << x << ")" << endl; }
   ~Foo()
   { cout << "~Foo(" << x << ")" << endl; }
   Foo(const Foo& rhs) = default;
   Foo(Foo&& rhs) = default;
   Foo& operator=(const Foo& rhs) = default;
   Foo& operator=(Foo&& rhs) = default;

   int x;
};

template<typename T>
void printDeref(T t)
{
   cout << "t.x = " << t->x << endl;
}

int main(int argc, char *argv[])
{
   cout << endl << "*** Working with shared_ptr" << endl;
   {
      unique_ptr<Foo> upf(new Foo(1));
      auto bar = make_unique<Foo>(4);
      printDeref(move(bar));
      cout << "back from printDeref()" << endl;
   }
   
   cout << endl << "*** Working with shared_ptr" << endl;
   shared_ptr<Foo> spf(new Foo(1));
   {
      auto spf2 = spf;
      auto bar = make_shared<Foo>(4);

      printDeref(bar);
      cout << "back from printDeref()" << endl;
      printDeref(move(bar));
      cout << "back from printDeref()" << endl;
      printDeref(spf2);
      cout << "back from printDeref()" << endl;
      printDeref(move(spf2));
      cout << "back from printDeref()" << endl;
   }

   cout << endl << "*** Working with weak_ptr" << endl;
   weak_ptr<Foo> wpf(spf);
   
   cout << "wpf.use_count() = " << wpf.use_count() << endl;
   spf.reset();
   cout << "wpf.use_count() = " << wpf.use_count() << endl
        << "wpf.expired()   = " << wpf.expired() << endl
        << endl;

   return 0;
}

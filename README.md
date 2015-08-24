# cpp11overview
Overview of C++11

## auto and decltype
Use auto to have the compiler deduce the type of a variable for you.

`  auto someVar = someFunction();`

### `auto`'s type deduction rules

### `decltype`'s type deduction rules


## R-value References and Move Semantics
L-values and their references are given this name because they are found on the *left* side of the '=' sign.  They have names and can be used as arguments to functions.

R-values and their references are found on the *right* side of the '=' sign and don't have names.  They are used to initialize l-values and are destructed at the end of the statement in which they are found.

C++11 introduced the ability to differentiate between the two types of values and references: 
* l-value reference:  `int&`
* r-value reference:  `int&&`

This ability to know when an argument is an r-value reference allows the programmer to optimize the acquisition of data within an argument.  Instead of copying the data from a provided argument, the programmer can more efficiently *move* the data out of the argument and into its own storage.  The type of the argument must support move construction and move assignment, however.  The built-in types already support move mechanics, and it is simple to add them to custom classes.
* Move Constructor: `Foo(Foo&& rhs);`
* Move Assignment: `Foo& operator=(Foo&& rhs);`

### Special Member Function Generation
If needed, but not written, the compiler will generate:
* a default constructor: `Foo();` - when no other constructors are defined
* a destructor: `~Foo();` - 
* a copy constructor: `Foo(const Foo& rhs);`
* a copy assignment operator: `Foo& operator=(const Foo& rhs);`
You may have heard of "The Rule of Three."  It is a reminder that if you define one of these three: the destructor, copy constructor, or copy assignment operator, then you should define all three.  This is to properly handle copy or destruction of a particular resource (i.e. a file-handle).

C++11 adds two more:
* a move constructor: `Foo(Foo&& rhs);`
* a move assignment operator: `Foo& operator=(Foo&& rhs);`

Defining either either of the copy operations (or the destructor) will prevent automatic generation of the move operations.  The converse is also true.  Again, this is because if you need to handle the management of a resource for either a copy or move operation, then you have to handle it for the other.
If, for example, you define the destructor because it is intended to be a base class, you can use the `default` keyword to signify that the default generated functions for copy and move will do: `Foo(Foo&& rhs) = default;`

## Lambdas


## Smart Pointers
### unique_ptr
Exclusive-ownership resource management
`auto upf = unique_ptr<Foo>(new Foo());`
This class will handle deletion of the Foo pointer when it goes out of scope.  By default, it calls `delete` on the pointer, but if needed, you can pass in a function object that it will use instead.
`auto delFoo = ...
auto upf = unique_ptr<Foo, decltype(delFoo)>(new Foo());`

### shared_ptr
Shared-ownership resource management
shared_ptr uses a reference-count mechanic to know how many copies of the pointer have been created, and when to delete the pointer that it owns.  It also has the ability to specify a custom deletion function, however the function is *not* part of its type.
`auto spf = shared_ptr<Foo>(new Foo(), delFoo);`
This allows objects of the same type to have different deletion functions.

### weak_ptr
`weak_ptr` objects are generated from `shared_ptr` objects, and are effectively `shared_ptr` objects that can "dangle". They use a separate counter; therefore, don't *own* the pointer, so it could be deleted from underneath them.  Use `weak_ptr`'s `expired()` function to check if the pointer has been deleted, or `lock()` to generate a `shared_ptr` which can be used safely.
One use of `weak_ptr` is for a child object to have access to its parent without creating a circular reference as would result from use of a `shared_ptr`.

### Use `make_shared()` and `make_unique()` instead of `new`
This prevents memory leaks in case the program is interrupted between the call to `new` and passing the pointer to the constructor for `shared_ptr` or `unique_ptr`.
`make_unique` is only in C++14, but is trivial to write:
`
template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params)
{
   return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}
`
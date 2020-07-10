# Modern C++ Sparse Container

a header only C++11 sparse template container. Sparse container interface looks like other C++ standard template containers such as std::vector. However in a sparse container only the effective values will be stored. So it is a great replacement for std::vector where the sparsity of the container is greather than 0.5 

## What is a Sparse Matrix/Array?

In numerical analysis and scientific computing, a sparse matrix or sparse array is a matrix in which most of the elements are zero(or any other default value). The number of zero-valued(default-valued) elements divided by the total number of elements (e.g., m × n for an m × n matrix) is called the sparsity of the matrix (which is equal to 1 minus the density of the matrix). Using those definitions, a matrix will be sparse when its sparsity is greater than 0.5.

## Getting Started

It is a header only single .hpp file. Just copy it into your project include directory and try to include it in any translation unit.

```cxx
#include <sparse.hpp>
```

### Prerequisites

This file only use C++11 standard features. So make sure you are using an up-to-date compiler with at least c++11 support.


### How to use?

#### Constructor

To Construct an object of the sparse container of integers with size 1000: 

```cxx
sparse<int> sp(100);
```

In the above example of calling constructor the default value of the sparse container is provided by the default constructor of type int. so with the above call the type should provide a default constructor.
Either you just want to define a custom default value for the sparse container or you are using the container with a template argument that does not support a default constructor you should provide the default value by passing a second or more arument to the constructor either by passing an arbitary argument number of the type constructor or just a lvalue or rvalue of an object of the type.

```cxx
sparse<std::string> sp(100, std::string("No Value"));
```

or in a better approach:

```cxx
sparse<std::string> sp(100, "No Value");
```
#### Basic Usage
The object can be use in a way very similar to other standard C++ containers such as std::vector as bellow:

```cxx
sp[0] = 0;
sp[10] = 1;
sp[20] = sp[1] * 2;
sp[30] = sp[2] + sp[1];

int x = sp[50];
x += 5;
sp[50] = x;
std::cout << sp[50] << std::endl;
```

The container use a proxy in the return type of operator[] overload (just like std::vector<bool>)
So it is not possible to capture a non-const refrence to the the underlying type:

```cxx
int& rx = sp[10];         // it won't compile!
const int& crx = sp[10];  // it does compile
```

To have a mutable reference to the underlying type you should have the proxy type either by explicitly define the proxy type variable or just using auto keyword:

```cxx
sparse<int>::reference r1 = sp[50];   // This proxy type is just act as a int&
auto r2 = sp[60];                     // The proxy type will deduce by the compiler

r1 = 5;
r2 = r1;
r2 = 6;
```

#### Iterators

The container support iterators(begin, end, rbegin, rend, cbegin, cend, crbegin, crend) just like any other STL containers.

```cxx
sparse<int>::const_iterator iter = sp.cbegin();
auto end_iter = sp.cend();

while (iter++ != end_iter)
    std::cout << *iter << std::endl;
```

The sparse container also support ranged-base loop:
```cxx
for (int x : sp)
    std::cout << x << std::endl;
```

The sparse container iterators can be used in conjunction with standard algorithms:
```cxx
std::accumulate(sp.begin(), sp.end(), 0);	
```

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/Arzaghi/sparse/tags). 

## Authors

* **[Hamid Reza Arzaghi](https://github.com/Arzaghi)**

<!-- See also the list of [contributors](https://github.com/Arzaghi/sparse/contributors) who participated in this project. -->

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details


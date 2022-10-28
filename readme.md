## How to build
  - `cd <cloned-directory>`
  - `mkdir build`
  - `make -j$(nproc)`

# containers-lib
Modern C++ implementation of widely used containers
## List<T>
  - List<T> is a linear container header for C++ which uses the linked list data structure to internally manage the nodes
  - Since it is a generic class hence can support the storage of primitive and user defined types
  - it has implementation for several useful functions which are as follows:
    - `Iterator begin() const { return Iterator(startNode); }`
    - `Iterator end() const { return Iterator(nullptr); }`
    - `uint length() const { return this->size; }`
    - `void append(T dataItem);`
    - `void insert(T item,ulong index=0);`
    - `T& at (ulong index) const;`
    - `void erase(ulong index);`
    - `void erase(Iterator& indexIt);`
    - `T popFront();`
    - `T popBack();`
    - `Iterator& find(T dataItem);`
    - `bool contains(T dataItem);`
    - `uint count(bool(*pred)(T& dataItem));`
    - `uint count(std::function<bool(T& dataItem)>&&);`
    - `void sort(bool desc=false);`
    - `List<T>* extractFor(std::function<bool(T& dataItem)>&&);`
    - `List<T>* extractFor(std::function<bool(T& dataItem)>&&,uint);`
  - It is evident from the above mentioned text that we have tried to implement the iterator style list,
    so that basic modern C++ constructs can be supprted. e.g the range based for loop etc.

## Matrix
  - This is a container which stores data in form of matrices, while internally manages memory as dynamically allocated arrays
  - This container aims to provide all basic functionality for matrix operations and make its data easy to access
  - Since matrix class manages memory with raw pointers hence memory management is tested thoroughly, and before any commit the code is tested with valgrind.
  - Following methods have been implemented:
    - `type& operator() (size_t _i, size_t _j)`
    - `bool operator== (const matrix& _mat)`
    - `matrix& operator= (matrix&& _mat)`
    - `const type* get_data() const`
    - `bool is_square_matrix() const`
    - `size_t row_size() const`
    - `size_t col_size() const`
    - `size_t size() const`
    - `void resize(size_t _newrows, size_t _newcols, bool _preserve = true)`

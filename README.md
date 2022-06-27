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

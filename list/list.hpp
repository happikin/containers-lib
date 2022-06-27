#include <thread>
#include <functional>

using ulong = unsigned long;
using uint = unsigned int;

template <typename T>
class List {
    public:

        struct Node {
            T data;
            Node* nextNode;
        };

        class Iterator {
            private:
                Node* pointer;
            public:
                Iterator() = default;
                Iterator(Node* ptr) : pointer(ptr) {}

                void operator=(const Iterator& it) {
                    this->pointer = it.pointer;
                }
                bool operator!=(const Iterator& it) {
                    return this->pointer != it.pointer;
                }
                void operator++(int) {
                    this->pointer = this->pointer->nextNode;
                }
                void operator++() {
                    this->pointer = this->pointer->nextNode;
                }
                T& operator*() {
                    return pointer->data;
                }
                Node* thisNode() const { return this->pointer; }
                Node* nextNode() const { return this->pointer->nextNode; }
                void destroyInnerPtr() { delete this->pointer; this->pointer = nullptr; }
                //~Iterator() { this->destroyInnerPtr(); }
        };

    public:

        List(bool setSorted=false) : size(0), isSorted(setSorted) {
            startNode = endNode = nullptr;
        }
        List(std::initializer_list<T>&& ilist, bool setSorted=false) : List(setSorted) {
            if(!isSorted) {
                for(auto& item:ilist) {
                    this->append(item);
                }
            } else {

            }
        }
        List(List<T>* inlist, bool setSorted=false) : List(setSorted) {
            for(auto& item:*inlist)
                this->append(item);
            delete inlist;
        }
        // void operator=(const List<T>& list) {
        //     for(ulong i=0;i<list.length();i++) {
        //         this->append(list.at(i));
        //     }
        // }
        void operator=(const List<T>* list) {
            for(ulong i=0;i<list->length();i++) {
                this->append(list->at(i));
            } delete list;
        }
        ~List() {
            while(startNode != nullptr) {
                Node* node = startNode;
                startNode = startNode->nextNode;
                delete node;
            }
            //this->monitor->join();
            //delete this->monitor;
        }

        Iterator begin() const { return Iterator(startNode); }
        Iterator end() const { return Iterator(nullptr); }
        uint length() const { return this->size; }

        /**
         * append() will insert a dataItem at the end of the list only
        */
        void append(T dataItem);
        
        /**
         * insert() will insert the specified data at the specified index
         * by default it will insert at the start
        */
        void insert(T item,ulong index=0);
        
        /**
         * at() will return a read/write reference to the element at the specified index
        */
        T& at (ulong index) const;
        
        /**
         * erase() will take the index of the element in the list which we want to remove
        */
        void erase(ulong index);

        /**
         * erase() will take the `iterator` of the element in the list which we want to remove
        */
        void erase(Iterator& indexIt);

        /**
         * popFront() will remove the first node in the list
        */
        T popFront();

        /**
         * popBack() will remove the last node in the list
        */
        T popBack();

        /**
         * find() will accept the value and will return the iterator to that element in this list
         * if that element does not exist in this list then will return a nullptr Iterator
        */
        Iterator& find(T dataItem);

        /**
         * contains() will return true if the given element exists in the list else will return false
        */
        bool contains(T dataItem);

        /**
         * count() will take a predicate and will execute for each dataItem in the list
         * and will return the total number of times the predicate returned true
        */
        uint count(bool(*pred)(T& dataItem));
        uint count(std::function<bool(T& dataItem)>&&);

        /**
         * This overloaded ' + ' operator will merge two lists into one
        */
        List<T>* operator+(const List<T>& inlist);
        //List<T> operator+(const List<T>& inlist);

        /**
         * sort() uses bubble sort to sort the list in ascending order
        */
        void sort(bool desc=false);

        /**
         * extractFor() will check if the result of predicate is true for each element
         * then return a new List<> for all true predicate
        */
        List<T>* extractFor(std::function<bool(T& dataItem)>&&);
        List<T>* extractFor(std::function<bool(T& dataItem)>&&,uint);

    private:
        Node* startNode;
        Node* endNode;
        uint size;
        bool isSorted;
};

template<typename T>
void List<T>::append(T dataItem) {
    Node* temp = new Node;
    temp->data = dataItem;
    temp->nextNode = nullptr;
    if(startNode == nullptr) {
        // std::cout << "List is empty...\n";
        startNode = temp;
        endNode = startNode;
        temp = nullptr;
    } else {
        // std::cout << "List has items...\n";
        endNode->nextNode = temp;
        endNode = endNode->nextNode;
        temp = nullptr;
    }
    size++;
}

template <typename T>
void List<T>::insert(T dataItem, ulong index) {
    if(startNode == nullptr) {
        if(index != 0) {
            throw "Cannot insert at non zero index in empty list!";
        }
        this->append(dataItem);
    } else {
        if(index >= this->size) {
            throw "IndexOutOfBoundsException";
        }
        Node* node = new Node;
        node->data = dataItem;


        if(index == 0) {
            node->nextNode = startNode;
            startNode = node;
            size++;
        } else {
            Node* targetNode = startNode;
            Node* prevNode = targetNode;
            for(uint i=0;i<index;i++) {
                prevNode = targetNode;
                targetNode = targetNode->nextNode;
                // if(targetNode == nullptr) {
                //     throw "IndexOutOfBoundsException";
                // }
            }
            node->nextNode = targetNode;
            prevNode->nextNode = node;
            size++;
        }

        node = nullptr;
    }
}

template <typename T>
T& List<T>::at(ulong index) const {
    Iterator it(startNode);
    for(ulong i=0;i<index;i++) {
        it++;
    } return *it;
}

template <typename T>
void List<T>::erase(ulong index) {
    if(index >= this->size) {
        throw "IndexOutOfBounds";
    } else if(index == 0) {
        this->popFront();
    } else {
        Node *prevNode, *targetNode = startNode;
        for(ulong i=0;i<index;i++) { prevNode = targetNode; targetNode = targetNode->nextNode; }
        prevNode->nextNode = targetNode->nextNode;
        delete targetNode;
        this->size--;
    }
}

template <typename T>
void List<T>::erase(Iterator& indexIt) {
    if(indexIt.thisNode() == nullptr) return;
    Node* prevNode = startNode;
    while(prevNode->nextNode != indexIt.thisNode())
        prevNode = prevNode->nextNode;
    prevNode->nextNode = indexIt.nextNode();
    indexIt.destroyInnerPtr();
    indexIt.~Iterator();
    this->size--;
}

template <typename T>
T List<T>::popFront() {
    if(this->startNode != nullptr) {
        Node* targetNode = startNode;
        T data = targetNode->data;
        startNode = startNode->nextNode;
        delete targetNode;
        this->size--;
        return data;
    } return T{};
}

template <typename T>
T  List<T>::popBack() {
    if(length() >= 2) {
        Node* targetNode = startNode;
        while(targetNode->nextNode->nextNode != nullptr) {
            targetNode = targetNode->nextNode;
        } T data = targetNode->nextNode->data;
        delete targetNode->nextNode;
        targetNode->nextNode = nullptr;
        this->size--;
        return data;
    } else {
        return this->popFront();
    }
}

template <typename T>
List<T>* List<T>::operator+(const List<T>& inlist) {
    // needs a lot of improvement
    List<T> *list=new List<T>;
    for(auto& item:*this) {
        list->append(item);
    }    
    for(T& item:inlist) {
        list->append(item);
    } return list;
}

// template <typename T>
// List<T> List<T>::operator+(const List<T>& inlist) {
//     // needs a lot of improvement
//     List<T> list;
//     for(auto& item:*this) {
//         list.append(item);
//     }    
//     for(T& item:inlist) {
//         list.append(item);
//     } return list;
// }

template <typename T>
void List<T>::sort(bool desc) {
    for( ulong i=0; i < this->size; i++ ) {
        for( ulong j=0; j < this->size-1; j++ ) {
            if(desc) {
                if(this->at(j) <= this->at(j+1)) {
                    T temp = this->at(j);
                    this->at(j) = this->at(j+1);
                    this->at(j+1) = temp;
                }
            } else {
                if(this->at(j) >= this->at(j+1)) {
                    T temp = this->at(j);
                    this->at(j) = this->at(j+1);
                    this->at(j+1) = temp;
                }
            }
        }
    }
}

template <typename T>
uint List<T>::count(std::function<bool(T& dataItem)>&& predicate) {
    std::cout << "using std::functional\n";
    uint count{0};
    for(T& item:*this) {
        (predicate(item) ? count++ : count=count);
    } return count;
}

template <typename T>
uint List<T>::count(bool(*predicate)(T& dataItem)) {
    std::cout << "using function pointer\n";
    return this->count(std::function<bool(T& dataItem)>(predicate));
}

template <typename T>
List<T>* List<T>::extractFor(std::function<bool(T& dataItem)>&& predicate) {
    List<T>* list = new List<T>;
    for(auto& item:*this) {
        if(predicate(item)) {
            list->append(item);
        }
    } return list;
}

template <typename T>
List<T>* List<T>::extractFor(std::function<bool(T& dataItem)>&& predicate, uint limit) {
    List<T>* list = new List<T>; uint i{0};
    for(auto& item:*this) {
        if(i >= limit) break;
        if(predicate(item)) {
            list->append(item);
        } i++;
    } return list;
}
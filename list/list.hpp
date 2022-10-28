#include <thread>
#include <functional>
namespace ycontainer {
    
    using ulong = unsigned long;
    using uint = unsigned int;

    template <typename type>
    class list {
        public:

            struct node {
                type data;
                node* next_node;
            };

            class iterator {
                private:
                    node* pointer;
                public:
                    iterator() = default;
                    iterator(node* ptr) : pointer(ptr) {}

                    void operator=(const iterator& it) {
                        this->pointer = it.pointer;
                    }
                    bool operator!=(const iterator& it) {
                        return this->pointer != it.pointer;
                    }
                    void operator++(int) {
                        this->pointer = this->pointer->next_node;
                    }
                    void operator++() {
                        this->pointer = this->pointer->next_node;
                    }
                    type& operator*() {
                        return pointer->data;
                    }
                    node* thisnode() const { return this->pointer; }
                    node* next_node() const { return this->pointer->next_node; }
                    void destroy_inner_pointer() { delete this->pointer; this->pointer = nullptr; }
            };

        public:

            list(bool _set_sorted=false) : size(0), m_sorted(_set_sorted) {
                startnode = endnode = nullptr;
            }
            list(std::initializer_list<type>&& ilist, bool _set_sorted=false) : list(_set_sorted) {
                if(!m_sorted) {
                    for(auto& item:ilist) {
                        this->append(item);
                    }
                } else {

                }
            }
            list(list<type>* inlist, bool _set_sorted=false) : list(_set_sorted) {
                for(auto& item:*inlist)
                    this->append(item);
                delete inlist;
            }
            // void operator=(const list<type>& list) {
            //     for(ulong i=0;i<list.length();i++) {
            //         this->append(list.at(i));
            //     }
            // }
            void operator=(const list<type>* list) {
                for(ulong i=0;i<list->length();i++) {
                    this->append(list->at(i));
                } delete list;
            }
            ~list() {
                while(startnode != nullptr) {
                    node* node = startnode;
                    startnode = startnode->next_node;
                    delete node;
                }
            }

            iterator begin() const { return iterator(startnode); }
            iterator end() const { return iterator(nullptr); }
            uint length() const { return this->size; }

            /**
             * append() will insert a dataItem at the end of the list only
            */
            void append(type dataItem);
            
            /**
             * insert() will insert the specified data at the specified index
             * by default it will insert at the start
            */
            void insert(type item,ulong index=0);
            
            /**
             * at() will return a read/write reference to the element at the specified index
            */
            type& at(ulong index) const;
            
            /**
             * erase() will take the index of the element in the list which we want to remove
            */
            void erase(ulong index);

            /**
             * erase() will take the `iterator` of the element in the list which we want to remove
            */
            void erase(iterator& indexIt);

            /**
             * pop_front() will remove the first node in the list
            */
            type pop_front();

            /**
             * pop_back() will remove the last node in the list
            */
            type pop_back();

            /**
             * find() will accept the value and will return the iterator to that element in this list
             * if that element does not exist in this list then will return a nullptr iterator
            */
            iterator& find(type dataItem);

            /**
             * contains() will return true if the given element exists in the list else will return false
            */
            bool contains(type dataItem);

            /**
             * count() will take a predicate and will execute for each dataItem in the list
             * and will return the total number of times the predicate returned true
            */
            uint count(bool(*pred)(type& dataItem));
            uint count(std::function<bool(type& dataItem)>&&);

            /**
             * This overloaded ' + ' operator will merge two lists into one
            */
            list<type>* operator+(const list<type>& inlist);
            //list<type> operator+(const list<type>& inlist);

            /**
             * sort() uses bubble sort to sort the list in ascending order
            */
            void sort(bool desc=false);

            /**
             * extract_for() will check if the result of predicate is true for each element
             * then return a new list<> for all true predicate
            */
            list<type>* extract_for(std::function<bool(type& dataItem)>&&);
            list<type>* extract_for(std::function<bool(type& dataItem)>&&,uint);

        private:
            node* startnode;
            node* endnode;
            uint size;
            bool m_sorted;
    };

    template<typename type>
    void list<type>::append(type dataItem) {
        node* temp = new node;
        temp->data = dataItem;
        temp->next_node = nullptr;
        if(startnode == nullptr) {
            // std::cout << "list is empty...\n";
            startnode = temp;
            endnode = startnode;
            temp = nullptr;
        } else {
            // std::cout << "list has items...\n";
            endnode->next_node = temp;
            endnode = endnode->next_node;
            temp = nullptr;
        }
        size++;
    }

    template <typename type>
    void list<type>::insert(type dataItem, ulong index) {
        if(startnode == nullptr) {
            if(index != 0) {
                throw "Cannot insert at non zero index in empty list!";
            }
            this->append(dataItem);
        } else {
            if(index >= this->size) {
                throw "IndexOutOfBoundsException";
            }
            node* l_node = new node;
            l_node->data = dataItem;


            if(index == 0) {
                l_node->next_node = startnode;
                startnode = l_node;
                size++;
            } else {
                node* targetnode = startnode;
                node* prevnode = targetnode;
                for(uint i=0;i<index;i++) {
                    prevnode = targetnode;
                    targetnode = targetnode->next_node;
                    // if(targetnode == nullptr) {
                    //     throw "IndexOutOfBoundsException";
                    // }
                }
                l_node->next_node = targetnode;
                prevnode->next_node = l_node;
                size++;
            }

            l_node = nullptr;
        }
    }

    template <typename type>
    type& list<type>::at(ulong index) const {
        iterator it(startnode);
        for(ulong i=0;i<index;i++) {
            it++;
        } return *it;
    }

    template <typename type>
    void list<type>::erase(ulong index) {
        if(index >= this->size) {
            throw "IndexOutOfBounds";
        } else if(index == 0) {
            this->pop_front();
        } else {
            node *prevnode, *targetnode = startnode;
            for(ulong i=0;i<index;i++) { prevnode = targetnode; targetnode = targetnode->next_node; }
            prevnode->next_node = targetnode->next_node;
            delete targetnode;
            this->size--;
        }
    }

    template <typename type>
    void list<type>::erase(iterator& indexIt) {
        if(indexIt.thisnode() == nullptr) return;
        node* prevnode = startnode;
        while(prevnode->next_node != indexIt.thisnode())
            prevnode = prevnode->next_node;
        prevnode->next_node = indexIt.next_node();
        indexIt.destroy_inner_pointer();
        indexIt.~iterator();
        this->size--;
    }

    template <typename type>
    type list<type>::pop_front() {
        if(this->startnode != nullptr) {
            node* targetnode = startnode;
            type data = targetnode->data;
            startnode = startnode->next_node;
            delete targetnode;
            this->size--;
            return data;
        } return type{};
    }

    template <typename type>
    type  list<type>::pop_back() {
        if(length() >= 2) {
            node* targetnode = startnode;
            while(targetnode->next_node->next_node != nullptr) {
                targetnode = targetnode->next_node;
            } type data = targetnode->next_node->data;
            delete targetnode->next_node;
            targetnode->next_node = nullptr;
            this->size--;
            return data;
        } else {
            return this->pop_front();
        }
    }

    template <typename type>
    list<type>* list<type>::operator+(const list<type>& inlist) {
        // needs a lot of improvement
        list<type> *list_var=new list<type>;
        for(auto& item:*this) {
            list_var->append(item);
        }    
        for(type& item:inlist) {
            list_var->append(item);
        } return list_var;
    }

    // template <typename T>
    // list<type> list<type>::operator+(const list<type>& inlist) {
    //     // needs a lot of improvement
    //     list<type> list;
    //     for(auto& item:*this) {
    //         list.append(item);
    //     }    
    //     for(T& item:inlist) {
    //         list.append(item);
    //     } return list;
    // }

    template <typename type>
    void list<type>::sort(bool desc) {
        for( ulong i=0; i < this->size; i++ ) {
            for( ulong j=0; j < this->size-1; j++ ) {
                if(desc) {
                    if(this->at(j) <= this->at(j+1)) {
                        type temp = this->at(j);
                        this->at(j) = this->at(j+1);
                        this->at(j+1) = temp;
                    }
                } else {
                    if(this->at(j) >= this->at(j+1)) {
                        type temp = this->at(j);
                        this->at(j) = this->at(j+1);
                        this->at(j+1) = temp;
                    }
                }
            }
        }
    }

    template <typename type>
    uint list<type>::count(std::function<bool(type& dataItem)>&& predicate) {
        // std::cout << "using std::functional\n";
        uint count{0};
        for(type& item:*this) {
            (predicate(item) ? count++ : count=count);
        } return count;
    }

    template <typename type>
    uint list<type>::count(bool(*predicate)(type& dataItem)) {
        // std::cout << "using function pointer\n";
        return this->count(std::function<bool(type& dataItem)>(predicate));
    }

    template <typename type>
    list<type>* list<type>::extract_for(std::function<bool(type& dataItem)>&& predicate) {
        list<type>* list_var = new list<type>;
        for(auto& item:*this) {
            if(predicate(item)) {
                list_var->append(item);
            }
        } return list_var;
    }

    template <typename type>
    list<type>* list<type>::extract_for(std::function<bool(type& dataItem)>&& predicate, uint limit) {
        list<type>* list_var = new list<type>; uint i{0};
        for(auto& item:*this) {
            if(i >= limit) break;
            if(predicate(item)) {
                list_var->append(item);
            } i++;
        } return list_var;
    }
} // namespace container

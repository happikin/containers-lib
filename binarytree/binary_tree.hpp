/**
 * end goal is to implement a container called " ntree<type> "
 * which will have n number of direct children possible
*/

#ifdef DEBUG_MODE
    #include <iostream>
#endif
#include <list.hpp>

#define isnull_macro(item) (item == nullptr)
#define notnull_macro(item) (item != nullptr)

namespace ycontainer {
    
    using size_t = unsigned long;
    
    enum traversal_e {
        default_order = 0,
        inorder,
        preorder,
        postorder
    };
    
    template <typename type>
    class binary_tree;

    namespace util {

        template <typename type>
        void mirror(ycontainer::binary_tree<type>& _in) {
            std::function<void(struct ycontainer::binary_tree<type>::node*)> local_mirror
                = [&](struct ycontainer::binary_tree<type>::node* _node){
                    if(isnull_macro(_node)) return;
                    if(isnull_macro(_node->left_node) && isnull_macro(_node->right_node))
                        return;
                    
                    local_mirror(_node->left_node);
                    local_mirror(_node->right_node);

                    decltype(_node) node_ptr = _node->left_node;
                    _node->left_node = _node->right_node;
                    _node->right_node = node_ptr;
                };
            local_mirror(_in.m_root);
        }

        template <typename type>
        void print(ycontainer::binary_tree<type>& _in, const traversal_e _traversal) {
            /**
             * @brief this print function uses recirsion to print
             * but will be soon transformed to use simple non-recursive logic
            */
            switch(_traversal) {
                case traversal_e::inorder: {
                    std::function<void(const struct ycontainer::binary_tree<type>::node*)> local_print
                        = [&](const struct ycontainer::binary_tree<type>::node* _node){
                        if(isnull_macro(_node)) return;
                        local_print(_node->left_node);
                        std::cout << _node->data << "\n";
                        local_print(_node->right_node);
                    };

                    local_print(_in.m_root);
                } break;
                case traversal_e::preorder: {
                    std::function<void(const struct ycontainer::binary_tree<type>::node*)> local_print
                        = [&](const struct ycontainer::binary_tree<type>::node* _node){
                        if(isnull_macro(_node)) return;
                        std::cout << _node->data << "\n";
                        local_print(_node->left_node);
                        local_print(_node->right_node);
                    };

                    local_print(_in.m_root);
                } break;
                case traversal_e::postorder: {
                    std::function<void(const struct ycontainer::binary_tree<type>::node*)> local_print
                        = [&](const struct ycontainer::binary_tree<type>::node* _node){
                        if(isnull_macro(_node)) return;
                        local_print(_node->left_node);
                        local_print(_node->right_node);
                        std::cout << _node->data << "\n";
                    };

                    local_print(_in.m_root);
                } break;
                default: {
                    throw std::invalid_argument("only inorder, preorder or postorder allowed");
                }
            }
        }
    
    }


    template <typename type>
    class binary_tree {

        public:
            template <typename type_1>
            friend void ycontainer::util::print(
                ycontainer::binary_tree<type_1>& _in,
                const traversal_e _traversal);
            
            template <typename type_1>
            friend void ycontainer::util::mirror(
                ycontainer::binary_tree<type_1>& _in);

            struct node {
                node* left_node;
                type data;
                node* right_node;
            };

            binary_tree(traversal_e _insertiontype = traversal_e::default_order)
            :   m_root(nullptr), m_height(0),
                m_node_count(0), m_insertion_type(_insertiontype) { }

            void insert(type);
            type* flatten();
            node* find(type);
            void erase(type _dataitem);
            // ~binary_tree();

        private: /* data fields */
            node* m_root;
            size_t m_height;
            size_t m_node_count;
            traversal_e m_insertion_type;
            // ycontainer::list<node*> m_addressbook;

        private: /* internal member functions */
            void default_insert(type);
            void inorder_insert(type);
            void preorder_insert(type);
            void postorder_insert(type);

            // node* malloc_node();
            // void free_node(node* _node_address);

    };

    // template <typename type>
    // typename ycontainer::binary_tree<type>::node* binary_tree<type>::malloc_node() {
    //     node* tmp_node = new node;
    //     m_addressbook.append(tmp_node);
    //     return tmp_node;
    // }

    // template <typename type>
    // void binary_tree<type>::free_node(node* _node_address) {
    //     auto tmp_node = m_addressbook.find(_node_address);
    //     if((*tmp_node) != nullptr) {
    //         m_addressbook.erase(tmp_node);
    //     }
    // }

    template <typename type>
    void binary_tree<type>::insert(type _dataitem) {
        switch(m_insertion_type) {
            case traversal_e::default_order: {
                default_insert(_dataitem);
            } break;

            case traversal_e::inorder: {
                std::cout << "inorder to be implemented\n";
            } break;
            case traversal_e::preorder: {
                std::cout << "preorder to be implemented\n";
            } break;
            case traversal_e::postorder: {
                std::cout << "postorder to be implemented\n";

            } break;

            default: {}
        }
    }

    template <typename type>
    void binary_tree<type>::default_insert(type _dataitem) {
        if(m_root == nullptr) {
            node *tmp = new node();
            tmp->data = _dataitem;
            tmp->left_node = nullptr;
            tmp->right_node = nullptr;
            m_root = tmp;
            tmp = nullptr;
        } else {
            node *tmp = new node();
            tmp->data = _dataitem;
            tmp->left_node = nullptr;
            tmp->right_node = nullptr;
            node *node_ptr = m_root;
            while(true) {
                if(_dataitem >= node_ptr->data) {
                    if(node_ptr->right_node == nullptr) {
                        node_ptr->right_node = tmp;
                        tmp = nullptr;
                        break;
                    } else {
                        node_ptr = node_ptr->right_node;
                    }
                } else if(_dataitem < node_ptr->data) {
                    if(node_ptr->left_node == nullptr) {
                        node_ptr->left_node = tmp;
                        tmp = nullptr;
                        break;
                    } else {
                        node_ptr = node_ptr->left_node;
                    }
                }
            }
        }
    }

    template <typename type>
    typename binary_tree<type>::node* binary_tree<type>::find(type _dataitem) {
        if(m_root == nullptr) {
            return m_root;
        } else {
            node* node_ptr = m_root;
            while(true) {
                if(_dataitem == node_ptr->data) {
                    return node_ptr;
                } else if(_dataitem >= node_ptr->data) {
                    if(node_ptr->right_node != nullptr) {
                        node_ptr = node_ptr->right_node;
                    } else return node_ptr->right_node;
                } else if(_dataitem < node_ptr->data) {
                    if(node_ptr->left_node != nullptr) {
                        node_ptr = node_ptr->left_node;
                    } else return node_ptr->left_node;
                }
            }
        }
    }

    template <typename type>
    void binary_tree<type>::erase(type _dataitem) {
        if(m_root != nullptr) {
            node* parent_node_ptr = nullptr;
            node* node_ptr = m_root;
            while(true) {
                if(_dataitem == node_ptr->data) {
                    /**
                     * @brief here we have few cases
                     * 1. when we are deleting a leaf node
                     * 2. deleting a node with just one child
                     * 3. deleting a node with both childs
                     * 4. deleting a node with both childs as subtrees
                    */
                    if(isnull_macro(node_ptr->left_node) && isnull_macro(node_ptr->right_node)) {
                        std::cout << "first case\n";
                        if(isnull_macro(parent_node_ptr)) {
                            delete (node_ptr);
                            break;
                        } else {
                            if(parent_node_ptr->right_node == node_ptr) {
                                parent_node_ptr->right_node = nullptr;
                            } else {
                                parent_node_ptr->left_node = nullptr;
                            }
                            delete (node_ptr);
                            break;
                        }
                    } else if(notnull_macro(node_ptr->left_node) ^ notnull_macro(node_ptr->right_node)) {
                        std::cout << "second case\n";
                        if(isnull_macro(parent_node_ptr)) {
                            if(notnull_macro(node_ptr->left_node)) {
                                m_root = node_ptr->left_node;
                            } else m_root = node_ptr->right_node;
                            delete (node_ptr);
                            break;
                        } else {
                            if(notnull_macro(node_ptr->left_node)) {
                                if(parent_node_ptr->left_node == node_ptr) {
                                    parent_node_ptr->left_node = node_ptr->left_node;
                                } else parent_node_ptr->right_node = node_ptr->left_node;
                            } else {
                                if(parent_node_ptr->left_node == node_ptr) {
                                    parent_node_ptr->left_node = node_ptr->right_node;
                                } else parent_node_ptr->right_node = node_ptr->right_node;
                            }
                            delete (node_ptr);
                            break;
                        }
                    } else if(notnull_macro(node_ptr->left_node) && notnull_macro(node_ptr->right_node)) {
                        std::cout << "third case\n";
                        if(isnull_macro(parent_node_ptr)) {
                            m_root = node_ptr->left_node;
                            node* tmp_node_ptr = m_root;
                            while(notnull_macro(tmp_node_ptr->right_node)) {
                                tmp_node_ptr = tmp_node_ptr->right_node;
                            }
                            tmp_node_ptr->right_node = node_ptr->right_node;
                            delete (node_ptr);
                            break;
                        } else {
                            node* tmp_node_ptr = nullptr;
                            if(parent_node_ptr->left_node == node_ptr) {
                                parent_node_ptr->left_node = node_ptr->left_node;
                                tmp_node_ptr = parent_node_ptr->left_node;
                            } else {
                                parent_node_ptr->right_node = node_ptr->left_node;
                                tmp_node_ptr = parent_node_ptr->right_node;
                            }
                            while(notnull_macro(tmp_node_ptr->right_node)) {
                                tmp_node_ptr = tmp_node_ptr->right_node;
                            }
                            tmp_node_ptr->right_node = node_ptr->right_node;
                            delete (node_ptr);
                            break;
                        }
                    }
                } else if(_dataitem < node_ptr->data) {
                    if(node_ptr->left_node != nullptr) {
                        parent_node_ptr = node_ptr;
                        node_ptr = node_ptr->left_node;
                    } else break;
                } else if(_dataitem > node_ptr->data) {
                    if(node_ptr->right_node != nullptr) {
                        parent_node_ptr = node_ptr;
                        node_ptr = node_ptr->right_node;
                    } else break;
                }
            }
        }
    }

    // template <typename type>
    // binary_tree<type>::~binary_tree() {
    //     std::cout << "node count: " << m_addressbook.length() << "\n";
    //     for(size_t i{1}; i < m_addressbook.length(); i++) {
    //         // delete m_addressbook.at(i);
    //         // std::cout << m_addressbook.at(i)->data << std::endl;
    //     }
    //     std::cout << "destruction done\n";
    // }



} // namespace ycontainer

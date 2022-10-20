/**
 * end goal is to implement a container called " ntree<type> "
 * which will have n number of direct children possible
*/

#ifdef DEBUG_MODE
#endif
    #include <iostream>
#define isnull_macro(item) (item == nullptr)
#define notnull_macro(item) (item != nullptr)
namespace ycontainer {
    
    using size_t = unsigned long;
    
    enum insertion_type_e {
        default_order = 0,
        inorder,
        preorder,
        postorder
    };

    template <typename type>
    class binary_tree {
        public:

            struct node {
                node* left_node;
                type data;
                node* right_node;
            };

            binary_tree(insertion_type_e _insertiontype = insertion_type_e::default_order)
            :   m_root(nullptr), m_height(0),
                m_node_count(0), m_insertion_type(_insertiontype) {
                
            }

            void insert(type);
            type* flatten();
            node* find(type);
            void delete_node(type _dataitem);
            ~binary_tree();

        private: /* data fields */
            node* m_root;
            size_t m_height;
            size_t m_node_count;
            insertion_type_e m_insertion_type;

        private: /* internal member functions */
            void default_insert(type);
            void inorder_insert(type);
            void preorder_insert(type);
            void postorder_insert(type);

    };

    template <typename type>
    void binary_tree<type>::insert(type _dataitem) {
        switch(m_insertion_type) {
            case insertion_type_e::default_order: {
                default_insert(_dataitem);
            } break;

            case insertion_type_e::inorder: {
                std::cout << "inorder to be implemented\n";
            } break;
            case insertion_type_e::preorder: {
                std::cout << "preorder to be implemented\n";

            } break;
            case insertion_type_e::postorder: {
                std::cout << "postorder to be implemented\n";

            } break;

            default: {}
        }
    }

    template <typename type>
    void binary_tree<type>::default_insert(type _dataitem) {
        if(m_root == nullptr) {
            node *tmp = new node;
            tmp->data = _dataitem;
            tmp->left_node = nullptr;
            tmp->right_node = nullptr;
            m_root = tmp;
            tmp = nullptr;
        } else {
            node *tmp = new node;
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
    void binary_tree<type>::delete_node(type _dataitem) {
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
                            delete node_ptr;
                            break;
                        } else {
                            if(parent_node_ptr->right_node == node_ptr) {
                                parent_node_ptr->right_node = nullptr;
                            } else {
                                parent_node_ptr->left_node = nullptr;
                            }
                            delete node_ptr;
                            break;
                        }
                    } else if(notnull_macro(node_ptr->left_node) ^ notnull_macro(node_ptr->right_node)) {
                        std::cout << "second case\n";
                        if(isnull_macro(parent_node_ptr)) {
                            if(notnull_macro(node_ptr->left_node)) {
                                m_root = node_ptr->left_node;
                            } else m_root = node_ptr->right_node;
                            delete node_ptr;
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
                            delete node_ptr;
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
                            delete node_ptr;
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
                            delete node_ptr;
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

    template <typename type>
    binary_tree<type>::~binary_tree() {
        if(notnull_macro(m_root->left_node)) {
            std::thread([&](){
                
            });
        }
        if(notnull_macro(m_root->right_node)) {
            std::thread([&](){
                
            });
        }
        std::cout << "destruction done\n";
    }
} // namespace ycontainer

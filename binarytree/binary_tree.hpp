/**
 * end goal is to implement a container called " ntree<type> "
 * which will have n number of direct children possible
*/

namespace ycontainer {
    
    using size_t = unsigned long;
    template <typename type>
    class binary_tree {
        public:

            struct node {
                node* left_node;
                type data;
                node* right_node;
            };
            enum insertion_type_e {
                default_order = 0,
                inorder,
                preorder,
                postorder
            };

            binary_tree(insertion_type_e _insertiontype = insertion_type_e::default_order)
            :   root(nullptr), height(0),
                node_count(0), m_insertion_type(_insertiontype) {
                
            }

            void insert(type);
            type* flatten();
            node* find(type);
        private:
            node* root;
            size_t height;
            size_t node_count;
            insertion_type_e m_insertion_type;

        private:
            void default_insert(type);

    };

    template <typename type>
    void binary_tree<type>::insert(type _dataitem) {
        switch(m_insertion_type) {
            case insertion_type_e::default_order: {
                default_insert(_dataitem);
            } break;

            case insertion_type_e::inorder: {} break;
            case insertion_type_e::preorder: {} break;
            case insertion_type_e::postorder: {} break;

            default: {}
        }
    }

    template <typename type>
    void binary_tree<type>::default_insert(type _dataitem) {
        if(root == nullptr) {
            node *tmp = new node;
            tmp->data = _dataitem;
            tmp->left_node = nullptr;
            tmp->right_node = nullptr;
            root = tmp;
            tmp = nullptr;
        } else {
            node *tmp = new node;
            tmp->data = _dataitem;
            tmp->left_node = nullptr;
            tmp->right_node = nullptr;
            node *node_ptr = root;
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
        if(root == nullptr) {
            return root;
        } else {
            node* node_ptr = root;
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

} // namespace ycontainer

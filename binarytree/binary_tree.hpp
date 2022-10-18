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
            binary_tree() : root(nullptr), height(0),  node_count(0) {}
            void insert(type);
            type* flatten();
        private:
            node* root;
            size_t height;
            size_t node_count;

    };

    template <typename type>
    void binary_tree<type>::insert(type _dataitem) {
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

} // namespace ycontainer

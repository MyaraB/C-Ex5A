#include <deque>
#include <stack>
#include <iostream>
#include <iterator>

namespace ariel
{
    template <typename T>
    class BinaryTree
    {
        //build a template Node class for the Binary Tree
        class Node
        {
            T val;// template value
            Node *left, *right; // left and right sons of node
        // initialize node
            Node(const T value)
                : val(value), left(nullptr), right(nullptr){};

                //destroctor, makes sure all the tree is deleted
            ~Node(){
                if(right){delete right;}
                if(left){delete left;}
               
            }
            friend class BinaryTree; // in order to have access to the nodes
        };

        Node *root;

        enum OrderBy // different order types for our binary tree
        {
            preorder,
            inorder,
            postorder
        };
        

    public:
    // creating an iterator class to be able to iterate over the binary tree
        class iterator
        {
            template <Node *, class Container = std::deque<Node *>> //help get the correct order of the tree  by using stacks
            class stack;

            Node *temp;
            OrderBy orderby;
            std::stack<Node *> tack;

        public:

        
            iterator(Node *start, const OrderBy &order) : orderby(order) // to be able to choose an iteration depending on binary tree order (pre,in,post)
            {
                initStack(start);
                temp = tack.top();
                tack.pop();
            }
            ~iterator(){} // destructer
            iterator() : temp(nullptr){};
            
            

            void initStack(Node *a)// initialize stack by order. helps to iterate over binary tree in the correct order.
            {
                if (a == nullptr)
                {
                    return;
                }
                if (orderby == preorder)
                {
                    initStack(a->right);
                    initStack(a->left);
                    tack.push(a);
                }
                else if (orderby == inorder)
                {
                    initStack(a->right);
                    tack.push(a);
                    initStack(a->left);
                }
                else
                {
                    tack.push(a);
                    initStack(a->right);
                    initStack(a->left);
                }
            }

              const iterator operator++(int)
            {
                if (tack.empty())
                {   
                    temp = nullptr;
                    return *this;
                }
                Node *current = temp;
                temp = tack.top();
                tack.pop();
                return iterator(current, inorder);
            }

            iterator &operator++()
            {
                if (tack.empty()) // if our stack is empty make sure iterator points at nullptr
                {   
                    temp = nullptr;
                    return *this;
                }
                temp = tack.top();
                tack.pop();
                return *this;
            }

            T &operator*() const  // returns pointer to val
            {
                return temp->val;
            }

            T *operator->() const // refrence to pointer
            {
                return &(temp->val);
            }
            bool operator==(const iterator &iter) const
            {
                if (temp == nullptr || iter.temp == nullptr)
                {
                    if (temp == nullptr && iter.temp == nullptr)
                    {
                        return true;
                    }
                    return false;
                }
                return temp->val == iter.temp->val;
            }

            bool operator!=(const iterator &iter) const
            {
                return !(*this == iter);
            }
        };
        BinaryTree<T>():root(nullptr){};

        ~BinaryTree<T> (){if(root) {delete(root);}}

        // add new root or override old root

        BinaryTree<T> &add_root(const T a)  
        {
            if(root){
                root->val = a;
            }
            else{
                root = new Node(a);
            }
            return *this;
        }

        BinaryTree<T> &add_right(const T last, const T right_node) // add a right son to the last node
        {
            Node *node = searchNode(root, last);
            if (node != nullptr)
            {
                if (node->right == nullptr) //if right son doesnt exist we create new
                {
                    (node->right) = new Node(right_node);
                }
                else
                {
                    node->right->val = right_node;
                }
                return *this;
            }
            throw std::invalid_argument("This node does not exist");
        }

        BinaryTree<T> &add_left(const T last, const T left_node) // add a left son to the last node
        {
            Node *node = searchNode(root, last);

            if (node != nullptr) // if the last node doesnt exist we throw an invalid argument.
            {
                if (node->left == nullptr) //if left son doesnt exist we create new
                {
                    node->left = new Node(left_node);
                }
                else
                {
                    node->left->val = left_node;
                }
                
                return *this;
            }
            throw std::invalid_argument("This node does not exist");
        }


        Node *searchNode(Node *point, T find) // find specific node in the tree. given beginning node and the value to find. 
        {
            if (point == nullptr)
            {
                return nullptr;
            }
            if (point->val == find)
            {
                return point;
            }

            Node *right = searchNode(point->right, find);

            Node *left = searchNode(point->left, find);
            if (right != nullptr)
            {
                return right;
            }
            return left;
        }

        // functions of binary tree

        iterator begin() { return iterator{root, inorder}; }
        
        iterator end() { return iterator{}; }

        iterator begin_preorder() { return iterator{root, preorder}; }

        iterator end_preorder() { return iterator{}; }

        iterator begin_inorder() { return iterator{root, inorder}; }

        iterator end_inorder() { return iterator{}; }

        iterator begin_postorder() { return iterator{root, postorder}; }

        iterator end_postorder() { return iterator{}; }

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &tree) { return os; }
    };
}
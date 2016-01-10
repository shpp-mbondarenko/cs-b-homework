#ifndef MYTREE
#define MYTREE
#include <iostream>

using namespace std;


template <class T, class K>
class BSTree {

public:
private:
    struct Node{
        K key;
        T val;
        int height;
        Node(){};
        Node(T value, K keyval){
            val = value;
            key = keyval;
            left = 0;
            right = 0;
        }
        Node* left;
        Node* right;
    };
    Node* root;

    //find height of root
    int findHeight(Node* root){
        if(root == NULL)
            return -1;
        int lefth = findHeight(root->left);
        int righth = findHeight(root->right);

        if(lefth > righth)
            return lefth + 1;
        else
            return righth + 1;
    }

    /* find factor balase of BSTree */
    int balanceFactor(Node* n){
        return findHeight(n->right) - findHeight(n->left);
    }

    /* fixing height of root node */
    void fixHeight(Node* n){
        int hl = findHeight(n->left);               // Getting height of left subtree
        int hr = findHeight(n->right);              // Getting height of right subtree
        n->height = ((hl > hr) ? hl : hr) + 1;      // root height is longest height of subtree +1
    }


    /* Deleting ode with key "k" */
    Node* removeNode(Node* n, K k){
        if (n == NULL){
            cout << "You can't delete node from empty tree!" << endl;
            return NULL;
        }
        if (k < n->key){                    // if "k" less than current key go to left subtree and do removeNode
            n->left = removeNode(n->left, k);
        }else if (k > n->key) {
            n->right = removeNode(n->right, k);
        }else{                             // if "k" = key
            Node* l = n->left;                   // save left subtree of current node
            Node* r = n->right;                  // and save right sub-tree
            delete n;                            // Delete n Node
            if (r == NULL){                       // if right is null return left
                return l;
            }
            Node* m = findMinimum(r);            // find and save min node of right sub-tree
            m->right = removeMinimum(r);         // delete minimum from right sub-tree
            m->left = l;
            return balance(m);
        }
        return balance(n);
    }


    /* Finding minimum node */
    Node* findMinimum(Node* t){
        if (t->left == NULL)
            return t;
        return findMinimum(t->left);
    }

    /* delete minimum node  */
    Node* removeMinimum(Node* n){
        if (n->left == NULL)
            return n->right;
        n->left = removeMinimum(n->left);
        return balance(n);
    }

    /* Right turn of tree */
    Node* rotateRight(Node* n){
        Node* l = n->left;   // Keeping the left subtree of the current node
        n->left = l->right;  // The left subtree of the current node becomes the right subtree stored subtree
        l->right = n;        // Subtree right subtree saved becomes the current node
        fixHeight(n);
        fixHeight(l);
        return l;
    }

    /* Left turn of tree */
    Node* rotateLeft(Node* n){
        Node* r = n->right;
        n->right = r->left;
        r->left = n;
        fixHeight(n);
        fixHeight(r);
        return r;
    }

    /* Balancing tree */
    Node* balance(Node* n){
        fixHeight(n);                              // Calculating balance factor of tree
        if (balanceFactor(n) == 2){               // If the height of the right subtree of the current node greater than the height of the left 2
            if (balanceFactor(n->right) < 0)           // If the balance factor of the right subtree is less than 0 (requires big turn)
                n->right = rotateRight(n->right);          // Make a right turn right subtree
            return rotateLeft(n);                      // We perform a left turn tree and return it
        }
        if (balanceFactor(n) == -2){
            if (balanceFactor(n->left) > 0)
                n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        return n;
    }

    /* Find key in tree */
    Node* findNode(Node* t, K key){
        if (t == NULL){
            cout << "You trying to look in empty tree. Please add elements, first." << endl;
            return NULL;
        }
        if (key == t->key){
            return t;
        }
        if (key < t->key){
            if(t->left != NULL && (t->left->key) > key){
                cout << "Sorry, can't find value, with this key." << endl;
                return NULL;
            }else{
                return findNode(t->left, key);
            }
        } else if (key > t->key){
            if(t->right != NULL && (t->right->key) < key){
                cout << "Sorry, can't find value, with this key." << endl;
                return NULL;
            }else{
                return findNode(t->right, key);
            }
        }

    }



    /* go through all tree */
    void infixTraverseTree(Node* t, int k = 0){
        if (t != NULL){
            infixTraverseTree(t->left, k+3);
            for(int i = 0; i < k; i++){
                cout << "   ";
            }
            cout << t->key <<" : " << t->val << endl;
            infixTraverseTree(t->right, k+3);
        }
    }

    //insert Node
    Node* insertNode(Node* t, T value, K keyval){
        if(t == NULL){
            t = new Node();
            t->key = keyval;
            t->val = value;
            t->left = NULL;
            t->right = NULL;
        }else{
            if(keyval < t->key){
                t->left = insertNode(t->left, value, keyval);
            } else if (keyval > t->key){
                t->right = insertNode(t->right, value, keyval);
            }
        }
        return balance(t);
    }
public:
    //constructor
    BSTree(){
        root = NULL;
    }

    ~BSTree(){}

    //insert element into BSTree
    void insert(T value, K keyval){
        root = insertNode(root, value, keyval);
    }

    //print BST
    void print(){
        if(root!=0){
            infixTraverseTree(root);
        }
    }
    //remove node
    void remove(K keyval){
        root = removeNode(root, keyval);
    }

    //return value from node
    T find(K key){
        Node* tmp = findNode(root, key);
        if(tmp == NULL){
            return NULL;
        }else{
            return tmp->val;
        }
    }
};

#endif // MYTREE

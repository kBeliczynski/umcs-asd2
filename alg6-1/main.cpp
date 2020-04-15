#include <iostream>
#include <vector>
using namespace std;

struct Node{
    Node * left, *right, *father;
    int value;
    Node(int v){
        value = v;
        left = right = father = nullptr;
    }
};

bool findPair(Node * node, int &a, int &b, vector<int> &s,int sum){
    if(node == nullptr) return false;
    if(findPair(node->left,a,b,s,sum)) return true;
    for(int val : s){
        if((sum - val) == node->value){
            a = node->value;
            b = val;
            return true;
        }
    }
    s.push_back(node->value);
    if(findPair(node->right,a,b,s,sum)) return true;

    return false;
}

class BSTtree{
    Node * root;
    int count;

public:
    BSTtree(){
        root = nullptr;
        count = 0;
    }

    Node * getRoot(){return root;}

    void addNode(Node *node){
       Node *a, *b= root;
       a = node->left = node->right = nullptr;
       while(b){
            if(node->value == b->value){
                return;
            }
            a = b;
            if(node ->value < b->value)
                b = b->left;
            else
                b = b->right;
       }
       node->father = a;
       if(!a)
            root = node;
        else if(node->value < a->value)
            a->left = node;
        else
            a->right = node;
        count++;
    }

    Node * minNode(Node * node){
        while(node->left) node = node->left;
        return node;
    }

    Node * search(int value){
        Node * node = root;
        while((node) && (node->value != value))
            node = (value < node->value) ? node->left : node->right;
        return node;
    }

    Node * maxNode(Node * node)
    {
        while(node->right) node = node->right;
        return node;
    }

    Node * pred(Node * node){
        if(node->left) return maxNode(node->left);
        Node * y;
        do{
            y = node;
            node = node->father;
        }while(node && (node->right != y));
        if(!node)
            return node->father;
        return node;
    }

    Node * succ(Node * node)
    {
        if(node->right) return minNode(node->right);
        Node * y;
        do{
            y = node;
            node = node->father;
        } while(node && (node->left != y));
        if(!node)
            return node->father;
        return node;
    }

    Node * removeNode(Node * node){

        Node * y = node->father, * z;

        if((node->left) && (node->right) && node){
            z = (rand() % 2) ? removeNode(pred(node)) : removeNode(succ(node));
            z->left = node->left;   if(z->left)  z->left->father  = z;
            z->right = node->right; if(z->right) z->right->father = z;
            count++;
        }
        else z = (node->left) ? node->left : node->right;

        if(z) z->father = y;

        if(!y) root = z;
        else if(y->left == node) y->left = z; else y->right = z;

        count--;
        return node;
    }

};

int main(){
    int n;
    int val;
    int left,right;
    int sum;
    int pairL=0,pairR=0;

    cin >> n;
    BSTtree bst;
    vector<int> values;
    vector<int> s;
    for(int i=0; i<n; i++){
        cin >> val;
        values.push_back(val);
        Node * n = new Node(val);
        bst.addNode(n);
    }

    cin >> left >> right >> sum;

    for(auto val : values){
        if(val < left || val > right)
            bst.removeNode(bst.search(val));
    }

    if(findPair(bst.getRoot(),pairL,pairR,s,sum) && pairL!=0){
       if(pairL > pairR) cout << pairR << " " << pairL;
       else cout << pairL << " " << pairR;
    }
    else
        cout << "NIE ZNALEZIONO" <<endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Node{
public:
    string value;
    vector<string> list;
    Node *l_son, *r_son;
};

Node* newNode(string value){
    Node* node = new Node();
    node->value = value;
    node->l_son = node->r_son = nullptr;
    return node;
}

Node *rightRotate(Node *node){
    Node *tmp = node->l_son;
    node->l_son = tmp->r_son;
    tmp->r_son = node;
    return tmp;
}

Node *leftRotate(Node *node){
    Node *tmp = node->r_son;
    node->r_son = tmp->l_son;
    tmp->l_son = node;
    return tmp;
}

Node *splay(Node *root, string value){
    if(root == nullptr || root->value.compare(value)==0)
        return root;
    if(root->value.compare(value)>0){
        if(root->l_son == nullptr)
            return root;
        if(root->l_son->value.compare(value)>0){
            root->l_son->l_son = splay(root->l_son->l_son, value);
            root = rightRotate(root);
        }
        else if(root->l_son->value.compare(value)<0){
            root->l_son->r_son = splay(root->l_son->r_son, value);
            if(root->l_son->r_son != nullptr)
                root->l_son = leftRotate(root->l_son);
        }
        return (root->l_son == nullptr)? root: rightRotate(root);
    }else{
        if(root->r_son == nullptr) return root;
        if(root->r_son->value.compare(value)>0){
            root->r_son->l_son = splay(root->r_son->l_son, value);
            if(root->r_son->l_son != nullptr)
                root->r_son = rightRotate(root->r_son);
        }else if(root->r_son->value.compare(value)<0){
            root->r_son->r_son = splay(root->r_son->r_son, value);
            root = leftRotate(root);
        }
        return (root->r_son == nullptr)? root: leftRotate(root);
    }
}

Node *insert(Node *root, string k){
    if(root == nullptr) return newNode(k);
        root = splay(root, k);
    if(root->value == k) return root;
        Node *node = newNode(k);
    if(root->value.compare(k)>0){
        node->r_son = root;
        node->l_son = root->l_son;
        root->l_son = nullptr;
    }else{
        node->l_son = root;
        node->r_son = root->r_son;
        root->r_son = nullptr;
    }
    return node;
}

Node *search(Node *root, string value){
    return splay(root, value);
}

int main(){
ios_base::sync_with_stdio(false);
    int n;
    string c;
    string title, band;
    Node * titleRoot = nullptr;
    Node * bandRoot = nullptr;
    cin >> n;
    cin.ignore();
    for(int i=0; i<n; i++){
        getline(cin,c);
        c.erase(remove_if(c.begin(),c.end(),::isspace), c.end());
        if(c == "d"){
            getline(cin,band);
            getline(cin,title);
            bandRoot = insert(bandRoot,band);
            bandRoot->list.push_back(title);
            titleRoot = insert(titleRoot,title);
            titleRoot->list.push_back(band);
        }else if(c == "w"){
            getline(cin,band);
            if(bandRoot == nullptr)
                continue;
            bandRoot = search(bandRoot,band);
            if(band.compare(bandRoot->value)==0)
                for(auto titles : bandRoot->list){
                    cout << titles << endl;
                }
        }else if (c == "z"){
            getline(cin,title);
            if(titleRoot == nullptr)
               continue;
            titleRoot = search(titleRoot,title);
            if(title.compare(titleRoot->value)==0)
                for(auto bands : titleRoot->list){
                    cout << bands << endl;
                }
        }
    }
    return 0;
}

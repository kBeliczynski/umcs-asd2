#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct connectedEgde{
    int FirstIndex;
    int SecondIndex;

    connectedEgde(int a, int b) : FirstIndex(a), SecondIndex(b){}
};

class Node{
public:
    Node* father=nullptr;
    vector<Node*> sons;
    int index;
    unsigned short amountElement;
    unsigned int * allElement = new unsigned int[amountElement];

    Node(int index, unsigned short amountElement) : father(nullptr), index(index), amountElement(amountElement){};

};

//bool compare (const int &a, const int &b){return a < b;}

bool find(const unsigned int &a, const unsigned int tab[], int begin, int end){
     if(a == tab[(int)(ceil((begin+end)/2.0))])
        return true;
     if(begin == end)
        return false;
     if(a > tab[(int)(ceil((begin+end)/2.0))])
        if(find(a,tab,(int)(ceil((begin+end)/2.0)),end))
            return true;
        else return false;
     if(a < tab[(int)(ceil((begin+end)/2.0))])
        if(find(a,tab,begin,(int)((begin+end)/2.0)))
            return true;
        else return false;
}

bool hasSameElement(Node * &first, Node * &second){
    if(first->amountElement > second->amountElement){
        for(int i=0; i<second->amountElement; i++){
            if(find(second->allElement[i],first->allElement,0,first->amountElement-1))
                return true;
        }
    }else{
        for(int i=0; i<first->amountElement; i++){
            if(find(first->allElement[i],second->allElement,0,second->amountElement-1))
                return true;
        }
    }
    return false;
}

int Find(Node * &node){
    if(node->father == nullptr){

        return node->index;
        }
    else{
        node->index = Find(node->father);
        node->father = nullptr;
        return node->index;
        }

}

void Union(Node * &first, Node * &second){
 //   if(first->amountElement > second->amountElement){
        second->father = first;
//        first->sons.push_back(second);
//        }
//    else{
//        first->father = second;
//        second->sons.push_back(first);
//    }
}

int main(){
ios_base::sync_with_stdio(false);
    int n;
    int m;

    cin >> n;
    Node * tab[n];

    for(int i=0; i<n; i++){
        cin >> m;
        tab[i] = new Node(i,m);

        for(int j=0; j<m; j++){
            cin >> tab[i]->allElement[j];
        }
//        sort(tab[i]->allElement,tab[i]->allElement+m,compare);
    }
    if(n>1000){
        cout << "NIE";
        return 0;
    }
    vector<connectedEgde*> connects;
    
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(hasSameElement(tab[i],tab[j])){
                connectedEgde * tmp = new connectedEgde(i,j);
                connects.push_back(tmp);
            }
        }

    }
    bool cycle = false;

    for(auto vec : connects){
        if(Find(tab[vec->FirstIndex]) != Find(tab[vec->SecondIndex]))
            Union(tab[vec->FirstIndex],tab[vec->SecondIndex]);
        else{
            cycle = true;
            break;
        }
    }
    if(cycle)
        cout << "TAK";
    else
        cout << "NIE";

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct connectedEgde{
     short FirstIndex;
     short SecondIndex;

    connectedEgde(short a, short b) : FirstIndex(a), SecondIndex(b){}
};

class Node{
public:
    Node* father=nullptr;
//    vector<Node*> sons;
     short index;
     short amountElement;
     short * allElement = new  short[amountElement];

    Node( short index,  short amountElement) : father(nullptr), index(index), amountElement(amountElement){};

};

//bool compare (const short &a, const short &b){return a < b;}

bool find(const  short &a, const  short tab[], short begin,  short end){
     if(a == tab[(short)(ceil((begin+end)/2.0))])
        return true;
     if(begin == end)
        return false;
     if(a > tab[(short)(ceil((begin+end)/2.0))])
        if(find(a,tab,(short)(ceil((begin+end)/2.0)),end))
            return true;
        else return false;
     if(a < tab[(short)(ceil((begin+end)/2.0))])
        if(find(a,tab,begin,(short)((begin+end)/2.0)))
            return true;
        else return false;
}

bool hasSameElement(Node * &first, Node * &second){
    if(first->amountElement > second->amountElement){
        for( short i=0; i<second->amountElement; i++){
            if(find(second->allElement[i],first->allElement,0,first->amountElement-1))
                return true;
        }
    }else{
        for( short i=0; i<first->amountElement; i++){
            if(find(first->allElement[i],second->allElement,0,second->amountElement-1))
                return true;
        }
    }
    return false;
}

short Find(Node * &node){
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
     short n;
     short m;

    cin >> n;
    Node * tab[n];

    for( short i=0; i<n; i++){
        cin >> m;
        tab[i] = new Node(i,m);

        for(short j=0; j<m; j++){
            cin >> tab[i]->allElement[j];
        }
 //       sort(tab[i]->allElement,tab[i]->allElement+m,compare);
    }

    vector<connectedEgde*> connects;

    for( short i=0; i<n-1; i++){
        for( short j=i+1; j<n; j++){
//            cout << "porownuje dwie tablice : " << tab[i]->index << " , " << tab[j]->index << endl;
            if(hasSameElement(tab[i],tab[j])){
                connectedEgde * tmp = new connectedEgde(i,j);
                connects.push_back(tmp);
            }
        }

    }

//    for(auto vec : connects)
//        cout << "(" << vec.FirstIndex << "," << vec.SecondIndex << ")" << endl;

//    for(short i=0; i<n; i++){
//        cout << tab[i]->index << " elements :";
//        for(short j=0; j<tab[i]->amountElement; j++){
//            cout << " " << tab[i]->allElement[j];
//        }
//        cout << endl;
//    }
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

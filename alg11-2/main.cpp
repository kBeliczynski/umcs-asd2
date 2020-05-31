#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node{
    string value;
    vector<string> list;
    Node(string key, string val){
        value = key;
        list.push_back(val);
    }
};

class HashTable{
    long long mod;
    vector<Node *> table;

public:
    HashTable(long long n){
        this->mod = n;
        this->table.resize(mod);
    }

    long long hashFunction(string name){
        long long suma = 0;
        for(char c : name)
           suma += c*c;
        return suma%mod;
    }

    void insert(Node * node){
        long long i = 0;
        long long hash = hashFunction(node->value);
        while(table[hash] != NULL && table[hash]->value.compare(node->value)!=0){
            i++;
            hash = (hash + i*i)%mod;
        }
        if(table[hash]!=NULL)
            if(table[hash]->value.compare(node->value)==0){
                table[hash]->list.push_back(node->list.front());
                delete node;
                return;
            }
        table[hash] = node;
    }

    void searchAndShow(string key){
        long long i = 0;
        long long hash = hashFunction(key);
        while(table[hash] != NULL && table[hash]->value.compare(key)!=0){
            i++;
            hash = (hash + i*i)%mod;
        }
        if(table[hash] != NULL)
            for(auto var : table[hash]->list)
                cout << var << endl;
    }
};

int main(){
ios_base::sync_with_stdio(false);
    long long n;
    string c;
    string title, band;
    cin >> n;
    cin.ignore();
    HashTable bandTable(n);
    HashTable titleTable(n);
    for(int i=0; i<n; i++){
        getline(cin,c);
        c.erase(remove_if(c.begin(),c.end(),::isspace), c.end());
        if(c == "d"){
            getline(cin,band);
            getline(cin,title);
            Node * bandNode = new Node(band,title);
            Node * titleNode = new Node(title,band);
            bandTable.insert(bandNode);
            titleTable.insert(titleNode);
        }else if(c == "w"){
            getline(cin,band);
            bandTable.searchAndShow(band);
        }else if (c == "z"){
            getline(cin,title);
            titleTable.searchAndShow(title);
        }
    }
    return 0;
}

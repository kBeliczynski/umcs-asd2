#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>
#include <queue>
#include <cmath>
using namespace std;

struct Point{
    int x,y; // point coordinates
    int w=INT_MAX;  // weight
    int index;
    bool visit=false;
    Point* parent=nullptr;
    Point* child=nullptr;
    Point* left=nullptr;
    Point* right=nullptr;
    int degree=0;
    bool mark=false;
    bool inHeap=false;

public:
    friend class Fib;
    Point* getLeft() {return left;}
    Point* getRight() {return right;}
    Point* getChild() {return child;}
    Point* getParent() {return parent;}
    int getValue() {return w;}
    bool isMarked() {return mark;}
    bool hasChildren() {return child;}
    bool hasParent() {return parent;}
};
struct CompareWeight {
    bool operator()(Point * p1, Point * p2){
        return p1->w > p2->w;
    }
};
bool sortByX(Point *a, Point *b) {return a->x < b->x;}
bool sortByY(Point *a, Point *b) {return a->y < b->y;}

void addNeighbors(vector<Point *> list[], int n, Point ** X, Point ** Y){ // add only nearest neighbors
    for(int i=0; i<n; i++){
        if(i==0){
            list[X[i]->index].push_back(X[i+1]);
            list[Y[i]->index].push_back(Y[i+1]);
            }
        else if(i == n-1){
            list[X[i]->index].push_back(X[i-1]);
            list[Y[i]->index].push_back(Y[i-1]);
            }
        else{
            list[X[i]->index].push_back(X[i+1]);
            list[X[i]->index].push_back(X[i-1]);
            list[Y[i]->index].push_back(Y[i+1]);
            list[Y[i]->index].push_back(Y[i-1]);
        }
    }
}

int weight(Point a, Point *b){
 return (abs(a.x-b->x) < abs(a.y-b->y)) ? abs(a.x-b->x) : abs(a.y-b->y);
}

void countDistance(vector<Point *> list[],int n, Point points[],int distance[][4]){
    for(int i=0; i<n; i++){
        for(int j=0; j<list[i].size(); j++){
            distance[i][j] = weight(points[i],list[i][j]);
        }
    }
}

class Fib{
protected:
    Point* heap;
public:

Fib() {
        heap=_empty();
    }
    virtual ~Fib() {
        if(heap) {
            _deleteAll(heap);
        }
    }
    Point* insert(Point* value) {
        Point* ret=_singleton(value);
        heap=_merge(heap,ret);
        return ret;
    }
    void merge(Fib& other) {
        heap=_merge(heap,other.heap);
        other.heap=_empty();
    }

    bool isEmpty() {
        return heap==NULL;
    }

    Point * getMinimum() {
        return heap;
    }
 //nie iwem czy * czy ne
    Point * removeMinimum() {
        Point * old=heap;
        heap=_removeMinimum(heap);
        Point* ret=old;
        old = NULL;
        return ret;
    }

    void decreaseKey(Point* n,int value) {
        heap=_decreaseKey(heap,n,value);
    }

    Point* find(int value) {
        return _find(heap,value);
    }
private:
    Point * _empty() {
        return NULL;
    }

    Point* _singleton(Point * n) {
        n->w=n->w;
        n->left=n->right=n;
        n->degree=0;
        n->mark=false;
        n->child=NULL;
        n->parent=NULL;
        return n;
    }

    Point* _merge(Point* a,Point * b) {
        if(a==NULL)return b;
        if(b==NULL)return a;
        if(a->w>b->w) {
            Point* temp=a;
            a=b;
            b=temp;
        }
        Point * an=a->right;
        Point* bp=b->left;
        a->right=b;
        b->left=a;
        an->left=bp;
        bp->right=an;
        return a;
    }

    void _deleteAll(Point * n) {
        if(n!=NULL) {
            Point* c=n;
            do {
                Point * d=c;
                c=c->right;
                _deleteAll(d->child);
                delete d;
            } while(c!=n);
        }
    }

    void _addChild(Point* parent,Point* child) {
        child->left=child->right=child;
        child->parent=parent;
        parent->degree++;
        parent->child=_merge(parent->child,child);
    }

    void _unMarkAndUnParentAll(Point* n) {
        if(n==NULL)return;
        Point* c=n;
        do {
            c->mark=false;
            c->parent=NULL;
            c=c->right;
        }while(c!=n);
    }

    Point* _removeMinimum(Point* n) {
        _unMarkAndUnParentAll(n->child);
        if(n->right==n) {
            n=n->child;
        } else {
            n->right->left=n->left;
            n->left->right=n->right;
            n=_merge(n->right,n->child);
        }
        if(n==NULL)return n;
        Point* trees[32]={NULL};

        while(true) {
            if(trees[n->degree]!=NULL) {
                Point* t=trees[n->degree];
                if(t==n)break;
                trees[n->degree]=NULL;
                if(n->w<t->w) {
                    t->left->right=t->right;
                    t->right->left=t->left;
                    _addChild(n,t);
                } else {
                    t->left->right=t->right;
                    t->right->left=t->right;
                    if(n->right==n) {
                        t->right=t->left=t;
                        _addChild(t,n);
                        n=t;
                    } else {
                        n->left->right=t;
                        n->right->left=t;
                        t->right=n->right;
                        t->left=n->left;
                        _addChild(t,n);
                        n=t;
                    }
                }
                continue;
            } else {
                trees[n->degree]=n;
            }
            n=n->right;
        }
        Point* min=n;
        do {
            if(n->w<min->w)min=n;
            n=n->right;
        } while(n!=n);
        return min;
    }

    Point * _cut(Point* heap,Point* n) {
        if(n->right==n) {
            n->parent->child=NULL;
        } else {
            n->right->left=n->left;
            n->left->right=n->right;
            n->parent->child=n->right;
        }
        n->right=n->left=n;
        n->mark=false;
        return _merge(heap,n);
    }

    Point* _decreaseKey(Point* heap,Point* n,int value) {
        if(n->w<value)return heap;
        n->w=value;
        if(n->parent == NULL)
        return heap;
        if(n->w<n->parent->w) {
            heap=_cut(heap,n);
            Point* parent=n->parent;
            n->parent=NULL;
            while(parent!=NULL && parent->mark) {
                heap=_cut(heap,parent);
                n=parent;
                parent=n->parent;
                n->parent=NULL;
            }
            if(parent!=NULL && parent->parent!=NULL)parent->mark=true;
        }
        return heap;
    }

    Point* _find(Point* heap,int value) {
        Point* n=heap;
        if(n==NULL)return NULL;
        do {
            if(n->w==value)return n;
            Point* ret=_find(n->child,value);
            if(ret)return ret;
            n=n->right;
        }while(n!=heap);
        return NULL;
    }
};
void dijkstra(vector<Point *> list[],int n,Point points[], int s, int distance[][4]){
    Fib * heap = new Fib;
    points[s].w=0;  // start
    heap->insert(&points[s]);
    while(heap->getMinimum() !=nullptr){
        if(heap->getMinimum()->visit == false){
            int ind = heap->getMinimum()->index;
            heap->removeMinimum();
            for(int i=0; i<list[ind].size();i++){
                if(list[ind][i]->w > (points[ind].w + distance[ind][i]))
                    heap->decreaseKey(list[ind][i],(points[ind].w + distance[ind][i]));
                if((list[ind][i]->visit == false))
                    heap->insert(list[ind][i]);
            }
            points[ind].visit=true;
        }
        else
            heap->removeMinimum();
    }
}
void print(Point **tab, int n){
    for(int i=0; i<n; i++){
        cout << "(" << tab[i]->x << "," << tab[i]->y << ") index: " << tab[i]-> index << endl;
    }
}
int main(){
ios_base::sync_with_stdio(false);
    int n; // number of stops
    int s; // start point coordinates
    int d; // end point cordintes
        cin >> n;
        vector<Point *> neighborsList[n];
        int distance[n][4];             //distance from neighbor
        Point * points = new Point[n];  //main array with coordinates
        Point * pointX[n];              // only has pointers to a sorted array towards X
        Point * pointY[n];              // only has pointers to a sorted array towards Y
        for(int i=0; i<n; i++){
            cin >> points[i].x >> points[i].y;
        points[i].index = i;
        pointX[i] = &points[i];
        pointY[i] = &points[i];
        }
    cin >> s >> d;
    sort(pointX, pointX+n, sortByX);
    sort(pointY, pointY+n, sortByY);
    addNeighbors(neighborsList,n,pointX,pointY);
    countDistance(neighborsList,n,points,distance);
    dijkstra(neighborsList,n,points,s,distance);
//    print(&points,n);
//        for(int i=0; i<n; i++){
//            cout << "(" << points[i].x << "," << points[i].y << ") visit:" << points[i].visit << "the best path: " << points[i].w << endl;
//        }
    cout << points[d].w;
    return 0;
}

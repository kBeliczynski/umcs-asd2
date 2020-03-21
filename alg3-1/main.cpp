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
    int rest; //unit that show  the amount of stress reduction
    int index;
    bool visit=false;
};
struct CompareWeight {
    bool operator()(Point * p1, Point * p2){
        return p1->w > p2->w;
    }
};
bool sortByX_withRest(Point *a, Point *b) {return (a->x+a->rest) < (b->x+b->rest);}
bool sortByY_withRest(Point *a, Point *b) {return (a->y+a->rest) < (b->y+b->rest);}

void print(Point **tab, int n){
    for(int i=0; i<n; i++){
        cout << "(" << tab[i]->x << "," << tab[i]->y << ") index: " << tab[i]-> index << endl;
    }
}

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

void dijkstra(vector<Point *> list[],int n,Point points[], int s, int d){
        points[s].w=0;  // start
     priority_queue<Point *,vector<Point*>,CompareWeight> Queue;
       Queue.push(&points[s]);
       while(!Queue.empty()){
            if(Queue.top()->visit == false){
                int ind = Queue.top()->index;
                cout << "usunieto wartosc o indeksie : " << ind << endl;
                Queue.pop();
                for(int i=0; i<list[ind].size();i++){
                    if(list[ind][i]->w > (points[ind].w + weight(points[ind],list[ind][i]))){
                        list[ind][i]->w = (points[ind].w + weight(points[ind],list[ind][i]));
                    }
                    if(list[ind][i]->visit == false){
                        cout << "dodano wartosc o indeksie : " << list[ind][i]->index << endl;
                        Queue.push(list[ind][i]);
                        }
                }
                points[ind].visit=true;
            }
            else
                Queue.pop();
       }
}

int main(){
ios_base::sync_with_stdio(false);
    int n; // number of stops
    int s; // start point coordinates
    int d; // end point cordintes
    int v; // unit that show  the amount of stress reduction
        cin >> n;
        vector<Point *> neighborsList[n];
        Point * points = new Point[n];  //main array with coordinates
        Point * pointX[n];              // only has pointers to a sorted array towards X
        Point * pointY[n];              // only has pointers to a sorted array towards Y
        for(int i=0; i<n; i++){
            cin >> points[i].x >> points[i].y >> points[i].rest;
        points[i].index = i;
        pointX[i] = &points[i];
        pointY[i] = &points[i];
        }
    cin >> s >> d;
    sort(pointX, pointX+n, sortByX_withRest);
    sort(pointY, pointY+n, sortByY_withRest);
    addNeighbors(neighborsList,n,pointX,pointY);
    dijkstra(neighborsList,n,points,s,d);
//for(int i=0; i<n; i++){
//            cout << "(" << points[i].x << "," << points[i].y << ") rest: " << points[i].rest << " visit:" << points[i].visit << "the best path: " << points[i].w << endl;
//        }
    cout << points[d].w;
    return 0;
}

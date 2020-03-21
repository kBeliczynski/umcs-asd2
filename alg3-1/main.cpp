#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>
#include <cmath>
using namespace std;
struct Point{
    int x,y; // point coordinates
    int w=INT_MAX;  // weight
    int rest; //unit that show  the amount of stress reduction
    int index;
};
struct CompareWeight {
    bool operator()(Point * p1, Point * p2){
        return p1->w > p2->w;
    }
};
bool sortByX_withRest(Point *a, Point *b) {return (a->x) < (b->x-b->rest);}
bool sortByY_withRest(Point *a, Point *b) {return (a->y) < (b->y-b->rest);}
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
            distance[i][j] = weight(points[i],list[i][j])-list[i][j]->rest;
        }
    }
}

bool Ford_Bellman(vector<Point *> list[],int n,Point points[], int s, int distance[][4]){
    points[s].w=0; // start
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n; j++)
             for(int k=0; k<list[j].size(); k++){
                if(points[j].w != INT_MAX && (list[j][k]->w > points[j].w+distance[j][k]))
                    list[j][k]->w = points[j].w+distance[j][k];
             }
    for(int j=0; j<n; j++)
             for(int k=0; k<list[j].size(); k++)
                if(points[j].w != INT_MAX && (list[j][k]->w > points[j].w+distance[j][k]))
                   return false;
    return true;
}

int main(){
ios_base::sync_with_stdio(false);
    int n; // number of stops
    int s; // start point coordinates
    int d; // end point cordintes
    int v; // unit that show  the amount of stress reduction
        cin >> n;
        vector<Point *> neighborsList[n];
        int distance[n][4];//distance from neighbor
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
    countDistance(neighborsList,n,points,distance);

    if(Ford_Bellman(neighborsList,n,points,s,distance))
        cout << points[d].w;
    else
        cout << "NIE ZA DOBRZE?";
    return 0;
}

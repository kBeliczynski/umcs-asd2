#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define PI 3.141592653589793238462643383279502884197169
using namespace std;

class Point{
    double x,y;
    double degree;
    double distance;

    double calculateDegree(){
        double result = atan2(y,x);
        if(result < 0)
            return (result+2.0*PI)*180.0/PI;
        return result*180.0/PI;
    }
    double calculateDistance(){return hypot(x,y);}
public:
    Point(double x,double y){
        this->x = x;
        this->y = y;
        this->degree = calculateDegree();
        this->distance = calculateDistance();
    }
    double getX(){return x;}
    double getY(){return y;}
    double getDegree(){return degree;}
    double getDistance(){return distance;}
    void showPoint(){cout << x << " " << y << endl;}
};

bool compareByDegree(Point * first, Point * second){return first->getDegree() < second->getDegree();}

int main(){
ios_base::sync_with_stdio(false);
    int n;
    double x,y;

    cin >> n;
    vector<Point *> points;
    for(int i=0; i<n; i++){
        cin >> x >> y;
        Point * p = new Point(x,y);
        points.push_back(p);
    }
    sort(points.begin(),points.end(),compareByDegree);
    Point tmpPoint = *points[0];

   for(auto var : points){
        if(tmpPoint.getDegree() != var->getDegree()){
            if(tmpPoint.getX() != 0 || tmpPoint.getY() != 0){
//                cout << tmpPoint.getDegree() << " ";
                tmpPoint.showPoint();
                }
            tmpPoint = *var;
        }else
            if(tmpPoint.getDistance() < var->getDistance())
                tmpPoint = *var;
   }
//   cout << tmpPoint.getDegree() << " ";
   tmpPoint.showPoint();
   return 0;
}

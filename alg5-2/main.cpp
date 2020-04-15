#include <iostream>

using namespace std;

bool findConnect(int n,int m,bool ** connections, int a,bool seen[], int occupied[]){

    for (int b = 0; b < m; b++){
        if (connections[a][b] && !seen[b]){
            seen[b] = true;
            if (occupied[b] < 0){
                occupied[b] = a;
                return true;
            }else {
                if(findConnect(n,m,connections, occupied[b],seen, occupied)){
                occupied[b] = a;
                return true;
                }
            }
        }
    }
    return false;
}

int allConnects(long int n, long int m, bool ** connections){
    int occupied[m];
    for(int i=0; i<m; i++)
        occupied[i]=-1;
    int result = 0;
    for (int a = 0; a < n; a++){
        bool seen[m];
        for(int j=0; j<m; j++)
            seen[j] = 0;
        if (findConnect(n,m,connections, a, seen, occupied))
        result++;
    }
    return result;
}
int main(){
    ios_base::sync_with_stdio(false);
    int n; // amount of people
    int m; // amount of meals
    int l; // people for meals
    char c;

    cin >> n >> m >> l;

    bool ** connections = new bool*[n];
    for(int i=0; i<n; i++)
        connections[i] = new bool[m*l];

    for(int i=0; i<n; i++){
        int tmp=0;
        for(int j=0; j<m; j++){
            cin >> c;
            if(c == 'x'){
               for(int k=0; k<l; k++){
                  connections[i][tmp] = 1;
                  tmp++;
                  }
            }else{
            for(int k=0; k<l; k++){
                  connections[i][tmp] = 0;
                  tmp++;
                  }
            }

        }
    }
    cout << allConnects(n,m*l,connections) << endl;

    return 0;
}

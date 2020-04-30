#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<vector<double> > equation(n,vector<double>(n+1));
    for(int i=0;i<n;i++){
        for(int j=0;j<=n;j++){
            cin>>equation[i][j];
        }
    }
    for(int i=0;i<n;i++){
        if(equation[i][i]==0){
            int c=1;
            while(i+c<n && equation[i+c][i]==0)
                c++;
            if(i+c==n)
                assert(false);
            swap(equation[i],equation[i+c]);
        }
        for(int j=0;j<n;j++){
            if(i==j)
                continue;
            double factor = equation[j][i]/equation[i][i];
            for(int k=0;k<=n;k++){
                equation[j][k] -= equation[i][k]*factor;
            }
        }
    }
    for(int i=0;i<n;i++){
        printf("%.6f ",equation[i][n]/equation[i][i]);
    }
    return 0;
}

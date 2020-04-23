#include<bits/stdc++.h>
using namespace std;

class BipartiteMatching{
private:
    int L,R;
    vector< vector<int> > graph;
    vector<int> matchL,matchR;
    vector<bool> vis;
public:
    BipartiteMatching(int L,int R):
        L(L), R(R), graph(vector< vector<int> >(L,vector<int>(R))),
        matchL(vector<int>(L,-2)), matchR(vector<int>(R,-2))
        { }
    void readData(){
        for(int u=0; u<L; u++)
            for(int v=0; v<R; v++)
                cin>>graph[u][v];
    }
    bool findMatch(int u){
        if(vis[u])
            return false;
        vis[u] = true;
        for(int v=0; v<R; v++){
            if(graph[u][v]){
                if(matchR[v]<0 || findMatch(matchR[v])){
                    matchL[u] = v;
                    matchR[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    void findMaxMatch(){
        for(int u=0; u<L; u++){
            vis = vector<bool>(L,false);
            findMatch(u);
        }
    }
    void printMatches(){
        for(int u=0; u<L; u++)
            cout<<matchL[u]+1<<" ";
        cout<<endl;
    }
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N,M;
    cin>>N>>M;
    BipartiteMatching bpm(N,M);
    bpm.readData();
    bpm.findMaxMatch();
    bpm.printMatches();
    return 0;
}

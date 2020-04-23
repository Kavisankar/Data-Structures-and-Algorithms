#include<bits/stdc++.h>
using namespace std;

bool bfs(vector<vector <int> >& edge, vector<int>& parant){
    int vertices = edge.size();
    vector<bool> visited(vertices,false);
    queue<int> q;
    q.push(0);
    visited[0] = true;
    parant[0] = -1;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v=0;v<vertices;v++){
            if(!visited[v] && edge[u][v]){
                q.push(v);
                visited[v] = true;
                parant[v] = u;
            }
        }
    }
    return visited[vertices-1];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int vertices, edge_count;
    cin>>vertices>>edge_count;
    vector< vector<int> > edge(vertices,vector<int>(vertices,0));
    int x,y,w;
    for(int i=0;i<edge_count;i++){
        cin>>x>>y>>w;
        edge[x-1][y-1] += w;
    }
    int max_flow = 0;
    int flow;
    vector<int> parant(vertices,-1);
    while(bfs(edge,parant)){
        int path_flow = INT_MAX;
        for(int v=vertices-1;v!=0;v=parant[v]){
            int u = parant[v];
            if(path_flow>edge[u][v])
                path_flow = edge[u][v];
        }
        max_flow+=path_flow;
        for(int v=vertices-1;v!=0;v=parant[v]){
            int u = parant[v];
            edge[u][v]-=path_flow;
            edge[v][u]+=path_flow;
        }
    }
    cout<<max_flow<<endl;
}

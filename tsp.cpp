#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct TSP{
private:
	struct node{
		int dist{INF};
		int parent{0};
	};
	
	int no_ver,no_edge,max_weight;
	vector<vector<int>> graph;
	vector<vector<node>> cost;
	vector<int> solution;
	
	void read(){
		std::ios::sync_with_stdio(false);
		
		cin>>no_ver>>no_edge;
		graph = vector<vector<int>>(no_ver,vector<int>(no_ver,INF));
		cost = vector<vector<node>>(1<<no_ver,vector<node>(no_ver));
		
		for(int i=0, from, to, weight; i<no_edge; i++){
			cin >> from >> to >> weight;
			--from;
			--to;
			graph[from][to] = graph[to][from] = weight;
		}
		
		for(int i=1; i<no_ver; i++){
			cost[1<<i][i] = node{graph[0][i], 0};
		}
	}
	
	vector<int> combination(int n){
		vector<int> comb;
		bitset<16> bset = n;
		
		for(auto k=0u; k<bset.size(); k++){
			if(bset[k]){
				comb.emplace_back(k+1);
			}
		}
		
		return comb;
	}
	
	void backtrack_optimal(){
		node min_node;
		int bits = (1<<no_ver) - 2;
		
		for(int k=1; k<no_ver; k++){
			if(min_node.dist > cost[bits][k].dist + graph[k][0]){
				min_node.dist = cost[bits][k].dist + graph[k][0];
				min_node.parent = k;
			}
		}
		
		if(min_node.dist == INF){
			max_weight = -1;
			return;
		}
		
		max_weight = min_node.dist;
		solution.clear();
		solution.resize(no_ver);
		solution[0] = 1;
		
		for(int i=1; i<no_ver; i++){
			solution[i] = min_node.parent +1;
			min_node.parent = cost[bits][min_node.parent].parent;
			bits = bits ^ (1<<(solution[i]-1));
		}
		
	}
	
	void solve(){
		for(int s=2; s < 1<<(no_ver-1); s++){
			if(s&(s-1)){
				vector<int> subset = combination(s);
				int bits = s*2;
				
				for(auto k: subset){
					int prev = bits ^ (1<<k);
					node min_node;
					
					for(auto m: subset){
						if(k!=m && cost[prev][m].dist + graph[m][k] < min_node.dist){
							min_node = node{cost[prev][m].dist + graph[m][k], m};
						}
					}
					
					cost[bits][k] = min_node;
				}
			}
		}
		
		backtrack_optimal();
	}
	
	void print(){
		cout<<max_weight<<endl;
		if(max_weight==-1)
			return;
		for(int i=0;i<no_ver; i++){
			cout<<solution[i]<<' ';
		}
		cout<<endl;
	}
	
public:
	void run(){
		read();
		solve();
		print();
	}
};


int main(){
	TSP obj;
	obj.run();
	return 0;
}


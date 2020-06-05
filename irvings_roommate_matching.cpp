#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>

using namespace std;
void propose(int u, int N, vector<vector<int>>& graph, vector<int>& best, vector<int>& remaining);

void remove(int u, int v, int N, vector<vector<int>>& graph, vector<int>& remaining){
	if(u == -1){
		return;
	}
	for(int i=1; i<N; i++){
		if(graph[u][i] == v){
			graph[u][i] = -1;
			remaining[u]--;
			return;
		}
	}
}

bool process_propose(int u, int v, int N, vector<vector<int>>& graph, vector<int>& best, vector<int>& remaining){
	if(best[u] == -1){
		best[u] = v;
		return true;
	}
	int curr = best[u];
	for(int i=1; i<N; i++){
		if(graph[u][i] == curr)
			return false;
		if(graph[u][i] == v){
			best[u] = v;
			propose(curr, N, graph, best, remaining);
			return true;
		}
	}
	return false;
}

void propose(int u, int N, vector<vector<int>>& graph, vector<int>& best, vector<int>& remaining){
	for(int i=1; i<N; i++){
		if(graph[u][i] != -1){
			if(process_propose(graph[u][i], u, N, graph, best, remaining))
				return;
			remaining[u]--;
			graph[u][i] = -1;
		}
	}
}

void debug(int N, vector<vector<int>>& graph, vector<int>& best, vector<int>& remaining){
	
	cerr << '\n';
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			cerr << graph[i][j] << ' ';
		}
		cerr << best[i] << ' ' << remaining[i] << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(11);
	cerr << fixed << setprecision(6);
	
	int N;
	cin >> N;
	
	unordered_map<int, string> members(N);
	unordered_map<string, int> ids(N);
	
	vector<vector<string>> input(N, vector<string>(N));
	
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			cin >> input[i][j];
		}
		members[i] = input[i][0];
		ids[input[i][0]] = i;
	}
	
	vector<vector<int>> graph(N, vector<int>(N));
	
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			graph[i][j] = ids[input[i][j]];
		}
	}
	
	
	vector<int> best(N, -1);
	vector<int> remaining(N, N-1);
	
	debug(N, graph, best, remaining);
	
	for(int i=0; i<N; i++){
		propose(i, N, graph, best, remaining);
	}
	
	debug(N, graph, best, remaining);

	for(int i=0; i<N; i++){
		if(!remaining[i]){
			cout << "No suitable pairs\n";
			return 0;
		}
	}
	
	
	for(int i=0; i<N; i++){
		for(int j=N-1; graph[i][j] != best[i]; j--){
			if(graph[i][j] != -1){
				remaining[i]--;
				remove(graph[i][j], i, N, graph, remaining);
				graph[i][j] = -1;
			}
		}
	}
	
	
	debug(N, graph, best, remaining);
	
	
	while(true){
		int u = -1;
		for(int i=0; i<N; i++){
			if(remaining[i] > 1){
				u = i;
				break;
			}
		}
		
		if(u == -1){
			break;
		}
		
		vector<bool> vis(N);
		deque<int> p,q;
		p.emplace_back(u);
		
		while(!vis[u]){
			vis[u] = true;
			int v = 1;
			while(v<N){
				if(graph[u][v] != -1)
					break;
				v++;
			}
			v++;
			while(v<N){
				if(graph[u][v] != -1)
					break;
				v++;
			}
			v = graph[u][v];
			if(vis[v])
				break;
			
			u = N-1;
			while(u>0){
				if(graph[v][u] != -1){
					break;
				}
				u--;
			}
			vis[v] = true;
			u = graph[v][u];
			p.emplace_back(u);
			q.emplace_back(v);
		}
		
		while(!q.empty()){
			remove(p.back(), q.back(), N, graph, remaining);
			remove(q.back(), p.back(), N, graph, remaining);
			p.pop_back();
			q.pop_back();
		}
				
	}
	
	
	for(int i=0; i<N; i++){
		if(!remaining[i]){
			cout << "No suitable pairs\n";
			return 0;
		}
	}
	
	debug(N, graph, best, remaining);
	
	vector<bool> vis(N);
	
	for(int i=0; i<N; i++){
		if(!vis[i]){
			cout << i << ' ';
			for(int j=1; j<N; j++){
				if(graph[i][j] != -1){
					cout << graph[i][j];
					vis[graph[i][j]] = true;
					break;
				}
			}
			cout << '\n';
		}
	}
	
	
	return 0;
}


#include<bits/stdc++.h>
using namespace std;

const int MAX = numeric_limits<int>::max();

struct Three_col{
private:
	struct util{
		int index, lowlink;
		bool on_stack;
		util()
			: index{MAX}
			, lowlink{MAX}
			, on_stack{false}
		{}
		vector<int> edges;
	};
		
	int N, M, no_var, t;
	stack<int> stk;
	unordered_map<int, util> graph;
	string org_col;
	vector<int> sol;
	bool sat;
	void read(){
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);
		cin >> N >> M;
		cin >> org_col;
		sat = true;
		no_var = 3 * N;
		graph = unordered_map<int, util>(2 * no_var + 1);
		sol = vector<int>(no_var+1, -1);
		for(int i=0, n=1; i<N; i++, n+=3){
			switch(org_col[i]){
				case 'R':
					graph[-(n+1)].edges.push_back(n+2);
					graph[-(n+2)].edges.push_back(n+1);
					graph[(n+1)].edges.push_back(-(n+2));
					graph[(n+2)].edges.push_back(-(n+1));
					graph[(n)].edges.push_back(-n);
					break;
				case 'G':
					graph[-(n)].edges.push_back(n+2);
					graph[-(n+2)].edges.push_back(n);
					graph[(n)].edges.push_back(-(n+2));
					graph[(n+2)].edges.push_back(-(n));
					graph[n+1].edges.push_back(-(n+1));
					break;
				case 'B':
					graph[-(n)].edges.push_back(n+1);
					graph[-(n+1)].edges.push_back(n);
					graph[(n)].edges.push_back(-(n+1));
					graph[(n+1)].edges.push_back(-(n));
					graph[n+2].edges.push_back(-(n+2));
					break;
			}
		}
		for(int i=0, from, to; i<M; i++){
			cin >> from >> to;
			from = from * 3 - 2;
			to = to * 3 - 2;
			graph[from].edges.push_back(-(to));
			graph[to].edges.push_back(-(from));
			graph[from+1].edges.push_back(-(to+1));
			graph[to+1].edges.push_back(-(from+1));
			graph[from+2].edges.push_back(-(to+2));
			graph[to+2].edges.push_back(-(from+2));
		}
	}
	
	void dfs(int u){
		
		auto& utl = graph[u];
		utl.lowlink = utl.index = t++;
		utl.on_stack = true;
		stk.push(u);
		
		for(int v: utl.edges){
			if(graph[v].index == MAX){
				dfs(v);
			}
			if(graph[v].on_stack){
				utl.lowlink = min(utl.lowlink, graph[v].lowlink);
			}
		}
		
		if(utl.lowlink == utl.index){
			int v;
			do{
				v = stk.top();
				stk.pop();
				
				if(utl.lowlink == graph[-v].lowlink){
					sat = false;
					return;
				}
				
				graph[v].on_stack = false;
				graph[v].lowlink = utl.lowlink;
				
				if(sol[abs(v)] == -1)
					sol[abs(v)] = v < 0 ? 0 : 1;
			} while(u != v);
		}
	}
	
	void solve(){
		t = 0;
		for(int i = -no_var; i < no_var && sat; i++){
			if(i && graph[i].lowlink == MAX){
				dfs(i);
			}
		}
	}
	
	void print(){
		if(sat){
			char colors[4] = "RGB";
			for(int i=0; i<no_var; i++){
				//clog<<sol[i+1];
				if(sol[i+1])
					printf("%c", colors[i%3]);
			}
			printf("\n");
		}
		else{
			printf("Impossible\n");
		}
	}
	
public:
	void run(){
		read();
		solve();
		print();
	}
};

int main(){
	Three_col obj;
	obj.run();
	return 0;	
}

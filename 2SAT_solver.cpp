#include<bits/stdc++.h>
using namespace std;

const int MIN = numeric_limits<int>::min();

struct SAT2{
private:
	struct util{
		util()
			: index {MIN}
			, lowlink {MIN}
			, id {-1}
			, on_stack {false}
		{}
		int index, lowlink, id;
		bool on_stack;
		vector<int> edges;
	};
	
	
	bool is_sat;
	int no_clause, no_var, t{0}, id{0};
	unordered_map<int, util> graph;
	vector<bool> solution;
	stack<int> stk;
	
	void read(){
		cin>>no_var>>no_clause;
		is_sat = true;
		graph  = unordered_map<int, util>(no_var * 2);
		solution = vector<bool>(no_var+1);
		for(int i=0,x,y;i<no_clause;i++){
			cin >> x >> y;
			graph[-x].edges.emplace_back(y);
			graph[-y].edges.emplace_back(x);
		}
	}
	
	void process_vertex(int u){
		auto& utl = graph[u];
		utl.lowlink = utl.index = t++;
		utl.on_stack = true;
		stk.push(u);
		
		for(int v: utl.edges){
			if(graph[v].index ==MIN){
				process_vertex(v);
				utl.lowlink = min(utl.lowlink, graph[v].lowlink);
			}
			else if(graph[v].on_stack){
				utl.lowlink = min(utl.lowlink, graph[v].index);
			}
		}
		
		if(utl.lowlink == utl.index){
			int v;
			do{
				v = stk.top();
				stk.pop();
				
				if(id == graph[-v].id){
					is_sat = false;
					return;
				}
				
				graph[v].on_stack = false;
				graph[v].id = id;
				
				solution[abs(v)] = v < 0 ? true : false;
			} while(u != v);
			++id;
		}
	}
	
	void solve() {
		for(int i = -no_var; i<=no_var; i++){
			if(i && graph[i].index == MIN)
				process_vertex(i);
		}
	}
	
	void print(){
		if(!is_sat){
			cout<<"UNSATISFIABLE\n";
		}
		else{
			cout<<"SATISFIABLE\n";
			for(int i=1; i<=no_var; i++)
				cout<<(solution[i] ? i : -i)<<' ';
			cout<<endl;
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
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	SAT2 obj;
	obj.run();
	return 0;
}

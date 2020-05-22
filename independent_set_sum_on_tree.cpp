#include<bits/stdc++.h>

using ll =  long long;

using namespace std;

struct max_independent_sets{
private:
	struct vertex{
		ll weight;
		vector<ll> edges;
	};
	
	ll no_vertex;
	vector<vertex> tree;
	vector<ll> sum;

	void read(){
		std::ios::sync_with_stdio(false);
		cin >> no_vertex;
		if(no_vertex == 0)
			return;
		tree = vector<vertex>(no_vertex+1);
		sum = vector<ll>(no_vertex+1, -1L);
		
		for(ll i=0; i<no_vertex; i++) {
			cin>>tree[i].weight;
		}
		
		for(ll i=1, from, to; i<no_vertex; i++){
			cin>>from>>to;
			tree[from-1].edges.emplace_back(to-1);
			tree[to-1].edges.emplace_back(from-1);
		}
	}
	
	ll find_max(ll v, ll par){
		if(sum[v] == -1L){
			if(tree[v].edges.empty()){
				sum[v] = tree[v].weight;
			}
			else {
				ll s = tree[v].weight;
				for(auto i: tree[v].edges){
					if(i!=par){
						for(auto j: tree[i].edges){
							if(j!=v){
								s += find_max(j,i);
							}
						}
					}
				}
				
				sum[v] = s;
				s = 0;
				
				for(auto i: tree[v].edges){
					if(i!=par){
						s += find_max(i,v);
					}
				}
				if(s > sum[v]){
					sum[v] = s;
				}
			}
		}
		return sum[v];
	}
	
	void solve() {
		if(no_vertex == 0)
			cout<<'0'<<endl;
		else
			cout<<find_max(0,-1)<<endl;
	}

public:
	void run(){
		read();
		solve();
	}
	
};

int main(){
	max_independent_sets obj;
	obj.run();
	return 0;
}


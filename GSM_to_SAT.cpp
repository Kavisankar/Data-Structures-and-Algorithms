#include <bits/stdc++.h>
using namespace std;

struct GSM_To_SAT{
	void read(){
		cin>>N>>M;
		edge_list = vector<pair<int,int>>(M);
		for(int i=0;i<M;i++){
			cin>>edge_list[i].first>>edge_list[i].second;
		}
	}
	
	void solve(){
		int no_of_clause = 3*M+N;
		int no_of_variables = 3*N;
		printf("%d %d\n",no_of_clause,no_of_variables);
		for(int i=0,k=1;i<N;i++,k+=3){
			printf("%d %d %d 0\n",k,k+1,k+2);
		}
		for(int i=0;i<M;i++){
			int v1 = edge_list[i].first*3;
			int v2 = edge_list[i].second*3;
			printf("%d %d 0\n",-v1+2,-v2+2);
			printf("%d %d 0\n",-v1+1,-v2+1);
			printf("%d %d 0\n",-v1,-v2);
		}
		//printf("\n");
	}
	
	void run(){
		read();
		solve();
	}
	
private:
	int N,M;
	vector<pair<int,int>> edge_list;
};


int main(){
	GSM_To_SAT obj;
	obj.run();
	return 0;
}

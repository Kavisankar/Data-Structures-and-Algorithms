#include <bits/stdc++.h>
using namespace std;

struct Hamiltonian_path_to_SAT{
	void read(){
		cin>>N>>M;
		variables = vector<vector<int>>(N,vector<int>(N));
		for(int i=0,cnt=0;i<N;i++){
			for(int j=0;j<N;j++){
				variables[i][j] = ++cnt;
			}
		}
		matrix = vector<vector<bool>>(N,vector<bool>(N));
		int from,to,rep=0;
		for(int i=0;i<M;i++){
			cin>>from>>to;
			if(matrix[from-1][to-1])
				rep++;
			matrix[from-1][to-1] = true;
			matrix[to-1][from-1] = true;
		}
		M-=rep;
	}
	
	void each_edge_atleast_once(){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				printf("%d ",variables[i][j]);
			}
			printf("0\n");
		}
	}
	
	void each_edge_atmost_once(){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				for(int k=i+1;k<N;k++){
					printf("%d %d 0\n",-variables[i][j],-variables[k][j]);
				}
			}
		}
	}
	
	void each_position_atleast_once(){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				printf("%d ",variables[j][i]);
			}
			printf("0\n");
		}
	}
	
	void each_position_atmost_once(){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				for(int k=j+1;k<N;k++){
					printf("%d %d 0\n",-variables[i][j],-variables[i][k]);
				}
			}
		}
	}
	
	void non_adjacent_should_not_adjacent(){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(i!=j && !matrix[i][j]){
					for(int k=1;k<N;k++){
						printf("%d %d 0\n",-variables[i][k-1],-variables[j][k]);
					}
				}
			}
		}				
	}
	
	void solve(){
		int no_of_variables = N*N;
		int no_of_clause = (no_of_variables*(N-1))+(2*N)+(no_of_variables-M-M-N)*(N-1);
		printf("%d %d\n",no_of_clause,no_of_variables);
		each_edge_atleast_once();
		each_edge_atmost_once();
		each_position_atleast_once();
		each_position_atmost_once();
		non_adjacent_should_not_adjacent();
	}
	
	void run(){
		read();
		solve();
	}
	
private:
	int N,M;
	vector<vector<bool>> matrix;
	vector<vector<int>> variables;
};


int main(){
	Hamiltonian_path_to_SAT obj;
	obj.run();
	return 0;
}

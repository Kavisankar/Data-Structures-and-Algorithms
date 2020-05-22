
#include <bits/stdc++.h>
using namespace std;

struct ILP_to_SAT{
	void read(){
		cin>>N>>M;
		A = vector<vector<int>>(N,vector<int>(M));
		B = vector<int>(N);
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				cin>>A[i][j];
			}
		}
		for(int i=0;i<N;i++){
			cin>>B[i];
		}
	}
	
	void solve(){
		int clause_cnt = 0;
		for(int i=0;i<N;i++){
			const auto& row = A[i];
			int n = count_if(row.begin(),row.end(),[](const auto& x){ return x!=0; });
			n = 1<<n;
			for(int j=0;j<n;j++){
				combinations = j;
				
				int sum=0,comp=0;
				for(const int x: row){
					if(x!=0 && combinations[comp++]){
						sum+=x;
					}
				}
				
				if(sum>B[i]){
					comp=0;
					for(int k=0;k<(int)row.size();k++){
						if(row[k]!=0){
							clause_stream += (combinations[comp++]?to_string(-k-1):to_string(k+1)) + ' ';
						}
					}
					clause_stream+="0 \n";
					clause_cnt++;
				}
			}
		}
		
		if(clause_cnt==0){
			clause_cnt++;
			clause_stream = "1 -1 0\n";
		}
		
		printf("%d %d\n%s",clause_cnt,(int)A[0].size(),clause_stream.c_str());
							
	}
	
	void run(){
		read();
		solve();
	}
	
private:
	int N,M;
	vector<vector<int>> A;
	vector<int> B;
	string clause_stream;
	bitset<32> combinations;
};


int main(){
	ILP_to_SAT obj;
	obj.run();
	return 0;
}

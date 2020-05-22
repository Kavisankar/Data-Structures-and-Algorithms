#include<bits/stdc++.h>
using namespace std;

using Matrix = vector<vector<long double>>;
using Vector =  vector<long double>;

struct Simplex{
	
private:
	static long double EPS;
	static size_t PRECISION;
	static size_t SML_PRECISION;
	static size_t SML_WIDTH;
	int N,M;
	Matrix A;
	Vector B;
	Vector basic_var;
	bool has_mixed_cons{false};
	
	
	void logMatrix(){
		for(size_t i=0;i<A.size();i++){
			for(size_t j=0;j<A[0].size();j++){
				clog<<fixed<<setw(SML_WIDTH)<<setprecision(SML_PRECISION)<<A[i][j]<<' ';
			}
			clog<<fixed<<setw(SML_WIDTH)<<setprecision(SML_PRECISION)<<B[i]<<endl;
		}
		clog<<endl;
	}
	
	void log_basic_var(){
		for(int i=0;i<N;i++){
			clog<<basic_var[i]<<" ";
		}
		clog<<endl;
	}
	
	bool equ_zero(long double x){
		return fabs(x-0.0)<EPS;
	}
	
	void readInput(){
		cin>>N>>M;
		A = Matrix(N+1,Vector(M+N));
		B = Vector(N+1);
		basic_var = Vector(N);
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				cin>>A[i][j];
			}
			A[i][M+i] = 1;
			basic_var[i] = M+i;
		}
		for(int i=0;i<N;i++){
			cin>>B[i];
		}
		for(int i=0;i<M;i++){
			cin>>A[N][i];
		}
		transform(A[N].begin(),A[N].end(),A[N].begin(),negate<long double>());
	}
	
	void check_mixed_cons(){
		for(int i=0;i<N;i++){
			if(B[i]<0.0){
				has_mixed_cons = true;
				return;
			}
		}
	}
	
	void prepare_mixed_cons(){
		int len = N+N+M;
		Vector W(len);
		B.push_back(0.0);
		for(int i=0,k=N+M;i<N;i++,k++){
			A[i].resize(len);
			if(B[i]<0.0){
				for(int j=0;j<N+M;j++){
					W[j] += A[i][j];
					A[i][j] = -A[i][j];
				}
				A[i][k] = 1.0;
				B[N+1] += B[i];
				B[i] = -B[i];
			}
		}
		A.back().resize(len);
		A.push_back(W);
	}
	
	void resize_matrix(){
		int len = N+M;
		B.pop_back();
		A.pop_back();
		for(int i=0;i<=N;i++){
			A[i].resize(len);
		}
	}
	
	void gaussian_elimination(int wid,int len){
		while(true){
			//logMatrix();
			int col = -1;
			long double min_val = -EPS;
			for(int i=0;i<len;i++){
				if(A[wid-1][i]<min_val){
					min_val = A[wid-1][i];
					col = i;
				}
			}
			if(col==-1)
				return;
			int row = -1;
			long double factor;
			min_val = numeric_limits<long double>::max()-1;
			for(int i=0;i<N;i++){
				factor = B[i]/A[i][col];
				if((A[i][col]>0.0 || A[i][col]<0.0) && factor-min_val < EPS && factor>0.0 ){
					min_val = factor;
					row = i;
				}
			}
			if(row == -1){
				throw 1;
			}
			basic_var[row] = col;
			for(int i=0;i<wid;i++){
				if(i==row)
					continue;
				factor = A[i][col]/A[row][col];
				for(int j=0;j<len;j++){
					A[i][j] -= factor*A[row][j];
				}
				A[i][col]=0.0;
				B[i] -= factor*B[row];
			}
				
		}
	}
	
	void handle_mixed_cons(){
		prepare_mixed_cons();
		gaussian_elimination(A.size(),A[0].size());
		//logMatrix();
		if(!equ_zero(B.back())){
			throw -1;
		}
		resize_matrix();
	}
	
	void printSolution(){
		Vector sol(M);
		for(int i=0;i<N;i++){
			int x = basic_var[i];
			if(x<M){
				sol[x] = B[i]/A[i][x];
			}
		}
		cout<<"Bounded solution"<<endl;
		for(int i=0;i<M;i++){
			cout<<fixed<<setprecision(PRECISION)<<sol[i]<<' ';
		}
		cout<<endl;
	}
	
public:
	void process(){
		try{
			readInput();
			check_mixed_cons();
			if(has_mixed_cons){
				handle_mixed_cons();
			}
			gaussian_elimination(A.size(),A[0].size());
			logMatrix();
			log_basic_var();
			printSolution();
		}
		catch(int x){
			//logMatrix();
			if(x==-1){
				cout<<"No solution"<<endl;
			}
			else{
				cout<<"Infinity"<<endl;
			}
		}
	}
	
};

long double Simplex::EPS = 0.0001;
size_t Simplex::PRECISION = 20;
size_t Simplex::SML_PRECISION = 2;
size_t Simplex::SML_WIDTH = 5;

int main(){
	Simplex sx;
	sx.process();
	return 0;
}


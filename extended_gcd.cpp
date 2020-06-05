#include<bits/stdc++.h>
using namespace std;

long long extended_gcd(long long a, long long b, long long& x, long long &y){
	if(!b){
		x = 1L;
		y = 0;
		return a;
	}
	long long x1,y1;
	long long g = extended_gcd(b, a%b, x1, y1);
	x = y1;
	y = x1 - y1 * (a/b);
	return g;
}

int main(){
	long long a, b, x, y;
	cout << "Enter a & b : ";
	cin >> a >> b;
	long long g = extended_gcd(a, b, x, y);
	cout << a << '*' << x << " + " << b << '*' << y << " = " << g << '\n';
	return 0;
}

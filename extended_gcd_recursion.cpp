#include<bits/stdc++.h>
using namespace std;

long long extended_gcd(long long a, long long b, long long& x, long long &y){
	x = 1;
	y = 0;
	long long x1 = 0, y1 = 1, t, q;
	while(b){
		q = a / b;
		t = x;
		x = x1;
		x1 = t - q * x1;
		t = y;
		y = y1;
		y1 = t - q * y1;
		t = a;
		a = b;
		b = t - q * b;
	}
	return a;
}

int main(){
	long long a, b, x, y;
	cout << "Enter a & b : ";
	cin >> a >> b;
	long long g = extended_gcd(a, b, x, y);
	cout << a << '*' << x << " + " << b << '*' << y << " = " << g << '\n';
	return 0;
}

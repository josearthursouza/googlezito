#include<iostream>
using std::cout;
using std::endl;
#include <typeinfo>
#include <algorithm>    
using std::min;
#include <chrono>

int main(){
	
	auto start = std::chrono::steady_clock::now();
	cout<<min(1,2)<<endl;
	auto end = std::chrono::steady_clock::now();
	
	std::chrono::duration<double> diff = end-start;
	cout << typeid(diff).name() ;
	return 0;
}

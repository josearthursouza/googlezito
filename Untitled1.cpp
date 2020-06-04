#include<iostream>
using std::cout;
using std::cin;
using std::endl;
#include<fstream>
using std::ifstream;
#include<sstream>

#include<string>
using std::stringstream;
using std::string;
using std::getline;
using std::to_string;

void a(){
	string txt;
	ifstream dados;
	dados.open("textos_teste.txt");
	for(int i;i<4;i++){
		getline(dados,txt);
	}
	cout<<txt;
}

void chaaar(int j){
	string a="";
	int i=1;
	int k=0;
	int l;
	while((j/i) >=1){
		i*=10;
		k++;
	}
	cout<<k;
	for(k;k<=0;k--){
		cout<<i;
		i/=10;
	}
}

int main(){
	int i=136;
	cout<<to_string(i);
	
	return 0;
}

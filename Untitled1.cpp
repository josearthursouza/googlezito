#include<iostream>
using std::cout;
using std::cin;
using std::endl;
#include<fstream>
using std::ifstream;
#include<sstream>

#include<string>
using std::string;
using std::getline;

void a(){
	string txt;
	ifstream dados;
	dados.open("textos_teste.txt");
	for(int i;i<4;i++){
		getline(dados,txt);
	}
	cout<<txt;
}

int main(){
	a();
	
	return 0;
}

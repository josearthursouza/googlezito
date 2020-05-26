#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include<string>
using std::string;
using std::getline;

#include<vector>
using namespace std; 

void printe(vector<int> g1){
    for (auto i = g1.begin(); i != g1.end(); ++i){
        cout << *i << " "; 
    }
    cout<<endl;
}

void inserir_id(vector<int> &  vec, int & id, int & len_id){
			cout <<"antes da função inserir_id, o tamanho do vec era: " <<len_id <<endl;
			for(int i=0; i<len_id; i++){
				if(vec.at(i)==id) {
					return;
				}
			}
			vec.push_back(id);
			len_id++;
			cout<<"agora, depois da função inserir_id, o tamanho do vec é: "<< len_id <<endl << "e o vec é: ";
			printe(vec);
			cout<< "---------------" <<endl;
			return;
		}

void procura_id(vector<int> vec, int id, int nn){
	if(nn>=1){
		//particion
		int n=(nn/2)+1;
		if(vec.at(n)>=id){
		//	procura_id(vec[0:n-2], id, n-1)
		}
		else{
		//	procura_id(vec[n-1:nn], id, n)
		}
	}
	else{
		if(nn==1){
			
		}
		else{
			
		}
	}
	
	
}



int main(){
	int a=3;
	cout<< a <<endl <<~a <<endl ;
	return 0;
}

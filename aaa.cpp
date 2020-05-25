#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include<string>
using std::string;
using std::getline;

#include<vector>
using namespace std; 

void inserir_id(vector<int> vec, int id, int len_id){
			for(int i=0; i<len_id; i++){
				if(vec.at(i)==id){
					return;
				}
			}
			vec.push_back(id);
			len_id++;
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

void printe(vector<int> g1){
    for (auto i = g1.begin(); i != g1.end(); ++i){
        cout << *i << " "; 
    }
    cout<<endl;
}

int main(){
	vector<int> vec;
	int len_id=0;
	inserir_id(vec, 1,len_id);
	inserir_id(vec,2,len_id);
	inserir_id(vec,1,len_id);
	cout<<len_id <<endl;
	
	return 0;
}

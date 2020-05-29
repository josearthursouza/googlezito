

#include<iostream>
using std::cout;
using std::cin;
using std::endl;
#include<fstream>
#include<sstream>

#include<string>
using std::string;
using std::getline;

#include<vector>
using namespace std; 

#include <chrono> 
using namespace std::chrono;

struct Node{
    char data; //um node tem um dado char
	bool fim; //0:a palavra n acabou; 1:a palavra acabou
    Node* pP; //ponteiro para o pai; ajudara na busca por palavras semelhantes
	Node* pchild[26]; //lista de chars possiveis a seguir
	vector<int> vec;
	int len_id;

	
    Node(char x):data(x), fim(0), pP(nullptr), len_id(0) {
	for(int i=0;i<26;i++){
		pchild[i]=nullptr; //a principio n faremos ponteiro nenhu se n precisar
	}
	}
	
	Node(): fim(0), pP(nullptr), len_id(0) {
	for(int i=0;i<26;i++){
		pchild[i]=nullptr; //a principio n faremos ponteiro nenhu se n precisar
	}
	}
};

class busca{
	private:
		Node *pRoot;
		string titulos[3];
		
	public:
		
	busca(){ //FUTURO CONSTRUTOR
			pRoot=new Node();
		}
		
		//~busca(){ //FUTURO DESTRUTOR
		
		int pesquisar(string word, Node* & pNode, int & ies){
			pNode=pRoot; //depois do loop este ponteiro deve apontar para o último node possível.
			ies=0; //e este deve ser o número de letras encontradas 
			for(int i=0; i< word.length(); i++){ 
			 	if(  pNode->pchild[int(word[i]) - 97] != nullptr ){ //se a letra i de word for valida em alguma palavra já existente, prosseguimos
			 		pNode = pNode->pchild[int(word[i]) - 97]; //fazemos o pNode ir pra próxima letra
			 		ies++; //aumentamos o ies
				 } 
				else{//se n, paramos aqui
					return 0; //retorn falso, pois a palavra n existe (pelo mens n inteira)
				}
			 }
    		return 1; //(retorna true pra sabermos q a palabra j[a existe)
		}
		
		void search(){
			Node* pNode=pRoot;
			int ies= 0;
			string word;
			
			while(true){
				
				cout<<"?quieres hacer una pesquisa? (s/n)" <<endl;
				getline(cin,word);
				
				if(word=="s"){
  					cout << "Digite uma palavra... ";
	  				getline(cin, word);
	  				
  					auto start = high_resolution_clock::now();
  					bool b=(pesquisar(word, pNode, ies)==1);
  					auto stop = high_resolution_clock::now();
  					if(b){
  						cout<< "achamos a palavra que você quer! "
						  	<<endl
							<<"Ela tem correspondencia no(s) seguinte(s) "
							<<pNode->len_id
							<<" titulo(s):"
							<<endl;
  						for(int i = 0; i<=pNode->len_id -1 ;i++){
	  						cout << "[" <<i <<"]....."<<titulos[pNode->vec.at(i)] <<endl;
					  	}
					  	cout <<"quer abrir algum desses titulos? (a resposta tem q ser n por enquanto)"<<endl;
					  	getline(cin, word);
					  	if(word=="n"){
					  		cout<< "ta legal!" <<endl;
						  }
					  	else{
						  cout<< "eu n disse q ainda n dava??" <<endl;
						  }
				  	}
					else{
						cout<<"Nao achamos a palavra na arvore :(" <<endl;
						sugerir(word);
						
					}
					auto duration = duration_cast<microseconds>(stop - start);
					cout << "a pesquisa foi feita em ";
					cout << duration.count()/1000000 <<" segundos... ou " << duration.count() <<" microsegundos :) "<<endl <<endl;
				}
				
				else{
					cout<< "obrigado e volte sempre!";
					return;
				}
			}
		}
		
		void inserir_titulo(string titulo, int id){
			titulos[id]=titulo;
		}
		
		void inserir(string word, int id){ //vamos inserir uma palavra
			Node* pNode=pRoot; //node para onde devemos começar a inseriri letras, considerando que parte da palavra pode já existir
			int ies= 0; //numero que indicará quantas letras da palavra já existem
			if(pesquisar(word, pNode, ies)==1){ //chamamos a função find, q retorna true caso a palavra já exista. ela tambem faz cm q ies seja o numero em q a palavra parou e pNode aponte pro ies-simo Node
				inserir_id(pNode->vec, id, pNode->len_id);
				return;
			}
			else{ //caso a palavra n exista por completo
				for(int i=ies; i< word.length(); i++){  //a partir da letra q ela n existe, prosseguimos da seguinte maneira:
					Node* &newNode = pNode->pchild[int(word[i]) - 97]; //esse é o próximo node, a principio nullptr
					newNode = new Node(word[i]); //fazemos ele apontar pra outro node
					newNode->pP=pNode; //criamos o pai dele
					pNode=newNode; //e vamos pro próximo node
					
				}
				inserir_id(pNode->vec, id, pNode->len_id);
				pNode->fim=1;
			}
			
			
		} 
		
		void printe(vector<int> g1){
    		for (auto i = g1.begin(); i != g1.end(); ++i){
        		cout << *i << " "; 
    		}
    		cout<<endl;
		}
		
		void inserir_id(vector<int> & vec, int & id, int & len_id){
			for(int i=0; i<len_id; i++){
				if(vec.at(i)==id) {
					return;
				}
			}
			vec.push_back(id);
			len_id++;
			return;
		}
		
		void inserir_idd(vector<int> & vec, int & id, int & len_id){
			vec.push_back(id);
			len_id++;
			return;
		}
		
		void sugerir(string word){
			Node* pNode=pRoot; 
			cout<<"nao encontramos a palavra " <<word <<". Sugerimos:" <<endl;
			for(int i=0; i< word.length(); i++){ 
			 	if(  pNode->pchild[int(word[i]) - 97] != nullptr ){ 
			 		pNode = pNode->pchild[int(word[i]) - 97];
			 		cout<< word[i] <<endl;
				 } 
				else{
					for(int j=0; j<26; j++){
						if( pNode->pchild[j] != nullptr ){
							cout <<char(j+97) <<" " ;
						}
					}
					cout<<endl <<endl;
					return;
				}
			 }
			
		}
		
		void compaquitar(){
			
		}
	
	
	
};

int main(){
	Node* pNode;
	int ies;
	string titulos[3];
	busca b;
	ifstream dados;
	dados.open("vai_dar_certo.txt");
	for(int i=0;i<3;i++){
		string id;
		getline(dados,id);
		string titulo;
		getline(dados,titulo);
		titulos[i] = titulo;
		
		string palavras;
		getline(dados,palavras);
		stringstream split;
		split << palavras;
		string word;
		b.inserir_titulo(titulo, i);
		while(split >> word){
			b.inserir(word,i);
		}
	}
	//string w="abacace";
	//b.sugerir(w);
	//w="streng";
	//b.sugerir(w);
	b.search();
	delete[] pNode;
	return 0;
}

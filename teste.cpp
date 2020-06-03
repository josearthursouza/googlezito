#include <chrono>

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

struct Node{
    char data; //um node tem um dado char
	bool fim; //0:a palavra n acabou; 1:a palavra acabou
    Node* pP; //ponteiro para o pai; ajudara na busca por palavras semelhantes
	Node* pchild[36]; //lista de chars possiveis a seguir
	vector<int> vec;
	int len_id;

    Node(char x):data(x), fim(0), pP(nullptr), len_id(0) {
	for(int i=0;i<36;i++){
		pchild[i]=nullptr; //a principio n faremos ponteiro nenhu se n precisar
	}
	}
	
	Node(): fim(0), pP(nullptr), len_id(0) {
	for(int i=0;i<36;i++){
		pchild[i]=nullptr; //a principio n faremos ponteiro nenhu se n precisar
	}
	}
};

class steady_clock;

class busca{
	private:
		Node *pRoot;
		string titulos[3];
		
	public:
		
	busca(){ //FUTURO CONSTRUTOR
			pRoot=new Node();
		}
		
		//~busca(){ //FUTURO DESTRUTOR
		
		char chaar(int i){
			if(i<=25){
				return char(i+97);
			}
			else{
				return char(i-26+48);
			}
		};
		int iint(char a){
			int i=int(a);
			if(i<69){
				return i-48+26;
			}
			else{
				return i-97;
			}
		}
		
		void inserir(string word, int id){ //vamos inserir uma palavra
			Node* pNode=pRoot; //node para onde devemos começar a inseriri letras, considerando que parte da palavra pode já existir
			int ies= 0; //numero que indicará quantas letras da palavra já existem
			if(pesquisar(word, pNode, ies)==1){ //chamamos a função find, q retorna true caso a palavra já exista. ela tambem faz cm q ies seja o numero em q a palavra parou e pNode aponte pro ies-simo Node
				inserir_idd(pNode->vec, id, pNode->len_id);
				return;
			}
			else{ //caso a palavra n exista por completo
				for(int i=ies; i< word.length(); i++){  //a partir da letra q ela n existe, prosseguimos da seguinte maneira:
					Node* &newNode = pNode->pchild[iint(word[i])]; //esse é o próximo node, a principio nullptr
					newNode = new Node(word[i]); //fazemos ele apontar pra outro node
					newNode->pP=pNode; //criamos o pai dele
					pNode=newNode; //e vamos pro próximo node	
				}
				inserir_idd(pNode->vec, id, pNode->len_id);
				pNode->fim=1;
			}	
		} 
		
		void inserir_titulo(string titulo, int id){
			titulos[id]=titulo;
		}
		
		void inserir_idd(vector<int> & vec, int & id, int & len_id){
			vec.push_back(id);
			len_id++;
			return;
		}
		
		int pesquisar(string word, Node* & pNode, int & ies){
			pNode=pRoot; //depois do loop este ponteiro deve apontar para o último node possível.
			ies=0; //e este deve ser o número de letras encontradas 
			for(int i=0; i< word.length(); i++){ 
			 	if(  pNode->pchild[iint(word[i])] != nullptr ){ //se a letra i de word for valida em alguma palavra já existente, prosseguimos
			 		pNode = pNode->pchild[iint(word[i])]; //fazemos o pNode ir pra próxima letra
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
	  				
	  				auto start = std::chrono::steady_clock::now();
  					bool b=(pesquisar(word, pNode, ies)==1);
  					auto end = std::chrono::steady_clock::now();
  					
  					if(b){
  						if(pNode->fim==1){
  							cout<< "achamos a palavra que voce quer! "
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
							cout <<"Hmmm...parece que voc� n�o digitou a palavra completa. Voc� pode tentar:"<<endl;
							printa_resto(pNode,word);
							cout<<endl<<endl;
						}
					}
					else{
						sugerir(word);
					}
					std::chrono::duration<double> diff = end-start;
					
					cout << "a pesquisa foi feita em ";
					cout <<diff.count() <<" segundos ou "<<diff.count()*10000000 <<" microsegundos"<<endl<<endl;
				}
				
				else{
					cout<< "obrigado e volte sempre!";
					return;
				}
			}
		}
		
		void sugerir(string word){
			Node* pNode=pRoot; 
			cout<<"Nao encontramos a palavra " <<word <<". Sugerimos:" <<endl;
			int i=0;
			string print="";
			while(i< word.length()){ 
			 	if(  pNode->pchild[iint(word[i])] != nullptr ){ 
			 		pNode = pNode->pchild[iint(word[i])];
			 		print+=word[i];
			 		i++;
				}
				 
				else{
					int j=0;
					while(j<36){
						if( pNode->pchild[j] != nullptr ){
							Node* pNodeee=pNode;
							cout <<"( " ;
							printa_resto(pNodeee,print);
							cout<<")" <<endl;
							return;
						}
						j++;
					}
					cout<<endl <<endl;
					return;
				}
			}
		}
		
		void printa_resto(Node* pNode, string print){
			print[print.length()-1]=pNode->data;
			print+=' ';
			if(pNode->fim!=1){
				for(int i=0;i<36;i++){
					if( pNode->pchild[i] != nullptr ){
						Node* pNodeee=pNode->pchild[i];
						printa_resto(pNodeee, print);		
					}
				}
			}
			else{
				cout<< print;
				return;
			}
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
	b.search();
	delete[] pNode;
	return 0;
}

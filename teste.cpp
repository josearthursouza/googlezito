#include<iostream>
using std::cout;
using std::cin;
using std::endl;

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
    Node* pP; //ponteiro para o pai; ajudará na busca por palavras semelhantes
	Node* pchild[26]; //lista de chars possíveis a seguir
	vector<int> vec; //vetor de ids
	int len_id; //tamanho do vetor de ids
	//resto (pra quando implementarmos a funçõa compaquitar
	
	//CONSTRUTOR DE NODE COM CHAR
    Node(char x):data(x), fim(0), pP(nullptr), len_id(0) {
	for(int i=0;i<26;i++){
		pchild[i]=nullptr; //não faremos ponteiro sem precisar
	}
	}
	
	//CONSTRUTOR DE NODE SEM CHAR
	Node(): fim(0), pP(nullptr), len_id(0) {
	for(int i=0;i<26;i++){
		pchild[i]=nullptr; //não faremos ponteiro sem precisar
	}
	}
};

//NOSSA LINDA CLASSE
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
					return 0; //retorna falso, pois a palavra n existe (pelo menos não inteirinha)
				}
			 }
    		return 1; //(retorna true pra sabermos q a palabra já existe)
		}
		
		void search(){
			Node* pNode=pRoot;
			int ies= 0;
			string word;
  			cout << "Digite uma palavra: ";
  			getline(cin, word);
  			auto start = high_resolution_clock::now();
  			if(pesquisar(word, pNode, ies)==1){
  				cout<<"a palavra existe" <<endl; //e tem correspondencia nos seguintes artigos: ";
  				//printe(pNode->vec);
			  }
			else{
				cout<<"a palavra não existe na arvore" <<endl;
				//SUGESTÃO
			}
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout<< "a pesquisa foi feita em ";
			cout << duration.count()/1000000 <<" segundos... ou " <<duration.count() <<" microsegundos!" <<endl;
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
		
		void inserir_titulo(string titulo, int id){
			titulos[id-1]=titulo;
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
		
		void compaquitar(){
			
		}
	
	
	
};

int main(){
	busca b;
	Node* pNode;
	int ies;

	b.inserir("correspondencia",1);
	b.inserir("oba",2);
	b.search();
	b.search();
	
	delete[] pNode;
	return 0;
}

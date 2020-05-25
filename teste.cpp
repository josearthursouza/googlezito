#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include<string>
using std::string;
using std::getline;

#include<vector>
using namespace std; 

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
		
	public:
		
	busca(){ //FUTURO CONSTRUTOR
			pRoot=new Node();
		}
		
		//~busca(){ //FUTURO DESTRUTOR
		
		bool pesquisar(string word, Node* pNode, int ies){
			pNode=pRoot; //depois do loop este ponteiro deve apontar para o último node possível.
			ies=0; //e este deve ser o número de letras encontradas 
			for(int i=0; i< word.length(); i++){ 
			 	if(  pNode->pchild[int(word[i]) - 97] != nullptr ){ //se a letra i de word for valida em alguma palavra já existente, prosseguimos
			 		pNode = pNode->pchild[int(word[i]) - 97]; //fazemos o pNode ir pra próxima letra
			 		cout<<pNode->data <<endl;
			 		ies++; //aumentamos o ies
				 } 
				else{//se n, paramos aqui
					return false; //retorn falso, pois a palavra n existe (pelo mens n inteira)
					
				}
			 }
    		return true; //(retorna true pra sabermos q a palabra j[a existe)
		}
		
		void inserir(string word, int id){ //vamos inserir uma palavra
			Node* pNode=pRoot; //node para onde devemos começar a inseriri letras, considerando que parte da palavra pode já existir
			int ies= 0; //numero que indicará quantas letras da palavra já existem
			if(pesquisar(word, pNode, ies)){ //chamamos a função find, q retorna true caso a palavra já exista. ela tambem faz cm q ies seja o numero em q a palavra parou e pNode aponte pro ies-simo Node
				//cout<< pNode->data <<endl;
				inserir_id(pNode->vec, id, pNode->len_id);
				cout<< "---------------" <<endl;
				return;
			}
			else{ //caso a palavra n exista por completo
				for(int i=ies; i< word.length(); i++){  //a partir da letra q ela n existe, prosseguimos da seguinte maneira:
					Node* &newNode = pNode->pchild[int(word[i]) - 97]; //esse é o próximo node, a principio nullptr
					newNode = new Node(word[i]); //fazemos ele apontar pra outro node
					newNode->pP=pNode; //criamos o pai dele
					pNode=newNode; //e vamos pro próximo node
					
				}
				//cout<< pNode->data <<endl;
				inserir_id(pNode->vec, id, pNode->len_id);
				cout<< "---------------" <<endl;
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
					printe(vec);
					return;
				}
			}
			vec.push_back(id);
			len_id++;
			//printe(vec);
			return;
		}
		
		
		
		void compaquitar(){
			
		}
	
	
	
};

int main(){
	busca b;
	Node* pNode;
	int ies;
	
//	b.pesquisar("oba", pNode, ies);
	b.inserir("oba",1);
	b.inserir("oba",2);
//	b.inserir("oba",1);
	b.inserir("oba",3);
//	cout<< b.pesquisar("oba", pNode, ies);
	
	delete[] pNode;
	return 0;
}

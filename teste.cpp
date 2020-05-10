#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include<string>
using std::string;
using std::getline;

struct Node{
    char data; //um node tem um dado char
	bool fim; //0:a palavra n acabou; 1:a palavra acabou
    Node* pP; //ponteiro para o pai; ajudara na busca por palavras semelhantes
	Node* pchild[26]; //lista de chars possiveis a seguir

	
    Node(char x):data(x), fim(0), pP(nullptr){
	for(int i=0;i<26;i++){
		pchild[i]=nullptr; //a principio n faremos ponteiro nenhu se n precisar
	}
	}
};

class busca{
	private:
		Node *pRoot;
		
	public:
		void inserir(string word){ //vamos inserir uma palavra
			Node* pNode=pRoot; //node para onde devemos come�ar a inseriri letras, considerando que parte da palavra pode j� existir
			int ies= 0; //numero que indicar� quantas letras da palavra j� existem
			if(pesquisar(word, pNode, ies)){ //chamamos a fun��o find, q retorna true caso a palavra j� exista. ela tambem faz cm q ies seja o numero em q a palavra parou e pNode aponte pro ies-simo Node
				return;
			}
			else{ //caso a palavra n exista por completo
				for(int i=ies; i< word.length(); i++){  //a partir da letra q ela n existe, prosseguimos da seguinte maneira:
					//pNode->pchild [int(word[i]) - 97] = new Node(word[i]);
					Node* &newNode = pNode->pchild[int(word[i]) - 97]; //esse � o pr�ximo node, a principio nullptr
					newNode = new Node(word[i]); //fazemos ele apontar pra outro node
					//newNode->data=word[i];
					newNode->pP=pNode; //criamos o pai dele
					pNode=newNode; //e vamos pro pr�ximo node
					
				}
				pNode->fim=1; //aqui ainda tem q mudar o bool da palavra pra dizer q acabou
			}
			
		} 
		
		bool pesquisar(string word, Node* pNode, int ies){
			pNode=pRoot;
			ies=0;
			for(int i=0; i< word.length(); i++){
			 	if(  pNode->pchild [int(word[i]) - 97] != nullptr ){ //se a letra i de word for valida em alguma palavra, prosseguimos
			 		pNode = pNode->pchild [int(word[i] - 97)];
			 		ies++;
				 } 
				else{ //se n, paramos aqui
					return false; //retorn falso, pois a palavra n existe (pelo mens n inteira)
				}
			 }
    		return true; //(retorna true pra sabermos q a palabra j[a existe)
		}
		
		void compaquitar(){
			
		}
	
	
	
};

int main(){
	busca b;
	Node* pNode;
	int ies;
	if(b.pesquisar("oba", pNode, ies)) cout<<"errou";
	b.inserir("oba");
	if(b.pesquisar("oba", pNode, ies)) cout<<"acertou";
	return 0;
}

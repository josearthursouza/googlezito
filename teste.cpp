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
		void inserir(string word){
			Node* pNode=pRoot;
			int ies= 0;
			if(pesquisar(word, pNode, ies)){
				return;
			}
			else{
				for(int i=ies; i< word.length(); i++){
					//pNode->pchild [int(word[i]) - 97] = new Node(word[i]);
					Node* &newNode = pNode->pchild[int(word[i]) - 97];
					newNode = new Node(word[i]);
					//newNode->data=word[i];
					newNode->pP=pNode;
					
				}
				//aqui ainda tem q mudar o bool da palavra pra dizer q acabou
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

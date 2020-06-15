#include <chrono>
#include <algorithm>    
using std::min;
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
#include<fstream>
#include<sstream>
#include<string>
using std::string;
using std::getline;
using std::to_string;
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
		
		void inserir(string word, string ids){ //vamos inserir uma palavra
			Node* pNode=pRoot; //node para onde devemos comeÃ§ar a inseriri letras, considerando que parte da palavra pode jÃ¡ existir
			int ies= 0; //numero que indicarÃ¡ quantas letras da palavra jÃ¡ existem
			if(pesquisar(word, pNode, ies)==1){ //chamamos a funÃ§Ã£o find, q retorna true caso a palavra jÃ¡ exista. ela tambem faz cm q ies seja o numero em q a palavra parou e pNode aponte pro ies-simo Node
				inserir_idd(pNode->vec, ids, pNode->len_id);
				return;
			}
			else{ //caso a palavra n exista por completo
				for(int i=ies; i< word.length(); i++){  //a partir da letra q ela n existe, prosseguimos da seguinte maneira:
					Node* &newNode = pNode->pchild[iint(word[i])]; //esse Ã© o prÃ³ximo node, a principio nullptr
					newNode = new Node(word[i]); //fazemos ele apontar pra outro node
					newNode->pP=pNode; //criamos o pai dele
					pNode=newNode; //e vamos pro prÃ³ximo node	
				}
				inserir_idd(pNode->vec, ids, pNode->len_id);
				pNode->fim=1;
			}	
		} 
		
		
		void inserir_idd(vector<int> & vec, string ids, int & len_id){
			stringstream split;
			split << ids;
			string id;
			while(split >> id){
				vec.push_back(stoi(id));
				len_id++;
			}
			return;
		}
		
		int pesquisar(string word, Node* & pNode, int & ies){
			pNode=pRoot; //depois do loop este ponteiro deve apontar para o Ãºltimo node possÃ­vel.
			ies=0; //e este deve ser o nÃºmero de letras encontradas 
			for(int i=0; i< word.length(); i++){ 
			 	if(  pNode->pchild[iint(word[i])] != nullptr ){ //se a letra i de word for valida em alguma palavra jÃ¡ existente, prosseguimos
			 		pNode = pNode->pchild[iint(word[i])]; //fazemos o pNode ir pra prÃ³xima letra
			 		ies++; //aumentamos o ies
				 } 
				else{//se n, paramos aqui
					return 0; //retorn falso, pois a palavra n existe (pelo mens n inteira)
				}
			 }
    		return 1; //(retorna true pra sabermos q a palabra j[a existe)
		}
		
		void searchy(){
			std::chrono::duration<double> diff;
			string palavras;
			Node* pNode;
			vector<int> vec1;
			
			while(true){
				vec1={};
				cout<<"?quieres hacer una pesquisa? (s/n)" <<endl;
				getline(cin,palavras);
				if(palavras=="s"){
					diff-=diff;
					string palavras;
					cout << "Digite sua pesquisa: ";
					getline(cin, palavras);
					stringstream split;
					split << palavras;
					string word;
					while(split >> word){
						pNode=pRoot;
						search(word,pNode,diff);
						titulos_comuns(vec1,pNode->vec); 
					}
					cout << "a pesquisa foi feita em "
					<<diff.count() <<" segundos ou "<<diff.count()*10000000 <<" microsegundos"<<endl
					<<"e ha correspondencia da pesquisa nos seguintes " << vec1.size() << " titulos:"<<endl;
					
					int j=20;
					int printados = 0;
					ifstream Titulos;
					Titulos.open("titulos_ordem.txt");
					int i = 1;
					while(printados < min(j,int(vec1.size()))){
						string Titulo;
						getline(Titulos, Titulo);
						if(i == vec1[printados]){
							cout<<"["<<printados<<"]- "<<Titulo <<endl;
							printados++;
						}
						i++;
					}					 
					while(int(vec1.size())>j){
						cout<<"H� mais titulos. Deseja ve-los? (s/n)" << endl;
						getline(cin,palavras);
						j+=20;
						if(palavras=="s"){ 
							while(printados < min(j,int(vec1.size()))){
								string Titulo;
								getline(Titulos, Titulo);
								if(i == vec1[printados]){
									cout<<"["<<printados<<"]- "<<Titulo <<endl;
									printados++;
								}
								i++;
							}
						}
						else{
							break;
						}
					}
					Titulos.close();
					
					while(true){
						cout<<"quer abrir algum titulo? (s/n)"<<endl;
						getline(cin,palavras);
						if(palavras=="s"){
							cout<<"qual?"<<endl;
							getline(cin,palavras);
							return_txt(vec1.at(stoi(palavras)) );
							cout<<endl;
						}
						else{
							break;
						}
					}
						
				}
				else{
					cout<< "obrigado e volte sempre!";
					return;
				}
			}
		}
		
		void return_txt(int i){ //recebe a id
			int j;
			string a="conteudos_ordem ("; //i t� na posi��o 13
			j=i/10000 +1;
			cout<<endl;
			a+=to_string(j);
			a+=")";
			ifstream dados;
			dados.open(a);
			for(int k;k<(i-(j-1)*10000);k++){
				getline(dados,a);
			}
			cout<<a;	
			dados.close();
		} 	
		
		void titulos_comuns(vector<int> & vec1, vector<int> vec2){
			if(vec1.empty()){
				vec1=vec2;
				return;
			}
			else{
				int i=0;
				while(!(vec2.empty()) and vec2.front()<=vec1.back()){
					if(vec1.at(i)==vec2.front()){
						i++;
						vec2.erase(vec2.begin());
					}
					else if(vec1.at(i)>vec2.front()){
						vec2.erase(vec2.begin());
					}
					else if(vec1.at(i)<vec2.front()){
						vec1.erase(vec1.begin()+i);
					}
				}
				while(vec1.size()>i){
					vec1.pop_back();
				}
			}
			return;
		}
		
		void printe(vector<int> g1){
    		for (auto i = g1.begin(); i != g1.end(); ++i){
        		cout << *i << " "; 
    		}
    		cout<<endl;
		}
		
		void search(string word, Node* & pNode,std::chrono::duration<double> & diff){
			int ies= 0;

	  		auto start = std::chrono::steady_clock::now();
  			bool b=(pesquisar(word, pNode, ies)==1);
  			auto end = std::chrono::steady_clock::now();
  					
  			if(b){
  				if(pNode->fim==1){//EXISTENTE E COMPLETA
				}
				else{//EXISTENTE, NÃO COMPLETA
					cout <<"Hmmm...parece que voce nao digitou a palavra " << word << " completa. Voce pode tentar:"<<endl;
					vector<Node*> vec;
					int j=-1;
					printa_resto(pNode,word,vec,j);
					auto end = std::chrono::steady_clock::now();
					cout<<"quieres usar alguma das sugestoes?(s/n)"<<endl;
					getline(cin, word);
					if(word=="s"){
						cout<<"qual?"<<endl;
						getline(cin, word);
						pNode=vec.at(stoi(word));
					}
					std::chrono::duration<double> suj=end-start;
					cout<<"a sugest�o levou "<<suj.count()*1000000<<" microsegundos"<<endl;
					return;
				}
			}
			else{//NÃO EXISTENTE
				sugerir(word, pNode);
				return;
			}
			diff += end-start;
			
			
		}
		
		void sugerir(string word,Node* & pNodee){
			Node* pNode=pRoot; 
			cout<<"Nao encontramos a palavra " <<word <<". Sugerimos:" <<endl;
			int i=0;
			string print="";
			auto start = std::chrono::steady_clock::now();
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
							vector<Node*> vecN;
							int l=-1;
							printa_resto(pNodeee,print,vecN,l);
							auto end = std::chrono::steady_clock::now();
							cout<<"quieres usar alguma das sugestoes?(s/n)"<<endl;
							getline(cin, word);
							if(word=="s"){
								cout<<"qual?"<<endl;
								getline(cin, word);
								pNodee=vecN.at(stoi(word));
								
							}	
							std::chrono::duration<double> suj=end-start;
							cout<<"a sugest�o levou "<<suj.count()*1000000<<" microsegundos"<<endl;
							return;
						}
						j++;
					}
					cout<<"EH BOMBA"<<endl;
					return;
				}
			}
		}
		
		void printa_resto(Node* pNode, string print,vector<Node*> & vec,int & k){
			if(k>=4) return;
			print[print.length()-1]=pNode->data;
			print+=' ';
			if(pNode->fim!=1){
				for(int i=0;i<36;i++){
					if( pNode->pchild[i] != nullptr ){
						Node* pNodeee=pNode->pchild[i];
						printa_resto(pNodeee, print,vec,k);
					}
				}
			}
			else{
				k++;
				vec.push_back(pNode);
				cout<<"["<<k<<"]- "<< print<<endl;
				return;
			}
		}
		
		
		void serializacao(string file_name){
			ofstream file;
			file.open(file_name);
			Node * pNode = pRoot;
			for(int i =0; i<36; i++){
        	segunda_serializacao(pNode->pchild[i], file);
        	}
		}
	
		void segunda_serializacao(Node * pCur, ofstream & file){
			if (pCur == nullptr){ return;
			}
        	file << pCur->data << " " << pCur ->fim << " ";
        	if(pCur->vec.size() != 0){
        		file<< pCur->vec.size() << " ";
        		for (auto i = pCur->vec.begin(); i != pCur->vec.end(); ++i) {
       				 file << *i << " ";
       			}
			}
        	for(int i=0;i<36;i++){
            	segunda_serializacao(pCur->pchild[i], file);
        	}
        
        file << "- "; 
    }
    
    	void desserializacao(string file_name){
    		ifstream file;
    		string line;
    		file.open(file_name);
    		getline(file,line);
    		Node ** pNode = &pRoot;
    		stringstream split;
    		split << line;
    		desserializacao_pRoot(pNode, split);
		}
		void desserializacao_pRoot(Node ** pNode, stringstream & split){
			string cur_name_s;
			while(split >> cur_name_s){
				if(desserializacao_resto(pNode, cur_name_s, split)) break;
			}
		}
		
		bool desserializacao_resto(Node ** pNode, string cur_name_s, stringstream  & split){
        if(cur_name_s == "-") return 1;
        char * cur_name = new char(cur_name_s[0]);
        Node * pNew = new Node(*cur_name); 
        (*pNode)->pchild[iint(*cur_name)] = pNew;
        pNew ->pP = (*pNode);
        pNode = &(*pNode)->pchild[iint(*cur_name)];
        string end; string tamanho;
        split >> end;
        (*pNode)->fim = stoi(end);
        if(end == "1"){
        	split >> tamanho;
        	cout << tamanho << " ";
        	(*pNode)->len_id = stoi(tamanho);
        	for(int i=0; i<(*pNode)->len_id; i++){
        		string ide;
        		split >> ide;
        		(*pNode)->vec.push_back(stoi(ide));
			}
		}
        while(split >> cur_name_s){ 
            if(desserializacao_resto(pNode, cur_name_s, split)){
            	break;
			}
			
        }
        return 0;
    }
	};

int main(){
	Node* pNode;
	int ies;

	busca b;
	ifstream dados;

	dados.open("palavras_ids_A (1)");
	string palavra;
	string ids;
	while(getline(dados,palavra)){
		getline(dados,ids);
		b.inserir(palavra,ids);
	}
	dados.close();
//	b.serializacao("cocinha.txt");


//	b.desserializacao("cocinha.txt");
	b.searchy();
	delete[] pNode;
	return 3221225477;
}


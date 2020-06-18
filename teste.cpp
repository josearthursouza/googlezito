#include <locale.h>
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
	Node* pchild[36]; //lista de chars possiveis a seguir (a-z, 0-9)
	vector<int> vec; //vetor de ids dos t�tulos correspondentes � palavra
	int len_id; //quantidade de ids associadas

    Node(char x):data(x), fim(0), len_id(0) {
	for(int i=0;i<36;i++){
		pchild[i]=nullptr; //a principio n faremos ponteiro nenhum se n�o precisar
	}
	}
	
	Node(): fim(0), len_id(0) {
	for(int i=0;i<36;i++){
		pchild[i]=nullptr; //a principio n faremos ponteiro nenhum se n�o precisar
	}
	}
};

class steady_clock;

class busca{
	private:
		Node *pRoot = new Node();	
	public:
	
		
		char chaar(int i){ //descobre o caracter correspondente a cada posi��o na array
			if(i<=25){
				return char(i+97);
			}
			else{
				return char(i-26+48);
			}
		};
		
		int iint(char a){ //descobre a posi��o respectiva na array
		
			int i=int(a);
			if(i<69){
				return i-48+26;
			}
			else{
				return i-97;
			}
		}
		
		int pesquisar(string word, Node* & pNode, int & ies){ //essa fun��o � para auxiliar na inser��o de palavras
			pNode=pRoot; //depois do loop este ponteiro deve apontar para o �ltimo node poss�vel.
			ies=0; //e este deve ser o n�mero de letras encontradas 
			for(int i=0; i< word.length(); i++){ 
			 	if(  pNode->pchild[iint(word[i])] != nullptr ){ //se a letra i de word for v�lida em alguma palavra j� existente, prosseguimos
			 		pNode = pNode->pchild[iint(word[i])]; //fazemos o pNode ir pra pr�xima letra
			 		ies++; //aumentamos o ies
				 } 
				else{//se n, paramos aqui
					return 0; //retorna falso, pois a palavra n existe (pelo mens n inteira)
				}
			 }
    		return 1; //(retorna true pra sabermos q a palavra j� existe)
		}
		
		void inserir_idd(vector<int> & vec, string ids, int & len_id){
			//pega uma string de ids separadas por " " e insere ao final do vetor de ids
			stringstream split;
			split << ids;
			string id;
			while(split >> id){
				vec.push_back(stoi(id));
				len_id++;
			}
			return;
		}
		
		void inserir(string word, string ids){ //vamos inserir uma palavra  
			Node* pNode=pRoot; //node para onde devemos come�ar a inserir letras, considerando que parte da palavra pode j� existir
			int ies= 0; //n�mero que indicar� quantas letras da palavra j� existem
			if(pesquisar(word, pNode, ies)==1){ //chamamos a fun��o find, que retorna true caso a palavra j� exista. ela tambem faz com q ies seja o numero em q a palavra parou e pNode aponte pro ies-simo Node
				inserir_idd(pNode->vec, ids, pNode->len_id);
				pNode->fim=1;
				return;
			}
			else{ //caso a palavra n�o exista por completo
				for(int i=ies; i< word.length(); i++){  //a partir da letra q ela n existe, prosseguimos da seguinte maneira:
					Node* &newNode = pNode->pchild[iint(word[i])]; //esse � o pr�ximo node, a principio nullptr
					newNode = new Node(word[i]); //fazemos ele apontar pra outro node
					pNode=newNode; //e vamos pro pr�ximo node	
				}
				inserir_idd(pNode->vec, ids, pNode->len_id);
				pNode->fim=1;
			}	
		} 
		
				
		void return_txt(int i){ //recebe a id
			int j=i/10000 +1; //j indicar� em qual arquivo est� o artigo de �ndice i
			string a="conteudos_ordem ("; //nome padronizado do arquivo
			a+=to_string(j);
			a+=")";
			ifstream dados;
			dados.open(a);
			for(int k;k<(i-(j-1)*10000);k++){ //i-(j-1)*10000 indica em qual linha do arquivo est� o texto de id i
				getline(dados,a); //pega a linha at� chegar na certa
			}
			cout<<endl << a << endl;	//printa o texto 
			dados.close();
		} 	
		
		void titulos_comuns(vector<int> & vec1, vector<int> vec2, bool & vazio,std::chrono::duration<double> & comp){
			auto star= std::chrono::steady_clock::now(); //tempo
			if(vec1.empty()){
				if(vazio) return;
				vec1=vec2;
				vazio=1;
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
			auto eend = std::chrono::steady_clock::now();
			comp=eend-star;
			return;
		}
				
				
		void printa_resto(Node* pNode, string print,vector<Node*> & vec,int & k){ //usada caso a palavra pesquisada esteja incompleta
			if(k>=4) return; //s� queremos no m�ximo 5 sugest�es (0 a 4)
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
		
		void sugerir(string word,Node* & pNodee, bool & sugs){  //sugest�o pra quando a pesquisa n�o existe em nenhum peda�o de palavra da �rvore
			Node* pNode=pRoot; 
			cout<<"No encontramos la palabra " <<word <<".";
			int i=0;
			string print="";
			auto start = std::chrono::steady_clock::now(); //tempo
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
							cout<<" Sugerimos:"<<endl;
							Node* pNodeee=pNode;
							vector<Node*> vecN;
							int l=-1;
							printa_resto(pNodeee,print,vecN,l);
							auto end = std::chrono::steady_clock::now(); 
							cout<<"�Quieres usar alguna de las sugestiones?(s/n)"<<endl;
							getline(cin, word);
							if(word=="s"){
								if(vecN.size() == 1){
									pNodee = vecN.at(0);
								}
								else{
								cout<<"�Cu�l?"<<endl;
								getline(cin, word);
								pNodee=vecN.at(stoi(word));
								}
							}
							else if(word=="n"){
								sugs=0;
							}
							std::chrono::duration<double> suj=end-start; //tempo
							cout<<"La sugesti�n llev� "<<suj.count()*1000000<<" microsegundos"<<endl;
							return;
						}
						j++;
					}
					
					cout<<endl<<"Talvez usted ha digitado cosa a m�s. Podemos returnar los resultados de la palabra " <<print <<endl <<"�Lo quieres?"<<endl;
					getline(cin, word);
					if(word=="s"){
						return;	
					}
					else{
						sugs=0;
						return;
					}
				}
			}
		}

		void search(string word, Node* & pNode,std::chrono::duration<double> & diff,bool & sugs){ 
			int ies= 0; //indica em qual letra da palavra est�

	  		auto start = std::chrono::steady_clock::now(); //tempo
  			bool b=(pesquisar(word, pNode, ies)==1);  //faz a pesquisa da palavra na �rvore e diz se conseguiu ou n�o
  			auto end = std::chrono::steady_clock::now();  //tempo
  					
  			if(b){ //se a palavra existir na arvore
  				if(pNode->fim==1){//EXISTENTE E COMPLETA
				}
				else{//EXISTENTE, N�O COMPLETA
					cout <<"Hmmm... parece que usted no digit� la palabra " << word << " completa. Usted puede tentar:"<<endl;
					vector<Node*> vec;
					int j=-1;
					printa_resto(pNode,word,vec,j);
					auto end = std::chrono::steady_clock::now(); //tempo
					cout<<"�Quieres usar alguna de las sugestiones?(s/n)"<<endl;
					getline(cin, word);
					if(word=="s"){
						if(vec.size() == 1){ //se s� tiver uma op��o, j� retorna sem perguntar qual
							pNode = vec.at(0);
						}
						else{
							cout<<"�Cu�l?"<<endl;
							getline(cin, word);
							pNode=vec.at(stoi(word));
						}
					}
					else{
						sugs=0;
					} 
					std::chrono::duration<double> suj=end-start; //tempo
					cout<<"La sugesti�n llev� "<<suj.count()*1000000<<" microsegundos"<<endl;
					return;
				}
			}
			else{//N�O EXISTENTE
				sugerir(word, pNode, sugs); 
				return;
			}
			diff += end-start; //tempo
		}

		
		void searchy(){  //essa � a fun��o pra rodar o Search Engine, fazer buscas
			std::chrono::duration<double> diff; //tempo
			string palavras; //v�o ser as entradas 
			Node* pNode; 
			vector<int> vec1; //vetor de ids 
			
			while(true){
				cout<<"�Quieres hacer una pesquisa? (s/n)" <<endl;
				getline(cin,palavras); //aqui "palavras" � a resposta para a pergunta acima. "s" pra caso afirmativo e qualquer outra coisa caso contr�rio
				if(palavras=="s"){ //se a resposta for s, come�a a pesquisa
					std::chrono::duration<double> comp; //tempo
					diff-=diff; //tempo
					bool vazio=0; //� pra caso a interse��o dos vetores de ids seja vazia
					bool sugs = 1;//se a resposta a sugest�o for sim (isso vai mudar s� quando for n)
					cout << "Digite su pesquisa: ";
					getline(cin, palavras); //agora palavras � a frase a pesquisar
					stringstream split;
					split << palavras;
					string word;
					pNode = pRoot;
					split >> word;
					search(word, pNode, diff, sugs); 
					vec1 = pNode->vec; //primeira palavra
					bool comparou = 0; //s� vai ser 1 se comparar t�tulos
					while(split >> word){ //s� vai entrar se pesquisar mais de uma palavra
						sugs=1; //s� vai ser 0 se n�o quiser sugest�o
						pNode=pRoot; //come�a a busca por uma palavra do 0, pela raiz da �rvore
						search(word,pNode,diff,sugs);	
						if(sugs){
							comparou = 1; //vai comparar t�tulos
							titulos_comuns(vec1,pNode->vec,vazio,comp);
						}
					}
					cout << "La pesquisa fue hecha en "
					<<diff.count() <<" segundos o "<<diff.count()*1000000 <<" microsegundos"<<endl;
					if(comparou){
					cout << "La comparaci�n de t�tulos fue hecha en " <<comp.count()*1000000 <<" microsegundos" <<endl;
					}
					
					if(vec1.size()!=0){ //n�o printa se tiver 0 t�tulos
					cout<<"y hay correspondencia de la pesquisa en los seguientes " << vec1.size() << " t�tulos:"<<endl;
					
					int j=20; //m�ximo de t�tulos na "p�gina"
					int printados = 0; //ainda n�o printou nada
					ifstream Titulos;
					Titulos.open("titulos_ordem");
					int i = 1; //n�mero da linha que vai ler do arquivo (que cont�m o t�tulo de id i)
					while(printados < min(j,int(vec1.size()))){
						string Titulo;
						getline(Titulos, Titulo);
						if(i == vec1[printados]){ //se achou o pr�ximo t�tulo a printar
							cout<<"["<<printados<<"]- "<<Titulo <<endl;
							printados++; //printados s� aumenta quando acha um t�tulo com id pertencente a vec
						}
						i++; //i aumenta a cada linha
					}					 
					while(int(vec1.size())>j){
						cout<<"Hay m�s t�tulos. �Desea verlos? (s/n)" << endl;
						getline(cin,palavras);
						j+=20; //pra printar de 20 em 20
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
						cout<<"�Quieres abrir alg�n t�tulo? (s/n)"<<endl;
						getline(cin,palavras); 
						if(palavras=="s"){
							if(vec1.size() == 1){ //se s� tiver uma op��o, printa ela
								return_txt(vec1.at(0));
								cout<<endl;
								break;
							}
							else{ //se tiver mais de uma, pergunta qual
								cout<<"�Cu�l?"<<endl;
								getline(cin,palavras);
								return_txt(vec1.at(stoi(palavras)));
								cout<<endl;
							}
						}
						else{
							break;
						}
					}
				}
				else{ //se tiver 0 t�tulos
					cout<<"No hay t�tulos correspondientes a su pesquisa :|"<<endl;
				}
						
				}
				else{ //se n�o quiser fazer uma pesquisa
					cout<< "�Gracias y volve siempre!";
					return;
				}
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
        	file << pCur->data << " " << pCur->fim<< " ";
        	if(pCur->fim == 1){
        		file << pCur->vec.size() << " ";
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
        pNode = &(*pNode)->pchild[iint(*cur_name)];
        string end; string tamanho;
        split >> end;
        (*pNode)->fim = stoi(end);
        if(end == "1"){
        	split >> tamanho;
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
	setlocale(LC_ALL,"");
	Node* pNode;
	int ies;

	busca b; /*
	ifstream dados;
	
	string palavra;
	string ids;
	/*
	
	//b.desserializacao("A1-5eB1.txt");
	
	dados.open("palavras_ids_B (39)");
	while(getline(dados,palavra)){
			getline(dados,ids);
			b.inserir(palavra,ids);
		}
		dados.close();
	
	
	cout << "vai come�ar! ";
	
	for(int i=1; i<51; i++){
		string nome = "palavras_ids_A (";
		nome += to_string(i);
		nome += ")";
		dados.open(nome);
		while(getline(dados,palavra)){
			getline(dados,ids);
			b.inserir(palavra,ids);
		}
		dados.close();
	}
	
	cout << "inseriu parte A! ";
	
	for(int i=1; i<52; i++){
		string nome = "palavras_ids_B (";
		nome += to_string(i);
		nome += ")";
		dados.open(nome);
		while(getline(dados,palavra)){
			getline(dados,ids);
			b.inserir(palavra,ids);
		}
		dados.close();
	}	
	
	cout << "inseriu parte B! ";
	
	
	b.serializacao("GrandiosaArvore");

	cout << "serializou!" << endl;
	*/
	b.desserializacao("GrandiosaArvore");
	b.searchy();
	delete[] pNode;
	return 3221225477;
}


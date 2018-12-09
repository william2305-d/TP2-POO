#include <iostream>
#include "Biblioteca.h"
#include <vector>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
// Sobre como ser estatico
class tentativa{
	private: 
		int a;
		int b;
	public: 
	virtual ~tentativa(){};
	tentativa(){ b=3; a=2; };
	int get_a(){return a; };
	int get_b(){return b; };
	
	virtual void out(){	cout << "Tentativa" << endl; };
	
	
};

class deus: public tentativa{
	
	public:
		deus():tentativa(){};
		virtual void out(){	cout << "Deus me ajuda" << endl;};
		virtual~deus(){};
		
};

void g(tentativa& t){
	t.out();
}

int main(int argc, char** argv) {

try{
	Usuario  a("Alice","cpf","end","21");
	Date hoje;
	
	
	Livro livro("amor",2,"t1","ed",2010,1);
	Livro livro2("iiib",2,"t2","ed",2010,1);
 	
 	ItemEmprestimo i(livro2);
 	
	Publicacao pub(2,"t2","ed",2010);

	Biblioteca b;

	Emprestimo e(a,hoje), g(a,hoje);
	
	b.novoItemEmprestimo(e,i);

	b.novaPublicacao(&pub);
	b.novaPublicacao(&livro2);
	b.novaPublicacao(&livro);
	vector <ItemEmprestimo> lista;
	
	lista = e.getItens();
	//Casting de c 
	
	for (int i = 0; i < lista.size(); i++){
		//	Livro* l = dynamic_cast <Livro*> (lista[i]); 
		//	if(l != NULL){
			Livro tit;
			tit = lista[i].getLivro();	
			cout << tit.getAutores() << endl;
				if(tit == livro2){
				cout << "igual"<< endl;
			}
	//	}
	}
	
	b.novoEmprestimo(e);
	e.adcItemEmprestimo(i);
	
	b.excluiPublicacao(&livro2);

	b.exluiEmprestimo(g);
	
}catch(Erro &e){
	e.out();
}
	
	
		
	return 0;
}

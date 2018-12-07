#include <string.h>
#include <iostream>
#include <time.h>
#include<vector>
using namespace std;

// --------------------------------------------------------------------    DATE   --------------------------------------------------------------------//

//Arrumar para inicializar com a data corrente do sistema
class Date{
		int dia;
		int mes;
		int ano;
	public:
		//Obs: O certo � tirar daqui as {} depois de implementar em todas as fun��es
		//De menos das contrutores que n recebem nada
		//Exemplo =>  Date DataNula();
		//Acho que ter� q fazer um contrutor por copia em todos!!!
		
		void DataNula(){ dia = 0; mes = 0; ano = 0;};  
		void DataCorrente(); //inicializa com a data do "dia" que voce usar essa fun��o, para gente ser� o msm dia.
		Date(); // inicializa com a data do dia da cria��o
		~Date(){};
		int getDia(){return dia;};
		int getMes(){return mes;};
		int getAno(){return ano;};
		int operator==(Date &d); 
		

};

// --------------------------------------------------------------------    USUARIO   --------------------------------------------------------------------//

class Usuario{
	private:
		string nome;
		string cpf;
		string endereco;
		string fone;
		Date dataPenalizacao;
	public:
	//	Usuario(Usuario &u);
		Usuario(){};
		Usuario(string nomeParametro, string cpfParametro, string enderecoParametro, string foneParametro);
		~Usuario(){};
		Date& getDataPenalizacao(){return dataPenalizacao;};
		int operator==(const Usuario &u)const;
};

// --------------------------------------------------------------------    PUBLICACAO   --------------------------------------------------------------------//

class Publicacao{
	private:
		int codPublicacao;
		string titulo;
		string editora;
		int ano;
	public:
	//	Publicacao(Publicacao &p);
		int operator==(Publicacao &p);
		string getTitulo()const{return titulo;};
		string getEditora()const{return editora;};
		int getCodPublicacao()const{return codPublicacao;};
		int getAno()const{return ano;};
		Publicacao(){codPublicacao = 0; titulo = " "; editora = " "; ano = 0;};
		Publicacao(int codP, string tit, string ed, int a): codPublicacao(codP), titulo(tit), editora(ed), ano(a){};
		~Publicacao(){}; 	
};

// --------------------------------------------------------------------    LIVRO   --------------------------------------------------------------------//

class Livro: public Publicacao{
	private:
		string autores;
		int qtdeExemplares;
	public:
	//	Livro(Livro& l);
	//	Livro operator=(Livro &l);
		Livro(){}; 
		Livro(string aut, int codP, string tit, string ed, int a,int qtdeE = 0):Publicacao( codP, tit, ed, a),autores(aut),qtdeExemplares(qtdeE){};
		~Livro(){};
		void incrementar();
		void decrementar();
		int getQtdeExemplares(){return qtdeExemplares;};
		string getAutores(){return autores;};
		int operator==(const Livro &l)const;
		
};

// ---------------------------------------------------------------------    PERIODICO   ---------------------------------------------------------------------//

class Periodico:public Publicacao{
	private:
		int numEdicao;
		string mes;
	public:
		Periodico(int numE, string m, int codP, string tit, string ed, int a):Publicacao( codP, tit, ed, a),numEdicao(numE),mes(m){};
		~Periodico(){};
		int operator==(const Periodico &p)const;
};

// ------------------------------------------------------------------    ITEM EMPRESTIMO   ------------------------------------------------------------------//

class ItemEmprestimo{
	private:
		Date dataDevolucao;
		Livro livro;	
	public:
		Date getDataDev(){return dataDevolucao;	};
		ItemEmprestimo(){};
		ItemEmprestimo(Livro l);
		Livro getLivro();
		void setDataDev(){ dataDevolucao.DataCorrente();};
};

// --------------------------------------------------------------------    EMPRESTIMO   --------------------------------------------------------------------//

class Emprestimo{		
	private:
		int numero;
		Date dataEmprestimo;
		Usuario usuario;
		static int proximoNumero;
		Date dataPrevDevolucao;
		vector <ItemEmprestimo> itens;
	public:
		Emprestimo(){};
		Emprestimo(Usuario usu, Date dataPrevDev);
		void adicionarLivro(Livro &nomeLivro);
		void excluirLivro(Livro &nomeLivro);
		void devolverLivro(Livro &nomeLivro);
		void devolverTodosOsLivros();
		Usuario& getUsuario(){return usuario;};
		void adcItemEmprestimo(ItemEmprestimo &i){ itens.push_back(i);};
		
};

class Erro{
	private:
		string tipo_erro;
	public:
		Erro(const string &a):tipo_erro(a){};
		void out(){ cout << tipo_erro << endl; };	
			
};

// --------------------------------------------------------------------    BIBLIOTECA   --------------------------------------------------------------------//

class Biblioteca{		
	private:
		//Ao iniciar aqui j� � dado como vazio (tamanho zero do vetor)
		vector <Emprestimo> emprestimos;
		vector <Usuario> usuarios;
		vector <Publicacao> livros;
	public:
		Biblioteca(); //
		void novoUsuario(const Usuario &u);
		void novaPublicacao(const Publicacao &p);
		void novoEmprestimo(const Emprestimo &e);
		void novoItemEmprestimo(Emprestimo &e, ItemEmprestimo &i); //tambem recebe itemdeemprestimo
		void excluiUsuario(const Usuario &u);
		int verificaUsuarioEmp(Usuario &u);
};

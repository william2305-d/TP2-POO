//biblioteca.cpp
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Biblioteca.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// --------------------------------------------------------------------    DATE   --------------------------------------------------------------------// 
int Date::operator==(Date &d){ 
	if( mes == d.mes && ano == d.ano && mes == d.mes){
		return true;
	}
	return false;
};

int Date::operator<(Date &d){
	if(ano < d.ano){
		return true;
	}	
	else if (ano == d.ano){
		if(mes < d.mes){
			return true;
		}
		else if(mes == d.mes){
			if(dia < d.dia){
				return true;
			}
		}
	}
	return false;
}

void Date::DataCorrente(){
  time_t rawtime;
  struct tm * timeinfo;
  string data;
  string d;
  string m;
  string a;
  
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  data = asctime (timeinfo);
  
  m = data.substr(4,3);
  d = data.substr(8,2);
  a = data.substr(20,4);
  
  if(m == "Jan"){
	mes = 1;
	}
	else{
		if(m == "Fen"){
			mes = 2;
		}
		else{
			if(m == "Mar"){
				mes = 3;
			}
			else{
				if(m == "Apr"){
					mes = 4;
				}
				else{
					if(m == "May"){
						mes = 5;
					}
					else{
						if(m == "Jun"){
							mes = 6;
						}
						else{
							if(m == "Jul"){
								mes = 7;
							}
							else{
								if(m == "Aug"){
									mes = 8;
								}
								else{
									if(m == "Sep"){
										mes = 9;
									}
									else{
										if(m == "Oct"){
											mes = 10;
										}
										else{
											if(m == "Nov"){
												mes = 11;
											}
											else{
												if(m == "Dec"){
													mes = 12;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	} 
  
  dia = atoi( d.c_str() );
  ano = atoi( a.c_str() );
}

Date::Date(){
	DataCorrente();
}


// --------------------------------------------------------------------    USUARIO   --------------------------------------------------------------------//

int Usuario::operator==(const Usuario &u)const{
	if( nome == u.nome && cpf == u.cpf && endereco == u.endereco && fone == u.fone){
		return true;
	}
	return false;
}

Usuario::Usuario(string nomeParametro, string cpfParametro, string enderecoParametro, string foneParametro){
	nome = nomeParametro;
	cpf = cpfParametro;
	endereco = enderecoParametro;
	fone = foneParametro;
}

// --------------------------------------------------------------------    PUBLICACAO   --------------------------------------------------------------------//

int Publicacao::operator==(Publicacao &p){
	if(p.ano == ano && p.codPublicacao == codPublicacao && (editora.compare(p.editora) == 0 ) && (titulo.compare(p.titulo) == 0)){
		return true;
	}
	else{
		return false;
	}
}

// --------------------------------------------------------------------    LIVRO   --------------------------------------------------------------------//

//Esta errado so fiz pr testar, falta testar se as outras variaveis sao iguais
//Observa��o importante para o Will (necessario fazer um get para todos os atributos) 
int Livro::operator==(const Livro &l)const{
	if (autores == l.autores && getCodPublicacao() == l.getCodPublicacao() && this->getTitulo() == l.getTitulo() && getEditora() == l.getEditora() && getAno() == l.getAno() && qtdeExemplares == l.qtdeExemplares ){
		return true;
	} 
	else{
		return false;	
	}
}

void Livro::incrementar(){
	qtdeExemplares++;
}

void Livro::decrementar(){
	if(qtdeExemplares <= 0){
		cout << "quantidade de exemplares igual a 0, impossivel decrementar" << endl;
	}
	else{
		qtdeExemplares--;
	}
}

// ---------------------------------------------------------------------    PERIODICO   ---------------------------------------------------------------------//

int Periodico::operator==(const Periodico &p)const{
	// comparar s� as vari�veis de periodico ou da classe base tbm?
	if(numEdicao == p.numEdicao && mes == p.mes && this->getCodPublicacao() == p.getCodPublicacao() && getTitulo() == p.getTitulo() && getEditora() == p. getEditora() && getAno() == p.getAno()){
		return true;
	}
	else{
		return false;
	}
}

// ------------------------------------------------------------------    ITEM EMPRESTIMO   ------------------------------------------------------------------//

ItemEmprestimo::ItemEmprestimo(Livro l):livro(l){
	dataDevolucao.DataNula();
}

Livro ItemEmprestimo::getLivro(){
	return livro;
}

// --------------------------------------------------------------------    EMPRESTIMO   --------------------------------------------------------------------//

//Contador 
int Emprestimo::proximoNumero = 0; 

Emprestimo::Emprestimo(Usuario usu, Date dataPrevDev):usuario(usu),dataPrevDevolucao(dataPrevDev){
	numero = proximoNumero;
	//Inicializar DataEmprestimo com a Data Corrente (Will)
}

void Emprestimo::adicionarLivro(Livro &nomeLivro){
	ItemEmprestimo A(nomeLivro);
	itens.push_back(A); //Acrescenta A ao final da fila!
	nomeLivro.decrementar(); //Testar se pode decrementar na classe Livro
}

void Emprestimo::excluirLivro(Livro &nomeLivro){

	//Tem que fazer o operador de == de livros
	int i;
	Date a;
	a.DataNula();
	
	for( i = 0; i < itens.size(); i++){
		 
		if ( nomeLivro == itens[i].getLivro()){
		
			itens.erase(itens.begin() + i); //Exlui o item 
	
			//Se for diferente � pq ja foi devolvido
			if(itens[i].getDataDev() == a ){
				nomeLivro.incrementar();
			}
			break; //sai do loop
		}
	}
	
	//Se pecorreu todo o vetor  significa que n�o encontrou
	if(i == itens.size()){
		throw Erro("Livro n�o encontrado");
	}
	
}

void Emprestimo::devolverLivro(Livro &nomeLivro){
	
	//Tem que fazer o operador de == de livros
	int i;
	
	for( i = 0; i < itens.size(); i++){
		 
		if ( nomeLivro == itens[i].getLivro()){
			// Como devolver um item ??? Devo exlui -lo da lista???
			nomeLivro.incrementar();
			itens[i].setDataDev();
			break; //sai do loop
		}
	}
	
	//Se pecorreu todo o vetor  significa que n�o encontrou
	if(i == itens.size()){
		throw Erro("Livro n�o encontrado");
	}
	
}

void Emprestimo::devolverTodosOsLivros(){
	
	for( int i = 0; i < itens.size(); i++){
		 
			Livro a = itens[i].getLivro(); //Sobrecarregar o operador = ou fazer constru��o por coia
			// Como devolver um item ??? Devo exclui -lo da lista??? Acho que n�o.
			a.incrementar();
			itens[i].setDataDev();
	
	}
	
}

int Emprestimo::operator==(const Emprestimo &e)const{
	
}

// --------------------------------------------------------------------    BIBLIOTECA   --------------------------------------------------------------------//

//Construtor para inicializar as listas
Biblioteca::Biblioteca(){
	//Mesmo ao inicializar, ja come�a como vazio, decidi remendicionar para 0;
	emprestimos.resize(0);
	usuarios.resize(0);
	livros.resize(0);
}

//Metodos para inserir

void Biblioteca::novoUsuario(const Usuario &u){
	usuarios.push_back(u);
}

void Biblioteca::novoEmprestimo(const Emprestimo &e){
	emprestimos.push_back(e);
}

void Biblioteca::novaPublicacao(const Publicacao &p){ //Precisa de fun��o virtual ? Para livro ser reconcedo como publica��o?
	livros.push_back(p);
}

void Biblioteca::novoItemEmprestimo(Emprestimo &e, ItemEmprestimo &i){
	e.adcItemEmprestimo(i);
}

//Metodos para exlus�o 
//Todos tem seu tratamento de excess�es!!! Lembrar de usar try and catch no main

void Biblioteca::excluiUsuario(const Usuario &u){
 //Primeiro ,tem que saber se o usuario existe
 //Fazer uma busca no vetor usuarios  
 //Se acha=lo, verificar se ele tem algum emprestimo
 //Para isso, � preciso acessar o usuario nas lista de emprestimos OK
//Tem que ter uma sobrecarga no operador na classe de usuario == OK
	int i;
	for(i = 0; i < emprestimos.size() ; i++){ // no vetor vai at� size-1 pq come�a em 0
		if(emprestimos[i].getUsuario() == u){ //Achou o usuario na lista de emprestimo
				
			
		}
	}
	//Fez uma busca em todo e n�o encontrou o usuario
	if(i == emprestimos.size()){
		throw Erro("Usuario n�o existe");
	}
	//usa o throw com o erro;
}

int Biblioteca::verificaUsuarioEmp(Usuario &u){
	int a = emprestimos.size();
	Usuario b;
	for(int i = 0; i < a ; i++){ // no vetor vai at� size-1 pq come�a em 0
		b = emprestimos[i].getUsuario();
		if(b == u){
		return true;
		}
	}
	
	return false;
}

void Biblioteca::excluiPublicacao(const Publicacao &p){
	int qtdePublicacoes = livros.size();
		
	for(int i = 0; i < qtdePublicacoes; i++){
		if(livros[i].getCodPublicacao() == p.getCodPublicacao()){
			livros.erase(livros.begin()+i);	
		}
	}
}

/*void Biblioteca::excluiEmprestimo(const Emprestimo &e){
	int qtdeEmprestimos = emprestimos.size();
	
	for(int i = 0; i < qtdeEmprestimos; i++){
		if(emprestimos[i].){
			livros.erase(livros.begin()+i);	
		}
	}
}*/

void Biblioteca::gravaArquivo(){
	
	ofstream arquivo("teste.txt");
	if(!arquivo){
		throw Erro("N�o foi poss�vel abrir o arquivo");
	}
	
	//imprimindo o vetor do tipo Usuario
	for(int i = 0; i < usuarios.size(); i++){
		arquivo << "Usuario ";
		arquivo << i + 1;
		arquivo << ":\n";
		arquivo << "Nome:";
		arquivo << usuarios[i].getNome();
		arquivo << "\nCPF:";
		arquivo << usuarios[i].getCPF();
		arquivo << "\nEndere�o:";
		arquivo << usuarios[i].getEndereco();
		arquivo << "\nFone:";
		arquivo << usuarios[i].getFone();
		arquivo << "\n\n";
	}
	
}

void Biblioteca::leArquivo(){
	string line;
	ifstream arquivo("teste.txt");
	if(!arquivo){
		throw Erro("N�o foi poss�vel abrir o arquivo");
	}
	
	string nome,cpf,fone,endereco,data,dia,mes,ano;
	int a,m,d;
	
	int i = 0;
	while(!arquivo.eof()){
		getline(arquivo,line);
		if(i == 1){
			nome = line.substr(5);
		}
		if(i == 2){
			cpf = line.substr(4);
		}
		if(i == 3){
			endereco = line.substr(9);
		}
		if(i == 4){
			fone = line.substr(5);
		}
		if(i!=6){
			i++;
		}
		if(i == 6){
			Usuario u(nome,cpf,endereco,fone);
			novoUsuario(u);
			i = 0;
		}
	}
}


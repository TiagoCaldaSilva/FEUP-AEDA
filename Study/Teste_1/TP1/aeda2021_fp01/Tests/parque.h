#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class InfoCartao {
public:
	string nome;
	bool presente;
	bool operator==(const InfoCartao &I2) const{return nome == I2.nome;}
};

class ParqueEstacionamento {
	unsigned int vagas;
	const unsigned int lotacao;
	vector<InfoCartao> clientes;
	const unsigned int numMaximoClientes;
public:
	ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli);
	bool adicionaCliente(const string & nome);
	bool retiraCliente(const string & nome);
	bool entrar(const string & nome);
	bool sair(const string & nome);
	int posicaoCliente(const string & nome) const;
	unsigned getNumLugares() const;
	unsigned getNumMaximoClientes() const;
	unsigned getNumLugaresOcupados() const;
	unsigned getNumClientesAtuais() const;
};

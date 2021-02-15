#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) : lotacao(lot), numMaximoClientes(nMaxCli)
{
    vagas = lot;
    clientes.clear();
}

unsigned ParqueEstacionamento::getNumLugares() const
{
    return lotacao;
}

unsigned ParqueEstacionamento::getNumMaximoClientes() const
{
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const
{
    for(size_t i = 0; i <= clientes.size(); i++)
    {
        if (clientes[i].nome == nome)
            return i;
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
    if (clientes.size() == numMaximoClientes)
        return false;
    InfoCartao cliente;
    cliente.presente = false;
    cliente.nome = nome;
    clientes.push_back(cliente);
    return true;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
    int n = posicaoCliente(nome);
    if(n == -1 || clientes[n].presente || vagas == 0)
        return false;
    clientes[n].presente = true;
    vagas--;
    return true;
}

bool ParqueEstacionamento::retiraCliente(const string & nome)
{
    int n = posicaoCliente(nome);
    if(clientes[n].presente || n == -1) //se o cliente estiver dentro do parque nao pode ocorrer a sua remoçao
        return false;
    clientes.erase(clientes.begin()+n);
    return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
    int n = posicaoCliente(nome);
    if(n == -1 || !clientes[n].presente)
        return false;
    clientes[n].presente = false;
    vagas++;
    return true;
}

unsigned ParqueEstacionamento::getNumLugaresOcupados() const
{
    return lotacao - vagas;
}

unsigned ParqueEstacionamento::getNumClientesAtuais() const {
    return unsigned(clientes.size());
}



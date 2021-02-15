#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli): lotacao(lot), numMaximoClientes(nMaxCli)
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
    InfoCartao ic;
    ic.nome = nome;
    auto it = find(clientes.begin(), clientes.end(), ic);
    if(it == clientes.end())
        return -1;
    return distance(clientes.begin(), it);

}

bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
    if(clientes.size() == numMaximoClientes)
        return 0;
    InfoCartao newClient;
    newClient.nome = nome; newClient.presente = 0;
    clientes.push_back(newClient);
    return 1;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
    int ind = posicaoCliente(nome);
    if(!vagas || ind == -1 || clientes[ind].presente)
        return 0;
    clientes[ind].presente = true;
    vagas--;
    return 1;
}

bool ParqueEstacionamento::retiraCliente(const string & nome)
{
    int ind = posicaoCliente(nome);
    if(clientes[ind].presente || ind == -1)
        return 0;
    clientes.erase(clientes.begin() + ind);
    return 1;

}

bool ParqueEstacionamento::sair(const string & nome)
{
    int ind = posicaoCliente(nome);
    if(!clientes[ind].presente || ind == -1)
        return 0;
    clientes[ind].presente = 0;
    vagas++;
    return 1;
}

unsigned ParqueEstacionamento::getNumLugaresOcupados() const
{
    return lotacao - vagas;
}

unsigned ParqueEstacionamento::getNumClientesAtuais() const
{
    return clientes.size();
}
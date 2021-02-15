
#include "Clinica.h"

//Animal

Animal::Animal(string umNome, string umaEspecie, int numeroConsultas):
nome(umNome), especie(umaEspecie), numConsultas(numeroConsultas)
{}

string Animal::getNome() const
{ return nome; }

string Animal::getEspecie() const
{ return especie; }

int Animal::getNumConsultas() const
{ return numConsultas; }

void Animal::incNumConsultas()
{ numConsultas++; }


// Veterinario

Veterinario::Veterinario(string umNome):nome(umNome)
{}

string Veterinario::getNome() const
{ return nome; }

list<string> Veterinario::getAnimais() const
{ return meusAnimais; }

void Veterinario::addAnimal(string umNomeAnimal)
{ meusAnimais.push_back(umNomeAnimal); }


// Consulta

Consulta::Consulta(int umaHora, int umDia, int umMes, string umNomeAnimal):
	hora(umaHora), dia(umDia), mes(umMes), nomeAnimal(umNomeAnimal)
{}

string Consulta::getNomeAnimal() const
{ return nomeAnimal; }

int Consulta::getHora() const { return hora; }
int Consulta::getDia() const { return dia; }
int Consulta::getMes() const { return mes; }


void ConsultasVet::addConsulta(const Consulta &c1)
{ minhasConsultas.insert(c1); }


//Clinica

Clinica::Clinica()
{}

list<ConsultasVet> Clinica::getConsultasDisponiveis() const
{ return consultasDisponiveis; }

hashAnimal Clinica::getAnimais() const
{ return animais; }

priority_queue<Veterinario> Clinica::getVeterinarios() const
{ return veterinarios; }

void Clinica::addConsultasDisponiveisVet(const ConsultasVet &v1)
{ consultasDisponiveis.push_front(v1); }

void Clinica::addAnimal(const Animal &a1)
{ animais.insert(a1); }

void Clinica::addVeterinario(const Veterinario &v1)
{ veterinarios.push(v1); }


/////////////////////////////////////////////////////////////////////////


//TODO: Implementar corretamente o construtor e inicializacao da BST!
ConsultasVet::ConsultasVet(string umNomeVet): nomeVeterinario(umNomeVet),
		minhasConsultas(Consulta(0,0,0))
{}


bool Consulta::operator < (const Consulta &c2) const {
    if(mes == c2.mes) {
        if(dia == c2.dia){
            return hora < c2.hora;
        }return dia < c2.dia;
    }return mes < c2.mes;
}

bool Veterinario::operator<(const Veterinario& v1) const
{
    if(meusAnimais.size() == v1.meusAnimais.size()){
        return nome > v1.nome;
    }
	return meusAnimais.size() > v1.meusAnimais.size();
}

void Clinica::addConsultas(vector<Consulta> consultas1, string nomeVet1){
    for(auto &elem: consultasDisponiveis){
        if(elem.nomeVeterinario == nomeVet1){
            for(auto x:consultas1){
                elem.addConsulta(x);
            }
            return;
        }
    }
    ConsultasVet x(nomeVet1);
    for(auto elem:consultas1){
        x.addConsulta(elem);
    }
    consultasDisponiveis.push_back(x);
}

list<Consulta> Clinica::veConsultasDisponiveis(int dia1, int dia2, int mesC, string nomeVet) const {
    list<Consulta> temp;
    for(auto elem:consultasDisponiveis){
        if(elem.nomeVeterinario == nomeVet){
            BSTItrIn<Consulta> it(elem.minhasConsultas);
            while(!it.isAtEnd()){
                if(mesC == it.retrieve().getMes()) {
                    if (dia1 <= it.retrieve().getDia() && it.retrieve().getDia() <= dia2) {
                        temp.push_back(it.retrieve());
                    }
                }
                it.advance();
            }
            break;
        }
    }
    return temp;
}

bool Clinica::marcaConsulta(int &horaC, int &diaC, int &mesC, string nomeAnimal, string nomeVet){
    for(auto &elem:consultasDisponiveis){
        if(elem.nomeVeterinario == nomeVet){
            list<Consulta> temp = veConsultasDisponiveis(diaC, 31, mesC, nomeVet);
            if(temp.empty()) return false;
            temp.sort();
            for(auto element:temp){
                if(diaC == element.getDia() && element.getHora() < horaC)
                    temp.pop_front();
            }
            horaC = temp.front().getHora();
            diaC = temp.front().getDia();
            auto it = elem.minhasConsultas.find(Consulta(horaC, diaC, mesC, nomeAnimal));
            elem.minhasConsultas.remove(it);
            return true;
        }
    }
    return false;
}

Animal Clinica::fimConsulta(string umNomeAnimal, string umNomeEspecie) {
    Animal temp(umNomeAnimal, umNomeEspecie, 1);
    for(auto elem:animais){
        if(elem.getNome() == umNomeAnimal){
            for(int i = 0; i < elem.getNumConsultas(); i++){
                temp.incNumConsultas();
            };
            animais.erase(elem);
            break;
        }
    }
    animais.insert(temp);
    return temp;
}

int Clinica::numAnimaisEspecie(string umNomeEspecie) const{
    int result = 0;
    for(auto elem:animais){
        if(elem.getEspecie() == umNomeEspecie)
            result++;
    }
    return result;
}

Veterinario Clinica::alocaVeterinario(string umNomeAnimal){
    Veterinario temp = veterinarios.top();
    veterinarios.pop();
    temp.addAnimal(umNomeAnimal);
    veterinarios.push(temp);
    return temp;
}

list<string> Clinica::veterinariosMaisN(int n) const{
    list<string> result;
    priority_queue<Veterinario>temp = veterinarios;
    while(!temp.empty()){
        if(temp.top().getAnimais().size() > n){
            result.push_front(temp.top().getNome());
        }
        temp.pop();
    }
    return result;
}
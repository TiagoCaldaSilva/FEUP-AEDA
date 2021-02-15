
#include "Cooperativa.h"
#include <algorithm>
//TODO: Implementar corretamente o construtor e inicializacao da BST!
Cooperativa::Cooperativa():vinhos(Vinho("",0))
{}


void Cooperativa::addVinhos(const vector<Vinho> &vv) {
    for(auto elem:vv){
        vinhos.insert(elem);
    }
}

list<string> Cooperativa::vinhosDisponiveis(int ano1, int ano2){
    BSTItrIn<Vinho> it(vinhos);
    list<string> result;
    while(!it.isAtEnd()){
        if(it.retrieve().getAno() >= ano1 && it.retrieve().getAno() <= ano2){
            result.push_back(it.retrieve().getNome() + ' ' + to_string(it.retrieve().getAno()));
        }
        it.advance();
    }
    if(result.empty()) result.emplace_back(("Indisponivel"));
    else {
        result.sort();
        result.reverse();
    }
    return result;
}

int Cooperativa::delVinhoNome(string umVinho){
    int counter = 0;
    vector<Vinho> vv;
    BSTItrIn<Vinho> it(vinhos);
    while(!it.isAtEnd()){
        if(it.retrieve().getNome() == umVinho){
            vv.push_back(it.retrieve());
            counter++;
        }
        it.advance();
    }
    for(auto elem:vv){
        vinhos.remove(elem);
    }
    return counter;
}

void Cooperativa::addVinicola(string umaVinicola){
    Vinicola temp(umaVinicola);
    for(auto elem:vinicolas){
        if(elem == temp){
            Vinicola x = elem;
            x.addVinho();
            vinicolas.erase(elem);
            vinicolas.insert(x);
            return;
        }
    }
    vinicolas.insert(temp);
}

Vinicola Cooperativa::maisOpcoes(){
    Vinicola result = *vinicolas.begin();
    for(auto elem:vinicolas){
        if(result < elem)
            result = elem;
    }
    return result;
}

void Cooperativa::addEnologoVinicola(string umEnologo, string umaVinicola){
    Enologo z(umEnologo);
    priority_queue<Enologo>temp;
    if(enologos.empty()){enologos.push(z); return;}
    while(!enologos.empty()){
        if(enologos.top() == z){
            for(auto &elem:z.getVinicolas()){
                if(elem == umaVinicola) {
                    Vinicola x = elem;
                    x.setVinhos(x.getVinhos() + 1);
                    z.addVinicolaInexistente(x);
                }else
                    z.addVinicolaInexistente(elem);
            }
            enologos.pop();
            enologos.push(z);
            break;
        }
        temp.push(enologos.top());
        enologos.pop();
    }
    if(enologos.empty()){
        enologos.push(z);
    }
    while(!temp.empty()){
        enologos.push(temp.top());
        temp.pop();
    }
}

list<Vinicola> Cooperativa::vinicolasMelhoresNEnologos(int n) {
    list<Vinicola> result;
    vector<pair<int, list<Vinicola>>> xx;
    bool found= false;
    priority_queue<Enologo> temp = enologos;
    while(!temp.empty()){
        int counter = 0;
        for(auto elem:temp.top().getVinicolas()){
            counter += elem.getVinhos();
        }
        xx.emplace_back(counter, temp.top().getVinicolas());
        temp.pop();
    }
    if(xx.empty()) return result;

    sort(xx.begin(), xx.end(), [](pair<int, list<Vinicola>> p1, pair<int, list<Vinicola>> p2){return p1.first > p2.first;});

    for(int i = 0; i < n && i < xx.size(); i++){
        for(auto elem:xx[i].second)
            result.push_back(elem);
    }
    return result;
}
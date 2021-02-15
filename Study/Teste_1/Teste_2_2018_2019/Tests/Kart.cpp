#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <time.h>
#include <string>
#include "Kart.h"
#include <algorithm>

using namespace std;

//To help build better array
string itos(int i){
    stringstream s;
    s << i;
    return s.str();
}

void CGrupo::criaGrupo()
{
    float cilindradas[4]  = {134,250,450,600};
    bool avariados[3]  = {true,false,false};

    srand (1);   //Criar Pistas e Karts de Teste
    for(int i=1;i<=50;i++){
        vector<CKart> frota;
        for(int j=1;j<=50;j++){
            frota.push_back(CKart(avariados[rand()% 3],
                                  ("KART - "+itos(i))+itos(j),(i-1)*50+j,cilindradas[(rand() % 4)]));
        }
        adicionaPista(CPista("Pista - "+itos(i),frota));
    }
}


vector <CKart> CPista::getKartsAvariados()
{
    vector<CKart> aux;
    for (vector<CKart>::iterator it = frotaKartsPista.begin() ; it != frotaKartsPista.end(); ++it) {
        if ((it)->getAvariado()) aux.push_back((*it));
    }
    return aux;
}
 
//Exercicio 1 a)     
vector<CKart> CGrupo::ordenaKarts()
{
	vector<CKart> vord;
    for(CPista p: pistasG){
        for(CKart ck: p.getFrotaActual())
            vord.push_back(ck);
    }
    sort(vord.begin(), vord.end(), [](CKart k1, CKart k2){return k1.getNumero() < k2.getNumero();});
	return vord;
}

//Exercicio 1 b)
class KartComparator{
public:
    int c;
    KartComparator(int cilin){c = cilin;}
    bool operator()(CKart k1){return c == k1.getCilindrada();}
};
int CGrupo::numAvariados(int cilind)
{
    int result = 0;
    KartComparator x(cilind);
    for(CPista p: pistasG){
        vector<CKart> temp = p.getKartsAvariados();
        result += count_if(temp.begin(), temp.end(), x);
    }
    return result;
}

//Exercicio 1 c)   
bool CPista::prepararCorrida(int numeroKarts, int cilind)
{
    for(CKart k: frotaKartsPista){
        if(kartsLinhaPartida.size() < numeroKarts && k.getCilindrada() == cilind && k.getAvariado() == false){
            kartsLinhaPartida.push(k);
        }
    }
    if(kartsLinhaPartida.size() < numeroKarts)
        return false;
    return true;
}

//Exercicio 1 d) 
int CPista::inicioCorrida()
{
    while(!kartsLinhaPartida.empty()){
        kartsEmProva.push_back(kartsLinhaPartida.front());
        kartsLinhaPartida.pop();
    }
    return kartsEmProva.size();
}


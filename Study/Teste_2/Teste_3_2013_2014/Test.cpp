#include "Cooperativa.h"

void test_a1_addVinhos() {

	Vinho v1("Cartuxa", 1998);
	Vinho v2("Quinta do Falcao", 1998);
	Vinho v3("Duas Quintas", 2005);
	Vinho v4("Fado", 2000);
	vector<Vinho> vv;
	vv.push_back(v1); vv.push_back(v2); vv.push_back(v3); vv.push_back(v4);

	Cooperativa c;
	c.addVinhos(vv);
	BST<Vinho> bst = c.getVinhos();
	BSTItrIn<Vinho> it(bst);

	std::cout << "Duas Quintas" << '/' <<  it.retrieve().getNome() <<std::endl;
	it.advance(); it.advance();
	std::cout << "Cartuxa"<< '/' << it.retrieve().getNome() << std::endl;
	it.advance();
	std::cout << "Quinta do Falcao"<< '/' << it.retrieve().getNome() << std::endl;

}

void test_a2_vinhosDisponiveis() {

	Vinho v1("Cartuxa", 1998);
	Vinho v2("Quinta do Falcao", 1998);
	Vinho v3("Duas Quintas", 2005);
	Vinho v4("Fado", 2000);
	Vinho v5("Alvarinho", 2002);
	Vinho v6("Redoma", 1999);
	Vinho v7("Duas Quintas", 2007);
	Vinho v8("Quinta do Falcao", 2008);
	Vinho v9("Fado", 2008);
	Vinho v10("Fado", 2011);
	Vinho v11("Cartuxa", 2001);
	Vinho v12("Alvarinho", 2008);
	vector<Vinho> vv;
	vv.push_back(v1); vv.push_back(v2); vv.push_back(v3);
	vv.push_back(v4); vv.push_back(v5); vv.push_back(v6);
	vv.push_back(v7); vv.push_back(v8); vv.push_back(v9);
	vv.push_back(v10); vv.push_back(v11); vv.push_back(v12);

	Cooperativa c;
	c.addVinho(v1); c.addVinho(v2); c.addVinho(v3); c.addVinho(v4);
	c.addVinho(v5); c.addVinho(v6); c.addVinho(v7); c.addVinho(v8);
	c.addVinho(v9); c.addVinho(v10); c.addVinho(v11); c.addVinho(v12);

	list<string> ls;
	list<string>::iterator its;

	ls = c.vinhosDisponiveis(2008, 2011);
	std::cout << 4<< '/' << ls.size() << std::endl;
	its =ls.begin();
	std::cout << "Quinta do Falcao 2008"<< '/' <<*its << std::endl;
	its++; its++; its++;
	std::cout << "Alvarinho 2008"<< '/' <<*its << std::endl;

	ls = c.vinhosDisponiveis(2012, 2013);
	std::cout << 1<< '/' << ls.size() << std::endl;

	its = ls.begin();
	std::cout << "Indisponivel"<< '/' << (*its) << std::endl;

	ls = c.vinhosDisponiveis(1998, 1998);
	std::cout << 2<< '/' << ls.size() << std::endl;

	ls = c.vinhosDisponiveis(1900, 1997);
	std::cout << 1<< '/' << ls.size() << std::endl;
	its = ls.begin();
	std::cout << "Indisponivel"<< '/' << (*its) << std::endl;

	ls = c.vinhosDisponiveis(1900, 2020);
	std::cout << 12<< '/' << ls.size() << std::endl;

	its = ls.begin();
	std::cout << "Redoma 1999"<< '/' << (*its) << std::endl;

}

void test_a3_delVinhoNome() {

	Vinho v1("Cartuxa", 1998);
	Vinho v2("Quinta do Falcao", 1998);
	Vinho v3("Duas Quintas", 2005);
	Vinho v4("Fado", 2000);
	Vinho v5("Alvarinho", 2002);
	Vinho v6("Redoma", 1999);
	Vinho v7("Duas Quintas", 2007);
	Vinho v8("Quinta do Falcao", 2008);
	Vinho v9("Fado", 2008);
	Vinho v10("Fado", 2011);
	Vinho v11("Cartuxa", 2001);
	Vinho v12("Alvarinho", 2008);
	vector<Vinho> vv;
	vv.push_back(v1); vv.push_back(v2); vv.push_back(v3);
	vv.push_back(v4); vv.push_back(v5); vv.push_back(v6);
	vv.push_back(v7); vv.push_back(v8); vv.push_back(v9);
	vv.push_back(v10); vv.push_back(v11); vv.push_back(v12);

	Cooperativa c;
	c.addVinho(v1); c.addVinho(v2); c.addVinho(v3); c.addVinho(v4);
	c.addVinho(v5); c.addVinho(v6); c.addVinho(v7); c.addVinho(v8);
	c.addVinho(v9); c.addVinho(v10); c.addVinho(v11); c.addVinho(v12);

	std::cout << 3<< '/' << c.delVinhoNome("Fado") << std::endl;
	std::cout << 0<< '/' << c.delVinhoNome("Monte Velho")<< std::endl;
	std::cout << 1<< '/' << c.delVinhoNome("Redoma")<< std::endl;
	std::cout << 2<< '/' << c.delVinhoNome("Cartuxa")<< std::endl;
	std::cout << 2<< '/' << c.delVinhoNome("Quinta do Falcao")<< std::endl;
	std::cout << 2<< '/' << c.delVinhoNome("Duas Quintas")<< std::endl;

	BST<Vinho> bst = c.getVinhos();
	std::cout << true<< '/' << bst.isEmpty()<< std::endl; //teste está errado, alvarinho não é removido

}
void test_b1_addVinicola() {

	Cooperativa c;
	c.addVinicola("Quinta da Aveleda");
	c.addVinicola("Casa Agricola Quinta do Falcao");
	c.addVinicola("Sogrape Vinhos");

	hashVinicola hv = c.getVinicolas();
	std::cout << 3<< '/' << hv.size()<< std::endl;


	c.addVinicola("Casa Agricola Quinta do Falcao");
	c.addVinicola("Sogrape Vinhos");
	hv = c.getVinicolas();
	std::cout << 3<< '/' << hv.size()<< std::endl;

	c.addVinicola("Quinta da Aveleda");
	c.addVinicola("Herdade dos Coelheiros");
	hv = c.getVinicolas();
	std::cout << 4<< '/' << hv.size()<< std::endl;

	c.addVinicola("Herdade dos Coelheiros");
	std::cout << 4<< '/' << hv.size()<< std::endl;

	std::cout << 2<< '/' <<(c.getVinicolas().begin())->getVinhos()<< std::endl;

}

void test_b2_maisOpcoes() {

	Cooperativa c;
	hashVinicola hv;

	Vinicola v1("Quinta da Aveleda");
	v1.setVinhos(1);
	Vinicola v2("Casa Agricola Quinta do Falcao");
	v2.setVinhos(1);
	Vinicola v3("Minha Quinta");
	v3.setVinhos(3);

	c.add_Vinicola(v1); c.add_Vinicola(v2);
	c.add_Vinicola(v3);
	hv=c.getVinicolas();
	std::cout << 3<< '/' << hv.size()<< std::endl;

	Vinicola vx=c.maisOpcoes();
	std::cout << "Minha Quinta"<< '/' <<vx.getNome()<< std::endl;

	Vinicola v4("Sogrape Vinhos");
	v4.setVinhos(3);
	c.add_Vinicola(v4);
	vx=c.maisOpcoes();
	std::cout << "Sogrape Vinhos"<< '/' <<vx.getNome()<< std::endl;

}


void test_c1_addEnologoVinicola() {

	Cooperativa c;

	c.addEnologoVinicola("Pedro", "Cartuxa");
	std::cout << 1<< '/' << c.getEnologos().size()<< std::endl;

	c.addEnologoVinicola("Americo", "Casal Bom");
	c.addEnologoVinicola("Pedro", "Herdade do Mar");
	std::cout << 2<< '/' << c.getEnologos().size()<< std::endl;
	std::cout << "Pedro"<< '/' << c.getEnologos().top().getNome()<< std::endl;

	c.addEnologoVinicola("Antonio", "Esteva");
	c.addEnologoVinicola("Americo", "Herdade do Sol");
	c.addEnologoVinicola("Americo", "Herdade do Sol");
	c.addEnologoVinicola("Americo", "Herdade do Sol");
	std::cout << 3<< '/' << c.getEnologos().size()<< std::endl;
	std::cout << "Americo"<< '/' << c.getEnologos().top().getNome()<< std::endl;

}

void test_c2_vinicolasMelhoresNEnologos() {

	Cooperativa c;

	std::cout << 0<< '/' << c.vinicolasMelhoresNEnologos(2).size()<< std::endl;

	Vinicola v1("Adega Jose de Sousa");
	v1.setVinhos(2);
	Vinicola v2("Casa Agricola Quinta do Falcao");
	v2.setVinhos(1);
	Vinicola v3("Sogrape Vinhos");
	v3.setVinhos(1);
	Vinicola v4("Herdade da Lapa");
	v4.setVinhos(1);
	Vinicola v5("Quinta da Granja");
	v5.setVinhos(1);

	Enologo e1("Pedro");
	Enologo e2("Joao");
	Enologo e3("Antonio");

	e1.addVinicolaInexistente(v1);
	e1.addVinicolaInexistente(v4);
	e2.addVinicolaInexistente(v5);
	e2.addVinicolaInexistente(v2);
	e3.addVinicolaInexistente(v3);

	c.addEnologo(e1);
	c.addEnologo(e2);
	c.addEnologo(e3);

	std::cout << 4<< '/' << c.vinicolasMelhoresNEnologos(2).size()<< std::endl;
	std::cout << 5<< '/' << c.vinicolasMelhoresNEnologos(10).size()<< std::endl;
	std::cout << 2<< '/' << c.vinicolasMelhoresNEnologos(1).size()<< std::endl;



	Vinicola v6("Quinta da Coruja");
	v6.setVinhos(5);
	Enologo e4("Luis");
	e4.addVinicolaInexistente(v6);
	c.addEnologo(e4);
	list<Vinicola> lv=c.vinicolasMelhoresNEnologos(1);
	std::cout << 1<< '/' << lv.size()<< std::endl;
	std::cout << "Quinta da Coruja"<< '/' << (lv.begin())->getNome()<< std::endl;

}


int main(){
    test_c2_vinicolasMelhoresNEnologos();
    return 0;
}




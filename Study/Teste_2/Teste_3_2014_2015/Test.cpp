#include "Clinica.h"

void test_a1_addConsultas() {
 	Clinica cli;

	Consulta c1(2,10,3);
	Consulta c2(3,2,3);
	Consulta c3(4,10,3);
	Consulta c4(3,2,3);
	Consulta c5(4,20,2);

	vector<Consulta> vc;
	vc.push_back(c1);
	vc.push_back(c2);
	vc.push_back(c3);
	vc.push_back(c4);
	vc.push_back(c5);

	cli.addConsultas(vc,"Raul Santos");
	list<ConsultasVet> cv=cli.getConsultasDisponiveis();
	std::cout << 1 << '/' << cv.size() << std::endl;
	BST<Consulta> consultasV=cv.front().minhasConsultas;

	Consulta consulta1=consultasV.findMin();
	std::cout << 2<< '/' <<consulta1.getMes()<<std::endl;
	consultasV.remove(consulta1);
	consulta1=consultasV.findMin();
	std::cout << 3<< '/' <<consulta1.getMes()<<std::endl;
	std::cout << 2<< '/' <<consulta1.getDia()<<std::endl;
	consultasV.remove(consulta1);
	consulta1=consultasV.findMin();
	std::cout << 3<< '/' <<consulta1.getMes()<<std::endl;
	std::cout << 10<< '/' <<consulta1.getDia()<<std::endl;
	std::cout << 2<< '/' <<consulta1.getHora()<<std::endl;
	consultasV.remove(consulta1);
	consulta1=consultasV.findMin();
	std::cout << 10<< '/' <<consulta1.getDia() << std::endl;
	std::cout << 4<< '/' <<consulta1.getHora() << std::endl;
	consultasV.remove(consulta1);
	std::cout << true<< '/' <<consultasV.isEmpty() << std::endl;

	vc.clear();
	vc.push_back(c1);
    vc.push_back(c2);

    cli.addConsultas(vc,"Maria Dinis");
    cv=cli.getConsultasDisponiveis();
    std::cout << 2<< '/' <<cv.size() << std::endl;
    std::cout << "Maria Dinis"<< '/' <<cv.front().nomeVeterinario << std::endl;
}

void test_a2_veConsultasDisponiveis() {
	Clinica cli;

	Consulta c1(2,10,3);
	Consulta c2(3,2,3);
	Consulta c3(4,10,3);
	Consulta c4(3,5,3);
	Consulta c5(4,20,2);

	ConsultasVet vet1("Raul Santos");
	vet1.addConsulta(c1);
	vet1.addConsulta(c2);
	vet1.addConsulta(c3);
	vet1.addConsulta(c4);
	vet1.addConsulta(c5);
	ConsultasVet vet2("Maria Dinis");
	ConsultasVet vet3("Jaime Luis");
	vet3.addConsulta(c1);
	vet3.addConsulta(c2);
	vet3.addConsulta(c3);

	cli.addConsultasDisponiveisVet(vet1);
	cli.addConsultasDisponiveisVet(vet2);
	cli.addConsultasDisponiveisVet(vet3);

	list<Consulta> res;

	res = cli.veConsultasDisponiveis(1,12,3,"Raul Santos");
	std::cout << 4<< '/' <<res.size()<<std::endl;
	std::cout << 2<< '/' <<res.front().getDia()<<std::endl;
	std::cout << 4<< '/' <<res.back().getHora()<<std::endl;
	std::cout << 10<< '/' <<res.back().getDia()<<std::endl;
	std::cout << 3<< '/' <<res.back().getMes()<<std::endl;

	res = cli.veConsultasDisponiveis(1,12,3,"Maria Dinis");
	std::cout << 0<< '/' <<res.size() << std::endl;

	res = cli.veConsultasDisponiveis(1,12,3,"Carolina Silva");
	std::cout << 0<< '/' <<res.size() << std::endl;

	res = cli.veConsultasDisponiveis(12,14,3,"Jaime Luis");
	std::cout << 0<< '/' <<res.size() << std::endl;
}


void test_a3_marcaConsulta() {
	Clinica cli;

	Consulta c1(2,10,3);
	Consulta c2(3,2,3);
	Consulta c3(4,10,3);
	Consulta c4(3,5,3);

	ConsultasVet vet1("Raul Santos");
	vet1.addConsulta(c1);
	vet1.addConsulta(c2);
	vet1.addConsulta(c3);
	vet1.addConsulta(c4);

	cli.addConsultasDisponiveisVet(vet1);

	int horaC=3, diaC=2, mesC=3;
	bool res=cli.marcaConsulta(horaC,diaC,mesC,"bobby", "Raul Santos");
	std::cout << true<< '/' <<res << std::endl;
	std::cout << 2<< '/' <<diaC << std::endl;
	BST<Consulta> consultasX=cli.getConsultasDisponiveis().front().minhasConsultas;
	Consulta consX=consultasX.findMin();
	consultasX.remove(consX);
	consX=consultasX.findMin();
	consultasX.remove(consX);
	consX=consultasX.findMin();
	consultasX.remove(consX);
	std::cout << true<< '/' <<consultasX.isEmpty() << std::endl;

	horaC=4, diaC=5, mesC=3;
	res=cli.marcaConsulta(horaC,diaC,mesC,"bobby", "Raul Santos");
	std::cout << true<< '/' <<res << std::endl;
	std::cout << 2<< '/' <<horaC <<std::endl;
	std::cout << 10<< '/' <<diaC << std::endl;
	consultasX=cli.getConsultasDisponiveis().front().minhasConsultas;
	consX=consultasX.findMin();
	consultasX.remove(consX);
	consX=consultasX.findMin();
	consultasX.remove(consX);
	std::cout << true<< '/' <<consultasX.isEmpty() << std::endl;

	horaC=4, diaC=15, mesC=3;
	res=cli.marcaConsulta(horaC,diaC,mesC,"bobby", "Raul Santos");
	std::cout << false<< '/' <<res << std::endl;
	consultasX=cli.getConsultasDisponiveis().front().minhasConsultas;
	consX=consultasX.findMin();
	consultasX.remove(consX);
	consX=consultasX.findMin();
	consultasX.remove(consX);
	std::cout << true<< '/' <<consultasX.isEmpty() << std::endl;

	ConsultasVet vet2("Maria Dinis");
	cli.addConsultasDisponiveisVet(vet2);

	res=cli.marcaConsulta(horaC,diaC,mesC,"bobby", "Maria Dinis");
	std::cout << false<< '/' <<res << std::endl;

	res=cli.marcaConsulta(horaC,diaC,mesC,"bobby", "Joana Lima");
	std::cout << false << '/' << res << std::endl;
}


void test_b1_fimConsulta() {
	Clinica cli;
	Animal a1=cli.fimConsulta("bobby","cao");
	std::cout << "bobby"<< '/' << a1.getNome() << std::endl;
	std::cout << 1<< '/' << a1.getNumConsultas() << std::endl;

	a1=cli.fimConsulta("tareco","gato");
	std::cout << "tareco"<< '/' << a1.getNome() << std::endl;
	std::cout << 1<< '/' << a1.getNumConsultas() << std::endl;

	a1=cli.fimConsulta("bobby","cao");
	a1=cli.fimConsulta("bobby","cao");
	std::cout << "bobby" << '/' << a1.getNome() << std::endl;
	std::cout << 3 << '/' << a1.getNumConsultas() << std::endl;

	a1=cli.fimConsulta("dori","peixe");
	std::cout << "dori"<< '/' << a1.getNome() << std::endl;
	std::cout << 1<< '/' << a1.getNumConsultas() << std::endl;

	std::cout << 3<< '/' <<cli.getAnimais().size() << std::endl;
}

void test_b2_numEspecie() {
	Clinica cli;

	Animal a1("bobby", "cao");
	Animal a2("dori", "peixe");
	Animal a3("kurika","cao");
	Animal a4("nero","cao");
	Animal a5("nemo","peixe");
	cli.addAnimal(a1);
	cli.addAnimal(a2);
	cli.addAnimal(a3);
	cli.addAnimal(a4);
	cli.addAnimal(a5);
	std::cout << 3<< '/' <<cli.numAnimaisEspecie("cao") << std::endl;
}

void test_c1_alocaVeterinario() {
	Clinica cli;

	Veterinario vet1("Joao Santos");
	vet1.addAnimal("bobby");
	vet1.addAnimal("tareco");
	vet1.addAnimal("dori");
	cli.addVeterinario(vet1);

	Veterinario vet2("Jaime Dinis");
	cli.addVeterinario(vet2);

	Veterinario vet3("Maria Silva");
	vet3.addAnimal("tareco");
	vet3.addAnimal("lassie");
	cli.addVeterinario(vet3);

	Veterinario vetX=cli.alocaVeterinario("romi");
	std::cout << "Jaime Dinis"<< '/' << vetX.getNome() << std::endl;
	std::cout << 1<< '/' <<vetX.getAnimais().size() << std::endl;
	std::cout << 3<< '/' <<cli.getVeterinarios().size() << std::endl;

	vetX=cli.alocaVeterinario("bravo");
	std::cout << "Jaime Dinis"<< '/' << vetX.getNome() << std::endl;

	vetX=cli.alocaVeterinario("baba");
	std::cout << "Jaime Dinis"<< '/' << vetX.getNome() << std::endl;

	vetX=cli.alocaVeterinario("kurika");
	std::cout << "Maria Silva"<< '/' << vetX.getNome() << std::endl;
	std::cout << 3<< '/' <<vetX.getAnimais().size() << std::endl;
	std::cout << 3<< '/' <<cli.getVeterinarios().size() << std::endl;
}

void test_c2_veterinariosMaisN() {
	Clinica cli;

	Veterinario vet1("Joao Santos");
	vet1.addAnimal("bobby");
	vet1.addAnimal("tareco");
	vet1.addAnimal("dori");
	cli.addVeterinario(vet1);

	Veterinario vet2("Jaime Dinis");
	cli.addVeterinario(vet2);

	Veterinario vet3("Maria Silva");
	vet3.addAnimal("tareco");
	vet3.addAnimal("lassie");
	cli.addVeterinario(vet3);

	Veterinario vet4("Carlos Pereira");
	vet4.addAnimal("bobby");
	vet4.addAnimal("tareco");
	vet4.addAnimal("dori");
	vet4.addAnimal("lassie");
	cli.addVeterinario(vet4);

	list<string> res=cli.veterinariosMaisN(1);
	std::cout << 3 << '/' << res.size() << std::endl;
	std::cout << "Carlos Pereira" << '/' << res.front() << std::endl;
	res.pop_front();
	std::cout << "Joao Santos" << '/' << res.front() << std::endl;

	res=cli.veterinariosMaisN(6);
	std::cout << 0 << '/' << res.size() << std::endl;
}


int main(){
    test_c2_veterinariosMaisN();
    return 0;
}




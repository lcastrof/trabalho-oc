#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "MemoriaDeInstrucoes.h"
#include "BancoDeRegistradores.h"
#include "UnidadeDeControle.h"
#include "FuncoesAuxiliares.h"
#include "ALU.h"

using namespace std;

int PC = 0; // inicializando PC (lembrar de multiplicar/dividir por 4 para acessar corretamente as informações)

void estagio_1(MemoriaDeInstrucoes *memoria_de_instrucoes){
  int proximoPC = somaPC(PC);
  long long int instrucao = memoria_de_instrucoes->getInstrucao(PC);

  if_id.proximoPC = proximoPC;
  if_id.instrucao = instrucao;

  cout << "---------- Estagio 1 ----------" << endl;
  cout << "IF_ID: " << endl;
  cout << "proximoPC: " << if_id.proximoPC << endl;
  cout << "instrucao: " << if_id.instrucao << endl;
}

void estagio_2(UnidadeDeControle *unidade, BancoDeRegistradores *bancoReg){
  // Decodifica instruções, lê registradores
  // Define unidade de controle
  ElementosInstrucao el =  decodificaInstrucao(if_id.instrucao);

  unidade->analisaInstrucao(el.opcode);

  int conteudoReg1;
  int conteudoReg2;
  bancoReg->leBanco(el.rs, el.rt, &conteudoReg1, &conteudoReg2);

  id_ex.proximoPC = if_id.proximoPC;
  id_ex.readData1 = conteudoReg1;
  id_ex.readData2 = conteudoReg2;
  id_ex.instruction_15_0 = el.address;
  id_ex.instruction_20_16 = el.rt;
  id_ex.instruction_15_11 = el.rd;

  cout << "---------- Estagio 2 ----------" << endl;
  cout << "ID_EX: " << endl;
  cout << "proximoPC: " << id_ex.proximoPC << endl;
  cout << "readData1: " << id_ex.readData1 << endl;
  cout << "readData2: " << id_ex.readData2 << endl;
  cout << "instruction_15_0(address): " << id_ex.instruction_15_0 << endl;
  cout << "instruction_20_16(rt): " << id_ex.instruction_20_16 << endl;
  cout << "instruction_15_11(rd): " << id_ex.instruction_15_11 << endl;
}

void estagio_3(){
 // Execução ou cálculo do endereço 
 // ALU
 // 
}

void estagio_4(){
 // Acessa memória de dados (criar classe)
 // Atualiza PCSrc na unidade de controle
 // Atualiza PC
}

void estagio_6(){
 // Escrita do resultado

}


int main()
{  
  // Definindo estruturas
  MemoriaDeInstrucoes *memoria_de_instrucoes = new MemoriaDeInstrucoes();
  UnidadeDeControle *unidade = new UnidadeDeControle();
  BancoDeRegistradores *bancoReg = new BancoDeRegistradores();
  ALU *alu = new ALU();
  
  // leitura do arquivo
  ifstream arquivo;
  arquivo.open("comandos.txt");

  if (arquivo.is_open()) {
    string str;
    int count = 0;
    while(getline(arquivo, str)) {
      cout << "linha " << count << " = " << str << endl;
      if (str.length() != 32) {
        cout << "Encontrada instrucao invalida(diferente de 32 bits) no arquivo selecionado, na linha " << count + 1 << "." << endl;
        cout << "Favor ajustar e tentar novamente." << endl;
        exit(0);
      }
      long long int valor_convertido = converteBinarioParaInteiro(str);
      memoria_de_instrucoes->insereInstrucao(count, valor_convertido);
      count += 1;
    }
  }
  arquivo.close();

  
  // Loop
  // while (PC < 128*4) {
  //   estagio_1();
  //   estagio_2();
  //   estagio_3();
  //   estagio_4();
  //   estagio_5();
  // }

  memoria_de_instrucoes->imprimeNInstrucoes(2); // apenas para checar se está correto

  cout << "Exemplo de instrucao decodificada: " << endl;
  ElementosInstrucao el =  decodificaInstrucao(memoria_de_instrucoes->getInstrucao(0));
  cout << "el: " << endl;
  cout << el.opcode << endl;
  cout << el.rt << endl;
  cout << el.rs << endl;
  cout << el.rd << endl;

  estagio_1(memoria_de_instrucoes);
  estagio_2(unidade, bancoReg);
}

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>

#include "MemoriaDeInstrucoes.h"
#include "MemoriaDeDados.h"
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

  cout << "\n---------- Estagio 1 ----------" << endl;
  cout << "\n | IF_ID | " << endl;
  cout << " -> proximoPC: " << if_id.proximoPC << endl;
  cout << " -> instrucao: " << if_id.instrucao << endl;
}

int estagio_2(UnidadeDeControle *unidade, BancoDeRegistradores *bancoReg){
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
  id_ex.instruction_15_0 = extendeSinal(el.address) ;
  id_ex.instruction_20_16 = el.rt;
  id_ex.instruction_15_11 = el.rd;

  //Atualizar unidade de controle de acordo com a instrução lida
  unidade->atualizaUnidade(el.desc);


  cout << "\n---------- Estagio 2 ----------" << endl;
  cout << " -> Instrucao identificada: " << el.retornaTipo() << endl;
    unidade->statusUnidade();
  cout << "\n | ID_EX | " << endl;
  cout << " -> proximoPC: " << id_ex.proximoPC << endl;
  cout << " -> readData1: " << id_ex.readData1 << endl;
  cout << " -> readData2: " << id_ex.readData2 << endl;
  cout << " -> instruction_15_0(address extendido): " << id_ex.instruction_15_0 << endl;
  cout << " -> instruction_20_16(rt): " << id_ex.instruction_20_16 << endl;
  
  if(el.desc >= 1 && el.desc <= 6){
    cout << " -> instruction_15_11(rd): " << id_ex.instruction_15_11 << endl;
  } 


  return el.desc;
}




void estagio_3(UnidadeDeControle *unidade, ALU *alu, int desc){

  
 // Execução ou cálculo do endereço 
 // ALU
  cout << "\n---------- Estagio 3 ----------" << endl;
  // Resultado do Add
  ex_mem.addResult = addEnderecos();

  // Passando readData2 de ID/EX para EX/MEM
  ex_mem.readData2 = id_ex.readData2;

  // Resultado da ALU
  int entradaALU1 = id_ex.readData1;
  int entradaALU2;
  if(unidade->getALUSrc()){
    entradaALU2 = id_ex.instruction_15_0;
  } else {
    entradaALU2 = id_ex.readData2;
  }

  // Função que entrega resultado da ALU de acordo com a instrução

  ex_mem.ALUResult = alu->operacaoALU(entradaALU1, entradaALU2, desc); 


  // Passando Mux de acordo com controle
  if(unidade->getRegDst()){
    ex_mem.MuxRegDst = id_ex.instruction_15_11;
  } else {
    ex_mem.MuxRegDst = id_ex.instruction_20_16;
  }

  
  cout << "\n | EX/MEM | " << endl;
  cout << " -> addResult: " << ex_mem.addResult << endl;
  cout << " -> readData2: " << ex_mem.readData2 << endl;
  cout << " -> MuxRegDst: " << ex_mem.MuxRegDst << endl;

}

void estagio_4(MemoriaDeDados *memDados, UnidadeDeControle *unidade, int *PC){
  // Acessa memória de dados (criar classe)
  // Atualiza PCSrc na unidade de controle
  // Atualiza PC

  // Realiza operações na memória de dados
  int readData = memDados->operaDados(ex_mem.ALUResult, ex_mem.readData2, unidade->getMemWrite(), unidade->getMemRead());

  // Atualiza PC
  if (unidade->getPCSrc()) {
    *PC = ex_mem.addResult;
  } else {
    *PC = somaPC(*PC);
  }

  // Atualiza dados para a próxima etapa   
  mem_wb.readData = readData;
  mem_wb.ALUResult = ex_mem.ALUResult;
  mem_wb.MuxRegDst = ex_mem.MuxRegDst;

  cout << "\n---------- Estagio 4 ----------" << endl;
  cout << "\n | MEM/WB | " << endl;
  cout << " -> readData: " << mem_wb.readData << endl;
  cout << " -> ALUResult: " << mem_wb.ALUResult << endl;
  cout << " -> MuxRegDst: " << mem_wb.MuxRegDst << endl;

  // Falta atualizar o PCSrc de acordo com o Branch e Zero da aLU


}

void estagio_5(BancoDeRegistradores *bancoReg, UnidadeDeControle *unidade){
  // Escrita do resultado
  int wData;
  if (unidade->getMemtoReg()) {
    wData = mem_wb.readData;
  } else {
    wData = mem_wb.ALUResult;
  }

  bancoReg->escreveBanco(mem_wb.MuxRegDst, wData, unidade->getRegWrite());

  cout << "\n---------- Estagio 5 ----------" << endl;
  cout << "-> wData:  " << wData << endl;
}


int main()
{  
  // Definindo estruturas
  MemoriaDeInstrucoes *memoria_de_instrucoes = new MemoriaDeInstrucoes();
  UnidadeDeControle *unidade = new UnidadeDeControle();
  BancoDeRegistradores *bancoReg = new BancoDeRegistradores();
  MemoriaDeDados *memoria_de_dados = new MemoriaDeDados();
  ALU *alu = new ALU();

  bancoReg->escreveBanco(17, 10, true);
  
  // leitura do arquivo
  ifstream arquivo;
  arquivo.open("comandos_A5S28.txt");

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

  memoria_de_instrucoes->imprimeNInstrucoes(3); // apenas para checar se está correto

  cout << "Exemplo de instrucao decodificada: " << endl;
  ElementosInstrucao el =  decodificaInstrucao(memoria_de_instrucoes->getInstrucao(0));
  cout << "el: " << endl;
  cout << el.opcode << endl;
  cout << el.rs << endl;
  cout << el.rt << endl;
  cout << el.rd << endl;
  cout << el.shamt << endl;
  cout << el.funct << endl;
  cout << "Address: " << el.address << endl;
  string converted = "1111111111111111";
  cout << "Address decodificado: " << converted.append(bitset<16>(el.address).to_string()) << endl;
  cout << "Primeiro: " << converted[0] << endl;
  cout << "Segundo: " << (converteBinarioParaInteiro("010")<<2) << endl;

  // cout << "Exemplo de instrucao decodificada: " << endl;
  // ElementosInstrucao el1 =  decodificaInstrucao(memoria_de_instrucoes->getInstrucao(4));
  // cout << "el: " << endl;
  // cout << el1.opcode << endl;
  // cout << el1.rs << endl;
  // cout << el1.rt << endl;
  // cout << el1.rd << endl;
  // cout << el1.shamt << endl;
  // cout << el1.funct << endl;

  // cout << "Exemplo de instrucao decodificada: " << endl;
  // ElementosInstrucao el2 =  decodificaInstrucao(memoria_de_instrucoes->getInstrucao(8));
  // cout << "el: " << endl;
  // cout << el2.opcode << endl;
  // cout << el2.rs << endl;
  // cout << el2.rt << endl;
  // cout << el2.rd << endl;
  // cout << el2.shamt << endl;
  // cout << el2.funct << endl;

  int desc;

  estagio_1(memoria_de_instrucoes);
  desc = estagio_2(unidade, bancoReg);
  estagio_3(unidade, alu, desc);
  estagio_4(memoria_de_dados, unidade, &PC);
  estagio_5(bancoReg, unidade);
}

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "MemoriaDeInstrucoes.h"
#include "FuncoesAuxiliares.h"

using namespace std;

int main()
{  
  MemoriaDeInstrucoes *mem_inst = new MemoriaDeInstrucoes(); // onde serão armazenadas as sequências de instruções
  int PC = 0; // inicializando PC (lembrar de multiplicar/dividir por 4 para acessar corretamente as informações)

  // leitura do arquivo
  ifstream arquivo;
  arquivo.open("comandos.txt");
  cout << "entrou" << endl;

  if (arquivo.is_open()) {
    string str;
    int count = 0;
    while(getline(arquivo, str)) {
      if (str.length() != 32) {
        cout << "Encontrada instrucao invalida(diferente de 32 bits) no arquivo selecionado, na linha " << count + 1 << "." << endl;
        cout << "Favor ajustar e tentar novamente." << endl;
        exit(0);
      }
      long long int valor_convertido = converteBinarioParaInteiro(str);
      mem_inst->insereInstrucao(count, valor_convertido);
      count += 1;
    }
  }
  arquivo.close();

  mem_inst->imprimeNInstrucoes(2); // apenas para checar se está correto

  cout << "Exemplo de instrucao decodificada: " << endl;
  ElementosInstrucao el =  decodificaInstrucao(mem_inst->getInstrucao(0));
  cout << "el: " << endl;
  cout << el.opcode << endl;
  cout << el.rt << endl;
  cout << el.rs << endl;
  cout << el.rd << endl;
}




void estagio_1(){

}

void estagio_2(){
 // Decodifica instruções, lê registradores
 // Define unidade de controle


}

void estagio_3(){
 // Execução ou cálculo do endereço 
 // ALU
 // 
}

void estagio_4(){
 // Acessa memória de dados (criar classe)
 // Atualiza PCSrc na unidade de controle
}

void estagio_5(){
 // Escrita do resultado

}
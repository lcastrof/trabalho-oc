#ifndef __FUNCOESAUXILIARES_H__
#define __FUNCOESAUXILIARES_H__
#include <iostream>
#include <sstream>
#include <fstream>


using namespace std;

struct IF_ID {
  int proximoPC;
  long long int instrucao;
};
IF_ID if_id;

struct ID_EX {
  int proximoPC;
  int readData1;
  int readData2;
  int instruction_15_0;
  int instruction_20_16;
  int instruction_15_11;
};
ID_EX id_ex;

struct EX_MEM {
  
};

struct MEM_WB {
  
};


struct ElementosInstrucao {
  int opcode;
  int rs;
  int rt;
  int rd;
  int shamt;
  int funct;
  int address;
};

long long int converteBinarioParaInteiro(string strBin) {
  cout << "conversao: " << strBin << " para decimal: " << stoi(strBin, 0, 2) << endl;
  return stoll(strBin, 0, 2);
}

int somaPC(int PC) {
  return PC + 4;
}

ElementosInstrucao decodificaInstrucao(long long int instruct) {
  ElementosInstrucao elementos;
  
  // opcode (como sempre são os primeiros 6 bits, não é necessário uma máscara para recuperá-lo)
  int opcode = (instruct>>26);
  cout << "opcode " << opcode << endl;
  elementos.opcode = opcode;

  // rs
  string mascara_rs = "00000011111000000000000000000000";
  int rs = (instruct&converteBinarioParaInteiro(mascara_rs))>>21;
  cout << "rs " << rs << endl;
  elementos.rs = rs;

  // rt
  string mascara_rt = "00000000000111110000000000000000";
  int rt = (instruct&converteBinarioParaInteiro(mascara_rt))>>16;
  cout << "rt " << rt << endl;
  elementos.rt = rt;

  if (opcode == 0) { // instrução tipo R
    string mascara_rd = "00000000000000001111100000000000";
    int rd = (instruct&converteBinarioParaInteiro(mascara_rd))>>11;
    cout << "rd " << rd << endl;
    elementos.rd = rd;
    
    string mascara_shamt = "00000000000000000000011111000000";
    int shamt = (instruct&converteBinarioParaInteiro(mascara_shamt))>>6;
    cout << "shamt " << shamt << endl;
    elementos.shamt = shamt;

    string mascara_funct = "00000000000000000000000000111111";
    int funct = (instruct&converteBinarioParaInteiro(mascara_funct));
    cout << "funct " << funct << endl;
    elementos.funct = funct;
  } else if (opcode == 2) { // instrução tipo J
    string mascara_jump_address = "00000011111111111111111111111111";
    int jump_address = (instruct&converteBinarioParaInteiro(mascara_jump_address));
    cout << "jump_address " << jump_address << endl;
    elementos.address = jump_address;
  } else { // instrução tipo I
    string mascara_address = "00000000000000001111111111111111";
    int address = (instruct&converteBinarioParaInteiro(mascara_address));
    cout << "address " << address << endl;
    elementos.address = address;
  }

  return elementos;
}

#endif // __FUNCOESAUXILIARES_H__
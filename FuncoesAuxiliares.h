#ifndef __FUNCOESAUXILIARES_H__
#define __FUNCOESAUXILIARES_H__
#include <iostream>
#include <sstream>
#include <fstream>
#include <bitset>


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
  int addResult;
  int ALUResult;
  int readData2;
  int MuxRegDst;
};
EX_MEM ex_mem;

struct MEM_WB {
  int readData;
  int ALUResult;
  int MuxRegDst;
};
MEM_WB mem_wb;

struct ElementosInstrucao {
  int opcode;
  int rs;
  int rt;
  int rd;
  int shamt;
  int funct;
  int address;

  int desc;
  //descrições abaixo
  string retornaTipo(){

    switch(desc){
      case 1: return "add";
      case 2: return "sub";
      case 3: return "and";
      case 4: return "or";
      case 5: return "slt";
      case 6: return "sll";
      case 7: return "addi";
      case 8: return "lw";
      case 9: return "sw";
      case 10: return "beq";
      case 11: return "bne";
      case 12: return "j";
      case 13: return "jr";
      case 14: return "jal";
      default: return "";
      }
  
  }
};


long long int converteBinarioParaInteiro(string strBin) {
  cout << "conversao: " << strBin << " para decimal: " << stoll(strBin, 0, 2) << endl;
  return stoll(strBin, 0, 2);
}

long long int extendeSinal(long int numero) {
  string numBin = bitset<16>(numero).to_string();
  string extensor;

  if (numBin[0] == '1') { // negativo
    extensor = "1111111111111111";
  } else {
    extensor = "0000000000000000";
  }

  string binarioExtendido = extensor + numBin;
  cout << "Bin ext: " << binarioExtendido << endl;

  long long int convertido =  converteBinarioParaInteiro(binarioExtendido);

  cout << "Convertido: " << convertido << endl;

  return convertido;
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

    //identificar a operação do tipo R
    if(funct == converteBinarioParaInteiro("100000")){
      elementos.desc = 1;
    } else if (funct == converteBinarioParaInteiro("100010")){
      elementos.desc = 2;
    } else if(funct == converteBinarioParaInteiro("100100")){
      elementos.desc = 3;
    } else if (funct == converteBinarioParaInteiro("100101")){
      elementos.desc = 4;
    } else if(funct == converteBinarioParaInteiro("101010")){
      elementos.desc = 5;
    } else if(funct == converteBinarioParaInteiro("000000")){
      elementos.desc = 6;
    } else {
      elementos.desc = -1;
    }

  } 
  
  
  else if (opcode == 2) { // instrução tipo J

    string mascara_jump_address = "00000011111111111111111111111111";
    int jump_address = (instruct&converteBinarioParaInteiro(mascara_jump_address));
    cout << "jump_address " << jump_address << endl;
    elementos.address = jump_address;
  } 
  
  
  else { // instrução tipo I

    string mascara_address = "00000000000000001111111111111111";
    int address = (instruct&converteBinarioParaInteiro(mascara_address));
    cout << "address " << address << endl;
    elementos.address = address;

    // se for lw
    if(opcode == converteBinarioParaInteiro("100011")){
      elementos.desc = 8;
    // se for sw
    } else if (opcode == converteBinarioParaInteiro("101011") ) {
      elementos.desc = 9;
    // se for addi
    } else if (opcode == converteBinarioParaInteiro("001000")) {
      elementos.desc = 7;
    // se for beq 
    } else if (opcode == converteBinarioParaInteiro("000100")){
      elementos.desc = 10;
    // se for bne
    } else if (opcode == converteBinarioParaInteiro("000101")){
      elementos.desc = 11;
    } else {
      elementos.desc = -1;
    }

  }


  return elementos;
}

#endif // __FUNCOESAUXILIARES_H__
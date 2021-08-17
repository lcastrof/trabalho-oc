#ifndef UNIDADEDECONTROLE_H_INCLUDED
#define UNIDADEDECONTROLE_H_INCLUDED

#include <iostream>
#include <cstdlib>

#include "FuncoesAuxiliares.h"

using namespace std;

class UnidadeDeControle {
  private:
    bool RegDst;
    bool RegWrite;
    bool ALUSrc;
    bool ALUOp0;
    bool ALUOp1;
    bool PCSrc;
    bool MemRead;
    bool MemWrite;
    bool MemoReg;

  public:
    UnidadeDeControle() {
      RegDst = false;
      RegWrite = false;
      ALUSrc = false;
      ALUOp0 = false;
      ALUOp1 = false;
      PCSrc = false;
      MemRead = false;
      MemWrite = false;
      MemoReg = false;
    };

    void analisaInstrucao(int opcode) {
      if (opcode == 0) { // Tipo R
        RegDst = true;
        RegWrite = true;
        ALUOp1 = true;
      } 
    }
};

#endif // UNIDADEDECONTROLE_H_INCLUDED
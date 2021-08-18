#ifndef UNIDADEDECONTROLE_H_INCLUDED
#define UNIDADEDECONTROLE_H_INCLUDED

#include <iostream>
#include <cstdlib>

#include "FuncoesAuxiliares.h"

using namespace std;

class UnidadeDeControle {

  // No estágio de decodificação

  private:
    
    // Determina se o banco deve ou não ser escrito
    // quanto ativo permite que o valor WriteData seja escrito no registrador WriteRegister
    bool RegWrite;

    // Determina qual o número do registrador que será escrito
    // Se instrução do tipo R -> RegDst = 1, registrador a ser escrito é 
    // determinado pelos bits de 11 a 15
    // Se for RegDst = 0, instrução lw. Pega o número do registrador a ser 
    // escrito dos bits de 16 a 20
    bool RegDst;

    // Determina se veio do banco de registradores (0) ou do extensor de sinal (1)
    bool ALUSrc;

    // Determina qual é a operação a ser executada pela ALU, pode ser uma soma quando 
    // se tem uma operação de lw/sw
    // uma subtração quando tem o beq 
    // ou determinação por funct 
    bool ALUOp0;
    bool ALUOp1;


    // Determina qual valor será atribuído a PC
    // Quanto ativo: PC = PC + 4
    // Quando inativo: PC = desvio
    bool PCSrc;

    // lw
    bool MemRead;

    // sw
    bool MemWrite;

    // Determinar o que vai ser escrito no banco de registradores
    // 1 - lw
    // 0 - R
    bool MemtoReg;

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
      MemtoReg = false;
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
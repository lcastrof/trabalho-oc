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

    bool Branch;

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
      Branch = false;
    };

    string analisaInstrucao(int opcode) {
      string tipo;
      if (opcode == 0) { // Tipo R
        RegDst = true;
        RegWrite = true;
        ALUOp1 = true;
        tipo = "R";
      }
      else{ // Enquanto não implementamos J

        tipo = 'I';
      }
    
      return tipo;
    }

    void statusUnidade(){
      
      cout << "\n   ------ CONTROLE ------ " << endl;
      cout << " # RegDst: " << RegDst << endl;
      cout << " # RegWrite: " << RegWrite << endl;   
      cout << " # ALUSrc: " << ALUSrc << endl; 
      cout << " # ALUOp0: " << ALUOp0 << endl; 
      cout << " # ALUOp1: " << ALUOp1 << endl; 
      cout << " # Branch: " << Branch << endl; 
      cout << " # MemRead: " << MemRead << endl; 
      cout << " # MemWrite: " << MemWrite << endl; 
      cout << " # MemtoReg: " << MemtoReg << endl; 

    }


    void atualizaUnidade(int instrucao){

      // se instrução é do tipo R (menos jr)
      if(instrucao >= 1 & instrucao <= 6){

        RegDst = true;
        RegWrite = true;
        ALUSrc = false;
        ALUOp0 = false;
        ALUOp1 = true;
        Branch = false;
        MemRead = false;
        MemWrite = false;
        MemtoReg = true;

     // se instrução for lw   
     } else if (instrucao == 8){
        RegDst = false;
        RegWrite = true;
        ALUSrc = true;
        ALUOp0 = false;
        ALUOp1 = false;
        Branch = false;
        MemRead = true;
        MemWrite = false;
        MemtoReg = false;

     // se instrução for sw
     } else if (instrucao == 9){
        
        RegWrite = false;
        ALUSrc = true;
        ALUOp0 = false;
        ALUOp1 = false;
        Branch = false;
        MemRead = false;
        MemWrite = true;

     // se instrucao for beq
     } else if (instrucao == 10){
       
        RegWrite = false;
        ALUSrc = false;
        ALUOp0 = true;
        ALUOp1 = false;
        Branch = true;
        MemRead = false;
        MemWrite = true;

     // se for addi 
     } else if (instrucao == 7) {
        RegDst = false;
        RegWrite = true;
        ALUSrc = true;
        ALUOp0 = true;
        ALUOp1 = true;
        MemRead = false;
        MemWrite = false;
        MemtoReg = false;
        Branch = false;
    // se for bne
     } else if (instrucao == 11){
       
        RegWrite = false;
        ALUSrc = false;
        ALUOp0 = true;
        ALUOp1 = false;
        MemRead = false;
        MemWrite = true;
     // se for j, jr ou jal 
     } else {
       cout << "Instrução ainda não implementada" << endl;
     }

    }



    bool getRegWrite(){
      return RegWrite;
    }

    void setRegWrite(bool RegWrite){
      this->RegWrite = RegWrite;
    }
    
    bool getRegDst(){
      return RegDst;
    }

    void setRegDst(bool RegDst){
      this->RegDst = RegDst;
    }

    bool getALUSrc(){
      return ALUSrc;
    }

    void setALUSrc(bool ALUSrc){
      this->ALUSrc = ALUSrc;
    }

    bool getALUOp0(){
      return ALUOp0;
    }

    void setALUOp0(bool ALUOp0){
      this->ALUOp0 = ALUOp0;
    }
    
    bool getALUOp1(){
      return ALUOp1;
    }

    void setALUOp1(bool ALUOp1){
      this->ALUOp1 = ALUOp1;
    }

    bool getPCSrc(){
      return PCSrc;
    }

    void setPCSrc(bool PCSrc){
      this->PCSrc = PCSrc;
    }

    bool getMemRead(){
      return MemRead;
    }

    void setMemRead(bool MemRead){
      this->MemRead = MemRead;
    }

    bool getMemWrite(){
      return MemWrite;
    }

    void setMemWrite(bool MemWrite){
      this->MemWrite = MemWrite;
    }

    bool getMemtoReg(){
      return MemtoReg;
    }

    void setMemtoReg(bool MemtoReg){
      this->MemtoReg = MemtoReg;
    }

};

#endif // UNIDADEDECONTROLE_H_INCLUDED
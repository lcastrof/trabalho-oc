#ifndef ALU_H_INCLUDED
#define ALU_H_INCLUDED
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

#include "FuncoesAuxiliares.h"

class ALU{
    public:

        // R[rd] = R[rs] + R[rt]
        int add(int entrada1, int entrada2){
            return entrada1 + entrada2;
            //conversões
        }

        // R[rd] = R[rs] - R[rt]
        int sub(int entrada1,int entrada2){
            return entrada1 - entrada2;
        }

        // R[rd] = R[rs] & R[rt]
        int operacaoAND(int entrada1,int entrada2){
            return (entrada1&entrada2);
        }

        // R[rd] = R[rs] | R[rt]
        int operacaoOR(int entrada1,int entrada2){
            return (entrada1||entrada2);
        }

        // R[rd] = (R[rs] < R[rt]) ? 1 : 0
        int setLessThan(int entrada1, int entrada2){
            return entrada1 < entrada2 ? 1 : 0;
        }

        // R[rd] = R[rt]<<shamt
        int shiftLeftLogical(int entrada1, int entrada2){
            return entrada1<<entrada2;
        }

        


    int operacaoALU(int entrada1, int entrada2, ElementosInstrucao el){
        switch(el.desc){
            case 1: return add(entrada1, entrada2);// "add";
            case 2: return sub(entrada1, entrada2);// "sub";
            case 3: return operacaoAND(entrada1, entrada2);//  "and";
            case 4: return operacaoOR(entrada1, entrada2); //  "or";
            case 5: return setLessThan(entrada1, entrada2); //  "slt";
            case 6: return shiftLeftLogical(entrada1, el.shamt);//  "sll";
            case 7: return add(entrada1, entrada2);// "addi";
            case 8: return add(entrada1, entrada2);//  "lw";
            case 9: return add(entrada1, entrada2);// "sw";
            case 10: return sub(entrada1, entrada2);//  "beq";
            case 11: return add(entrada1, entrada2);//  "bne";
            case 12: return 0;//  "j";
            case 13: return 0;//  "jr";
            case 14: return 0;// "jal";
            default: 
                cout << "Operação Desconhecida" << endl;
                return 0;
            
        }
    }


};


#endif // ALU_H_INCLUDED
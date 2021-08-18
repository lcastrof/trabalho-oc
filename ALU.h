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
        int add(int entrada1,int entrada2){
            return entrada1 + entrada2;
        }

        // R[rd] = R[rs] - R[rt]
        int sub(int entrada1,int entrada2){
            return entrada1 - entrada2;
        }

        // R[rd] = R[rs] & R[rt]
        int operacaoAND(int entrada1,int entrada2){
            return (entrada1 && entrada2);
        }

        // R[rd] = R[rs] | R[rt]
        int operacaoOR(int entrada1,int entrada2){
            return (entrada1 || entrada2);
        }

        // R[rd] = (R[rs] < R[rt]) ? 1 : 0
        int setLessThan(int entrada1, int entrada2){
            return entrada1 < entrada2 ? 1 : 0;
        }

};


#endif // ALU_H_INCLUDED
#ifndef BANCODEREGISTRADORES_H_INCLUDED
#define BANCODEREGISTRADORES_H_INCLUDED

#include <iostream>
#include <cstdlib>

using namespace std;

class BancoDeRegistradores {
  private:
    int *registradores;

  public:
    BancoDeRegistradores() {
      registradores = new int[32];
      for(int i = 0; i < 32; i++){
        registradores[i] = 0;
      }
    };

    void imprimeRegistradores() {
      for (int i = 0; i < 32; i++) {
        cout << "  |  " <<"R[" << i << "] = " << registradores[i];

        if(i%4 == 0){
          cout << endl;
        }
      }
    };
    
    int leBanco(int reg1, int reg2, int *rd1, int *rd2) {
      if (reg1 < 0 || reg1 >= 32) return 0;

      *rd1 = registradores[reg1];
      *rd2 = registradores[reg2];
      return 1;
    };

    int escreveBanco(int wReg, int wData, int regWrite) {
      if (wReg == 0 || regWrite == 0) return 0;
      registradores[wReg] = wData;
      return 1;
    };
};

#endif // BANCODEREGISTRADORES_H_INCLUDED
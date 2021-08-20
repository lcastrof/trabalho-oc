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
      registradores[0] = 0;
    };

    void imprimeRegistradores() {
      for (int i = 0; i < 32; i++) {
        cout << "I[" << i << "] = " << registradores[i] << endl;
      }
    };
    // Basicamente o que ele explicou na aula, deve mudar mais pra frente
    int leBanco(int reg1, int reg2, int *rd1, int *rd2) {
      if (reg1 < 0 || reg1 >= 32) return 0;

      *rd1 = registradores[reg1];
      *rd2 = registradores[reg2];
      return 1;
    };

    int escreveBanco(int wReg, int wData, int regWrite) {
      if (wReg == 0 || (regWrite && !wReg)) return 0;
      registradores[wReg] = wData;
      return 1;
    };
};

#endif // BANCODEREGISTRADORES_H_INCLUDED
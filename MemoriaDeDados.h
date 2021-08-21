#ifndef MEMORIADEDADOS_H_INCLUDED
#define MEMORIADEDADOS_H_INCLUDED

#include <iostream>
#include <cstdlib>

using namespace std;

class MemoriaDeDados {
  private:
    int *memoria;

  public:
    MemoriaDeDados() {
      memoria = new int[128];
    };

    int operaDados(int address, int writeData, bool memWrite, bool memRead) {
      


      if (!memWrite && !memRead) return 0;

      int indice = address;
      if (memWrite) {
        memoria[indice] = writeData;

        return 1;
      }

      return memoria[indice];
    };
};

#endif // MEMORIADEDADOS_H_INCLUDED
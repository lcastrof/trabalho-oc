#ifndef MEMORIADEINSTRUCOES_H_INCLUDED
#define MEMORIADEINSTRUCOES_H_INCLUDED

#include <iostream>
#include <cstdlib>

using namespace std;

class MemoriaDeInstrucoes {
  private:
    long long int *instrucoes;
    

  public:
    MemoriaDeInstrucoes() {
      instrucoes = new long long int[128];
    };

    void imprimeNInstrucoes(int quantidade) {
      for (int i = 0; i < quantidade; i++) {
        cout << "I[" << i << "] = " << instrucoes[i] << endl;
      }
    };

    long long int getInstrucao(int end_memoria) {
      int end_convertido = end_memoria / 4;
      return instrucoes[end_convertido];
    };

    void insereInstrucao(int indice, long long int valor) {
      if (valor >= 0) {
        instrucoes[indice] = valor;
      } else {
        cout << "Tentativa de inserir uma instrucao negativa" << endl;
      }
    };
};

#endif // MEMORIADEINSTRUCOES_H_INCLUDED
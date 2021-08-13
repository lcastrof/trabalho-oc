#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

long long int converteBinarioParaInteiro(string strBin) {
  return stoll(strBin, 0, 2);
}

int main()
{
  // onde serão armazenadas as sequências de instruções
  long long int memoria_instrucoes[128];

  // leitura do arquivo
  ifstream arquivo;
  arquivo.open("comandos.txt");

  if (arquivo.is_open()) {
    string str;
    int count = 0;
    while(getline(arquivo, str)) {
      long long int valor_convertido = converteBinarioParaInteiro(str);
      memoria_instrucoes[count] = valor_convertido;
      count += 1;
    }
    arquivo.close();

    // inicializa PC como 0 (lembrar de multiplicar/dividir por 4 para acessar corretamente as informações)
    int PC = 0;

    cout << "memoria " <<  memoria_instrucoes[PC] << endl;
    // exemplos de máscaras para obter os campos necessários
    
    // opcode (como sempre são os primeiros 6 bits, não é necessário uma máscara para recuperá-lo)
    int opcode = (memoria_instrucoes[PC]>>26);
    cout << "opcode " << opcode << endl;

    // rs
    string mascara_rs = "00000011111000000000000000000000";
    int rs = (memoria_instrucoes[PC]&converteBinarioParaInteiro(mascara_rs))>>21;
    cout << "rs " << rs << endl;

    // rt
    string mascara_rt = "00000000000111110000000000000000";
    int rt = (memoria_instrucoes[PC]&converteBinarioParaInteiro(mascara_rt))>>16;
    cout << "rt " << rt << endl;

    if (opcode == 0) { // instrução tipo R
      string mascara_rd = "00000000000000001111100000000000";
      int rd = (memoria_instrucoes[PC]&converteBinarioParaInteiro(mascara_rd))>>11;
      cout << "rd " << rd << endl;
      
      string mascara_shamt = "00000000000000000000011111000000";
      int shamt = (memoria_instrucoes[PC]&converteBinarioParaInteiro(mascara_shamt))>>6;
      cout << "shamt " << shamt << endl;

      string mascara_funct = "00000000000000000000000000111111";
      int funct = (memoria_instrucoes[PC]&converteBinarioParaInteiro(mascara_funct));
      cout << "funct " << funct << endl;
    } else if (opcode == 2) { // instrução tipo J
      string mascara_jump_address = "00000011111111111111111111111111";
      int jump_address = (memoria_instrucoes[PC]&converteBinarioParaInteiro(mascara_jump_address));
      cout << "jump_address " << jump_address << endl;
    } else { // instrução tipo I
      string mascara_address = "00000000000000001111111111111111";
      int address = (memoria_instrucoes[PC]&converteBinarioParaInteiro(mascara_address));
      cout << "address " << address << endl;
    }
  }
}
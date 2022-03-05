#include <iostream>
#include <string>
#include <vector>

using namespace std;

class RC4
{
private:
    int S[256]; // vector de estados
    int k[256];
    int texto_size;
    int *texto;

public:
    void set_vector_estados();
    void swap(int x, int y);
    void KSA();  // key scheduling algorithm
    void PRGA(); // generación de secuencia cifrante
    void set_clave();
    void comprobacion();
    void set_mensaje();
    void set_size_text(int number) { texto = new int[number]; }
    string to_binary(int n);
};

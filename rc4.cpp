/**
 * @file rc4.cpp
 * @author Stephanie Arismendi Escobar (alu0101351728)
 * @brief
 * @version 0.1
 * @date 2022-03-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "rc4.hpp"

int main()
{
    RC4 obj;
    cout << "                                                                                       " << endl;
    cout << " /$$$$$$$  /$$$$$$ /$$   /$$        /$$$$$$ /$$$$$$/$$$$$$$ /$$   /$$/$$$$$$$$/$$$$$$$ " << endl;
    cout << "| $$__  $$/$$__  $| $$  | $$       /$$__  $|_  $$_| $$__  $| $$  | $| $$_____| $$__  $$" << endl;
    cout << "| $$  \ $| $$  \__| $$  | $$      | $$  \__/ | $$ | $$  \ $| $$  | $| $$     | $$  \ $$" << endl;
    cout << "| $$$$$$$| $$     | $$$$$$$$      | $$       | $$ | $$$$$$$| $$$$$$$| $$$$$  | $$$$$$$/" << endl;
    cout << "| $$__  $| $$     |_____  $$      | $$       | $$ | $$____/| $$__  $| $$__/  | $$__  $$" << endl;
    cout << "| $$  \ $| $$    $$     | $$      | $$    $$ | $$ | $$     | $$  | $| $$     | $$  \ $$" << endl;
    cout << "| $$  | $|  $$$$$$/     | $$      |  $$$$$$//$$$$$| $$     | $$  | $| $$$$$$$| $$  | $$" << endl;
    cout << "|__/  |__/\______/      |__/       \______/|______|__/     |__/  |__|________|__/  |__/" << endl;
    cout << "                                                                                       " << endl;
    cout << "                                     : alu0101351728                                   " << endl;
    cout << endl;
    obj.set_mensaje();
    obj.KSA();
    obj.PRGA();
}

/**
 * @brief se crea el vector de estados con números decimales del 0 al 255
 * 
 */
void RC4::set_vector_estados()
{
    for (int i = 0; i < 256; i++)
    {
        S[i] = i;
    }
}

/**
 * @brief función genérica para intercambiar los valores de S[i] y S[j] siempre que sea necesario
 * 
 * @param i 
 * @param j 
 */
void RC4::swap(int i, int j)
{
    int aux = 0;
    aux = S[i];
    S[i] = S[j];
    S[j] = aux;
}

/**
 * @brief se pide por pantalla el número de semillas a usar, y cuáles.
 * 
 */
void RC4::set_clave()
{
    int aux, nsemillas;
    cout << "¿Cuántas semillas quieres usar? : ";
    cin >> nsemillas;
    int Semilla[nsemillas];
    for (int i = 0; i < nsemillas; i++)
    {
        cout << "Introduzca la semilla número " << i + 1 << " : ";
        cin >> aux;
        Semilla[i] = aux;
    }
    for (int i = 0; i < 256; i++)
    {
        k[i] = Semilla[i % nsemillas];
    }
}

/**
 * @brief Key Scheduling Algorithm. Se pide por pantalla el número de semillas y cuáles se quiere usar, además de inicializarse el vector de estados.
 * 
 */
void RC4::KSA()
{
    set_vector_estados();
    set_clave();
    cout << "\nComenzando inicialización. . ." << endl;
    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        // cout << "S[" << i << "]= " << S[i] << " K[" << i << "]= " << k[i];
        j = (j + S[i] + k[i]) % 256;
        swap(i, j);
        // cout << " produce f= " << j << " y S[" << i << "]= " << S[i] << " y S[" << j << "]= " << S[j] << endl;
    }
    // comprobacion();
}

/**
 * @brief pide por pantalla el tamaño del mensaje, además de pedir que se introduzcan sus digitos uno a uno. 
 * Se hace un resize al array de texto por medio de la función set_size_text
 * 
 */
void RC4::set_mensaje()
{
    int aux = 0;
    cout << "¿Cuántos digitos tendrá su mensaje? : ";
    cin >> texto_size;
    set_size_text(texto_size);
    for (int i = 0; i < texto_size; i++)
    {
        cout << "Introduzca el digito " << i + 1 << " de su mensaje: ";
        cin >> aux;
        texto[i] = aux;
    }
}

/**
 * @brief Pseudo-Random Generation Algorithm. Cifra el mensaje y devuelve el resultado en decimal o binario.
 * Formato igual al del guion de la práctica.
 * 
 */
void RC4::PRGA()
{
    int i = 0, j = 0, t = 0, k = 0;
    cout << endl;
    cout << "GENERACIÓN DE SECUENCIA CIFRANTE Y TEXTO CIFRADO." << endl;
    cout << endl;
    for (k = 0; k < texto_size; k++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(i, j);
        t = (S[i] + S[j]) % 256;
        cout << "Byte " << k + 1 << " de secuencia cifrante: Salida= S[" << t << "]= " << S[t] << endl;
        cout << "En binario: " << to_binary(S[t]) << endl;
        cout << "Byte " << k + 1 << " de texto original: Entrada= M[" << k + 1 << "]= " << texto[k] << endl;
        cout << "En binario: " << to_binary(texto[k]) << endl;
        texto[k] ^= S[t];
        cout << "Byte " << k + 1 << " de texto cifrado, Salida= C[" << k + 1 << "]= " << texto[k] << endl;
        cout << "En binario: " << to_binary(texto[k]) << endl;
        cout << endl;
        // cout << "XOR: " << to_binary(texto[k]) << endl;
    }
}

/**
 * @brief función que transforma un int en una cadena en binario. no toma en cuenta los ceros de la izquierda.
 * 
 * @param n 
 * @return string 
 */
string RC4::to_binary(int n)
{

    std::string r;
    while (n != 0)
    {
        r = (n % 2 == 0 ? "0" : "1") + r;
        n /= 2;
    }
    return r;
}

/**
 * @brief función que retorna los arrays con el mismo formato que el guión de la práctica. Usada para verificar el
 * correcto funcionamiento del KSA.
 *
 */
void RC4::comprobacion()
{
    for (int i = 0; i < 256; i++)
    {
        if (i == 0)
        {
            cout << "S= [" << S[i] << ", ";
        }
        else if (i == 255)
        {
            cout << S[i] << "]" << endl;
        }
        else
        {
            cout << S[i] << ", ";
        }
    }
}
#include <iostream>

using namespace std;

/*
Un espacio de nombres es una colección de nombres o
identificadores que se definen juntos. Un programa 
que contiene esta línea podrá acceder a todas las
funciones e identificadores declarados en la biblioteca estándar.
*/


int main(){
    cout <<"Vamos a estudiar el Manejo de Memoria en C++" << endl;

    int i;
    int* bloque = new int[10];
    for (i = 0; i < 10; i++)
    {
        bloque[i] = i*i*i;
    }

    for (i = 0; i < 15; i++)
    {
        cout << bloque[i] << ", ";
    }
    cout << endl;

    //  0, 1, 8, 27, 64, 125, 216, 343, 512, 729, 60705, 0, 0, 0, 0,
    
    /*
    int* block;
    for (i = 0; i < 15; i++)
    {
        cout << block[i] << ", ";
    }

    Este código causa un Segmentation fault ó Violación de acceso, que es un 
    intento fallido de acceso a información, esto porque no hemos pedido memoria

    */

    int* block = new int[1];
    for (i = 0; i < 15; i++)
    {
        cout << block[i] << ", ";
    }
    cout << endl;
    // 0, 0, 0, 0, 0, 0, 60673, 0, 0, 0, 0, 0, 0, 0, 0

    /*
    el operador 'new' asigna un bloque de memoria cuyo tamaño
    es del tipo de dato al que se aplica. El dato u objeto 
    puede ser un int, un float, una estructura, un array o
    cualquier otro tipo de dato. El operador new devuelve un
    apuntador, que es la dirección del bloque asignado de memoria.
    */

   delete bloque;

    for (i = 0; i < 15; i++)
    {
        cout << bloque[i] << ", ";
    }
    cout << endl;
    //0, 0, 1823682576, 21935, 64, 125, 216, 343, 512, 729, 33, 0, 0, 0, 0,

    /*
    La acción de delete elimina la memoria a la cual apunta 'bloque' pero no borra el apuntador 'bloque' que se
    puede seguir utilizando.
    Es importante que exista siempre una correspondencia new-delete NO se puede usar delete
    para liberar memoria creada por declaración de variables ordinarias.
    */

   bloque = new int;
   *bloque = 5;
   cout << *bloque << endl;

   for (i = 0; i < 15; i++)
    {
        cout << bloque[i] << ", ";
    }
    cout << endl;

    /*
    5
    5, 0, 0, 0, 0, 0, 60641, 0, 0, 0, 0, 0, 0, 0, 0,
    */



}

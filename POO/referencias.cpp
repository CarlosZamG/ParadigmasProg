#include <iostream>

using namespace std;

/*
Programa para entender las referencias en C++


comando para compilar:      g++ referencias.cpp -o referencias
comando para ejecutar:      ./referencias

    Referencia: Es una atadura a un objeto o una variable
    Se dice que es un tipo compuesto porque se define en términsos de otro tipo
    Se define de la siguiente manera:
        
        tipo_v_o& referncia = var_obj

    dónde:
    - tipo_v_o es el tipo de la variable u objeto a la que hace referencia
    - var_obj es el objeto o variable a la que se le está ligando la referencia.



*/


//Las referncias son útiles para pasar parámetros
//Visitar: https://1.bp.blogspot.com/-CQbZXPaIQEE/XEs2pGPuwgI/AAAAAAAA81Y/bzI2E-yPTgw7StM8F2XsEWabqtbza12ZwCLcBGAs/s1600/s_C7912688E88BFAE5A561B8B4DE886E409DF5757778FCB5013C93CC42DC0B0EEA_1487999359969_pass-by-reference-vs-pass-by-value-animation.gif

/*
La función intercambio SÍ funciona correctamente, porque lo que yo 
le haga a mi referencia dentro de la función, se lo estoy haciendo al 
objeto o  a la varible

*/

void intercambio(int& num1, int& num2){

    int temporal = num1;
    num1 = num2;
    num2 = temporal;


}

/*
La función intercambio_por_valor NO funciona correctamente,
debido a que estoy pasando los parámetros por valor, entonces num1 y num2 
son variables nuevas que solo existen dentro de la función y se les asigna
el VALOR, es decir, una copia del objeto o variable 

*/
void intercambio_por_valor(int num1, int num2){

    int temporal = num1;
    num1 = num2;
    num2 = temporal;


}

//Así es como se hace en el viejo C
void intercambio_punteros(int* num1, int* num2){

    int temporal = *num1;
    *num1 = *num2;
    *num2 = temporal;


}

int main(){
    
    int var = 5;
    int& ref2var = var;
    int var2var = var;

    //int& ref; Marca un error diciendo que la referncia no está inicializada
    //int& ref=4; Marca error porque la referencia debe ser inicializada con una variable u objeto

    cout << "El valor de var es:" << var << endl;
    cout << "El valor de ref2var es:" << ref2var << endl;
    cout << "El valor de var2var es:" << var2var << endl << endl;

    ref2var = 30;
    var = var + 5;
    
    cout << "El valor de var es:" << var << endl;
    cout << "El valor de ref2var es:" << ref2var << endl;
    cout << "El valor de var2var es:" << var2var << endl << endl;
    /*
    El valor de var es:5
    El valor de ref2var es:5
    El valor de var2var es:5

    El valor de var es:35
    El valor de ref2var es:35
    El valor de var2var es:5

    Lo que yo le haga a var afecta a ref2var y viceversa
    var2var no se ve afectada porque es una variable que se inicializa con el valor de var, pero es independiente
    
    */
    int a = 50;
    int b = 100;
    cout << "El valor de a es:" << a << endl;
    cout << "El valor de b es:" << b << endl;
    cout << "Intercambiando ... " << endl;
    intercambio(a,b);
    //intercambio(3,4); Marca error porque espera una referencia, NO valores enteros
    cout << "El valor de a es:" << a << endl;
    cout << "El valor de b es:" << b << endl << endl;

    /*
    El valor de a es:50
    El valor de b es:100
    Intercambiando ...
    El valor de a es:100
    El valor de b es:50

    Sí intercambia los valores
    */

    cout << "El valor de a es:" << a << endl;
    cout << "El valor de b es:" << b << endl;
    cout << "Intercambiando ... " << endl;
    intercambio_por_valor(a,b);     //NO hace el intercambio
    intercambio_por_valor(3,4);     //Sí compila porque estoy pasando por valor, pero no hace el intercambio
    cout << "El valor de a es:" << a << endl;
    cout << "El valor de b es:" << b << endl<< endl;

    /*
    El valor de a es:100
    El valor de b es:50
    Intercambiando ...
    El valor de a es:100
    El valor de b es:50
    */


    cout << "El valor de a es:" << a << endl;
    cout << "El valor de b es:" << b << endl;
    cout << "Intercambiando ... " << endl;
    //intercambio_punteros(a,b); NO funciona porque se está pasando por dirección, no recibe variables, recibe direcciones
    //intercambio_punteros(3,4); NO funciona porque se está pasando por dirección, no recibe valores, recibe direcciones
    intercambio_punteros(&a,&b);    //Sí funciona
    cout << "El valor de a es:" << a << endl;
    cout << "El valor de b es:" << b << endl << endl;



}

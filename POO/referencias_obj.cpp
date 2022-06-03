#include <iostream>

using namespace std;

/*
Programa para entender las referencias con objetos en C++


comando para compilar:  g++ referencias_obj.cpp -o referencias_obj
comando para ejecutar:  ./referencias_obj   

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


class entero
{
private:
    int numero;
public:
    entero(int numero){ this->numero=numero;}
    int get_numero(){return numero;}
    void set_numero(int numero){this->numero=numero;}


    friend ostream& operator<<(ostream& flujo, entero num){

        return flujo << num.numero;

    }

    
};

/*
La función intercambio SÍ funciona correctamente, porque lo que yo 
le haga a mi referencia dentro de la función, se lo estoy haciendo al 
objeto o  a la varible

*/


void intercambio(entero& num1, entero& num2){

    /*
    int temporal = num1;
    num1 = num2;
    num2 = temporal;
    */

   entero* temporal = new entero(num1.get_numero());
   num1.set_numero(num2.get_numero());
   num2.set_numero(temporal->get_numero()); 

}


//Así es como se hace en el viejo C
void intercambio_punteros(entero* num1, entero* num2){


    entero* temporal = new entero(num1->get_numero());
    num1->set_numero(num2->get_numero());
    num2->set_numero(temporal->get_numero());

}

int main(){
    /*
    int var = 5;
    int& ref2var = var;
    int var2var = var;
    */
    entero var(7);
    entero& ref2var = var;
    entero var2var = var;

    cout << "El valor de var es:" << var << endl;
    cout << "El valor de ref2var es:" << ref2var << endl;
    cout << "El valor de var2var es:" << var2var << endl << endl;
   
    //entero& ref; Marca un error diciendo que la referncia no está inicializada
    //entero& ref(4); Marca error
    //entero& ref = new entero(10); Marca error
    entero& ref = *new entero(10); //Sí compila
    

    //ref2var = 30;
    //var = var + 5;
    ref2var.set_numero(30);
    var.set_numero(var.get_numero()+5);

    
    cout << "El valor de var es:" << var << endl;
    cout << "El valor de ref2var es:" << ref2var << endl;
    cout << "El valor de var2var es:" << var2var << endl << endl;
    /*
    El valor de var es:7
    El valor de ref2var es:7
    El valor de var2var es:7

    El valor de var es:35
    El valor de ref2var es:35
    El valor de var2var es:7

    Lo que yo le haga a var afecta a ref2var y viceversa
    var2var no se ve afectada porque es una variable que se inicializa con el valor de var, pero es independiente
    
    */


   /*
    int a = 50;
    int b = 100;*/
    entero a(100);
    entero b(50); 
    
    
    
    cout << "El valor de a es:" << a << endl;
    cout << "El valor de b es:" << b << endl;
    cout << "Intercambiando ... " << endl;
    intercambio(a,b);
    //intercambio(3,4); Marca error porque espera una variable u objeto, NO valores enteros
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
    cout << "Intercambiando ... de nuevo " << endl;
    intercambio_punteros(&a,&b);
    //intercambio(3,4); Marca error porque espera una variable u objeto, NO valores enteros
    cout << "El valor de a es:" << a << endl;
    cout << "El valor de b es:" << b << endl << endl;

    /*
    El valor de a es:50
    El valor de b es:100
    Intercambiando ... de nuevo
    El valor de a es:100
    El valor de b es:50
    */



}

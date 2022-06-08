#include <iostream>
#include <stdexcept>

using namespace std;

class fraccion{

    int numerador, denominador;
    

    public:
        fraccion(int numerador, int denominador);
        fraccion(int num);
        void simplificar(); 
        int mcd();

    friend ostream& operator <<(ostream& flujo, fraccion frac);
    friend fraccion operator+(fraccion f1, fraccion f2);
    friend fraccion operator+(int z, fraccion f2);
    friend fraccion operator+(fraccion f1, int z);
    friend fraccion operator-(fraccion f1);
    friend fraccion operator-(fraccion f1,fraccion f2);
    //friend fraccion operator-(fraccion f1);
};

    /*
    Formas de crear una fracción con el programa:
    
        fraccion frac(2,3);         Crea la fracción 2/3
        fraccion frac2(10,15);      También crea la fracción 2/3 debido a que hace la simplificación


        - con punteros:
        fraccion* pfrac = new fraccion(1,3);    Crea la fraccion 1/3 con punteros

        -con referencias:
        fraccion& rfrac = *new fraccion(3,9);   Crea la fraccion 1/3 con referncias

    -Entero: se puede crear una fracción a partir de un número entero

        fraccion cinco(5);      Crea la fracción 5/1
        fraccion veinte(20);    Crea la fracción 20/1
    

    -Negativos: 
    
    fraccion f1(-25,45);    Crea la fracción -5/9
    fraccion f2(25,-45);    Crea la fracción -5/9 (Pasa el negativo al numerador)

    fraccion f3(-25,-35);   Crea la fracción 5/7 debido a que simplifica

    -Fracción 0
    Si el usuario introduce un cero en el numerador, creará la fracción 0/1

    fraccion cero1(0,5);
    fraccion cero2(0,1);
    fraccion cero3(0,12);

    Tanto cero1, cero2, como cero3 tienen 0 en su numerador y 1 en el denominador
    son la fracción 0/1 

    -Denominador 0
    Se generará un error al intentar crear una fracción con denominador 0
    
    fraccion error(23,0);

    Salida:

    terminate called after throwing an instance of 'std::runtime_error'
        what():  ERROR MATEMÁTICO: NO SE PUEDE DIVIDIR ENTRE CERO

    Aborted


    */

fraccion::fraccion(int numerador, int denominador){
            
    if (denominador == 0) {
        throw runtime_error("ERROR MATEMÁTICO: NO SE PUEDE DIVIDIR ENTRE CERO\n");
    }else if (numerador == 0){
        this->numerador = numerador;
        this->denominador = 1;
    }else if (denominador<0){
        this->numerador = -numerador;
        this->denominador = -denominador;
        simplificar();
    }else{
        this->numerador = numerador;
        this->denominador = denominador;
        simplificar();    
    }
            
}


fraccion::fraccion(int num){
    *this = *new fraccion(num,1);
}

/*
Calcula el máximo común divisor entre el numerador y el donominador para simplificar la fracción.
Utiliza el Algoritmo de Euclides
*/
int fraccion::mcd(){ 

    int a = abs(this->numerador);
    int b = abs(this->denominador);
    int r=1;

    while (b != 0)
    {
        r = a % b;
        a = b;
        b = r;
    }
    
    return a;

}


/*
Simplifica la función dividiendo al numerador y al denominador por su mcd y asignando 
los resultados como los nuevos valores 
*/
void fraccion::simplificar(){

    int div = mcd();
    numerador = numerador/div;
    denominador = denominador/div;

}

/*
Sobrecargamos el operador '<<' para poder mostrar en consola a la fracción de la forma: numerador/denominador

    fraccion frac(5,4);
    cout <<"La fración es: "<< frac << endl;

    Salida:
    La fración es: 5/4

*/
ostream& operator <<(ostream& flujo, fraccion frac){

    flujo << frac.numerador << "/" << frac.denominador;
    return flujo;

}


/*
Sobrecargamos el operador '+' para poder hacer la suma entre fracciones expresiva

    fraccion f1(6,7);
    fraccion f2(5,4);

    fraccion r = f1 + f2;   El resultado devuelve una fracción

    cout << "El resultado es " << r << endl;

    Salida
    El resultado es 59/28

*/
fraccion operator+(fraccion f1, fraccion f2){
    
    int den = f1.denominador * f2.denominador;
    int num = f1.numerador*f2.denominador +  f2.numerador*f1.denominador;
    fraccion ret = *new fraccion(num,den);
    return ret;

}


/*
También es válida la suma entre fracciones y enteros
    
    fraccion f(4,9);
    fraccion res = f + 5;
    cout << f << " + " << 5 << " = " << res << endl; 

    Salida:
    4/9 + 5 = 49/9

La suma está diseñada para ser conmutativa:

    fraccion res2 = 5 + f;
    cout << 5 << " + " << f << " = " << res << endl;

    Salida:
    5 + 4/9 = 49/9


*/
fraccion operator+(int z, fraccion f){

    fraccion zf = *new fraccion(z);
    return zf + f;    

}

fraccion operator+(fraccion f, int z){

    fraccion zf = *new fraccion(z);
    return zf + f;

}

fraccion operator-(fraccion f1){

    fraccion nf = *new fraccion(-(f1.numerador),f1.denominador);
    return nf;
}

fraccion operator-(fraccion f1,fraccion f2){

    return f1 + (-f2);

}


int main()
{    
    fraccion f(4,9);
    fraccion res2 = 5 + f;
    cout << 5 << " + " << f << " = " << res2 << endl;


    /*
    fraccion& r1 = *new fraccion(45,35);
    fraccion& r2 = *new fraccion(25,35);
    
    //Probamos la salida y la suma de dos fracciones
    cout << r1 <<" + " << r2 << " = " << (r1+r2) << endl;
    
    //Creamos la fracción 0
    fraccion& cero = *new fraccion(0,33);
    cout << cero << endl;

     
    fraccion& z = *new fraccion(5);
    cout <<"Entero: " <<z << endl;
    z = *new fraccion(-3);
    cout <<"Entero negativo: " << z <<endl;

    //Probamos la suma con enteros
    cout << r1 <<" + 5 = "<< (r1 + 5) << endl;
    cout <<"3 +  " << r1 <<" = "<< (3 + r1) << endl;

    //Probamos el operador unario menos(-)
    cout << -r2 << endl;
    fraccion& fracp = *new fraccion(-9,-36);
    cout << "Prueba: "<<fracp << endl; 

    //Probamos el operador binario menos(-)
    cout << r1 <<" - " << r2 << " = " << (r1-r2) << endl;

    //Error al dividir entre 0
    //fraccion& e = *new fraccion(25,0);
    */

}
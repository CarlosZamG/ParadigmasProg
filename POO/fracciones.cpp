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
    friend fraccion operator-(fraccion f1, int z);
    friend fraccion operator-(int z, fraccion f1);
    friend fraccion operator*(fraccion f1, fraccion f2);
    friend fraccion operator*(fraccion f1, int z);
    friend fraccion operator*(int z, fraccion f1);
    friend fraccion operator/(fraccion f1, fraccion f2);
    friend fraccion operator/(fraccion f1, int z);
    friend fraccion operator/(int z, fraccion f1);

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
Se sobrecargó el operador '<<' para poder mostrar en consola a la fracción de la forma: numerador/denominador

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
Se sobrecargó el operador '+' para poder hacer la suma entre fracciones expresiva

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
/*
Se sobrecargó el operador unario '-' para que nos devuelva el inverso aditivo de la fracción

    fraccion f(2,9);
    fraccion f2(-3,4);

    fraccion inv = -f;
    cout << inv << endl;
    inv = - f2;
    cout << inv << endl;


    Salida:
    -2/9
    3/4

    fraccion cero(0,5);
    fraccion inv = -cero;
    cout << inv << endl;

    Salida:
    0/1     

    El inverso de la fracción cero (0/1) es el mismo

*/
fraccion operator-(fraccion f1){

    fraccion nf = *new fraccion(-(f1.numerador),f1.denominador);
    return nf;
}

/*
Se sobrecargó el operador '-' para hacer la resta entre fracciones:

    fraccion f1(4,5);
    fraccion f2(14,15) ;
    fraccion res = f1 - f2;
    cout << f1 << " - (" << f2<<") = " << res << endl;

    Salida: 
    4/5 - (14/15) = -2/15

    
    
    fraccion f(3,5);
    cout << f << " - (" << f<<") = " << f-f << endl;

    Salida:
    3/5 - (3/5) = 0/1

*/

fraccion operator-(fraccion f1,fraccion f2){

    return f1 + (-f2);

}

/*
La resta también es válida para un entero menos una fracción y una fracción menos un entero:

    fraccion f(10,3);
    cout << f << " - (" << 2 <<") = " << f-2 << endl;
    fraccion f2(1,3);
    cout << 5<< " - (" << f2 <<") = " << 5-f2 << endl;


    Salida:
    10/3 - (2) = 4/3
    5 - (1/3) = 14/3

*/
fraccion operator-(fraccion f1, int z){
    
    fraccion zf = *new fraccion(z);
    return f1 - zf;
}


fraccion operator-(int z, fraccion f1){

    fraccion zf = *new fraccion(z);
    return  zf - f1;

}

/*
Se sobrecargó el operador '*' para hacer la multiplicación de fracciones:

    fraccion f1(3,4);
    fraccion f2(6,4);
    cout << f1 << " * " << f2 <<" = " << f1 * f2 << endl;
    
    Salida:
    3/4 * 3/2 = 9/8


    fraccion f1(1,-4);
    fraccion f2(-5,2);
    cout << f1 << " * " << f2 <<" = " << f1 * f2 << endl;

    Salida:
    -1/4 * -5/2 = 5/8

    fraccion f1(1,4);
    fraccion f2(0,8);
    cout << f1 << " * " << f2 <<" = " << f1 * f2 << endl;

    Salida:
    1/4 * 0/1 = 0/1


*/
fraccion operator*(fraccion f1, fraccion f2){

    int num = f1.numerador * f2.numerador;
    int den = f1.denominador * f2.denominador;
    fraccion ret =*new fraccion(num, den);
    return ret;

}

/*
También se puede hacer la multiplicación con enteros:

    fraccion f1(1,5);
    cout << f1 << " * " << 3 <<" = " << f1 * 3 << endl;
    cout << 8 << " * " << f1 <<" = " <<  8 * f1  << endl;
    cout << 0 << " * " << f1 <<" = " <<  0 * f1  << endl;

    Salida:
    1/5 * 3 = 3/5
    8 * 1/5 = 8/5
    0 * 1/5 = 0/1

*/

fraccion operator*(fraccion f1, int z){

    fraccion zf = *new fraccion(z);
    return  zf * f1;

}

fraccion operator*(int z, fraccion f1){

    fraccion zf = *new fraccion(z);
    return  zf * f1;

}

/*
Se sobrecargó el operador '/' para hacer la división entre fracciones:

    fraccion f1(1,5);
    fraccion f2(7,3);
    cout << f1 << " / (" << f2 <<") = " << f1 / f2 << endl;

    Salida:
    1/5 / (7/3) = 3/35

    
    fraccion f1(0,5);
    fraccion f2(2,3);
    cout << f1 << " / (" << f2 <<") = " << f1 / f2 << endl;

    Salida:
    0/1 / (2/3) = 0/1


    fraccion f1(2,5);
    fraccion f2(0,4);
    cout << f1 << " / (" << f2 <<") = " << f1 / f2 << endl;
    
    Salida:
    terminate called after throwing an instance of 'std::runtime_error'
        what():  ERROR MATEMÁTICO: NO SE PUEDE DIVIDIR ENTRE CERO

    Aborted

*/

fraccion operator/(fraccion f1, fraccion f2){

    int num = f1.numerador * f2.denominador;
    int den = f1.denominador * f2.numerador;
    fraccion ret = *new fraccion(num, den);
    return ret;
    


}

/*
También es válida la división entre un entero y una fracción ó una fracción y un entero:

    fraccion f1(2,5);
    cout << f1 << " / " << 2 <<" = " << f1 / 2 << endl;
    cout << 2 << " / " << f1 <<" = " << 2 / f1 << endl;

    Salida: 
    2/5 / 2 = 1/5
    2 / 2/5 = 5/1


    fraccion f1(0,5);
    cout << f1 << " / " << 9 <<" = " << f1 / 9 << endl;

    Salida:
    0/1 / 9 = 0/1

    
    fraccion f1(2,5);
    cout << f1 << " / " << 0 <<" = " << f1 / 0 << endl;

    Salida:
    terminate called after throwing an instance of 'std::runtime_error'
        what():  ERROR MATEMÁTICO: NO SE PUEDE DIVIDIR ENTRE CERO

    Aborted

*/
fraccion operator/(fraccion f1, int z){

    fraccion zf = *new fraccion(z);
    return f1 / zf;

}

fraccion operator/(int z, fraccion f1){

    fraccion zf = *new fraccion(z);
    return  zf / f1;

}

int main()
{    
    fraccion f1(5,7);
    fraccion f2(4,6);
    int ent1 = 2, ent2 = 3; 
    cout << "f1 = " << f1 << ", f2 = " << f2 << endl << endl;
    //f2 ha sido simplificado
    cout << "Suma de fracciones: " << f1 << " + " << f2 << " = " << f1 + f2 <<endl;
    cout << "Suma de fracción y entero: " << f1 << " + " << ent1 << " = " << f1 + ent1 <<endl;
    cout << "Suma de entero y fracción: " << ent2 << " + " << f2 << " = " <<  ent2 + f2 <<endl<<endl; 
    cout << "-f1 = " << -f1;
    cout << ", -f2 = " << -f2 << endl << endl;
    cout << "Resta de fracciones: " << endl << f1 << " - " << f2 << " = " << f1 - f2 <<endl;
    cout << f2 << " - " << f1 << " = " << f2 - f1 <<endl;
    cout << "Resta de fracciones y enteros: " << endl << ent1 << " - " << f2 << " = " << ent1 - f2 <<endl;
    cout << f1 << " - " << ent2 << " = " << f1 - ent2 <<endl<<endl;
    cout << "Multiplicación de fracciones: " << f1 << " * " << f2 << " = " << f1 * f2 <<endl;
    cout << "Multiplicación de fracción y entero: " << f1 << " * " << ent1 << " = " << f1 * ent1 <<endl;
    cout << "Multiplicación de entero y fracción: " << ent2 << " * " << f2 << " = " <<  ent2 * f2 <<endl<<endl;
    cout << "División de fracciones: " << endl << f1 << " / " << f2 << " = " << f1 / f2 <<endl;
    cout << f2 << " / " << f1 << " = " << f2 / f1 <<endl;
    cout << "División de fracciones y enteros: " << endl << ent1 << " / " << f2 << " = " << ent1 / f2 <<endl;
    cout << f1 << " / " << ent2 << " = " << f1 / ent2 <<endl<<endl;

}
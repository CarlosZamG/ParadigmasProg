#include <iostream>
/*
#include <iostream> se denomina directiva del preprocesador 
El preprocesador es una parte de compilador que procesa un archivo fuente antes de que
tenga lugar la compilación. 
La directiva #include es reemplazado por el contenido del archivo indicado.
El tipo de archivo incluido normalmente por #include se denomina archivo de cabecera.

iostream manipula entrada y salida con formatos. La biblioteca iostream tiene dos tipos:
istream y ostream que representan los flujos de entrada y salida. Un flujo (stream) es una 
secuencia de caracteres empleadapara leer de un dispositivo o escribir en un dispositivo

cin => canal de entrada estándar (teclado)
cout => canal de salida estándar (pantalla)


C++ define unos operadores predefinidos que se pueden aplicar a tipos estándar
*/


using namespace std;

class coordenada
{
private:
    int x, y;
public:
    coordenada(){
        x=0;
        y=0;
    }
    coordenada(int x, int y){
        this->x = x;
        this->y = y;
    }
    /*
    Funciones amiga
    En ocasiones una función global (no miembro de una clase) necesita poder
    acceder a los miembros privados de una clase; al ser función externa de
    una clase no puede referirse a los miembros dato privados de la clase. 
    En estos casos, es posible declarar la función amiga (friend) de la clase.
    
    La declaración de la función amiga debe aparecer dentro de la definición de la clase. Aunque
    las funciones amigas se declaran dentro de una clase, no son funciones miembro, por consiguiente no
    están afectadas por la sección pública, privada o protegida en que están declaradas dentro del cuerpo de la
    clase.

    Una función operador debe ser o bien una función miembro no estática o una función no miembro
    que tenga al menos un parámetro cuyo tipo es una clase, referencia a una clase o una clase enumeración,
    o referencia a una enumeración. Esta regla evita cambiar el significado de operadores que operan sobre
    tipos de datos intrínsecos.

    Se nombran como 'operator X', en donde X es el símbolo del operador.
    */
    friend ostream& operator<<(ostream& flujo, coordenada c);
};

ostream& operator<<(ostream& flujo, coordenada c){

    return flujo<< "(" << c.x << "," << c.y <<")";

}




int main(){
    
    coordenada* coord = new coordenada();
    coordenada c1;
    coordenada c2();    
    //Esto lo que hace es declarar una función c2 sin parámetros y devolver un resultado de tipo 'coordenada'
    
    coordenada& ref2c1 = c1;

    

    
    cout << c1 << endl;     // (0,0)
    cout << c2 << endl;     // 1
    cout << coord << endl;  //0x5627acd9deb0
    cout << *coord << endl; //(0,0)
    cout << ref2c1 << endl; //(0,0)
    




}

#include <iostream>

using namespace std;

/*
Se puede definir un ojeto como “cualquier cosa,
real o abstracta, en la que se almacenan datos y
métodos (operaciones) que manipulan los datos”.

Una clase es un molde que contiene la especificación
de los datos que describen un objeto junto con la
descripción de las acciones que un objeto conoce cómo
ha de ejecutar.Estas acciones se conocen como servicios,
métodos o funciones miembro.

El término función miembro se utiliza, específicamente, en C++.

Una clase incluye también todos los datos necesarios
para describir los objetos creados a partir de la clase.
Estos datos se conocen como atributos o variables.


*/
class Objeto
{

    /*
    Visibilidad según los modificadores de acceso:

           Función:  | Miembro de la | Amiga  | Miembro de una |   No    |
    Tipo de miembro: | misma clase   |        | clase derivada | miembro |
    ----------------------------------------------------------------------
    private          |     Sí        |  Sí    |     No         |    No   |   
    ----------------------------------------------------------------------
    protected        |     Sí        |  Sí    |     Sí         |    No   |
    ----------------------------------------------------------------------
    public           |     Sí        |  Sí    |     Sí         |   Sí    |                         
    ----------------------------------------------------------------------



    */

private:
    int atributo;
public:
    Objeto();
    Objeto(int atributo);
    ~Objeto();
    int get_atributo();
};

// operador de resolución de ámbito (::)
Objeto::Objeto(){

    atributo = 0;
    cout << "Estoy en el constructor "<< endl;

}
/*
Un constructor es una función miembro de propósito
específico que se ejecuta automáticamente cuando
se crea un objeto de una clase. Un constructor 
sirve para inicializar los miembros datos de una clase.

    Reglas: 
        - Tiene el mismo nombre de la clase.
        - No devuelve ningún valor (ni siquera void).

*/

Objeto::Objeto(int atributo){
    /*
    this es un puntero que permite a cada objeto
    acceder a su propia dirección, sólo en las funciones
    miembro de instancia (no static)
    
    */ 
    this->atributo = atributo;
    cout << "Estoy en el constructor con parámetros"<< endl;


}

/*
Un destructor es función miembro especial que llama automáticamente
siempre que se destruye un objeto de la clase. El nombre del destructor
es el mismo que el nombre de la clase, precedida con el carácter ~.
*/
Objeto::~Objeto(){

    cout << "Estoy en el destructor, valor: "<< atributo <<endl;

}

int Objeto::get_atributo(){

    return atributo;

}



int main(){ 

    Objeto o1;
    Objeto o2(5);

    Objeto* o3 = new Objeto();
    Objeto* o4 = new Objeto(10);

    Objeto& o5 = *new Objeto();
    Objeto& o6 = *new Objeto(20);

    cout << "El atributo de o1 es: " << o1.get_atributo() << endl;
    cout << "El atributo de o2 es: " << o2.get_atributo() << endl;
    cout << "El atributo de o3 es: " << o3->get_atributo() << endl;
    cout << "El atributo de o4 es: " << o4->get_atributo() << endl;
    cout << "El atributo de o5 es: " << o5.get_atributo() << endl;
    cout << "El atributo de o6 es: " << o6.get_atributo() << endl;

    delete o3;
    delete o4;
    delete &o5;
    delete &o6;

    /*
    Salida:
    Estoy en el constructor
    Estoy en el constructor con parámetros
    Estoy en el constructor
    Estoy en el constructor con parámetros
    Estoy en el constructor
    Estoy en el constructor con parámetros
    El atributo de o1 es: 0
    El atributo de o2 es: 5
    El atributo de o3 es: 0
    El atributo de o4 es: 10
    El atributo de o5 es: 0
    El atributo de o6 es: 20
    Estoy en el destructor, valor: 0    (o3)
    Estoy en el destructor, valor: 10   (o4)
    Estoy en el destructor, valor: 0    (o5)
    Estoy en el destructor, valor: 20   (o6)
    Estoy en el destructor, valor: 5    (o2)
    Estoy en el destructor, valor: 0    (o1)

    
    */



    

}
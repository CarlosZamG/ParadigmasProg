#include <iostream>

using namespace std;

class Cadena
{
private:
    char* cadena;
public:
   Cadena(){
       cadena = "";
   } 
   Cadena(char* cadena){
        this->cadena = cadena;
    }

    char* getCadena(){
        return cadena;
    }

    int size(){

        int i=0;
        for (;; i++)
        {
            if(cadena[i]=='\0'){
                break;
            }
        }
        return i;
    }
};




int main(){
    
    Cadena cad("Hola");
    cout << cad.getCadena() << " Tam Cadean " << cad.size() <<endl;
    
}



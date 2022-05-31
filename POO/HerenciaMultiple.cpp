#include <iostream>

using namespace std;

class Bisabuelo1{
    public:
    Bisabuelo1(){
        cout << "Creando al bisabuelo 1" << endl;
    }

};

class Bisabuelo2{
    public:
    Bisabuelo2(){
        cout << "Creando al bisabuelo 2" << endl;
    }

};

class Bisabuelo3{
    public:
    Bisabuelo3(){
        cout << "Creando al bisabuelo 3" << endl;
    }

};

class Bisabuelo4{
    public:
    Bisabuelo4(){
        cout << "Creando al bisabuelo 4" << endl;
    }

};

class Bisabuelo5{
    public:
    Bisabuelo5(){
        cout << "Creando al bisabuelo 5" << endl;
    }

};

class Bisabuelo6{
    public:
    Bisabuelo6(){
        cout << "Creando al bisabuelo 6" << endl;
    }

};

class Bisabuelo7{
    public:
    Bisabuelo7(){
        cout << "Creando al bisabuelo 7" << endl;
    }

};

class Bisabuelo8{
    public:
    Bisabuelo8(){
        cout << "Creando al bisabuelo 8" << endl;
    }

};

class Abuelo1 : public Bisabuelo1, public Bisabuelo2{
    public:
    Abuelo1(){
        cout << "Creando al abuelo 1" << endl;
    }
};

class Abuelo2 : public Bisabuelo3, public Bisabuelo4{
    public:
    Abuelo2(){
        cout << "Creando al abuelo 2" << endl;
    }
};


class Abuelo3 : public Bisabuelo5, public Bisabuelo6{
    public:
    Abuelo3(){
        cout << "Creando al abuelo 3" << endl;
    }
};

class Abuelo4: public Bisabuelo7, public Bisabuelo8 {
    public:
    Abuelo4(){
        cout << "Creando al abuelo 4" << endl;
    }
};

class Padre1 : public Abuelo1, public Abuelo2{
    public:
    Padre1(){
        cout << "Creando al padre 1" << endl;
    }
};

class Padre2 : public Abuelo3, public Abuelo4{
    public:
    Padre2(){
        cout << "Creando al padre 2" << endl;
    }
};

class Hijo : public Padre1, public Padre2{
    public:
    Hijo(){
        cout << "Creando al hijo" << endl;
    }
};

int main(){
    Hijo hijo;
}

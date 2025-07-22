#include <iostream>
#include "estudiante.cpp"
using namespace std;

int main(){
    Estudiante me(1234567891, "Me R H", 21, Genero::Femenino, "a", "b", "c");
    cout<< "ID: " << me.get_id();
    ofstream archivo("estudiantes.txt", ios::app);
    if (archivo.is_open()) {
        me.guardar_estudiante_en_archivo(archivo, me);
        archivo.close();
    }
    ifstream estudiantes("estudiantes.txt", ios::app);
    bool existe= me.existe_id(123589976, estudiantes);
    cout<<"exist";
    cout <<existe;

    return 0;
}
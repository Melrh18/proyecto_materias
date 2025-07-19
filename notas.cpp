// Clase notas 
#include <iostream>
#include <string>
#include <tuple>
using namespace std; 

class Notas{
    private: 
    int id; 
    string materia;
    tuple<int, int, int, int, int> nota;
    string estado; 

    public:
    Notas(int _id = 0,string _materia = "", int proyecto1 = 0, int proyecto2 = 0, int ensayo = 0, int foro = 0, int defensa = 0, string _estado= 0 ){
        id= _id;
        materia = _materia; 
        nota = make_tuple(proyecto1, proyecto2, ensayo, foro, defensa);
        estado = _estado;
    }

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Getters and Setters 
    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    int get_id() const {
        return id; 
    }

};
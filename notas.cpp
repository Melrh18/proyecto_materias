// Clase notas
#include <iostream>
#include <string>
#include <tuple>
#include <fstream>    //manejo de archivos
#include <stdexcept>  //manejo de exepciones
#include <filesystem> //a partir de c++ 17
using namespace std;
namespace fs = filesystem;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Creacion de Archivo
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ofstream archivo_notas("notas.txt", ios::app);

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Nota
{
private:
  int id;
  string materia;
  float proyecto1;
  float proyecto2;
  float ensayo;
  float foro;
  float defensa;

public:
  Nota(int _id = 0, string _materia = "", float _proyecto1 = 0, float _proyecto2 = 0, float _ensayo = 0, float _foro = 0, float _defensa = 0)
  {
    id = _id;
    materia = _materia;
    proyecto1 = _proyecto1;
    proyecto2 = _proyecto2;
    ensayo = _ensayo;
    foro = _foro;
    defensa = _defensa;
  }

  //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Getters and Setters
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  int get_id() const
  {
    return id;
  }

  string get_materia() const
  {
    return materia;
  }

  float get_proyecto1() const
  {
    return proyecto1;
  }

  float get_proyecto2() const
  {
    return proyecto2;
  }

  float get_ensayo() const
  {
    return ensayo;
  }

  float get_foro() const
  {
    return foro;
  }

  float get_defensa() const
  {
    return defensa;
  }

  void set_id(int _id)
  {
    id = _id;
  }

  void set_materia(string _materia)
  {
    materia = _materia;
  }

  void set_proyecto1(float _proyecto1)
  {
    if (proyecto1 < 0 || proyecto1 > 10)
    {
      throw invalid_argument("La nota debe estar en base 10");
    }
    proyecto1 = _proyecto1;
  }

  void set_proyecto2(float _proyecto2)
  {
    if (proyecto2 < 0 || proyecto2 > 10)
    {
      throw invalid_argument("La nota debe estar en base 10");
    }
    proyecto2 = _proyecto2;
  }

  void set_ensayo(float _ensayo)
  {
    if (proyecto1 < 0 || proyecto2 > 10)
    {
      throw invalid_argument("La nota debe estar en base 10");
    }
    ensayo = _ensayo;
  }

  void set_foro(float _foro)
  {
    if (proyecto1 < 0 || proyecto2 > 10)
    {
      throw invalid_argument("La nota debe estar en base 10");
    }
    foro = _foro;
  }

  void set_defensa(float _defensa)
  {
    if (proyecto1 < 0 || proyecto2 > 10)
    {
      throw invalid_argument("La nota debe estar en base 10");
    }
    defensa = _defensa;
  }

  float calcular_promedio()
  {
    float p1 = 0.1 * proyecto1;
    float p2 = 0.2 * proyecto2;
    float cal_ens = 0.3 * ensayo;
    float cal_fo = 0.1 * foro;
    float def = 0.3 * defensa;
    return p1 + p2 + cal_ens + cal_fo + def;
  }

  string estado()
  {
    float promedio = calcular_promedio();
    if (promedio < 5)
    {
      return "Reprobo";
    }

    if (promedio >= 5 && promedio < 7)
    {
      return "Reposición";
    }
    return "Aprobo";
  }

  bool archivo_vacio()
  {
    ifstream archivo("notas.txt", ios::app);
    return archivo.peek() == ifstream::traits_type::eof();
  }

  void guardar_nota(int id, string materia, float proyecto1, float proyecto2, float ensayo, float foro, float defensa)
  {
    archivo_notas << "[";
    archivo_notas << id << ";";
    archivo_notas << materia << ";";
    archivo_notas << proyecto1 << ";";
    archivo_notas << proyecto2 << ";";
    archivo_notas << ensayo << ";";
    archivo_notas << foro << ";";
    archivo_notas << defensa << "]" << endl;
  }

  int cantidad_maxima(int id)
  {
    int contador = 0;
    ifstream archivo("notas.txt", ios::app);
    string linea;
    while (getline(archivo, linea))
    {
      stringstream ss(linea);
      string identificacion;
      if (getline(ss, identificacion, ';'))
      {
        if (id == stoi(identificacion.substr(1)))
        {
          contador++;
        }
      }
    }
    archivo.close();
    return 3 - contador;
  }
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Leer archivo estudainte.txt
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

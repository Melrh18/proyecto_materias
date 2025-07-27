#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>
#include <tuple>
#include <fstream>

using namespace std;

enum class Genero
{
  Femenino,
  Masculino,
  Otro
};

class Estudiante
{
private:
  int id;
  string nombre;
  tuple<string, string, string> residencia;
  int edad;
  Genero genero;
  bool genero_definido;

  string generoToString(Genero _genero) const;
  Genero intToGenero(int _genero) const;

public:
  Estudiante(int _id = 0, string _nombre = "", int _edad = 0, Genero _genero = Genero::Femenino, string provincia = "", string canton = "", string distrito = "");

  // Getters
  int get_id() const;
  string get_nombre() const;
  int get_edad() const;
  string get_genero() const;
  bool get_genero_definido() const;
  string get_provincia() const;
  string get_canton() const;
  string get_distrito() const;

  // Setters
  void set_id(int _id);
  void set_nombre(string _nombre);
  void set_edad(int _edad);
  void set_genero(int _genero);
  void set_provincia(const string &provincia);
  void set_canton(const string &canton);
  void set_distrito(const string &distrito);

  // Archivo
  void guardar_estudiante_en_archivo(const Estudiante &estudiante);
  Estudiante obtener_estudiante(const int id, ifstream &arc);
  bool existe_id(const int id);
  void modificar_estudiante(int id, int nueva_edad, string nueva_provincia, string nuevo_canton, string nuevo_distrito);
  void eliminar_estudiante(int id);
};

#endif

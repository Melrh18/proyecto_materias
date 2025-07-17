// Crear Clase estudiante
#include <iostream>
#include <string>
#include <tuple>
#include <stdexcept>
#include <cctype>
using namespace std;

// TODO: Un enum limita los valores posibles para x propiedad
// TODO: En este caso limito a estos 3 únicos valores
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
  // Debe llevar los dos apeliidos
  string nombre;
  // Debe llevar residencia: Provincia, cantón y distrito
  tuple<string, string, string> residencia;
  int edad;
  Genero genero;

  // TODO: Conversión de Genero a texto (string)
  string generoToString(Genero _genero) const {
    switch (_genero)
    {
    case Genero::Femenino: return "Femenino";
      break;
    case Genero::Masculino: return "Masculino";
      break;
    case Genero::Otro: return "Otro";
      break;
    
    default:
      throw invalid_argument("Género inválido");
      break;
    }
  }

  // TODO: Conversión de texto (string) a Genero
  Genero stringToGenero(string _genero) const {
    // TODO: Fíjate que aquí hago la validación y el return en la misma línea
    // TODO: esto es posible, no hay problema con ello, es solo para evitar líneas innecesarias
    for (char c: _genero)
    {
      c = toupper(c);
    }
    
    if (_genero == "FEMENINO") return Genero::Femenino;
    if (_genero == "MASCULINO") return Genero::Masculino;
    if (_genero == "OTRO") return Genero::Otro;
    throw invalid_argument("Género inválido");
  }

public:
  Estudiante(int _id = 0, string _nombre = "", int _edad = 0, Genero _genero = Genero::Femenino, string provincia = "", string canton = "", string distrito = "")
  {
    id = _id;
    nombre = _nombre;
    edad = _edad;
    genero = _genero;
    residencia = make_tuple(provincia, canton, distrito);
  }

  //-------------------------------------------------------------------------------------------
  // Getters and Setters
  //-------------------------------------------------------------------------------------------
  int get_id()
  {
    return id;
  }

  string get_nombre()
  {
    return nombre;
  }

  int get_edad()
  {
    return edad;
  }

  string get_genero() const
  {
    // TODO: Uso de método privado
    return generoToString(genero);
  }

  string get_provincia() const
  {
    return get<0>(residencia);
  }

  string get_canton() const
  {
    return get<1>(residencia);
  }

  string get_distrito() const
  {
    return get<2>(residencia);
  }

  void set_id(int _id)
  {
    id = _id;
  }

  void set_nombre(string _nombre)
  {
    nombre = _nombre;
  }

  // TODO: Hacer validación directamente en el set
  // TODO: Puedes agregar condicional para que sea mayor o igual a YYYY menor o igual a
  void set_edad(int _edad)
  {
    // TODO: Si no cumple agrega un throw error de tipo out_of_range (Busca como hacerlo)
    edad = _edad;
    // TODO: Cuando vayas a solicitar la edad de la persona lo encierras en try-catch para que manejes el posible error
  }

  void set_genero(string _genero)
  {
    genero = stringToGenero(_genero);
  }

  void set_provincia(const string &provincia)
  {
    get<0>(residencia) = provincia;
  }

  void set_canton(const string &canton)
  {
    get<1>(residencia) = canton;
  }

  void set_distrito(const string &distrito)
  {
    get<2>(residencia) = distrito;
  }
};

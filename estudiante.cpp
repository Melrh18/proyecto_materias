#include <iostream>
#include <string>
#include <tuple>
#include <stdexcept> //manejo de exepciones
#include <cctype>    //manejo de tipo de carácteres
#include <vector>
#include <sstream> //Para convertir un string en un flujo de datos tipo entrada
#include <fstream> //manejo de archivos
using namespace std;

//----------------------------------------------------------------------------------------------------------------------
// Creación de Archivo
//-----------------------------------------------------------------------------------------------------------------------

ofstream archivo("estudiantes.txt", ios::app);

//-----------------------------------------------------------------------------------------------------------------------

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
  string nombre; // Debe llevar los dos apeliidos
  tuple<string, string, string> residencia;
  int edad;
  Genero genero;
  bool genero_definido;

  string generoToString(Genero _genero) const
  {
    switch (_genero)
    {
    case Genero::Femenino:
      return "Femenino";
      break;
    case Genero::Masculino:
      return "Masculino";
      break;
    case Genero::Otro:
      return "Otro";
      break;

    default:
      throw invalid_argument("Género inválido");
      break;
    }
  }

  Genero intToGenero(int _genero) const
  { // Entero a Genero
    if (_genero == 0)
      return Genero::Femenino;
    if (_genero == 1)
      return Genero::Masculino;
    if (_genero == 2)
      return Genero::Otro;
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
    genero_definido = false;
  }

  //---------------------------------------------------------------------------------------------------------------------------------
  // Getters and Setters
  //---------------------------------------------------------------------------------------------------------------------------------
  int get_id() const
  {
    return id;
  }

  string get_nombre() const
  {
    return nombre;
  }

  int get_edad() const
  {
    return edad;
  }

  string get_genero() const
  {
    return generoToString(genero);
  }

  bool get_genero_definido() const
  {
    return genero_definido;
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

  // TODO: Hacer validación de ID único haciendo un for y buscando el ID digitado con los del txt
  void set_id(int _id)
  {
    string string_id = to_string(_id);
    if (string_id.length() != 10)
    {
      throw invalid_argument("La identificación debe contener 10 números");
    }
    for (char cada_numero : string_id)
    {
      if (!isdigit(cada_numero))
      {
        throw logic_error("Error: La identificación no debe contener letras");
      }
    }
    id = _id;
  }

  void set_nombre(string _nombre)
  {
    vector<string> nombre_vector;
    stringstream ss(_nombre);
    string cada_palabra;
    while (ss >> cada_palabra)
    {
      nombre_vector.push_back(cada_palabra);
    }

    if (nombre_vector.size() != 3)
    {
      throw invalid_argument("Nombre incorrecto: debe tener un nombre y dos apellidos");
    }

    nombre = _nombre;
  }

  void set_edad(int _edad)
  {
    if (_edad < 18 || _edad > 100)
    {
      throw out_of_range("Edad no valida, debe estar entre 18 a 100 ");
    }
    edad = _edad;
  }

  void set_genero(int _genero)
  {
    genero = intToGenero(_genero);
    genero_definido = true;
  }
  void set_provincia(const string &provincia)
  {
    if (provincia == "")
    {
      throw invalid_argument("Tienes que agregar el nombre de la provincia, no se permite campos vacíos");
    }
    for (char i : provincia)
    {
      if (isdigit(i))
      {
        throw invalid_argument("La provincia no debe contener números");
      }
    }
    get<0>(residencia) = provincia;
  }

  void set_canton(const string &canton)
  {
    if (canton == "")
    {
      throw invalid_argument("Tienes que agregar el nombre del cantón, no se permite campos vacíos");
    }
    for (char i : canton)
    {
      if (isdigit(i))
      {
        throw invalid_argument("El cantón no debe contener números");
      }
    }
    get<1>(residencia) = canton;
  }

  void set_distrito(const string &distrito)
  {
    if (distrito == "")
    {
      throw invalid_argument("Tienes que agregar el nombre del distrito, no se permite campos vacíos");
    }
    for (char i : distrito)
    {
      if (isdigit(i))
      {
        throw invalid_argument("El distrito no debe contener números");
      }
    }
    get<2>(residencia) = distrito;
  }

  //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  //-------------------------------------------------------------------------------------------
  // Lógica funcional
  //-------------------------------------------------------------------------------------------

  // TODO: Método para abrir archivo txt estudiantes.txt
  // vector<Estudiante> o array, no sé que sea mejor, obtenerEstudiantes
  // En caso que no exista el archivo lanzar error

  // TODO: Método para guardar estudiante en archivo estudiantes.txt
  // Si no existe el archivo crearlo con método crearArchivo, no manualmente
  // Recibir de parámetros un objeto tipo Estudiante
  // Consumir método obtenerEstudiantes
  // Validaciones extras
  // Escribir los datos del estudiante en el txt y separar por ';' o '_' o '|', algún separador visible y poco usado
  //---------------------------------------------------------------------------------------------------------------------------------
  // Funciones para el manejo de archivo "estudiante.txt"
  //---------------------------------------------------------------------------------------------------------------------------------
  void guardar_estudiante_en_archivo(const Estudiante &estudiante)
  {
    archivo << estudiante.get_id() << ";";
    archivo << estudiante.get_nombre() << ";";
    archivo << estudiante.get_edad() << ";";
    archivo << estudiante.get_genero() << ";";
    archivo << estudiante.get_provincia() << ",";
    archivo << estudiante.get_canton() << ",";
    archivo << estudiante.get_distrito() << "/" << endl;
    cout << "Estudiante registrado con exito en: 'Estudiante.txt' " << endl;
  }

  Estudiante obtener_estudiante(const int id, ifstream &archivo)
  {
    string linea;
    while (getline(archivo, linea))
    {
      stringstream ss(linea);
      string identificacion;
      int contador = 0;
      string nombre;
      if (getline(ss, identificacion, ';'))
      {
        if (id == stoi(identificacion))
        {
          while (getline(ss, nombre, ';'))
          {
            contador++;
            if (contador == 1)
            {
              return Estudiante(id, nombre);
            }
          }
        }
      }
    }
    archivo.close();
    return Estudiante();
  }

  bool existe_id(const int id)
  {
    ifstream archivo("estudiantes.txt", ios::app);
    string linea;
    while (getline(archivo, linea))
    {
      stringstream ss(linea);
      string identificacion;
      if (getline(ss, identificacion, ';'))
      {
        if (id == stoi(identificacion))
        {
          return true;
        }
      }
    }
    archivo.close();
    return false;
  }

  void modificar_estudiante(int id, int nueva_edad, string nueva_provincia, string nuevo_canton, string nuevo_distrito)
  {
    ifstream archivo_entrada("estudiantes.txt", ios::app);
    vector<string> lineas_actualizadas;
    string linea;

    while (getline(archivo_entrada, linea))
    {
      stringstream ss(linea);
      string id_str;
      getline(ss, id_str, ';');
      int id_actual = stoi(id_str);

      if (id_actual == id)
      {
        // Ya estos parámetros están definidos a excepción de direccion
        // Dará error por doble definición
        string nombre, edad, genero, direccion;
        getline(ss, nombre, ';');
        getline(ss, edad, ';');
        getline(ss, genero, ';');
        getline(ss, direccion, ';');

        stringstream nueva_linea;
        // La dirección debe ser separada por comas y no puntos y comas
        nueva_linea << id_str << ";" << nombre << ";" << nueva_edad << ";" << genero << ";" << nueva_provincia << "," << nuevo_canton << "," << nuevo_distrito << "/";
        lineas_actualizadas.push_back(nueva_linea.str());
      }
      else
      {
        // Indicar que el ID ingresado por el usuario no fue encontrado
        // Se devolvería un throw
        lineas_actualizadas.push_back(linea);
      }
    }
    archivo_entrada.close();

    // Volver a escribir las lineas en el archivo
    // ios::trunck se usa para sobreescribir
    ofstream archivo_salida("estudiantes.txt", ios::trunc);
    for (const string &nueva_linea : lineas_actualizadas)
    {
      archivo_salida << nueva_linea << endl;
    }
    archivo_salida.close();
  }
};

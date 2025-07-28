#include <iostream>
#include <string>
#include <tuple>
#include <stdexcept> //manejo de exepciones
#include <cctype>    //manejo de tipo de carácteres
#include <vector>
#include <sstream> //Para convertir un string en un flujo de datos tipo entrada
#include <fstream> //manejo de archivos
#include <iomanip> //Se uso en el programa con la función: setw
#include <cmath>   // para round

using namespace std;

ofstream archivo("estudiantes.txt", ios::app);
ofstream archivo_notas("notas.txt", ios::app);

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

  Estudiante obtener_estudiante(const int id)
  {
    ifstream arc("estudiantes.txt", ios::app);
    string linea;
    while (getline(arc, linea))
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
    arc.close();
    return Estudiante();
  }

  bool existe_id(const int id)
  {
    ifstream ae("estudiantes.txt", ios::app);
    string linea;
    while (getline(ae, linea))
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
    ae.close();
    return false;
  }

  void seleccionar_materias(int id)
  {
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
        string nombre, edad, genero, direccion;
        getline(ss, nombre, ';');
        getline(ss, edad, ';');
        getline(ss, genero, ';');
        getline(ss, direccion, ';');

        stringstream nueva_linea;
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

  void eliminar_estudiante(int id)
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

      if (id_actual != id)
      {
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
  float promedio;
  string estado;

public:
  Nota(int _id = 0, string _materia = "", float _proyecto1 = 0, float _proyecto2 = 0, float _ensayo = 0, float _foro = 0, float _defensa = 0, float _promedio = 0, string _estado = "")
  {
    id = _id;
    materia = _materia;
    proyecto1 = _proyecto1;
    proyecto2 = _proyecto2;
    ensayo = _ensayo;
    foro = _foro;
    defensa = _defensa;
    promedio = _promedio;
    estado = _estado;
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

  float get_promedio() const
  {
    return promedio;
  }

  float get_estado() const
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

    float redondeado = round(_proyecto1 * 100.0f) / 100.0f;
    if (fabs(_proyecto1 - redondeado) > 0.00001f)
    {
      throw invalid_argument("No pueden haber más de dos decimales");
    }
    proyecto1 = _proyecto1;
  }

  void set_proyecto2(float _proyecto2)
  {
    if (proyecto2 < 0 || proyecto2 > 10)
    {
      throw invalid_argument("La nota debe estar en base 10");
    }

    float redondeado = round(_proyecto2 * 100.0f) / 100.0f;
    if (fabs(_proyecto2 - redondeado) > 0.00001f)
    {
      throw invalid_argument("No pueden haber más de dos decimales");
    }
    proyecto2 = _proyecto2;
  }

  void set_ensayo(float _ensayo)
  {
    if (proyecto1 < 0 || proyecto2 > 10)
    {
      throw invalid_argument("La nota debe estar en base 10");
    }
    float redondeado = round(_ensayo * 100.0f) / 100.0f;
    if (fabs(_ensayo - redondeado) > 0.00001f)
    {
      throw invalid_argument("No pueden haber más de dos decimales");
    }
    ensayo = _ensayo;
  }

  void set_foro(float _foro)
  {
    if (proyecto1 < 0 || proyecto2 > 10)
    {
      throw invalid_argument("La nota debe estar en base 10");
    }
    float redondeado = round(_foro * 100.0f) / 100.0f;
    if (fabs(_foro - redondeado) > 0.00001f)
    {
      throw invalid_argument("No pueden haber más de dos decimales");
    }
    foro = _foro;
  }

  void set_defensa(float _defensa)
  {
    if (proyecto1 < 0 || proyecto2 > 10)
    {
      throw invalid_argument("La nota debe estar en base 10");
    }
    float redondeado = round(_defensa * 100.0f) / 100.0f;
    if (fabs(_defensa - redondeado) > 0.00001f)
    {
      throw invalid_argument("No pueden haber más de dos decimales");
    }
    defensa = _defensa;
  }

  void set_promedio(float _promedio)
  {
    if (_promedio < 0 || _promedio > 10)
    {
      throw invalid_argument("El promedio debe estar en base 10");
    }
    float redondeado = round(_promedio * 100.0f) / 100.0f;
    if (fabs(_promedio - redondeado) > 0.00001f)
    {
      throw invalid_argument("No pueden haber más de dos decimales");
    }
    promedio = _promedio;
  }

  void set_estado(string _estado)
  {
    estado = _estado;
  }

  float calcular_promedio(Nota nota)
  {
    float p1 = 0.1 * nota.get_proyecto1();
    float p2 = 0.2 * nota.get_proyecto2();
    float cal_ens = 0.3 * nota.get_ensayo();
    float cal_fo = 0.1 * nota.get_foro();
    float def = 0.3 * nota.get_defensa();
    float resultado = p1 + p2 + cal_ens + cal_fo + def;
    return round(resultado * 100) / 100.0f;
  }

  string obtener_estado(Nota nota)
  {
    float promedio = calcular_promedio(nota);
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
    ifstream an("notas.txt", ios::app);
    return an.peek() == ifstream::traits_type::eof();
  }

  void guardar_nota(int id, Nota nueva_nota)
  {
    nueva_nota.set_id(id);
    archivo_notas << "[";
    archivo_notas << id << ";";
    archivo_notas << nueva_nota.get_materia() << ";";
    archivo_notas << nueva_nota.get_proyecto1() << ";";
    archivo_notas << nueva_nota.get_proyecto2() << ";";
    archivo_notas << nueva_nota.get_ensayo() << ";";
    archivo_notas << nueva_nota.get_foro() << ";";
    archivo_notas << nueva_nota.get_defensa() << ";";
    float promedio = calcular_promedio(nueva_nota);
    string estado = obtener_estado(nueva_nota);
    archivo_notas << promedio << ";";
    archivo_notas << estado << "]" << endl;
  }

  void editar_nota(int id, Nota nueva_nota)
  {
    ifstream archivo_entrada("notas.txt", ios::app);
    vector<string> lineas_actualizadas;
    string linea;

    while (getline(archivo_entrada, linea))
    {
      stringstream ss(linea);
      string id_str;
      string mat;
      getline(ss, id_str, ';');
      getline(ss, mat, ';');
      int id_actual = stoi(id_str.substr(1));

      if (id_actual == id && mat == nueva_nota.get_materia())
      {
        string materia, proyecto1, proyecto2, ensayo, foro, defensa, promedio, estado;
        getline(ss, proyecto1, ';');
        getline(ss, proyecto2, ';');
        getline(ss, ensayo, ';');
        getline(ss, foro, ';');
        getline(ss, defensa, ';');
        getline(ss, estado, ']');

        stringstream nueva_linea;
        float nuevo_promedio = calcular_promedio(nueva_nota);
        string nuevo_estado = obtener_estado(nueva_nota);
        nueva_linea << "[" << id_actual << ";" << mat << ";" << nueva_nota.get_proyecto1() << ";" << nueva_nota.get_proyecto2() << ";" << nueva_nota.get_ensayo() << ";" << nueva_nota.get_foro() << ";" << nueva_nota.get_defensa() << ";" << nuevo_promedio << ";" << nuevo_estado << "]";
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
    ofstream archivo_salida("notas.txt", ios::trunc);
    for (const string &nueva_linea : lineas_actualizadas)
    {
      archivo_salida << nueva_linea << endl;
    }
    archivo_salida.close();
  }

  int cantidad_maxima(int id)
  {
    int contador = 0;
    ifstream arn("notas.txt", ios::app);
    string linea;
    while (getline(arn, linea))
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
    arn.close();
    return 3 - contador;
  }

  void generar_reporte()
  {
    cabecera_reporte();
    obtener_notas();
  }

  void cabecera_reporte()
  {
    cout << "+" << string(12, '-') << "+" << string(30, '-') << "+" << string(20, '-') << "+" << string(12, '-') << "+" << string(16, '-') << "+" << endl;
    cout << "|" << left << setw(12) << " ID" << "|" << left << setw(30) << " Nombre" << "|" << left << setw(20) << " Materia" << "|" << left << setw(12) << " Promedio" << "|" << left << setw(16) << " Estado" << "|" << endl;
    cout << "+" << string(12, '-') << "+" << string(30, '-') << "+" << string(20, '-') << "+" << string(12, '-') << "+" << string(16, '-') << "+" << endl;
  }

  void obtener_notas()
  {
    ifstream archn("notas.txt", ios::app);
    string linea;
    Estudiante e;
    Nota n;
    int est_id = 0;
    string est_nombre = "";
    float promedio = 0;
    string estado = "";
    while (getline(archn, linea))
    {
      stringstream ss(linea);
      string identificacion;
      string materia, p1, p2, ensayo, foro, defensa;
      if (getline(ss, identificacion, ';'))
      {
        est_id = stoi(identificacion.substr(1));
        e = e.obtener_estudiante(est_id);
        est_id = e.get_id();
        est_nombre = e.get_nombre();
      }
      if (getline(ss, materia, ';'))
      {
        n.set_materia(materia);
      }
      if (getline(ss, p1, ';'))
      {
        n.set_proyecto1(stof(p1));
      }
      if (getline(ss, p2, ';'))
      {
        n.set_proyecto2(stof(p2));
      }
      if (getline(ss, ensayo, ';'))
      {
        n.set_ensayo(stof(ensayo));
      }
      if (getline(ss, foro, ';'))
      {
        n.set_foro(stof(foro));
      }
      if (getline(ss, defensa, ';'))
      {
        n.set_defensa(stof(defensa));
      }

      promedio = calcular_promedio(n);
      estado = obtener_estado(n);

      cout << "| " << left << setw(11) << e.get_id();
      cout << "| " << left << setw(29) << e.get_nombre();
      cout << "| " << left << setw(20) << n.get_materia();
      cout << "| " << left << setw(11) << promedio;
      cout << "| " << left << setw(15) << estado;
      cout << "|" << endl;
      e = Estudiante();
    }
    archn.close();
  }

  vector<Nota> notas_por_estudiante(int id)
  {
    ifstream archivo_entrada("notas.txt", ios::app);
    Nota nota_estudiante;
    vector<Nota> notas_a_devolver;
    string linea;

    while (getline(archivo_entrada, linea))
    {
      stringstream ss(linea);
      string id_str;
      getline(ss, id_str, ';');
      int id_actual = stoi(id_str.substr(1));

      if (id_actual == id)
      {
        nota_estudiante.set_id(id);
        string materia, proyecto1, proyecto2, ensayo, foro, defensa, promedio, estado;
        getline(ss, materia, ';');
        nota_estudiante.set_materia(materia);
        getline(ss, proyecto1, ';');
        nota_estudiante.set_proyecto1(stof(proyecto1));
        getline(ss, proyecto2, ';');
        nota_estudiante.set_proyecto2(stof(proyecto2));
        getline(ss, ensayo, ';');
        nota_estudiante.set_ensayo(stof(ensayo));
        getline(ss, foro, ';');
        nota_estudiante.set_foro(stof(foro));
        getline(ss, defensa, ';');
        nota_estudiante.set_defensa(stof(defensa));
        getline(ss, promedio, ';');
        nota_estudiante.set_promedio(stof(promedio));
        getline(ss, estado, ']');
        nota_estudiante.set_estado(estado);

        notas_a_devolver.push_back(nota_estudiante);
        nota_estudiante = Nota();
      }
    }
    archivo_entrada.close();

    return notas_a_devolver;
  }
};

Estudiante estudiante;
Nota nota;

// Funcion que solo imprime las opciones del menú.
void imprimir_menu()
{
  cout << "----------------------------------------------------------------------------" << endl;
  cout << "                        Menú Principal" << endl;
  cout << "----------------------------------------------------------------------------" << endl;
  cout << "1. Registrar Estudiante. " << endl;
  cout << "2. Ingresar Calificaciones. " << endl;
  cout << "3. Modificar datos Estudiante. " << endl;
  cout << "4. Modificar Registro de Notas por Estudiante. " << endl;
  cout << "5. Eliminar Registro de Estudiante " << endl;
  cout << "6. Reporte de Estudiantes, promedios y estado" << endl;
  cout << "7. Salir del Programa  " << endl;
  cout << "Indique el número de la opción que desea realizar;" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
}

Estudiante registrar_estudiante()
{
  int identidad = 0;
  string nombre = "";
  int edad = 0;
  int genero = 0;
  string provincia = "";
  string canton = "";
  string distrito = "";
  bool datos_completos = false;
  while (!datos_completos)
  {
    try
    {
      //----------------------------------------------------------------------------------------------------------------------------------------
      if (estudiante.get_id() == 0)
      {
        cout << "Escriba la identificación del estudiante" << endl;
        cin >> identidad;
        if (estudiante.existe_id(identidad))
        {
          throw invalid_argument("La identificación ya existe, debe registar otra");
        }
        estudiante.set_id(identidad);
      }
      //----------------------------------------------------------------------------------------------------------------------------------------
      if (estudiante.get_nombre() == "")
      {
        cout << "Escriba el nombre del estudiante, debe de llevar nombre y los dos apellidos" << endl;
        cin.ignore();
        getline(cin, nombre);
        estudiante.set_nombre(nombre);
      }
      //----------------------------------------------------------------------------------------------------------------------------------------
      if (estudiante.get_edad() == 0)
      {
        cout << "Ingrese la edad " << endl;
        cout << "El rango debe de ser entre 18-100 años" << endl;
        cin >> edad;
        estudiante.set_edad(edad);
      }
      //----------------------------------------------------------------------------------------------------------------------------------------
      if (!estudiante.get_genero_definido())
      {
        cout << "Ingrese el género:" << endl;
        cout << "Digite [0] para femenino" << endl;
        cout << "Digite [1] para Masculino" << endl;
        cout << "Digite [2] para Otro" << endl;
        cin >> genero;
        estudiante.set_genero(genero);
      }

      //----------------------------------------------------------------------------------------------------------------------------------------
      if (estudiante.get_provincia() == "")
      {
        cout << "Por último se debe ingresar la residencia" << endl;
        cout << "Ingrese el nombre de la provincia" << endl;
        cin.ignore();
        getline(cin, provincia);
        estudiante.set_provincia(provincia);
      }
      //------------------------------------------------------------------------------------------------------------------------------------------
      if (estudiante.get_canton() == "")
      {
        cout << "Ingrese el nombre del cantón" << endl;
        getline(cin, canton);
        estudiante.set_canton(canton);
      }
      //-------------------------------------------------------------------------------------------------------------------------------------------------
      if (estudiante.get_distrito() == "")
      {
        cout << "Ingrese el nombre del distrito" << endl;
        getline(cin, distrito);
        estudiante.set_distrito(distrito);
      }
      //----------------------------------------------------------------------------------------------------------------------------------------
      estudiante.guardar_estudiante_en_archivo(estudiante);
      //----------------------------------------------------------------------------------------------------------------------------------------
      datos_completos = true;
      estudiante = Estudiante();
      continue;
    }
    catch (const exception &e)
    {
      cerr << "Se ha producido un error: " << e.what() << endl;
    }
  }

  return estudiante;
}

void modificar_estudiante()
{
  bool datos_completos = false;
  bool encontro_estudiante = false;
  int identidad_buscar = 0;
  int edad = 0;
  string provincia = "";
  string canton = "";
  string distrito = "";
  while (!datos_completos)
  {
    try
    {
      if (!encontro_estudiante)
      {
        cout << "Ingrese la identificación del estudiante que desea buscar" << endl;
        cin >> identidad_buscar;
        if (!estudiante.existe_id(identidad_buscar))
        {
          throw invalid_argument("Estudiante no existe");
          datos_completos = true;
        }
        encontro_estudiante = true;
      }

      if (estudiante.get_edad() == 0)
      {
        cout << "Ingrese la nueva edad del estudiante" << endl;
        cin >> edad;
        estudiante.set_edad(edad);
      }

      if (estudiante.get_provincia() == "")
      {
        cout << "Ingrese la nueva provincia" << endl;
        cin.ignore();
        getline(cin, provincia);
        estudiante.set_provincia(provincia);
      }

      if (estudiante.get_canton() == "")
      {
        cout << "Ingrese el nuevo cantón" << endl;
        getline(cin, canton);
        estudiante.set_canton(canton);
      }

      if (estudiante.get_distrito() == "")
      {
        cout << "Ingrese el nuevo distrito" << endl;
        getline(cin, distrito);
        estudiante.set_distrito(distrito);
      }

      estudiante.modificar_estudiante(identidad_buscar, edad, provincia, canton, distrito);
      datos_completos = true;
      continue;
    }
    catch (const exception &e)
    {
      cerr << "Se ha producido un error: " << e.what() << endl;
    }
  }
}

void eliminar_estudiante()
{
  int id_buscar = 0;
  cout << "Ingrese la identificación del estudiante que desea eliminar";
  cin >> id_buscar;
  estudiante.set_id(id_buscar);
  if (!estudiante.existe_id(id_buscar))
  {
    throw invalid_argument("Estudiante no existe");
  }
  else
  {
    estudiante.eliminar_estudiante(id_buscar);
  }
}

tuple<int, int, bool> cantidad_calificaciones()
{
  int identidad = 0;
  int cantidad_a_registrar = 0;
  bool datos_completos = false;
  while (!datos_completos)
  {
    //----------------------------------------------------------------------------------------------------------------------------------------
    cout << "Escriba la identificación del estudiante" << endl;
    cin >> identidad;
    if (!estudiante.existe_id(identidad))
    {
      throw invalid_argument("El estudiante digitado no existe");
    }
    nota.set_id(identidad);
    //----------------------------------------------------------------------------------------------------------------------------------------
    // Validación cantidad de notas
    int cantidad_maxima = nota.cantidad_maxima(nota.get_id());
    if (cantidad_maxima == 0)
    {
      cout << "No se pueden registrar más de 3 notas por estudiante";
      return make_tuple(0, 0, false);
    }
    if (cantidad_a_registrar == 0)
    {
      cout << "Digite la cantidad de notas que desea ingresar, máximo de notas a registrar para este estudiante es de: " << cantidad_maxima << endl;
      cin >> cantidad_a_registrar;
      if (cantidad_a_registrar > cantidad_maxima)
      {
        throw invalid_argument("No se pueden registrar más de 3 notas por estudiante");
      }
    }
    datos_completos = true;
    continue;
  }
  return make_tuple(identidad, cantidad_a_registrar, true);
}

void registrar_nota(int identidad)
{
  string materia = "";
  float proyecto1 = 0;
  float proyecto2 = 0;
  float ensayo = 0;
  float foro = 0;
  float defensa = 0;
  bool datos_completos = false;
  while (!datos_completos)
  {
    try
    {
      //----------------------------------------------------------------------------------------------------------------------------------------
      if (nota.get_materia() == "")
      {
        cout << "Escriba el nombre de la materia" << endl;
        cin.ignore();
        getline(cin, materia);
        nota.set_materia(materia);
      }
      //----------------------------------------------------------------------------------------------------------------------------------------
      if (nota.get_proyecto1() == 0)
      {
        cout << "Ingrese la nota del proyecto 1 en base 10 (0-10)" << endl;
        cin >> proyecto1;
        nota.set_proyecto1(proyecto1);
      }
      //----------------------------------------------------------------------------------------------------------------------------------------
      if (nota.get_proyecto2() == 0)
      {
        cout << "Ingrese la nota del proyecto 2 en base 10 (0-10)" << endl;
        cin >> proyecto2;
        nota.set_proyecto2(proyecto2);
      }
      //----------------------------------------------------------------------------------------------------------------------------------------
      if (nota.get_ensayo() == 0)
      {
        cout << "Ingrese la nota del ensayo en base 10 (0-10)" << endl;
        cin >> ensayo;
        nota.set_ensayo(ensayo);
      }
      //----------------------------------------------------------------------------------------------------------------------------------------
      if (nota.get_foro() == 0)
      {
        cout << "Ingrese la nota del foro en base 10 (0-10)" << endl;
        cin >> foro;
        nota.set_foro(foro);
      }
      //----------------------------------------------------------------------------------------------------------------------------------------
      if (nota.get_defensa() == 0)
      {
        cout << "Ingrese la nota de la defensa en base 10 (0-10)" << endl;
        cin >> defensa;
        nota.set_defensa(defensa);
      }
      //----------------------------------------------------------------------------------------------------------------------------------------
      nota.guardar_nota(identidad, nota);
      //----------------------------------------------------------------------------------------------------------------------------------------
      datos_completos = true;
      nota = Nota();
      continue;
    }
    catch (const exception &e)
    {
      cerr << "Se ha producido un error: " << e.what() << endl;
    }
  }
}

void ingresar_calificaciones()
{
  tuple<int, int, bool> datos;
  bool datos_iniciales = false;
  while (!datos_iniciales)
  {
    try
    {
      datos = cantidad_calificaciones();
      datos_iniciales = true;
    }
    catch (const exception &e)
    {
      cerr << "Se ha producido un error: " << e.what() << endl;
    }
  }

  int identidad = get<0>(datos);
  int cantidad = get<1>(datos);
  bool es_posible_ingresar_mas_datos = get<2>(datos);
  bool datos_completos = false;
  if (es_posible_ingresar_mas_datos)
  {
    for (int i = 0; i < cantidad; i++)
    {
      registrar_nota(identidad);
    }
    cout << "Nota registrada con exito en: 'notas.txt' " << endl;
  }
}

void modificar_calificaciones()
{
  bool datos_completos = false;
  bool encontro_estudiante = false;
  int identidad_buscar = 0;
  float proyecto1 = 0;
  float proyecto2 = 0;
  float ensayo = 0;
  float foro = 0;
  float defensa = 0;
  while (!datos_completos)
  {
    try
    {
      if (!encontro_estudiante)
      {
        cout << "Ingrese la identificación del estudiante que desea modificar notas" << endl;
        cin >> identidad_buscar;
        if (!estudiante.existe_id(identidad_buscar))
        {
          throw invalid_argument("Estudiante no existe");
        }
        encontro_estudiante = true;
      }

      vector<Nota> notas_del_estudiante = nota.notas_por_estudiante(identidad_buscar);

      if (notas_del_estudiante.empty())
      {
        cout << "Este estudiante no tiene notas registradas" << endl;
        continue;
      }

      // Validar cual nota modificar
      cout << "Cuál de las siguientes notas desea modificar: " << endl;
      for (size_t i = 0; i < notas_del_estudiante.size(); i++)
      {
        cout << i << " - " << notas_del_estudiante[i].get_materia() << endl;
      }

      string val = "";
      int op = 0;
      bool seleccion_hecha = false;
      int valor_maximo = notas_del_estudiante.size() - 1;
      while (!seleccion_hecha)
      {
        getline(cin, val);

        try
        {
          op = stoi(val);
          if (op < 0 || op > valor_maximo)
          {
            throw out_of_range("Valor fuera de rango");
          }
          else
          {
            seleccion_hecha = true;
          }
        }
        catch (const invalid_argument &e)
        {
          cout << "Error: No digitó un número válido." << endl;
          continue;
        }
        catch (const out_of_range &e)
        {
          cout << "Error: El número está fuera de rango." << endl;
          continue;
        }
      }

      if (nota.get_proyecto1() == 0)
      {
        cout << "Ingrese la nueva nota del proyecto 1" << endl;
        cin >> proyecto1;
        notas_del_estudiante[op].set_proyecto1(proyecto1);
      }

      if (nota.get_proyecto2() == 0)
      {
        cout << "Ingrese la nueva nota del proyecto 2" << endl;
        cin >> proyecto2;
        notas_del_estudiante[op].set_proyecto2(proyecto2);
      }

      if (nota.get_ensayo() == 0)
      {
        cout << "Ingrese la nueva nota de ensayo" << endl;
        cin >> ensayo;
        notas_del_estudiante[op].set_ensayo(ensayo);
      }

      if (nota.get_foro() == 0)
      {
        cout << "Ingrese la nueva nota de foro" << endl;
        cin >> foro;
        notas_del_estudiante[op].set_foro(foro);
      }

      if (nota.get_defensa() == 0)
      {
        cout << "Ingrese la nueva nota de defensa" << endl;
        cin >> defensa;
        notas_del_estudiante[op].set_defensa(defensa);
      }

      nota.editar_nota(identidad_buscar, notas_del_estudiante[op]);

      datos_completos = true;
      continue;
    }
    catch (const exception &e)
    {
      cerr << "Se ha producido un error: " << e.what() << endl;
      continue;
    }
  }
}

int main()
{
  int opcion = 0;
  do
  {
    imprimir_menu();
    cin >> opcion;
    switch (opcion)
    {
    case 1:
    {
      registrar_estudiante();
      break;
    }

    case 2:
    {
      ingresar_calificaciones();
      break;
    }

    case 3:
    {
      modificar_estudiante();
      break;
    }

    case 4:
    {
      modificar_calificaciones();
      break;
    }

    case 5:
    {
      eliminar_estudiante();
      break;
    }

    case 6:
    {
      nota.generar_reporte();
      break;
    }
    }
  } while (opcion != 7);
  cout << "Saliendo del programa";
  return 0;
}

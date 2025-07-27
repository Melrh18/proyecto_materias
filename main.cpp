#include <iostream>
#include <stdexcept> //manejo de exepciones1
#include "estudiante.cpp"
using namespace std;

Estudiante estudiante;

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

  void eliminar_estudiante(){
    int id_buscar= 0;
    cout << "Ingrese la identificación del estudiante que desea eliminar"; 
    cin>> id_buscar; 
    estudiante.set_id(id_buscar);
    if (!estudiante.existe_id(id_buscar))
        {
          throw invalid_argument("Estudiante no existe");
        }else{
          estudiante.el(id_buscar);
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
    }

    case 2:
    {
    }

    case 3:
    {
      modificar_estudiante();
    }

    case 4:
    {
    }

    case 5:
    {
      eliminar_estudiante();
    }

    case 6:
    {
    }
    }
  } while (opcion != 7);
  cout << "Saliendo del programa";

  return 0;
}
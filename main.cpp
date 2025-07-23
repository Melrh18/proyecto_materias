#include <iostream>
#include "estudiante.cpp"
using namespace std;

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

int main()
{
  int opcion= 0;
  do{
    imprimir_menu();
    cin >> opcion;
    switch (opcion){
      case 1:{

      }

      case 2:{

      }

      case 3:{
        
      }

      case 4:{
        
      }

      case 5:{
        
      }

      case 6:{
        
      }

    }
  }
  while( opcion != 7);
  cout<<"Saliendo del programa";
  Estudiante me(1234567891, "Me R H", 21, Genero::Femenino, "a", "b", "c");
  cout << "ID: " << me.get_id();
  ofstream archivo("estudiantes.txt", ios::app);
  if (archivo.is_open())
  {
    me.guardar_estudiante_en_archivo(archivo, me);
    archivo.close();
  }
  ifstream estudiantes("estudiantes.txt", ios::app);
  Estudiante estudiante = estudiante.obtener_estudiante(123567891, estudiantes);
  cout << "exist";
  cout << estudiante.get_nombre();

  return 0;
}
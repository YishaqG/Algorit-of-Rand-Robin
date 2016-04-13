#ifndef STATICS_H
#define STATICS_H

//Tamaños maximos
#define TAM_BUFF 20 //Tamaño para almacenar cadenas y posteriormente validarlas

/*Estados(ID, Nombre)*/
#define ID_EJEC 1
#define EJEC "Ejecutando"
#define ID_LIS 2
#define LIS "Listo"
#define ID_ESP 3
#define ESP "Esperando"
#define ID_DOR 4
#define DOR "Dormido"

/*Impresiones a pantalla*/
#define SELEC "Introduzca el numero entre () para seleccionar"

/*Valores que identifican a un proceso como frente, fondo o intermedio*/
#define FRONT  -1
#define MIDLE 0
#define REAR  1


/*Mesajes de Error*/
#define FAIL -1
#define EMPTY_FAIL "No hay procesos"
#define MEM_FAIL "Error al asignar memoria."
#define NUM0_FAIL "Error, debe ingresar un numero mayor o igual a 0"
#define NUM1_FAIL "Error, debe ingresar un numero mayor a 0"
#define NUEVO_ER "Imposible crear."
#define FIND_FAIL "Error, elemento inexistente. Intenta nuevamente."
#define MFULL_FAIL " Memoria llena."
#define DEL_FAIL "Imposible eliminar elemento, proceso en ejecucion."
#define REP_FAIL "El id y/o nombre que ha introducido ya existe(n)."
#define DEFAULT_FAIL "Opcion no valida. Vuelva a intentar."

#endif

#ifndef PCB
#define PCB
/*Estructura para la tabla de control de procesos.*/
struct pcb_p
{
  int cp; //Momento de llegada del proceso
  int state; //Estado del programa
  int pid; //Identificador de proceso
  int tim[3];//Tiempo que necesita para ejecutarse, total,restante, consumido
  int gen;//Variable para indicar si un nodo es frente, fondo o un nodo intermedio.
  int first_exe;
  struct users_p *user; //Usuario
  struct groups_p *group; //Grupo

  struct pcbMov_p *sense;// Variable para indicar anterior y siguiente de cada elemento segun su Momento de llegada
  struct pcbMov_p *stateSense;// Variable para indicar anterior y siguiente de cada elemento segun su estado.
  struct pcbMov_p *groupSense;// Variable para indicar anterior y siguiente de cada elemento segun su grupo.
  struct pcbMov_p *userSense;// Variable para indicar anterior y siguiente de cada elemento segun su usuario.
};

/*Estructura para controlar los nodos anteriores y siguientes de cada nodo*/
struct pcbMov_p
{
  struct pcb_p *prev;
  struct pcb_p *next;
};

/*Estructura para controlar la lista ligada para datos tipo pcb*/
struct pcbCtrl_p
{
  struct pcb_p *front;
  struct pcb_p *rear;
};

/*Estructura para controlar las listas por estado*/
struct pcbStates_p
{
  struct pcbCtrl_p *readys;
  struct pcbCtrl_p *sleeping;
  struct pcbCtrl_p *waiting;
};

#endif

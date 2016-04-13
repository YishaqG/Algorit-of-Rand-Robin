#ifndef GROUPS_H
#define GROUPS_H

//Estructura grupo.
struct groups_p
{
  char n[TAM_BUFF]; //Nombre de grupo
  int gid;// Id
  struct pcbCtrl_p *pcbG;
  struct groupsMov_p *sense; //Siguiente y anterior nodo de grupos
};

/*Estructura para manejar el siguiente y anterior de la lista de grupos.*/
struct groupsMov_p
{
  struct groups_p *prev;
  struct groups_p *next;
};

/*Estructura para manejar la lista de grupos*/
struct groupsCtrl_p
{
  struct groups_p *front;
  struct groups_p *rear;
};

#endif

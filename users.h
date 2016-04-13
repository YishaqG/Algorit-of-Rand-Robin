#ifndef USERS_H
#define USERS_H

//Estructura usuario.
struct users_p
{
  char n[TAM_BUFF]; //Nombre de usuario
  int uid;// Id
  struct pcbCtrl_p *pcbU;
  struct usersMov_p *sense; //Siguiente y anterior nodo de usuarios
};

/*Estructura para manejar el siguiente y anterior de la lista de usuarios.*/
struct usersMov_p
{
  struct users_p *prev;
  struct users_p *next;
};

/*Estructura para manejar la lista de usuarios*/
struct usersCtrl_p
{
  struct users_p *front;
  struct users_p *rear;
};
#endif

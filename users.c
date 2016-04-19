/*Prototipos de funciones*/
users* create_user_mem();//Crea memoria para un usuario
int set_uid(users *front);
void create_user(usersCtrl *ctrlU); //Crea un usuario
void show_users(usersCtrl *ctrlU); //Muestra los usuarios
users* find_user(int uid,users *front); //Busca el usuario a imprimir
int next_user(users **aux, users *f);//Para desplazarse.
int prev_user(users **aux, users *r);//Para desplazarse.
int list_lenghtU(pcbCtrl *ctrl);
int del_user(pcbCtrl *ctrl, pcbStates *states, usersCtrl *us);
int set_user(users **u,usersCtrl *ctrlU);

/*Crea la memoria para alojar un usuario*/
users* create_user_mem()
{
  users *temp;
  temp = (users *)malloc(sizeof(users));

  temp->pcbU = (pcbCtrl *)malloc(sizeof(pcbCtrl));
  temp->pcbU->front = NULL;
  temp->pcbU->rear = NULL;

  temp->sense = (usersMov *)malloc(sizeof(usersMov));
  temp->sense->next = NULL;
  temp->sense->prev = NULL;
  temp->uid = -1;
  strcpy(temp->n," ");

  return temp;
}

/*Para desplazarse al siguiente usuario de la lista*/
int next_user(users **aux, users *f)
{
  int b = 0;
  if(((**aux).sense->next == NULL) || ((**aux).sense->next == f))
    b = FAIL;
  else
    *aux = (**aux).sense->next; //Desplazamiento al siguiente elemento
  return b;
}

/*Para desplazarse al usuario anterior de la lista*/
int prev_user(users **aux,users *r)
{
  int b = 0;
    if((**aux).sense->prev == r)
      b = FAIL;
    else
      *aux = (**aux).sense->prev; //Desplazamiento al siguiente elemento

  return b;
}

/*Evalua si el id de un usuario ha sido repetido y de ser
asi pregunta por otro o cancela la creacion del proceso*/
int set_uid(users *front)
{
  int uid,flag = 0;
  users *f = front;
  if(front == NULL)
    uid = set_int("el id del nuevo usuario",0);
  else
  {
    uid = set_int("el id del nuevo usuario",0);
    do
    {
      if(uid == f->uid)
      {
        flag = FAIL;
        break;
      }
    }while(next_user(&f,front) != FAIL);
    if(flag == FAIL)
    {
      printf("%s\n",REP_FAIL);
      if(cancel("creacion del usuario") == 0)
        uid = set_uid(front);
      else
        uid = FAIL;
    }
  }

  return uid;
}
/**/

/*Crea un nuevo usuario*/
void create_user(usersCtrl *ctrlU)
{
  int uid;
  char *name = create_string_mem(TAM_BUFF);
  if((uid = set_uid(ctrlU->front)) > 0)
  {
    printf("\n");
    if(set_name(name,"usuario") >= 0)//falta hacer que lo pida de uevo si pasa el tam
    {
      if(ctrlU->front == NULL)
      {
        ctrlU->front = create_user_mem();
        if(ctrlU->front != NULL)
        {
          strcpy(ctrlU->front->n, name);
          ctrlU->front->uid = uid;
          ctrlU->rear = ctrlU->front;
          free(name);
        }
        else printf("%s",MEM_FAIL);
      }
      else
      {
        ctrlU->rear->sense->next = create_user_mem();
        if(ctrlU->rear->sense->next != NULL)
        {
          ctrlU->rear->sense->next->sense->prev = ctrlU->rear; //?
          ctrlU->rear = ctrlU->rear->sense->next;

          strcpy(ctrlU->rear->n, name);
          ctrlU->rear->uid = uid;

          ctrlU->rear->sense->next = ctrlU->front;
          ctrlU->front->sense->prev = ctrlU->rear;
          free(name);
        }
        else printf("%s",MEM_FAIL);
      }
    }
  }
}

/*Muestra los usuarios esxistentes*/
void show_users(usersCtrl *ctrlU)
{
  users *f;
  if(ctrlU->front != NULL)
  {
    f = ctrlU->front;

    printf("\n    USUARIOS EXISTENTES\n");
    printf("|%7s|%15s|\n","ID","Descripcion");
    printf("=========================\n");
    do
    {
      printf("|(%5i)|%15s|\n",f->uid,f->n);
    }while(next_user(&f,ctrlU->front) != FAIL);
    printf("\n");
  }
  else
    printf("No se han creado usuarios.\n");
}

/*Encuentra un usuario por id*/
users* find_user(int uid, users *front)
{
  users *chosen,*aux = front;
  chosen = NULL;
  do
  {
    if(uid == aux->uid)
    {
      chosen = aux;
      break;
    }
  }while(next_user(&aux,front) != FAIL);
  return chosen;
}

/*1_Retorna la cantidad de nodos de una lista*/
int list_lenghtU(pcbCtrl *ctrl)
{
  int i = 1;
  pcb *front = ctrl->front;
  while(next_pcbU(&front,  ctrl->front) != FAIL)
    i++;

  return i;
}
/*0_list_lenght*/

/*1_Eliminacion de usuario junto con sus procesos*/
int del_user(pcbCtrl *ctrl, pcbStates *states, usersCtrl *us)
{
  pcb *temp;
  int i;
  printf("<< Eliminación de usuario >>\n");

  if( us->front != NULL )
  {
    int eleccion; //Eleccion de grupo
    users *elm = NULL; //Grupo

    do
    {
      printf("Escoja el usuario a eliminar:\n");
      show_users(us);
      do
      {
        scanf("%i", &eleccion);
        getchar();
      }while(val_npos(eleccion, 0) == FAIL);
      elm = find_user(eleccion, us->front);
    }while( val_mem( (void *) elm) );

    printf("Procesando...\n");
    if(elm->pcbU->front != NULL)
    {
      printf("Calculando la cantidad de procesos relacionados...\n");
      int tam = list_lenghtU( elm->pcbU );
      i = 0;

      if(tam > 0)
      {
        temp = elm->pcbU->front;
        do
        {
          if(temp->state == 4)
          i++;
        }while( next_pcbU(&temp, elm->pcbU->front) != FAIL);
      }
      printf("Procesos relacionados:\nDormidos: %i Otros:%i\n", i, tam);

      if(i == tam)
      {
        printf("Eliminando procesos relacionados al usuario...\n");
        do //Ciclo para eliminar los procesos relacionados al usuario
        {
          if(elm->pcbU->front == elm->pcbU->rear)
          {
            del_pcss_reaper(ctrl, states, elm->pcbU->front);
            elm->pcbU->rear = elm->pcbU->front = NULL;
            break;
          }
          else
          {
            pcb *aux = elm->pcbU->front;
            elm->pcbU->front = elm->pcbU->front->userSense->next;
            elm->pcbU->front->userSense->prev = elm->pcbU->rear;
            elm->pcbU->rear->userSense->next = elm->pcbU->front;
            del_pcss_reaper(ctrl, states, aux);
          }
        }while(1);
        printf("Procesos eliminados.\n");

        printf("Eliminando usuario...\n");
        if(us->front == us->rear)
        us->front = us->rear = NULL;
        else
        if(elm == us->front)
        {
          us->front = us->front->sense->next;
          us->front->sense->prev = us->rear;
          us->rear->sense->next = us->front;
        }
        else
        if(elm == us->rear)
        {
          us->rear = us->rear->sense->prev;
          us->front->sense->prev = us->rear;
          us->rear->sense->next = us->front;
        }
        else
        {
          elm->sense->next->sense->prev = elm->sense->prev;
          elm->sense->prev->sense->next = elm->sense->next;
        }
        free( elm );
        printf("Usuario eliminado.\n");
      }
      else
      printf("No se puede eliminar el grupo, tiene procesos pendientes.\n");
    }
    else
    {
      if(us->front == us->rear)
      us->front = us->rear = NULL;
      else
      if(elm == us->front)
      {
        us->front = us->front->sense->next;
        us->front->sense->prev = us->rear;
        us->rear->sense->next = us->front;
      }
      else
      if(elm == us->rear)
      {
        us->rear = us->rear->sense->prev;
        us->front->sense->prev = us->rear;
        us->rear->sense->next = us->front;
      }
      else
      {
        elm->sense->next->sense->prev = elm->sense->prev;
        elm->sense->prev->sense->next = elm->sense->next;
      }
      free( elm );
    }

  }
  else
    printf("No existen usuarios.\n");

}
/*0_Eliminacion de usuario junto con sus procesos*/

int set_user(users **u,usersCtrl *ctrlU)
{
  int uid,flag = 1;
  do
  {
    printf("\n%s %s\n",SELEC, "un usuario");
    show_users(ctrlU);
    printf(">");
    scanf("%i",&uid);
    getchar();

    *u = find_user(uid,ctrlU->front);
    if(u != NULL)
      break;
    else
    {
      printf("%s\n",FIND_FAIL);
      if(cancel("creacion del proceso") == 1)
      {
        flag = FAIL;
        break;
      }
    }
  }while(1);

  return flag;
}

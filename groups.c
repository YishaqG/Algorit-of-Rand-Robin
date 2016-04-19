/*Prototipos de funciones*/
groups* create_group_mem();//Crea memoria para un grupo
int set_gid(groups *front);
void create_group(groupsCtrl *ctrlG); //Crea un grupo
void show_groups(groupsCtrl *ctrlG); //Muestra los grupos
groups* find_group(int gid,groups *front); //Busca el grupo a imprimir
int next_group(groups **aux, groups *f);//Para desplazarse.
int prev_group(groups **aux, groups *r);//Para desplazarse.
int del_grupo(pcbCtrl *ctrl, pcbStates *states, groupsCtrl *gp);
int list_lenghtG(pcbCtrl *ctrl);
int set_group(groups **g, groupsCtrl *ctrlG);
int check_name(groups *front,char*n);
int repeat_names(groups *front,char *name);

/*Crea la memoria para alojar un grupo*/
groups* create_group_mem()
{
  groups *temp;
  temp = (groups *)malloc(sizeof(groups));

  temp->pcbG = (pcbCtrl *)malloc(sizeof(pcbCtrl));
  temp->pcbG->front = NULL;
  temp->pcbG->rear = NULL;

  temp->sense = (groupsMov *)malloc(sizeof(groupsMov));
  temp->sense->next = NULL;
  temp->sense->prev = NULL;
  temp->gid = -1;
  strcpy(temp->n," ");

  return temp;
}

/*Para desplazarse al siguiente grupo de la lista*/
int next_group(groups **aux, groups *f)
{
  int b = 0;
  if(((**aux).sense->next == NULL) || ((**aux).sense->next == f))
    b = FAIL;
  else
    *aux = (**aux).sense->next; //Desplazamiento al siguiente elemento
  return b;
}

/*Para desplazarse al grupo anterior de la lista*/
int prev_group(groups **aux,groups *r)
{
  int b = 0;
    if((**aux).sense->prev == r)
      b = FAIL;
    else
      *aux = (**aux).sense->prev; //Desplazamiento al siguiente elemento

  return b;
}

/*Evalua si el id de un grupo ha sido repetido y de ser
asi pregunta por otro o cancela la creacion del proceso*/
int set_gid(groups *front)
{
  int gid,flag = 0;
  groups *f = front;
  if(front == NULL)
    gid = set_int("el id del nuevo grupo",0);
  else
  {
    gid = set_int("el id del nuevo grupo",0);
    do
    {
      if(gid == f->gid)
      {
        flag = FAIL;
        break;
      }
    }while(next_group(&f,front) != FAIL);
    if(flag == FAIL)
    {
      printf("%s\n",REP_FAIL);
      if(cancel("creacion del grupo") == 0)
        gid = set_gid(front);
      else
        gid = FAIL;
    }
  }

  return gid;
}
/**/

/*Crea un nuevo grupo*/
void create_group(groupsCtrl *ctrlG)
{
  int gid;
  char *name = create_string_mem(TAM_BUFF);
  if((gid = set_gid(ctrlG->front)) > 0)
  {
    if(check_name(ctrlG->front,name) >= 0)
    {
      if(ctrlG->front == NULL)
      {
        ctrlG->front = create_group_mem();
        if(ctrlG->front != NULL)
        {
          strcpy(ctrlG->front->n, name);
          ctrlG->front->gid = gid;
          ctrlG->rear = ctrlG->front;
          free(name);
        }
        else printf("%s",MEM_FAIL);
      }
      else
      {
        ctrlG->rear->sense->next = create_group_mem();
        if(ctrlG->rear->sense->next != NULL)
        {
          ctrlG->rear->sense->next->sense->prev = ctrlG->rear; //?
          ctrlG->rear = ctrlG->rear->sense->next;

          strcpy(ctrlG->rear->n, name);
          ctrlG->rear->gid = gid;

          ctrlG->rear->sense->next = ctrlG->front;
          ctrlG->front->sense->prev = ctrlG->rear;
          free(name);
        }
        else printf("%s",MEM_FAIL);
      }
    }
  }
}

/*Muestra los grupos esxistentes*/
void show_groups(groupsCtrl *ctrlG)
{
  groups *f;
  if(ctrlG->front != NULL)
  {
    f = ctrlG->front;

  printf("    GRUPOS EXISTENTES\n");
    printf("|%7s|%15s|\n","ID","Descripcion");
    printf("=========================\n");
    do
    {
      printf("|(%5i)|%15s|\n",f->gid,f->n);
    }while(next_group(&f,ctrlG->front) != FAIL);
    printf("\n");
  }
  else
    printf("No se han creado grupos.\n");
}

/*Encuentra un grupo por id*/
groups* find_group(int gid, groups *front)
{
  groups *chosen,*aux = front;
  chosen = NULL;
  do
  {
    if(gid == aux->gid)
    {
      chosen = aux;
      break;
    }
  }while(next_group(&aux,front) != FAIL);
  return chosen;
}

/*1_Eliminacion de grupo junto con sus procesos*/
int del_grupo(pcbCtrl *ctrl, pcbStates *states, groupsCtrl *gp)
{
  int i;
  pcb *temp;
  printf("\n<< Eliminación de grupo >>\n");
  if( gp->front != NULL )
  {
    int eleccion; //Eleccion de grupo
    groups *elm = NULL; //Grupo

    do
    {
      printf("%s el grupo a eliminar:\n",SELEC);
      show_groups(gp);
      do
      {
        printf("\n>");
        scanf("%i", &eleccion);
        getchar();
      }while(val_npos(eleccion, 0) == FAIL);
      elm = find_group(eleccion, gp->front);
    }while( val_mem( (void *) elm) );

    printf("Procesando...\n");
    if( elm->pcbG->front != NULL )
    {
      printf("Calculando la cantidad de procesos relacionados...\n");
      int tam = list_lenghtG( elm->pcbG ); //Obtenemos la cantidad de procesos relacionados con el grupo
      if(tam > 0) //Comprobamos tener al menos un proceso
      {
        i = 0;
        temp = elm->pcbG->front;
        do //Ciclo para recorrer todos los procesos relacionados y contar los dormidos
        {
          if(temp->state == ID_DOR)
            i++;
        }while( next_pcbG(&temp, elm->pcbG->front) != FAIL);
      }
      printf("Procesos relacionados:\nDormidos: %i Otros:%i\n", i, tam);

      if(i == tam) //El número de procesos dormidos es igual a la cantidad de procesos que tenemos
      {
        printf("Eliminando procesos relacionados al grupo...\n");
        do //Ciclo para eliminar los procesos relacionados al grupo
        {
          if(elm->pcbG->front == elm->pcbG->rear)
          {
            del_pcss_reaper(ctrl, states, elm->pcbG->front);
            elm->pcbG->rear = elm->pcbG->front = NULL;
            break;
          }
          else
          {
            pcb *aux = elm->pcbG->front;
            elm->pcbG->front = elm->pcbG->front->groupSense->next;
            elm->pcbG->front->groupSense->prev = elm->pcbG->rear;
            elm->pcbG->rear->groupSense->next = elm->pcbG->front;
            del_pcss_reaper(ctrl, states, aux);
          }
        }while(1);
        printf("Procesos eliminados.\n");

        printf("Eliminando grupo...\n");
        if(gp->front == gp->rear) //Caso en el que solo haya un grupo en la lista de grupos
          gp->front = gp->rear = NULL;
        else
          if(elm == gp->front)  //Caso en el que el grupo a eliminar sea el primero de la lista
          {
            gp->front = gp->front->sense->next;
            gp->front->sense->prev = gp->rear;
            gp->rear->sense->next = gp->front;
          }
          else
            if(elm == gp->rear) //Caso en el que el grupo a eliminar sea el ultimo de la lista
            {
              gp->rear = gp->rear->sense->prev;
              gp->front->sense->prev = gp->rear;
              gp->rear->sense->next = gp->front;
            }
            else  //Caso en el que el grupo a eliminar sea cualquier otro elemento
            {
              elm->sense->next->sense->prev = elm->sense->prev;
              elm->sense->prev->sense->next = elm->sense->next;
            }
        free( elm );
        printf("Grupo eliminado.\n");
      }
      else
      printf("No se puede eliminar el grupo, tiene procesos pendientes.\n");
    }
    else
    {
      if(gp->front == gp->rear) //Caso en el que solo haya un grupo en la lista de grupos
        gp->front = gp->rear = NULL;
      else
        if(elm == gp->front)  //Caso en el que el grupo a eliminar sea el primero de la lista
        {
          gp->front = gp->front->sense->next;
          gp->front->sense->prev = gp->rear;
          gp->rear->sense->next = gp->front;
        }
        else
          if(elm == gp->rear) //Caso en el que el grupo a eliminar sea el ultimo de la lista
          {
            gp->rear = gp->rear->sense->prev;
            gp->front->sense->prev = gp->rear;
            gp->rear->sense->next = gp->front;
          }
          else  //Caso en el que el grupo a eliminar sea cualquier otro elemento
          {
            elm->sense->next->sense->prev = elm->sense->prev;
            elm->sense->prev->sense->next = elm->sense->next;
          }
      free( elm );
    }
  }
  else
    printf("No existen grupos.\n");
}
/*0_Eliminacion de grupo junto con sus procesos*/
/*1_Retorna la cantidad de nodos de una lista*/
int list_lenghtG(pcbCtrl *ctrl)
{
  int i = 1;
  pcb *front = ctrl->front;
  while(next_pcbG(&front,  ctrl->front) != FAIL)
    i++;
  return i;
}
/*0_list_lenght*/

int set_group(groups **g, groupsCtrl *ctrlG)
{
  int gid,flag = 1;
  do
  {
    printf("\n%s un grupo\n\n",SELEC);
    show_groups(ctrlG);
    printf(">");
    scanf("%i",&gid);
    getchar();

    *g = find_group(gid,ctrlG->front);
    if(g != NULL)
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


/**/
int repeat_names(groups *front,char *name)
{
  int flag = 0;
  groups *f = front;
  if(front != NULL)
  {
    do
    {
      if(strcmp(f->n,name) == 0)
      {
        flag = FAIL;
        break;
      }
    }while(next_group(&f,front) != FAIL);
  }

  return flag;
}

/**/
int check_name(groups *front,char*n)
{

  int aux,flag = 0;
  do
  {
    printf("Ingrese el nombre del nuevo grupo: \n");
    printf(">");
    scanf("%[^\n]", n);

    if(strlen(n) > TAM_BUFF)
    {
      if(cancel("creacion del grupo") == 0)
      {
        check_name(front,n);
        break;
      }
      else
      {
        flag = FAIL;
        break;
      }
    }
    else
    {
      if(repeat_names(front,n) == FAIL)
      {
        printf("%s\n",REP_FAIL);
        if(cancel("creacion del grupo") == 0)
        {
          check_name(front,n);
          break;
        }
        else
        {
          flag = FAIL;
          break;
        }
      }
      else
        break;
    }
  }while(1);

  return flag;
}

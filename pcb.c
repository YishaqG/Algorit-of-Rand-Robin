/*Prototipos de funciones*/
pcb* create_pcb_mem();
int next_pcb(pcb **aux,pcb *f);
int prev_pcb(pcb **aux,pcb *r);
int next_pcbG(pcb **aux,pcb *f);
int prev_pcbG(pcb **aux,pcb *f);
int next_pcbU(pcb **aux,pcb *f);
int prev_pcbU(pcb **aux,pcb *f);
int next_pcb_states(pcb **aux,pcb *f);
int prev_pcb_states(pcb **aux,pcb *f);
void print_pcbInfo(pcb *aux);
pcb* find_pcb(int pid, pcb *front);
int can_create(groups *gFront, users *uFront);
int set_pid(pcb *front);
void create_process(int cpp, pcbCtrl *ctrl, pcbStates *states, groupsCtrl *ctrlG, usersCtrl *ctrlU);
int execute(int t,pcb *exec);
void rr(pcbStates *states, pcbCtrl *ctrl, int quantum, int *totalTime);
void show_pcb(pcbCtrl *ctrl);
void show_everything(pcbCtrl *ctrl, pcbStates *states, groupsCtrl *ctrlG, usersCtrl *ctrlU);
int del_pcss(pcbCtrl *ctrl, pcbStates *states);
void del_pcss_reaper(pcbCtrl *ctrl, pcbStates *states, pcb *elm);
void state_change(pcbCtrl *ctrl, pcbStates *states);
void changer(pcbCtrl *lista, pcb *elm,pcbStates *states);
void del_pcss_reaper(pcbCtrl *ctrl, pcbStates *states, pcb *elm);
int show_pcb_sleeping(pcbStates *states);
void del_option(pcbCtrl *ctrl, pcbStates *states, groupsCtrl *gp, usersCtrl *us);
/*Crea la memoria para alojar un proceso*/
pcb* create_pcb_mem()
{
  pcb *temp;
  temp = (pcb *)malloc(sizeof(pcb));
  temp->sense = (pcbMov *)malloc(sizeof(pcbMov *));
  temp->stateSense = (pcbMov *)malloc(sizeof(pcbMov *));
  temp->groupSense = (pcbMov *)malloc(sizeof(pcbMov *));
  temp->userSense = (pcbMov *)malloc(sizeof(pcbMov *));

  temp->group = (groups *)malloc(sizeof(groups *));
  temp->user = (users *)malloc(sizeof(users *));

  temp->sense->next = NULL;
  temp->sense->prev = NULL;

  temp->stateSense->next = NULL;
  temp->stateSense->prev = NULL;

  temp->groupSense->next = NULL;
  temp->groupSense->prev = NULL;

  temp->userSense->next = NULL;
  temp->userSense->prev = NULL;

  strcpy(temp->group->n," ");
  strcpy(temp->user->n," ");
  temp->first_exe = 0;
  temp->user->uid = -1;
  temp->group->gid = -1;
  temp->pid = -1;
  temp->cp = -1;
  temp->tim[0] = -1;
  temp->tim[1] = -1;
  temp->tim[2] = -1;
  temp->state = -1;
  temp->gen = 0;

  return temp;//
}

/*Desplaza al siguiente proceso en una determinada lista*/
int next_pcb(pcb **aux,pcb *f)
{
  int b = 0;
    if( ((**aux).sense->next == NULL) || ((**aux).sense->next == f))
      b = FAIL;
    else
      *aux = (**aux).sense->next; //Desplazamiento al siguiente elemento

  return b;
}

/*Desplaza al proceso anterior en una determinada lista*/
int prev_pcb(pcb **aux,pcb *r)
{
  int b = 0;
    if((**aux).sense->prev == r)
      b = FAIL;
    else
      *aux = (**aux).sense->prev; //Desplazamiento al siguiente elemento

  return b;
}

/*Desplaza al siguiente proceso en una determinada lista*/
int next_pcb_states(pcb **aux,pcb *f)
{
  int b = 0;
    if( ((**aux).stateSense->next == NULL) || ((**aux).stateSense->next == f))
      b = FAIL;
    else
      *aux = (**aux).stateSense->next; //Desplazamiento al siguiente elemento

  return b;
}

int prev_pcb_states(pcb **aux,pcb *f)
{
  int b = 0;
    if( ((**aux).stateSense->prev == NULL) || ((**aux).stateSense->prev == f))
      b = FAIL;
    else
      *aux = (**aux).stateSense->prev; //Desplazamiento al siguiente elemento

  return b;
}


/*Desplaza al siguiente proceso realacionado a cierto grupo*/
int next_pcbG(pcb **aux,pcb *f)
{
  int b = 0;
    if( ((**aux).groupSense->next == NULL) || ((**aux).groupSense->next == f))
      b = FAIL;
    else
      *aux = (**aux).groupSense->next; //Desplazamiento al siguiente elemento

  return b;
}

/*Desplaza al anterior proceso realacionado a cierto grupo*/
int prev_pcbG(pcb **aux,pcb *f)
{
  int b = 0;
    if( ((**aux).groupSense->prev == NULL) || ((**aux).groupSense->prev == f))
      b = FAIL;
    else
      *aux = (**aux).groupSense->prev; //Desplazamiento al siguiente elemento

  return b;
}

/*Desplaza al siguiente proceso relacionado a cierto usuario*/
int next_pcbU(pcb **aux,pcb *f)
{
  int b = 0;
    if( ((**aux).userSense->next == NULL) || ((**aux).userSense->next == f))
      b = FAIL;
    else
      *aux = (**aux).userSense->next; //Desplazamiento al siguiente elemento

  return b;
}

/*Desplaza al anterior proceso relacionado a cierto usuario*/
int prev_pcbU(pcb **aux,pcb *f)
{
  int b = 0;
    if( ((**aux).userSense->prev == NULL) || ((**aux).userSense->prev == f))
      b = FAIL;
    else
      *aux = (**aux).userSense->prev; //Desplazamiento al siguiente elemento

  return b;
}

/*Comprueba si hay  usuarios y grupos creados*/
int can_create(groups *gFront, users *uFront)
{
  int r = 0;
  if(gFront == NULL)
  {
    r = FAIL;
    printf("%s.\n","No se han creado grupos");
    if(uFront == NULL)
      printf("%s.\n","No se han creado usuarios");
  }
  else
  {
    if(uFront == NULL)
    {
      r =FAIL;
      printf("%s.\n","No se han creado usuarios");
    }
  }
  return r;
}

/*Encuentra un proceso*/
pcb* find_pcb(int pid, pcb *front)
{
  pcb *chosen,*aux = front;
  chosen = NULL;
  do
  {
    if(pid == aux->pid)
    {
      chosen = aux;
      break;
    }
  }while(next_pcb(&aux,front) != FAIL);
  return chosen;
}

/*Evalua si el id de un proceso ha sido repetido y de ser
asi pregunta por otro o cancela la creacion del proceso*/
int set_pid(pcb *front)
{
  int pid,flag = 0;
  pcb *f = front;
  if(front == NULL)
    pid = set_int("el id del nuevo proceso",0);
  else
  {
    pid = set_int("el id del nuevo proceso",0);
    do
    {
      if(pid == f->pid)
      {
        flag = FAIL;
        break;
      }
    }while(next_pcb(&f,front) != FAIL);
    if(flag == FAIL)
    {
      printf("%s\n",REP_FAIL);
      if(cancel("creacion del proceso") == 0)
        pid = set_pid(front);
      else
        pid = FAIL;
    }
  }

  return pid;
}
/**/

/*Crea un proceso, lo encola en la tabla de control de procesos conforme a
su momento de llegada y en la cola de listos
Se verifica que el id de proceso sea positivo y que
el grupo y usuario solicitado existan, de no hacerlo
se pregunta si se desea cancelar la operacion

*/
void create_process(int cpp,pcbCtrl *ctrl, pcbStates *states, groupsCtrl *ctrlG, usersCtrl *ctrlU)
{
  int p[2];
  groups *g;
  users *u;
  if(can_create(ctrlG->front,ctrlU->front) != FAIL)
  {
    if((p[0] = set_pid(ctrl->front)) > 0)
    {
      if((p[1] = set_int("la duracion del proceso",0)) > 0)
      {
        if(set_group(&g,ctrlG) > 0)
        {
          if(set_user(&u,ctrlU) > 0)
          {
            if(ctrl->front == NULL)//se verifica si hay procesos creados anteriormente
            {
              ctrl->front = create_pcb_mem();//se asigna la memoria para el proceso
              if(ctrl->front != NULL)
              {
                /*Asignacion de los campos al nuevo proceso*/
                printf("\nAsignando informacion al proceso...\n");
                ctrl->front->cp = cpp;
                ctrl->front->state = ID_LIS;
                ctrl->front->pid = p[0];
                ctrl->front->tim[0] = p[1];
                ctrl->front->tim[1] = p[1];
                ctrl->front->tim[2] = 0;
                ctrl->front->gen = -1;
                ctrl->front->user = u;
                ctrl->front->group = g;

                /*asignación del proceso a la lista de
                procesos del grupo correspondiente*/
                printf("Ligando proceso con su grupo...\n");
                g->pcbG->front = ctrl->front;
                g->pcbG->rear = g->pcbG->front;
                g->pcbG->rear->groupSense->prev = g->pcbG->front;
                g->pcbG->front->groupSense->prev = g->pcbG->rear;
                g->pcbG->front->groupSense->next = g->pcbG->rear;
                g->pcbG->rear->groupSense->next = g->pcbG->front;

                /*asignación del proceso a la lista de
                procesos del usuario correspondiente*/
                printf("Ligando proceso con su usuario...\n");
                u->pcbU->front = ctrl->front;
                u->pcbU->rear = u->pcbU->front;
                u->pcbU->rear->userSense->prev = u->pcbU->front;
                u->pcbU->front->userSense->prev = u->pcbU->rear;
                u->pcbU->front->userSense->next = u->pcbU->rear;
                u->pcbU->rear->userSense->next = u->pcbU->front;

                /*Se hace circular la lista que controla la pcb*/
                ctrl->rear = ctrl->front; //Igualamos el frente y el fondo
                ctrl->rear->sense->next = ctrl->front;
                ctrl->rear->sense->prev = ctrl->front;
                ctrl->front->sense->prev = ctrl->rear;
                ctrl->front->sense->next = ctrl->rear;

                /*Asignamos la lista de ejecucion */
                printf("Encolando elemento a la lista de ejecucion...\n");
                states->readys->front = ctrl->front;
                states->readys->rear = states->readys->front;
                states->readys->rear->stateSense->next = states->readys->front;
                states->readys->rear->stateSense->prev = states->readys->front;
                states->readys->front->sense->prev = states->readys->rear;
                states->readys->front->stateSense->next = states->readys->rear;
                printf("Proceso creado.\n");
              }
              else
                printf("%s\n",MEM_FAIL);
            }
            else
            {
              ctrl->rear->sense->next = create_pcb_mem();//se asigna a memoria para el proceso
              if(ctrl->rear->sense->next != NULL)//se verifica la creacion de la memoria
              {
                ctrl->rear->sense->next->sense->prev = ctrl->rear;
                ctrl->rear = ctrl->rear->sense->next;
                ctrl->rear->sense->next = ctrl->front;
                ctrl->front->sense->prev = ctrl->rear;

                printf("\nAsignando informacion al proceso...\n");
                ctrl->rear->cp = cpp;
                ctrl->rear->state = ID_LIS;
                ctrl->rear->pid = p[0];
                ctrl->rear->tim[0] = p[1];
                ctrl->rear->tim[1] = p[1];
                ctrl->rear->tim[2] = 0;
                ctrl->rear->gen = 1;
                ctrl->rear->user = u;
                ctrl->rear->group = g;

                if(ctrl->rear->sense->prev->gen != -1)
                  ctrl->rear->sense->prev->gen = 0;

                /*Asignación del proceso a la lista de
                procesos del grupo correspondiente*/
                /*En caso de que el grupo no tenga procesos
                asignados  */
                printf("Ligando proceso con su grupo...\n");
                if(g->pcbG->front == NULL)
                {
                  g->pcbG->front = ctrl->rear;
                  g->pcbG->rear = g->pcbG->front;
                  g->pcbG->rear->groupSense->prev = g->pcbG->front;
                  g->pcbG->front->groupSense->prev = g->pcbG->rear;
                  g->pcbG->front->groupSense->next = g->pcbG->rear;
                  g->pcbG->rear->groupSense->next = g->pcbG->front;
                }
                /*Caso en el que ya existan procesos con el
                grupo elegido*/
                else
                {
                  g->pcbG->rear->groupSense->next = ctrl->rear;
                  g->pcbG->rear->groupSense->next->groupSense->prev = ctrl->rear;
                  g->pcbG->rear = g->pcbG->rear->groupSense->next;
                  g->pcbG->rear->groupSense->next = g->pcbG->front;
                  g->pcbG->front->groupSense->prev = g->pcbG->rear;
                }

                /*Asignación del proceso a la lista de
                procesos del usuario correspondiente*/
                /*En caso de que el usuario no tenga procesos
                asignados  */
                printf("Ligando proceso con su usuario...\n");
                if(u->pcbU->front == NULL)
                {
                  u->pcbU->front = ctrl->rear;
                  u->pcbU->rear = u->pcbU->front;
                  u->pcbU->rear->userSense->prev = u->pcbU->front;
                  u->pcbU->front->userSense->prev = u->pcbU->rear;
                  u->pcbU->front->userSense->next = u->pcbU->rear;
                  u->pcbU->rear->userSense->next = u->pcbU->front;
                }
                /*Caso en el que ya existan procesos con el
                usuario elegido*/
                else
                {
                  u->pcbU->rear->userSense->next = ctrl->rear;
                  u->pcbU->rear->userSense->next->userSense->prev = ctrl->rear;
                  u->pcbU->rear = u->pcbU->rear->userSense->next;
                  u->pcbU->rear->userSense->next = u->pcbU->front;
                  u->pcbU->front->userSense->prev = u->pcbU->rear;
                }

                printf("Encolando elemento a la lista de ejecucion...\n");
                if(states->readys->front == NULL)
                {
                  states->readys->front = ctrl->rear;
                  states->readys->rear = states->readys->front;
                  states->readys->rear->stateSense->next = states->readys->front;
                  states->readys->rear->stateSense->prev = states->readys->front;
                  states->readys->front->sense->prev = states->readys->rear;
                  states->readys->front->stateSense->next = states->readys->rear;
                }
                else
                {
                  states->readys->rear->stateSense->next = ctrl->rear;
                  states->readys->front->stateSense->prev = ctrl->rear;
                  states->readys->rear->stateSense->next->stateSense->prev = ctrl->rear;
                  states->readys->rear = states->readys->rear->stateSense->next;
                  states->readys->rear->stateSense->next = states->readys->front;
                }
                printf("Proceso creado.\n");
              }
              else
              printf("%s\n",MEM_FAIL);
            }
          }
        }
      }
    }
  }
}

/*Imprime los campos que tiene un  proceso*/
void print_pcbInfo(pcb *aux)
{
  printf("|%6i|", aux->pid);
  printf("%4i|", aux->cp);
  printf("%4i", aux->group->gid);
  printf("%16s|",aux->group->n);
  printf("%4i", aux->user->uid);
  printf("%16s|",aux->user->n);
  printf("%5i|", aux->tim[0]);
  printf("%8i|", aux->tim[1]);
  printf("%9i|", aux->tim[2]);

  switch(aux->state)
  {
    case 1:
      printf("%10s|", EJEC);
      break;
    case 2:
      printf("%10s|", LIS);
      break;
    case 3:
      printf("%10s|", ESP);
      break;
    case 4:
      printf("%10s|", DOR);
      break;
  }

  printf("\n");

  aux = NULL;
}

/*Ejecuta el siguiente proceso en la cola de listos con el
algoritmo de despacho Round Robin*/
void rr(pcbStates *states, pcbCtrl *ctrl, int quantum, int *totalTime)
{
  pcb *temp,*f = states->readys->front;
  if(states->readys->front != NULL)
  {
    if(states->readys->front->first_exe == 0)
    {
      if(states->readys->front == states->readys->rear)
      {
        printf("Proceso comenzando ejecución en tiempo: %i\n\n",*totalTime);
        states->readys->front->state = ID_EJEC;
        states->readys->front->first_exe = 1;
        if(states->readys->front->tim[1] <= quantum)
        {
          *totalTime += execute(quantum,states->readys->front);
          printf("\nProceso terminando ejecucion en tiempo: %i\n\n",*totalTime);
          temp = find_pcb(states->readys->front->pid,ctrl->front);
          temp->state = ID_LIS;
          changer(states->sleeping,temp,states);
          temp->state = ID_DOR;
        }
        else
        {
          *totalTime += execute(quantum,states->readys->front);
          printf("\nProceso terminando ejecucion en tiempo: %i\n\n",*totalTime);
          temp = states->readys->front;
          temp->state = ID_LIS;
          changer(states->waiting, states->readys->front, states);
          temp->state = ID_ESP;
        }
      }
      else
      {
        printf("Proceso comenzando ejecución en tiempo: %i\n\n",*totalTime);
        states->readys->front->state = ID_EJEC;
        if(states->readys->front->tim[1] <= quantum)
        {
          *totalTime += execute(quantum,states->readys->front);
          printf("\nProceso terminando ejecucion en tiempo: %i\n\n",*totalTime);
          temp = find_pcb(states->readys->front->pid,ctrl->front);
          temp->state = ID_LIS;
          changer(states->sleeping,temp,states);
          temp->state = ID_DOR;
        }
        else
        {
          *totalTime += execute(quantum,states->readys->front);
          printf("\nProceso terminando ejecucion en tiempo: %i\n\n",*totalTime);
          temp = states->readys->front;
          temp->state = ID_LIS;
          changer(states->waiting, states->readys->front, states);
          temp->state = ID_ESP;
        }
      }
      temp->first_exe = 1;
    }
    else
    {
      if(states->readys->front == states->readys->rear)
      {
        printf("Proceso comenzando ejecución en tiempo: %i\n\n",*totalTime);
        states->readys->front->state = ID_EJEC;
        if(states->readys->front->tim[1] <= quantum)
        {
          *totalTime += execute(states->readys->front->tim[1],states->readys->front);
          printf("Proceso terminando ejecucion en tiempo: %i\n\n",*totalTime);
          temp = states->readys->front;
          temp->state = ID_LIS;
          changer(states->sleeping,temp,states);
          temp->state = ID_DOR;
        }
        else
        {
          *totalTime += execute(quantum,states->readys->front);
          printf("Proceso terminando ejecucion en tiempo: %i\n\n",*totalTime);
          states->readys->front->state = ID_LIS;
        }
      }
      else
      {
        printf("Proceso comenzando ejecución en tiempo: %i\n\n",*totalTime);
        states->readys->front->state = ID_EJEC;
        if(states->readys->front->tim[1] <= quantum)
        {
          *totalTime += execute(states->readys->front->tim[1],states->readys->front);
          printf("Proceso terminando ejecucion en tiempo: %i\n\n",*totalTime);
          temp = states->readys->front;
          temp->state = ID_LIS;
          changer(states->sleeping,temp,states);
          temp->state = ID_DOR;
        }
        else
        {
          *totalTime += execute(quantum,states->readys->front);
          printf("Proceso terminando ejecucion en tiempo: %i\n\n",*totalTime);
          states->readys->front->state = ID_LIS;
          states->readys->front->stateSense->next->stateSense->prev = states->readys->rear;
          states->readys->rear = states->readys->front;
          states->readys->front = states->readys->front->stateSense->next;
        }
      }
    }
  }
  else
    printf("%s\n",EMPTY_FAIL);
}

/*Hace que se ejecute un proceso por un tiempo maximo*/
int execute(int t,pcb *exec)
{
  int i;
  for(i = 0; i < t; i++)
  {
    if(exec->tim[1] > 0)
    {
      exec->tim[1]--;
      exec->tim[2]++;
    }
    else
      break;
    print_options(2);
    print_pcbInfo(exec);
    printf("\n");
  }

  return i;
}

/*Muestra los procesos existentes de acuerdo a su momento
  de llegada*/
void show_pcb(pcbCtrl *ctrl)
{
  if(ctrl->front != NULL)
  {
    pcb *f = ctrl->front;
    printf("\t\tTABLA DE PROCESOS\n\n");
    print_options(2);
    do
    {
      print_pcbInfo(f);
    }while(next_pcb(&f, ctrl->front) != FAIL);
    printf("\n");
  }

}
/*Muestra los procesos en funcion a lo que el usuario quiera
ver, puede ser por estado, grupo, usuario, o momento de
llegada y además da la opcion de mostrarlo desde el inicio
de la lista seleccionada o desde su fin*/
void show_everything(pcbCtrl *ctrl, pcbStates *states, groupsCtrl *ctrlG, usersCtrl *ctrlU)
{
  int ch,what, how;
  users *user;
  groups *group;
  int state, gid, uid;
  pcb *f, *r;

  do
  {
    printf("%s que desea ver\n",SELEC);
    print_options(3);
    printf("(4) Cancelar.\n");
    printf("\n>");
    scanf("%i",&ch);
    getchar();

    switch(ch)
    {
      case 1:
      if(ctrlG->front != NULL)
        show_groups(ctrlG);
      else
        printf("No hay grupos\n");
        break;
      case 2:
        if(ctrlU->front != NULL)
          show_users(ctrlU);
        else
        printf("No hay usuarios\n");
        break;
      case 3:
        if(ctrl->front != NULL)
        {
          do
          {
            print_options(1);
            printf("(5) Cancelar.\n");
            printf("\n>");
            scanf("%i",&what);
            getchar();
            if(what != 5)
            {
              do
              {
                printf("\n%s desde donde comenzar a ver los procesos.\n",SELEC);
                printf("(1) Desde el inicio.\n(2) Desde el fin.\n(3) Cancelar.\n");
                printf("\n>");
                scanf("%i",&how);
                getchar();

                if(how == 1)
                {
                  switch(what)
                  {
                    /*Muestra los procesos por estado a partir del inicio*/
                    case 1:
                      state = print_states(0);
                      switch(state)
                      {
                        case 1:
                          printf("%s en ejecucion·\n",EMPTY_FAIL);
                          break;
                        case 2:
                          if(states->readys->front != NULL)
                          {
                            f = states->readys->front;
                            printf("\t\t\t<< PROCESOS LISTOS PARA EJECUTARSE >>\n");
                            print_options(2);
                            do
                            {
                              print_pcbInfo(f);
                            }while(next_pcb_states(&f, states->readys->front) != FAIL);
                          }
                          else
                            printf("%s listos para ejecutarse·\n",EMPTY_FAIL);
                          break;
                        case 3:
                          if(states->waiting->front != NULL)
                          {
                            f = states->waiting->front;
                            printf("\t\t\t<< PROCESOS ESPERANDO EVENTO PARA EJECUTARSE >>\n");
                            print_options(2);
                            do
                            {
                              print_pcbInfo(f);
                            }while(next_pcb_states(&f, states->waiting->front) != FAIL);
                          }
                          else
                            printf("%s en espera de eventos·\n",EMPTY_FAIL);
                          break;
                        case 4:
                          if(states->sleeping->front != NULL)
                          {
                            f = states->sleeping->front;
                            printf("\t\t\t\t<< PROCESOS DORMIDOS >>\n");
                            print_options(2);
                            do
                            {
                              print_pcbInfo(f);
                            }while(next_pcb_states(&f, states->sleeping->front) != FAIL);
                          }
                          else
                            printf("%s dormidos·\n",EMPTY_FAIL);
                          break;
                      }
                      break;
                    /*Muestra los procesos por grupo a partir del inicio*/
                    case 2:
                      printf("%s el grupo del que desea ver sus procesos.\n",SELEC);
                      show_groups(ctrlG);
                      printf("\n>");
                      scanf("%i",&gid);
                      getchar();
                      group = find_group(gid,ctrlG->front);
                      if(group->pcbG->front != NULL)
                      {
                        printf("\t\t\t\t<< PROCESOS DEL GRUPO %s >>\n",group->n);
                        print_options(2);
                        f = group->pcbG->front;
                        do
                        {
                          print_pcbInfo(f);
                        }while(next_pcbG(&f,group->pcbG->front) != FAIL);
                      }
                      else
                        printf("%s pertenecientes a grupo seleccionado.\n",EMPTY_FAIL);
                      break;
                    /*Muestra los procesos por usuario a partir del inicio*/
                    case 3:
                      printf("%s el usuario de los procesos a mostrar.\n",SELEC);
                      show_users(ctrlU);
                      printf("\n>");
                      scanf("%i",&uid);
                      getchar();
                      user = find_user(uid,ctrlU->front);
                      if(user->pcbU->front != NULL)
                      {
                        printf("\t\t\t\t<< PROCESOS DEL USUARIO %s >>\n",user->n);
                        print_options(2);
                        f = user->pcbU->front;
                        do
                        {
                          print_pcbInfo(f);
                        }while(next_pcbU(&f,user->pcbU->front) != FAIL);
                      }
                      else printf("%s pertenecientes al usuario seleccionado·\n",EMPTY_FAIL);
                      break;
                    /*Muestra los procesos por momento de llegada a partir del inicio*/
                    case 4:
                      f = ctrl->front;
                      printf("\t\t\t\t<< TABLA DE PROCESOS >>\n\n");
                      print_options(2);
                      do
                      {
                        print_pcbInfo(f);
                      }while(next_pcb(&f, ctrl->front) != FAIL);
                      break;
                  }

                }
                else if(how == 2)
                {
                  switch(what)
                  {
                    /*Muestra los procesos por estado a partir del fin*/
                    case 1:
                      state = print_states(0);
                      switch(state)
                      {
                        case 1:
                          printf("%s en ejecucion.\n",EMPTY_FAIL);
                          break;
                        case 2:
                          if(states->readys->front != NULL)
                          {
                            r = states->readys->rear;
                            printf("\t\t\t<< PROCESOS LISTOS PARA EJECUTARSE >>\n");
                            print_options(2);
                            do
                            {
                              print_pcbInfo(r);
                            }while(prev_pcb_states(&r, states->readys->rear) != FAIL);
                          }
                          else printf("%s listos para ejecutarse.\n",EMPTY_FAIL);
                          break;
                        case 3:
                          if(states->waiting->front != NULL)
                          {
                            r = states->waiting->rear;
                            printf("\t\t\t<< PROCESOS ESPERANDO EVENTO PARA EJECUTARSE >>\n");
                            print_options(2);
                            do
                            {
                              print_pcbInfo(r);
                            }while(prev_pcb_states(&r, states->waiting->rear) != FAIL);
                          }
                          else printf("%s esperando eventos.",EMPTY_FAIL);
                          break;
                        case 4:
                          if(states->sleeping->front)
                          {
                            r = states->sleeping->rear;
                            printf("\t\t<< PROCESOS DORMIDOS >>\n");
                            print_options(2);
                            do
                            {
                              print_pcbInfo(r);
                            }while(prev_pcb_states(&r, states->sleeping->rear) != FAIL);
                          }
                          else printf("%s dormidos.\n",EMPTY_FAIL);
                          break;
                      }
                      break;
                    /*Muestra los procesos por grupo a partir del fin*/
                    case 2:
                      printf("%s el grupo del que desea ver sus procesos.\n",SELEC);
                      show_groups(ctrlG);
                      printf("\n>");
                      scanf("%i",&gid);
                      getchar();
                      group = find_group(gid,ctrlG->front);
                      if(group->pcbG->front != NULL)
                      {
                        printf("\t\t<< PROCESOS DEL GRUPO %s >>\n",group->n);
                        print_options(2);
                        r = group->pcbG->rear;
                        do
                        {
                          print_pcbInfo(r);
                        }while(prev_pcbG(&r,group->pcbG->rear) != FAIL);
                      }
                      else printf("%s pertenecientes al grupo seleccionado.\n",EMPTY_FAIL);
                      break;
                    /*Muestra los procesos por usuario a partir del fin*/
                    case 3:
                      printf("%s el usuario de los procesos a mostrar.\n",SELEC);
                      show_users(ctrlU);
                      printf("\n>");
                      scanf("%i",&uid);
                      getchar();
                      user = find_user(uid,ctrlU->front);
                      if(user->pcbU->front != NULL)
                      {
                        printf("\t\t<< PROCESOS DEL USUARIO %s >>\n",user->n);
                        print_options(2);
                        r = user->pcbU->rear;
                        do
                        {
                          print_pcbInfo(r);
                        }while(prev_pcbU(&r,user->pcbU->rear) != FAIL);
                      }
                      else printf("%s pertenecientes al usuario seleccionado\n",EMPTY_FAIL);
                      break;
                    /*Muestra los procesos por momento de llegada a partir del fin*/
                    case 4:
                      r = ctrl->rear;
                      printf("\t\t\t\t<< TABLA DE PROCESOS >>\n\n");
                      print_options(2);
                      do
                      {
                        print_pcbInfo(r);
                      }while(prev_pcb(&r, ctrl->rear) != FAIL);
                      break;
                  }

                }
                if(how == 3)
                  break;
              }while(how != 3);
            }
          }while(what != 5);
        }
        else
          printf("%s.\n",EMPTY_FAIL);
        break;
      case 4:
        break;
      default:
        printf("%s\n",DEFAULT_FAIL);
    }
  }while(ch != 4);

}

/*1_Eliminacion de un proceso*/
int del_pcss(pcbCtrl *ctrl, pcbStates *states)
{
  pcb *elm;
  if( states->sleeping->front != NULL )
  {
      int eleccion; //Eleccion de grupo
      elm = NULL;

      printf("\n<< Eliminación de proceso >>\n");
      do
      {
        printf("Escoja el proceso a eliminar:\n\n");
        print_options(2);
        if( show_pcb_sleeping(states) )
        {
          do
          {
            printf("\n>");
            scanf("%i", &eleccion);
            getchar();
          }while(val_npos(eleccion, 0) == FAIL);
          elm = find_pcb(eleccion, states->sleeping->front);
        }
      }while( val_mem( (void *) elm) );

      del_pcss_reaper(ctrl, states, elm);

  }
  else
    printf("%s para eliminar. Solo los procesos dormidos pueden ser eliminados.\n",EMPTY_FAIL);
}
/*0_Eliminacion de grupo junto con sus procesos*/

/*Elimina los procesos de la tabla de control y tambien los borra de la lista de dormidos*/
void del_pcss_reaper(pcbCtrl *ctrl, pcbStates *states, pcb *elm)
{
  pcb *aux;
  int flag;

    aux = elm;

  if(aux->gen == FRONT)
  {
    if(ctrl->front->sense->next == ctrl->front)
    {
      //Caso en el que solo exista un proceso creado
      ctrl->rear = ctrl->front = NULL;
    }
    else
    {
      //Caso en el que es el frente pero no es el unico elemento
      ctrl->front = ctrl->front->sense->next;
      ctrl->front->sense->prev = ctrl->rear;
      ctrl->rear->sense->next = ctrl->front;
    }
  }
  else
    if(aux->gen == REAR)
    {
      //Caso en el que es el frente pero no es el unico elemento
      ctrl->rear = ctrl->rear->sense->prev;
      ctrl->front->sense->prev = ctrl->rear;
      ctrl->rear->sense->next = ctrl->front;
    }
    else  //Caso en el que es cualquier otro elemento de la pcb
    {
      elm->sense->next->sense->prev = elm->sense->next;
      elm->sense->prev->sense->next = elm->sense->prev;
    }

  flag = 0;

  //1_Eliminacion del proceso en la lisa de dormidos
  if(states->sleeping->front->stateSense->next == states->sleeping->front)
  {
    states->sleeping->rear = states->sleeping->front = NULL;
    flag++;
  }
  else
    if(elm == states->sleeping->front)
    {
      states->sleeping->front->stateSense->next->stateSense->prev = states->sleeping->rear;
      states->sleeping->front = states->sleeping->front->stateSense->next;
      states->sleeping->rear->stateSense->next = states->sleeping->front;
      flag++;
    }
    else
      if(elm == states->sleeping->rear)
      {
        states->sleeping->rear->stateSense->prev->stateSense->next = states->sleeping->front;
        states->sleeping->rear = states->sleeping->rear->stateSense->prev;
        states->sleeping->front->stateSense->prev = states->sleeping->rear;
        flag++;
      }
      else
      {
        elm->stateSense->prev->stateSense->next = elm->stateSense->next;
        elm->stateSense->next->stateSense->prev = elm->stateSense->prev;
      }
  //0_Eliminacion del proceso en la lista de dormidos

  //1_Eliminacion del proceso en la lista de proceso del grupo
  if(elm->group->pcbG->front == elm->group->pcbG->rear)
    elm->group->pcbG->front = elm->group->pcbG->rear = NULL;
  else
    if(elm == elm->group->pcbG->front)
    {
      elm->group->pcbG->front = elm->groupSense->next;
      elm->group->pcbG->rear->groupSense->next = elm->group->pcbG->front;
      elm->group->pcbG->front->groupSense->prev = elm->group->pcbG->rear;
    }
    else
      if(elm == elm->group->pcbG->rear)
      {
        elm->group->pcbG->rear = elm->groupSense->prev;
        elm->group->pcbG->rear->groupSense->next = elm->group->pcbG->front;
        elm->group->pcbG->front->groupSense->prev = elm->group->pcbG->rear;
      }
      else
      {
        elm->groupSense->next->groupSense->prev = elm->groupSense->prev;
        elm->groupSense->prev->groupSense->next = elm->groupSense->next;
      }
  //0_Eliminacion del proceso en la lista de proceso del grupo

  //1_Eliminacion del proceso en la lista de proceso del usuario
  if(elm->user->pcbU->front == elm->user->pcbU->rear)
    elm->user->pcbU->front = elm->user->pcbU->rear = NULL;
  else
    if(elm == elm->user->pcbU->front)
    {
      elm->user->pcbU->front = elm->userSense->next;
      elm->user->pcbU->rear->userSense->next = elm->user->pcbU->front;
      elm->user->pcbU->front->userSense->prev = elm->user->pcbU->rear;
    }
    else
      if(elm == elm->user->pcbU->rear)
      {
        elm->user->pcbU->rear = elm->userSense->prev;
        elm->user->pcbU->rear->userSense->next = elm->user->pcbU->front;
        elm->user->pcbU->front->userSense->prev = elm->user->pcbU->rear;
      }
      else
      {
        elm->userSense->next->userSense->prev = elm->userSense->prev;
        elm->userSense->prev->userSense->next = elm->userSense->next;
      }
  //0_Eliminacion del proceso en la lista de proceso del usuario

    free( aux );

}
/*0_del_pcss_reaper*/

/*1_state_change Esta funcion cambia de estado un proceso*/
void state_change(pcbCtrl *ctrl, pcbStates *states)
{
  int eleccion, estado,t;
  pcb *elm = NULL;

  if(ctrl->front != NULL)
  {
    do
    {
      do
      {
        printf("\nIntroduzca el ID del proceso al cual desea cambiar su estado:\n");
        show_pcb(ctrl);
        do
        {
          printf("\n>");
          scanf("%i", &eleccion);
          getchar();
        }while(val_npos(eleccion, 0) == FAIL);
        elm = find_pcb(eleccion, ctrl->front);
      }while( val_mem( (void *) elm) );

      printf("\nNuevo estado del proceso:\n");
      estado = print_states(1);

      switch (estado)
      {
        case 2: //Listo
            if( elm->state == ID_DOR )
            {
              do
              {
                printf("Introduzca el nuevo tiempo del proceso:\n>");
                scanf("%i",&t);
                getchar();
              }while(val_npos(t, 0) != FAIL);

              elm->tim[1] = elm->tim[0] = t;
              elm->tim[2] = 0;

              changer( states->readys, elm, states );
              elm->state = ID_LIS;
            }
            else
              if( elm->state == ID_ESP )
              {
                changer( states->readys, elm, states );
                elm->state = ID_LIS;
              }
              else
                printf("No se puede cambiar el proceso a este estado.\n");
          break;
        case 5:
          break;
        default:
          printf("Estado inexistente o imposible operar con el, cambios habilitadsos de Dormido-Listo y de Esperando-Listo.\n");
          printf("Vuelva a intentarlo.\n");
          estado = FAIL;
          break;
      }
    }while(estado == FAIL);
  }
  else
    printf("%s Crea procesos primero.\n", EMPTY_FAIL);

}
/*0_state_change*/

/*1_changer Esta funcion cambia un proceso de una lista a otra*/
void changer(pcbCtrl *lista, pcb *elm, pcbStates *states)
{
  int flag = 0;
  //1_Eliminaion del estado en su lista de estado previo
  switch(elm->state)
  {
    case 2:
      if(states->readys->front->stateSense->next == states->readys->front)
        states->readys->rear = states->readys->front = NULL;
      else
        if(elm == states->readys->front)
        {
          states->readys->front->stateSense->next->stateSense->prev = states->readys->rear;
          states->readys->front = states->readys->front->stateSense->next;
          states->readys->rear->stateSense->next = states->readys->front;
        }
        else
          if(elm == states->readys->rear)
          {
            states->readys->rear->stateSense->prev->stateSense->next = states->readys->front;
            states->readys->rear = states->readys->rear->stateSense->prev;
            states->readys->front->stateSense->prev = states->readys->rear;
          }
      flag++;
      break;
    case 3:
      if(states->waiting->front->stateSense->next == states->waiting->front)
        states->waiting->rear = states->waiting->front = NULL;
      else
        if(elm == states->waiting->front)
        {
          states->waiting->front->stateSense->next->stateSense->prev = states->waiting->rear;
          states->waiting->front = states->waiting->front->stateSense->next;
          states->waiting->rear->stateSense->next = states->waiting->front;
        }
        else
          if(elm == states->waiting->rear)
          {
            states->waiting->rear->stateSense->prev->stateSense->next = states->waiting->front;
            states->waiting->rear = states->waiting->rear->stateSense->prev;
            states->waiting->front->stateSense->prev = states->waiting->rear;
          }
      flag++;
      break;
    case 4:
      if(states->sleeping->front->stateSense->next == states->sleeping->front)
        states->sleeping->rear = states->sleeping->front = NULL;
      else
        if(elm == states->sleeping->front)
        {
          states->sleeping->front->stateSense->next->stateSense->prev = states->sleeping->rear;
          states->sleeping->front = states->sleeping->front->stateSense->next;
          states->sleeping->rear->stateSense->next = states->sleeping->front;
        }
        else
          if(elm == states->sleeping->rear)
          {
            states->sleeping->rear->stateSense->prev->stateSense->next = states->sleeping->front;
            states->sleeping->rear = states->sleeping->rear->stateSense->prev;
            states->sleeping->front->stateSense->prev = states->sleeping->rear;
          }
      flag++;
      break;
  }

  if(flag == 0) //Cualquier otra posicion en las listas
  {
    elm->stateSense->next->stateSense->prev = elm->stateSense->prev;
    elm->stateSense->prev->stateSense->next = elm->stateSense->next;
  }
  //0_Eliminaion del estado en su lista de estado previo

  //Adicion del elemento a la nueva lista
  if(lista->front != NULL)
  {
    elm->stateSense->next = lista->front;
    elm->stateSense->prev = lista->rear;
    lista->front->stateSense->prev = elm;
    lista->rear->stateSense->next = elm;
    lista->rear = elm;
  }
  else
  {
    lista->front = elm;
    lista->rear = elm;
    elm->stateSense->next = elm;
    elm->stateSense->prev = elm;
  }
}
/*1_changer*/

/*1_show_pcb_sleeping*/
int show_pcb_sleeping(pcbStates *states)
{
  int flag = 0;
  if(states->sleeping->front != NULL)
  {
    flag = 1;
    pcb *aux = states->sleeping->front;

    print_pcbInfo( aux );
    while(aux->stateSense->next != states->sleeping->front )
    {
      aux = aux->stateSense->next;
      print_pcbInfo( aux );
    };
  }

  return flag;
}
/*0_show_pcss_sleeping*/

/*1_del_options*/
void del_option(pcbCtrl *ctrl, pcbStates *states, groupsCtrl *gp, usersCtrl *us)
{
  int opc, ban = 0;
  do
  {
    do
    {
      printf("%s lo que se desea eliminar:\n", SELEC);
      printf("(1)Grupo.\n");
      printf("(2)Usuario.\n");
      printf("(3)Proceso.\n");
      printf("\n>");
      scanf("%i", &opc);
      getchar();
    }while( (opc <= 0) && (opc > 3) );

    switch(opc)
    {
      case 1:
        del_grupo(ctrl, states, gp);
        ban++;
        break;
      case 2:
        del_user(ctrl, states, us);
        ban++;
        break;
      case 3:
        del_pcss(ctrl, states);
        ban++;
        break;
      default:
        printf("Opcion invalida.\n");
        ban = cancel("la eliminacion");
    }
  }while( ban == 0 );
}
/*0_del_options*/

/*1_*/

/**/

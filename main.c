#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*#include <unistd.h>
#include <windows.h>*/

#include "statics.h"
#include "pcb.h"
#include "groups.h"
#include "users.h"

typedef struct pcb_p pcb;
typedef struct pcbMov_p pcbMov;
typedef struct pcbCtrl_p pcbCtrl;
typedef struct pcbStates_p pcbStates;

typedef struct groups_p groups;
typedef struct groupsMov_p groupsMov;
typedef struct groupsCtrl_p groupsCtrl;

typedef struct users_p users;
typedef struct usersMov_p usersMov;
typedef struct usersCtrl_p usersCtrl;


#include "statics.c"
#include "groups.c"
#include "users.c"
#include "pcb.c"



int main()
{
  int totalTime;
  totalTime = 0;
  int quantum;
  int op;
  int cpp = 0;
  pcbCtrl *ctrl;
  pcbStates *states;
  groupsCtrl *ctrlG;
  usersCtrl *ctrlU;
  ctrl = malloc(sizeof(pcbCtrl));
  states = malloc(sizeof(pcbStates));
  states->readys = malloc(sizeof(pcbCtrl));
  states->waiting = malloc(sizeof(pcbCtrl));
  states->sleeping = malloc(sizeof(pcbCtrl));
  ctrlG = malloc(sizeof(groupsCtrl));
  ctrlU = malloc(sizeof(usersCtrl));

  printf("\n");

  quantum = set_int("Quantum del programa", 1);

  if(val_npos(quantum, 1) != FAIL)
  {
    do
    {
      printf("\n \t\t<< SIMULACION DE ALGORITMO DE DESPACHO RONUD-ROBIN >>\n");
      print_options(0);
      printf("\n>");
      scanf("%i",&op);
      getchar();

      switch(op)
      {
        case 1:
        printf("\n");
          create_group(ctrlG);
          break;
        case 2:
        printf("\n");
          create_user(ctrlU);
          break;
        case 3:
        printf("\n");
          create_process(cpp,ctrl,states,ctrlG,ctrlU);
          cpp++;
          break;
        case 4:
        printf("\n");
          state_change(ctrl,states);
          break;
        case 5:
        printf("\n");
          show_everything(ctrl,states,ctrlG,ctrlU);
          break;
        case 6:
        printf("\n");
          rr(states, ctrl, quantum, &totalTime);
          break;
        case 7:
        printf("\n");
          del_option(ctrl,states,ctrlG,ctrlU);
          break;
        case 8:
          break;
        default:
          printf("Opcion invalida, vuelva a intentarlo.\n");
      }
    }while(op != 8);

    if(ctrl->front != NULL)
    {
      pcb *aux = ctrl->front;
      while( next_pcb(&aux,ctrl->front) != FAIL )
      free(aux);
    }

    if(ctrlG->front != NULL)
    {
      groups *aux = ctrlG->front;
      while( next_group(&aux,ctrlG->front) != FAIL )
      free(aux);
    }

    if(ctrlU->front != NULL)
    {
      users *aux = ctrlU->front;
      while( next_user(&aux,ctrlU->front) != FAIL )
      free(aux);
    }

    free(ctrl->front);
    free(ctrlG->front);
    free(ctrlU->front);
    free(ctrl);
    free(ctrlG);
    free(ctrlU);
  }

  return 0;
}

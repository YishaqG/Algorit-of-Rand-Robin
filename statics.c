/*Prototipos de funciones*/
int val_num(int x);
int print_states(int flag);
void print_options(int t);
char* create_string_mem(int tam);
int val_npos(int v, int flag);
int cancel(char *s);
int val_mem(void *dat);
int set_int(char what[],int flag);
int set_name(char *name,char what[]);

void print_options(int t)
{
  switch(t)
  {
    case 0:
      printf("%s una accion.\n",SELEC);
      printf("(1) Crear grupo.\n");
      printf("(2) Crear usuario.\n");
      printf("(3) Crear proceso.\n");
      printf("(4) Cambiar el estado de un proceso.\n");
      printf("(5) Mostrar.\n");
      printf("(6) Ejecutar.\n");
      printf("(7) Eliminar.\n");
      printf("(8) Salir.\n");
      break;
    case 1:
      printf("%s como desea ver los procesos.\n",SELEC);
      printf("(1) Por estado.\n");
      printf("(2) Por grupo.\n");
      printf("(3) Por usuario\n");
      printf("(4) Por momento de llegada.\n");
      break;
    case 2:
      printf("\t\t%56s\n","Tiempo");
      printf("|%6s|", "  ID  ");
      printf("%4s|", "CP");
      printf("%20s|", "(ID)Grupo     ");
      printf("%20s|", "(ID)Usuario   ");
      printf("%5s|", "Total");
      printf("%8s|", "Restante");
      printf("%9s|", "Consumido");
      printf("%10s|", " Estado ");
      printf("\n");
      printf("%s","========================================");
      printf("%s","===========");
      printf("%s\n","========================================");
      break;
    case 3:
      printf("(1) Grupos existentes.\n");
      printf("(2) Usuarios existentes.\n");
      printf("(3) Procesos existentes\n");
      break;
    default:
      printf("No hay opciones asignadas.\n");
  }
}

int print_states(int flag)
{
  int est;

  do
  {
    printf("%s un estado.\n",SELEC);
    printf("(1) %s.\n",EJEC);
    printf("(2) %s.\n",LIS);
    printf("(3) %s.\n",ESP);
    printf("(4) %s.\n",DOR);

    if(flag == 1)
      printf("(5) Cancelar");

    scanf("%i",&est);
    getchar();

    switch (est)
    {
      case 1:
        return ID_EJEC;
      case 2:
        return ID_LIS;
      case 3:
        return ID_ESP;
      case 4:
        return ID_DOR;
      default:
        printf("Opcion invalida, vuelva a inentarlo.\n");
        continue;
    }
  }while(1);
}

char* create_string_mem(int tam)
{
  char *memS;
  memS = (char *) malloc(tam * sizeof(char));

  if(memS == NULL)
    printf("%s\n",MEM_FAIL);
  return memS;
}

int val_npos(int v, int flag)
{
  int r = 0;

  if(flag == 0)
  {
    if(v < 0)
    {
      r = FAIL;
      printf("%s\n",NUM0_FAIL);
    }
  }
  else
  {
    if(v <= 0)
    {
      r = FAIL;
      printf("%s\n",NUM1_FAIL);
    }
  }

  return r;
}

/*1_cancel
Esta función es para ver si el usuario desea cancelar la operación que realiza.
Recibe como parametro una cadena, que es para terminar la cadea que imprime la función.
Retorna 1 si el usuario desea terminarlo o 0 si no es así.
*/
int cancel(char *s)
{
  int flag = 0;
  char *temp;
  temp = create_string_mem(TAM_BUFF);

  printf("\nDesea cancelar la %s?(Si/No)\n",s);
  scanf("%s", temp);
  getchar();
  if( !strcmp(temp, "si") || !strcmp(temp, "s") ||
  !strcmp(temp, "Si") || !strcmp(temp, "SI")
   || !strcmp(temp, "S") )
  {
    flag = 1;
  }

  free(temp);
  s = NULL;

  return flag;
}
/*0_cancel*/

/*1_Valida si el dato tiene memoria asignada*/
int val_mem(void *dat)
{
  int i = 1;
  if(dat != NULL)
    i = 0;

  return i;
}
/*0_val_men*/

int set_int(char what[],int flag)
{
  int temp;
  do
  {
    printf("Ingrese %s: \n",what);
    printf(">");
    scanf("%i",&temp);
    getchar();
    if(val_npos(temp,flag) != FAIL)
      break;
    else
    {
      if(cancel("creacion del elemento.") == 1)
      {
        temp = FAIL;
        break;
      }
    }
  }while(1);

  return temp;
}

int set_name(char *name, char what[])
{
  int flag = 0;
  do
  {
    printf("Ingrese el nombre del nuevo %s: \n",what);
    printf(">");
    scanf("%[^\n]", name);

    if(strlen(name) > TAM_BUFF)
    {
      if(cancel("creacion del grupo") == 1)
        break;
      else
      {
        flag = FAIL;
        break;
      }
    }
    else//?
      break;
  }while(1);


  return flag;
}

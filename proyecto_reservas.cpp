/*
  Name: Proyecto 1
  Copyright: 2005 
  Author: Gustavo Bazan & Armando bracho
  Date: 21/04/05
  Description: programa para realizacion de reservas del hotel resort caribbean beach
*/


//Librerias
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h> 

//Declaracion de constantes
#define CANT 100 
#define N 20

//Declaracion de estructuras
struct fecha{
    int dia;
    int mes;
};

struct temp {
	char codigo[N];
};

typedef struct {   
        int posicion;   
        char CI[N];   
        struct fecha inicio, final;
        char suit[N]; 
        char confirmada[N];  
} reserva;

struct serv{   
        int tv;   
        int jacussi;   
};

typedef struct {   
        int posicion;
        int habilitada;   
        char codigo[N]; 
        char ubicacion[N];
		struct serv servicios;
		int tipo;
        int costo;   
} suit;

typedef struct {   
        int posicion;   
        char nombre[N];   
        char apellidos[N];   
        char CI[N];   
        char telefono[N];   
} cliente;



//Declaracion de prototipos
//VARIOS
void info();
void tecla();         /*Pausa*/
int compararcadenas(char *, char *);/*Compara si 2 cadenas son iguales*/
void leerchar(char *);/*Valida un entero*/
int leernum();/*valida una cadena*/
int menu();          /*menu*/
int confirmar();

//CARGAR Y GUARDAR
void cargar(cliente *lista_clientes, suit *lista_suits, reserva *lista_reservas);
void guardar(cliente *lista_clientes, suit *lista_suits, reserva *lista_reservas);

//CLIENTES
int posicionarcliente(cliente *lista_clientes);
int encontrarci(cliente *lista_clientes,char *);
int clientetienereservas(char *, reserva *lista_reservas);
void anadircliente(cliente *lista_clientes);
void mostrarcliente(cliente *lista_clientes);
void eliminarcliente(cliente *lista_clientes, reserva *lista_reservas);
void modificarcliente(cliente *lista_clientes);//FIN CLIENTES

//SUITS
int posicionarsuit(reserva *lista_suits);
int encontrarsuit(suit *lista_suits,char *);
void anadirsuit(suit *lista_suits);
void mostrarsuit(suit *lista_suits);
void buscarsuit(suit *lista_suits,char codigo[N]);
int encontrarreserva2(reserva *lista_reservas,char *);
void deshabilitar(suit *lista_suits, reserva *lista_reservas);
void habilitar(suit *lista_suits);//FIN SUITS

//RESERVAS
int posicionarreserva(reserva *lista_reservas);
int encontrarreserva(reserva *lista_reservas,char *);
void anadirreserva(reserva *lista_reservas, cliente *lista_clientes, suit *lista_suits);
void mostrarreserva(reserva *lista_reservas);
void eliminarreserva(reserva *lista_reservas);
void confirmarreserva(reserva *lista_reservas);//FIN RESERVAS

//LIBRES.OUT
void libre(suit *lista_suits,reserva *lista_reservas,int ,int ,int ,int );
bool validarfecha(int n,int fecha_inicio,int fecha_final);
void mostrarlibres(suit *lista_suits,reserva *lista_reservas);

//NO_CONFIRMADAS.OUT
void noconfirmadas(reserva *lista_reservas);
void mostrarnoconfirmadas();

//MAS DEMANDA
void masdemanda(reserva *lista_reservas);
int numdias(int , int );
bool validarfecha2(int ,int ,int );

//Variable global
struct fecha hoy;

// Cuerpo del programa    
main()
{
      // declaracion de variables locales
      cliente lista_clientes[CANT];   
      suit lista_suits[CANT];   
      reserva lista_reservas[CANT];   
      int respuesta, i;   
      bool d;
      
      /*inicializar las posiciones con 0 porque no tienen datos*/   
      for (i=0;i<CANT;i++) {      
         lista_suits[i].posicion=0;      
         lista_clientes[i].posicion=0;      
         lista_reservas[i].posicion=0;   
      }
	  //info();   
      cargar(lista_clientes, lista_suits, lista_reservas); 
      
      printf("\tPor favor introduzca la fecha actual: ");
      /*coger mes actual*/
      do{
        printf("\nIntroduzca el mes: ");
        hoy.mes=leernum();
        if(hoy.mes<1||hoy.mes>12) printf("\nMes de inicio Invalido");
     }while(hoy.mes<1||hoy.mes>12);
     /*coger dia actual*/
     do{
        d=true;
        printf("\nIntroduzca el dia: ");
        hoy.dia=leernum();
        if(hoy.mes==1||hoy.mes==3||hoy.mes==5||hoy.mes==7||hoy.mes==8||hoy.mes==10||hoy.mes==12){
           if(hoy.dia<1||hoy.dia>31){
              printf("\nDia de inicio Invalido");
              d=false;
           }
        }
        else if(hoy.mes==4||hoy.mes==6||hoy.mes==9||hoy.mes==11){
           if(hoy.dia<1||hoy.dia>30){
              printf("\nDia de inicio Invalido");
              d=false;
           }
        }
        else{
           if(hoy.dia<1||hoy.dia>29){
              printf("\nDia de inicio Invalido");
              d=false;
           }
        } 
     }while(d==false);
      
      
      noconfirmadas(lista_reservas);
      do {      
        tecla();      
        respuesta=menu();/*menu*/      
        system("cls");      
        switch(respuesta) {     
                          case 0:         
                               if (confirmar()==1) {            
                                  printf("\n\nSaliendo del programa...");
                                  guardar(lista_clientes, lista_suits, lista_reservas);         
                               }         
                               else respuesta=-1;         
                          break;      
                          
                          case 1:/*dar de alta un cliente*/         
                              anadircliente(lista_clientes);
						  break;      
                          
                          case 2:/*dar de baja un cliente*/         
                              eliminarcliente(lista_clientes, lista_reservas);          
                          break;   
                             
                          case 3:/*modificar un cliente*/         
                              modificarcliente(lista_clientes);        
                          break;
                                
                          case 4:/*dar de alta un suit*/ 
							  anadirsuit(lista_suits);
                          break;
                                
                          case 5:/*dar de baja un suit*/        
                              deshabilitar(lista_suits,lista_reservas);
                          break;
                                
                          case 6:/*habilitar una suit*/         
                              habilitar(lista_suits);          
                          break;
                                
                          case 7:/*dar de alta una reserva*/
							  anadirreserva(lista_reservas, lista_clientes, lista_suits);
                          break;
                                
                          case 8:/*dar de baja una reserva*/         
                              eliminarreserva(lista_reservas);
                          break;      
                                           
                          case 9:/*confirmar una reserva*/         
                              confirmarreserva(lista_reservas);
                          break;      
                          
                          case 10:/*consultar clientes*/         
                              mostrarcliente(lista_clientes);
                          break;      
                          
                          case 11:/*consultar suits*/         
                              mostrarsuit(lista_suits);
                          break;      
                          
                          case 12:/*consultar reservas*/         
                              mostrarreserva(lista_reservas);
                          break;
                          
                          case 13:/*consultar mas solisitadas*/         
                               masdemanda(lista_reservas);
                          break;
                          
                          case 14:/*consultar libres*/ 
							  	mostrarlibres(lista_suits,lista_reservas);
                          break;
                          
                          case 15:/*consultar no confirmadas*/         
                              mostrarnoconfirmadas();
                          break;      
                          
                          
                          default:         
                                           printf("\n\n\n****ERROR****");
                                           tecla();         
                          break;
        }   
     }while (respuesta!=0);/*CUANDO SE INTRODUCE 0 SE SALE DEL PROGRAMA*/   
     info();   
     
	 printf("\n\n\n\n\n\n\n\n\t\t\t\tFIN DEL PROGRAMA\n\n\n\n\n\n\n\n");   
     tecla();
}
      



/***********************************************PRESENTACION********************************/
void info(){   
    system("cls");   
    system("color 0c");   
    printf("\n€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞ PROYECTO 1 €±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");  
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€± GUSTAVO BAZAN ±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€ Y €±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€± ARMANDO BRACHO ≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    printf("€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞€±≤∞");   
    getch();   
    system("cls");   
    system("color f1");   
    return;
}

/***************************************FUNCIONES DE TIPOS*********************************/
void leerchar(char *resultado){
    
    fflush(stdin);   
    do {      gets(resultado);   
    } while (strlen(resultado)==0);   
    return;
}

int leernum(){
    
    char buffer[15];   
    fflush(stdin);   
    do {      gets(buffer);   
    } while (strlen(buffer)==0);   
    return atoi(buffer);
}
    
int compararcadenas(char *cad1, char *cad2){
    /*compara cadenas caracter a caracter con tolower*/   
    int i;   
    int resultado;   
    resultado=0;   
    
    if (strlen(cad1)!=strlen(cad2)) resultado=-1;   
    
    for (i=0;(unsigned)i<(unsigned)strlen(cad1) && resultado==0;i++) {      
        if (tolower(cad1[i])!=tolower(cad2[i])) resultado=-1;   
    }   
    return resultado;/*devuelve 0 si son iguales, -1 si son distintos*/
}

/***********************************************MENU**************************************/

int menu(){
    /*devuelve un numero entero entre 0 y 15*/   
    int resultado, principal, sub;   
    do {      
       system("cls");      
       printf("\n\n\n\n");      
       printf("\n\t€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€");      
       printf("\n\t€€                                                          €€");      
       printf("\n\t€€                  Resort Caribbean Beach                  €€");      
       printf("\n\t€€                                                          €€");      
       printf("\n\t€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€");      
       printf("\n\t€€                                                          €€");      
       printf("\n\t€€                1.-  Men£ de los clientes                 €€");      
       printf("\n\t€€                2.-  Men£ de las suits                    €€");      
       printf("\n\t€€                3.-  Men£ de las reservas                 €€");      
       printf("\n\t€€                4.-  Men£ de las consultas                €€");
       printf("\n\t€€                5.-  Men£ de las Extras                   €€");      
       printf("\n\t€€                                                          €€");      
       printf("\n\t€€                0.-  Salir del programa                   €€");      
       printf("\n\t€€                                                          €€");      
       printf("\n\t€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€\n\n");      
       printf("\n®QuÇ opci¢n elige\?\n");     
       principal=getch();      
       
       if (principal=='0') return 0;/*devuelve 00*/      
       
       if (principal!='1' && principal!='2' && principal!='3' && principal!='4' && principal!='5') {
          printf("\nElige una opci¢n v lida");         
          tecla();         
          continue;      
       }      
       do {         
          system("cls");         
          printf("\n\n\n");         
          printf("\n\t€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€");         
          printf("\n\t€€                                                          €€");         
          switch(principal) {         
                            case '1':            
                                 printf("\n\t€€                      Men£ de los clientes                €€");            
                                 printf("\n\t€€        1.-  A§adir un cliente                            €€");/*devuelve 01*/            
                                 printf("\n\t€€        2.-  Eliminar un cliente                          €€");/*devuelve 02*/            
                                 printf("\n\t€€        3.-  Modificar los datos de un cliente            €€");/*devuelve 03*/           
                            break;         
           
                            case '2':           
                                 printf("\n\t€€                      Men£ de las suits                   €€");            
                                 printf("\n\t€€        1.-  A§adir una suit                              €€");/*devuelve 04*/            
                                 printf("\n\t€€        2.-  Deshabilitar una suit                        €€");/*devuelve 05*/            
                                 printf("\n\t€€        3.-  Habilitar una suit                           €€");/*devuelve 06*/            
                            break;         
           
                            case '3':            
                                 printf("\n\t€€                      Men£ de las reservas                €€");            
                                 printf("\n\t€€        1.-  A§adir una reserva                           €€");/*devuelve 07*/            
                                 printf("\n\t€€        2.-  Eliminar una reserva                         €€");/*devuelve 08*/            
                                 printf("\n\t€€        3.-  Confirmar una reserva                        €€");/*devuelve 09*/            
                            break;         
           
                            case '4':            
                                 printf("\n\t€€                      Men£ de las consultas               €€");            
                                 printf("\n\t€€        1.-  Consultar Clientes                           €€");/*devuelve 10*/            
                                 printf("\n\t€€        2.-  Consultar Suits                              €€");/*devuelve 11*/           
                                 printf("\n\t€€        3.-  Consultar Reservas                           €€");/*devuelve 12*/            
                            break; 
                            
                            case '5':            
                                 printf("\n\t€€                      Men£ de extras                      €€");            
                                 printf("\n\t€€        1.-  Mas solicitada                               €€");/*devuelve 10*/            
                                 printf("\n\t€€        2.-  Consultar Libres                             €€");/*devuelve 11*/           
                                 printf("\n\t€€        3.-  Consultar No confirmadas                     €€");/*devuelve 12*/            
                            break;            
           
                            
                             default:            printf("\nElige una opci¢n v lida");tecla();            
                             sub='1';/*para que no repita el do{ }while() principal*/            
                             break;         
           }         
           printf("\n\t€€        0.-  Salir del submenu                            €€");         
           printf("\n\t€€                                                          €€");         
           printf("\n\t€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€\n\n");         
           printf("\nElige una opci¢n del submenu\n\n");         
           sub=getch();         
           if (sub!='1' && sub!='2' && sub!='3' && sub!='0') {            
              printf("\n\n\nIntroduzca una opci¢n v lida");
              tecla();         
           }      
       } while (sub!='1' && sub!='2' && sub!='3' && sub!='0');   
    } while ((principal!='1' && principal!='2' && principal!='3' && principal!='4' && principal!='5' && principal!='0') || sub=='0');   
    resultado=(principal-'1')*3+(sub-'1')+1;   
    return resultado;
}

/*****************************************VARIOS*******************************************/

void tecla(){   
     printf("\n\n\tPresione cualquier tecla para continuar el programa...\n\a");   
     getch();   
     system("cls");   
     return;
}

int confirmar(){
       
    char a;   
    do {      
       printf("\n\n\t®Est s seguro \"s\"/\"n\"\?");     
       a=tolower(getch());   
    } while (a!='s' && a!='n');   
    if (a=='s') return 1;   
    else return 0;
}


/************************************CARGAR Y GUARDAR******************************************/

void cargar(cliente *lista_clientes, suit *lista_suits, reserva *lista_reservas){
     
     int i;   
     FILE *puntero;/*PUNTERO AL ARCHIVO*/   
     char aux[20];   
     
     /*CARGAR LOS CLIENTES*/   
     strcpy(aux,"clientes.in");   
        
     puntero=fopen(aux,"r");   
     if (puntero==NULL)/*SI NO SE PUEDE ABRIR EL FICHERO*/      
        printf("\n\n\n***ERROR*** No se ha podido encontrar el archivo Cliente");   
     else {/*SI SE PUEDE ABRIR*/      
          for(i=0;i<CANT;i++) lista_clientes[i].posicion=0;/*se inicializan a 0 para que no tengan ningun dato inicialmente*/      
          for(i=0;i<CANT;i++) {         
                               fread(&lista_clientes[i],sizeof(cliente),1,puntero);         
                               if (feof(puntero)) 
                               break;     
          }      
          if (fclose(puntero)!=0) {         
             printf("\n\n\nEl archivo no se ha podido cerrar con Çxito");         
             return;
          }   
     }   
     
     /*CARGAR LOS SUITES*/   
     strcpy(aux,"suites.in");   
        
     puntero=fopen(aux,"r");   
     if (puntero==NULL)/*SI NO SE PUEDE ABRIR EL FICHERO*/      
        printf("\n\n\n***ERROR*** No se ha podido encontrar el archivo  suites");   
     else {/*SI SE PUEDE ABRIR*/      
          for(i=0;i<CANT;i++) lista_suits[i].posicion=0;/*se inicializan a 0 para que no tengan ningun dato inicialmente*/      
          for(i=0;i<CANT;i++) {         
                               fread(&lista_suits[i],sizeof(suit),1,puntero);         
                               if (feof(puntero)) break;      
          }      
          if (fclose(puntero)!=0) {         
             printf("\n\n\nEl archivo no se ha podido cerrar con Çxito");         
             return;      
          }   
     }   
     
     /*CARGAR LAS RESERVAS*/   
     strcpy(aux,"reservas.in");   
     
     puntero=fopen(aux,"r");   
     if (puntero==NULL)/*SI NO SE PUEDE ABRIR EL FICHERO*/      
        printf("\n\n\n***ERROR*** No se ha podido encontrar el archivo  reservas");   
     else {/*SI SE PUEDE ABRIR*/      
          for(i=0;i<CANT;i++) lista_reservas[i].posicion=0;/*se inicializan a 0 para que no tengan ningun dato inicialmente*/      
          for(i=0;i<CANT;i++) {         
                               fread(&lista_reservas[i],sizeof(reserva),1,puntero);         
                               if (feof(puntero)) break;      
          }      
          if (fclose(puntero)!=0) {         
                             printf("\n\nEl archivo no se ha podido cerrar con Çxito");         
                             return;      
          }   
     }   
     return;
}

/******************************************************************************/

void guardar(cliente *lista_clientes, suit *lista_suits, reserva *lista_reservas){
     
     int i;   
     FILE *puntero;/*PUNTERO AL ARCHIVO*/   
     char aux[20];   
     
     /*GUARDAR LOS CLIENTES*/   
     strcpy(aux,"clientes.in");   
	 
     puntero=fopen(aux,"wt+");   
     if (puntero==NULL) {/*SI NO SE PUEDE ABRIR EL FICHERO*/      
        printf("\n\n\n***ERROR*** No se ha podido guardar el archivo Cliente");      
        return;   
     }   
     for(i=0;i<CANT;i++) {      
                          if (lista_clientes[i].posicion==1) {/*TODAS LAS POSICIONES OCUPADAS*/         
                             fwrite(&lista_clientes[i],sizeof(cliente),1,puntero);      
                          }   
     }   
     if (fclose(puntero)!=0) {      
                             printf("\n\nEl archivo no se ha podido cerrar con Çxito");      
                             return;   
     }
        
     /*GUARDAR LAS SUITS*/   
     strcpy(aux,"suites.in");
	 
     puntero=fopen(aux,"wt+");   
     if (puntero==NULL) {/*SI NO SE PUEDE ABRIR EL FICHERO*/      
        printf("\n\n\n***ERROR*** No se ha podido guardar el archivo suites");      
        return;   
     }   
     for(i=0;i<CANT;i++) {      
                          if (lista_suits[i].posicion==1) {/*TODAS LAS POSICIONES OCUPADAS*/
                             fwrite(&lista_suits[i],sizeof(suit),1,puntero);      
                          }   
     }   
     if (fclose(puntero)!=0) {      
                             printf("\n\n\nEl archivo no se ha podido cerrar con Çxito");
                             return;   
     }   
     /*GUARDAR LAS RESERVAS*/   
     strcpy(aux,"reservas.in");
	 
     puntero=fopen(aux,"wt+");   
     if (puntero==NULL) {/*SI NO SE PUEDE ABRIR EL FICHERO*/      
        printf("\n\n\n***ERROR*** No se ha podido guardar el archivo reservas");      
        return;   
     }   
     for(i=0;i<CANT;i++) {      
                          if (lista_reservas[i].posicion==1) {/*TODAS LAS POSICIONES OCUPADAS*/         
                             fwrite(&lista_reservas[i],sizeof(reserva),1,puntero);
                          }   
     }   
     if (fclose(puntero)!=0) {      
                             printf("\n\n\nEl archivo no se ha podido cerrar con Çxito");      
                             return;   
     }
     return;
}

/**********************************CLIENTES****************************************/

int posicionarcliente(cliente *lista_clientes){
    /*devuelve el indice de la primera posicion vacia*/   
    int i,resultado;   
    resultado=-1;   
    for(i=0;i<CANT;i++) {      
                          if (lista_clientes[i].posicion==0){
                            resultado=i;         
                            break;      
                         }   
    }   
    return resultado;
}

/*************************************ENCONTAR CLIENTE*****************************************/

int encontrarci(cliente *lista_clientes,char *ci_buscar){
    /*devuelve -1 si no se encuentra, y si se encuentra la posicion en la que esta en el vector i=0,1,2...*/
    int i,encontrado;   
    encontrado=-1;   
    for(i=0;i<CANT && lista_clientes[i].posicion==1 && encontrado==-1;i++) {      
                    if (compararcadenas(lista_clientes[i].CI,ci_buscar)==0) 
                       encontrado=i;   
    }   
    return encontrado;
}

/******************************************************************************/

int clientetienereservas(char *CI, reserva *lista_reservas){
    /*devuelve 1 si tiene reservas, 0 si no tiene*/   
    int i,resultado;   
    resultado=0;   
    for(i=0;i<CANT && lista_reservas[i].posicion==1;i++) { 
                    if (compararcadenas(CI,(lista_reservas+i)->CI)==0) 
                       resultado=1;   
    }   
    return resultado;
}

/***************************FUNCION A—ADIR CLIENTES****************************************/

void anadircliente(cliente *lista_clientes){   
     int i,a,encontrado;   
        
     i=posicionarcliente(lista_clientes);   
     if (i>=CANT || i==-1) {      
                  printf("\n\n\nNo se puede introducir ningun cliente m s.\nLa memoria est  llena");      
                  return;   
     }   
     lista_clientes[i].posicion=1; /*PARA QUE LA POSICION i ESTE OCUPADA*/   
     /*leer nombre*/   
     printf("\n\nIntroduzca el nombre del cliente: ");   
     leerchar((lista_clientes+i)->nombre);   
     /*leer apellidos*/   
     printf("\nIntroduzca los apellidos del cliente: ");   
     leerchar((lista_clientes+i)->apellidos);   
     /*leer CI*/   
     do {      
        printf("\nIntroduzca el numero de CI: ");      
        leerchar((lista_clientes+i)->CI);           
        encontrado=0;      
        for(a=0;a<CANT && encontrado==0 && lista_clientes[i].posicion==1;a++) {         
                        if (a!=i &&compararcadenas((lista_clientes+i)->CI,(lista_clientes+a)->CI)==0) 
                           encontrado=1;      
        }
             
        if (encontrado==1) 
           printf("\n\nNo puede haber dos CI con  el mismo n£mero");   
     } while (encontrado==1);
     
     /*leer telefono*/   
     printf("\nIntroduzca el n£mero de telÇfono: ");      
     leerchar((lista_clientes+i)->telefono);      
                 
              
       
     return;
}

/***************************FUNCION MOSTRAR CLIENTES****************************************/

void mostrarcliente(cliente *lista_clientes)
{
    int i;
    printf("Lista Clientes : ");
    for(i=0;i<CANT && lista_clientes[i].posicion == 1;i++)
	{
            printf("\n\nNombre: ");puts(lista_clientes[i].nombre);
            printf("Apellido: ");puts(lista_clientes[i].apellidos);
            printf("Cedula: ");puts(lista_clientes[i].CI);
            printf("Telefono : ");puts(lista_clientes[i].telefono);
			printf("\n");
	} 
    return;
}

/***************************FUNCION ELIMINAR CLIENTES****************************************/

void eliminarcliente(cliente *lista_clientes, reserva *lista_reservas){   
     int encontrado;   
     char CI[20];   
     
     printf("\n\nIntroduzca el n£mero de CI: ");   
     leerchar(CI);   
     encontrado=encontrarci(lista_clientes,CI);   
     if (encontrado==-1) 
        printf("\n\n\nNo hay ning£n cliente con esa CI.");   
     else {      
          /*ver que no tiene niguna reserva*/      
          if(clientetienereservas(CI,lista_reservas)==1) 
          printf("\n\n\nNo se puede eliminar puesto que el cliente tiene una reserva.");      
          else {
               if (confirmar()==1) {      
                  lista_clientes[encontrado].posicion=0;         
                  printf("\n\n\nCliente eliminado con Çxito.");   
               }         
          }   
     }   
     return;
}

/***************************FUNCION MODIFICAR CLIENTES****************************************/

void modificarcliente(cliente *lista_clientes){
     
     int encontrado;   
     char CI[20], modificar;   
     printf("\n\nIntroduzca el n£mero de CI: ");   
     leerchar(CI);   
     encontrado=encontrarci(lista_clientes,CI);   
     if (encontrado==-1) 
        printf("\n\nNo hay ning£n cliente con esa CI.");   
     else {      
          do {
              printf("\n\n®Desea modificar el nombre\?");         
              modificar=tolower(getch());      
          } while (modificar!='s' && modificar!='n');      
          if (modificar=='s') {         
             /*coger nombre*/         
             printf("\n\nIntroduzca el nombre del cliente: ");         
             leerchar((lista_clientes+encontrado)->nombre);      
          }      
          do {         
             printf("\n\n®Desea modificar los apellidos\?");         
             modificar=tolower(getch());      
          } while (modificar!='s' && modificar!='n');      
          if (modificar=='s') {         
             /*Leer apellidos*/         
             printf("\n\nIntroduzca los apellidos del cliente: ");
             leerchar((lista_clientes+encontrado)->apellidos);      
          }      
          do {         
             printf("\n\n®Desea modificar el telÇfono\?");         
             modificar=tolower(getch());      
          } while (modificar!='s' && modificar!='n');      
          if (modificar=='s') {         
             /*Leer telefono*/         
             printf("\nIntroduzca el n£mero de telÇfono: ");            
             leerchar((lista_clientes+encontrado)->telefono);            
          }      
     printf("\n\n\nCliente modificado con Çxito");   
     }   
     return;
}
/**********************************FIN CLIENTES****************************************/

/*************************** SUITS ****************************************/

int posicionarsuit(suit *lista_suits){
    /*devuelve el indice de la primera posicion vacia*/   
    int i,resultado;   
    resultado=-1;   
    for(i=0;i<CANT;i++) { 
						 if (lista_suits[i].posicion==0){
                            resultado=i;         
                            break;      
                         }   
    }   
    return resultado;
}

/*************************** ENCONTRAR SUITS ****************************************/

int encontrarsuit(suit *lista_suits,char *suit_buscar){
    /*devuelve -1 si no se encuentra, y si se encuentra la posicion en la que esta en el vector i=0,1,2...*/   
    int i,encontrado;   
    encontrado=-1;   
    for(i=0;i<CANT && lista_suits[i].posicion==1 && encontrado==-1;i++) {      
                    if (compararcadenas(lista_suits[i].codigo,suit_buscar)==0) 
                    encontrado=i;   
    }   
    return encontrado;
}

/******************************************************************************/

int suittienereservas(char *cod, reserva *lista_reservas){
    /*devuelve 1 si tiene reservas, 0 si no tiene*/   
    int i,resultado;   
    resultado=0;   
    for(i=0;i<CANT && lista_reservas[i].posicion==1;i++) { 
                    if (compararcadenas(cod,(lista_reservas+i)->suit)==0) 
                       resultado=1;   
    }   
    return resultado;
}
/***************************FUNCION A—ADIR SUIT****************************************/

void anadirsuit(suit *lista_suits){   
     int i,a,encontrado;   
     i=posicionarsuit(lista_suits);   
     if (i>=CANT || i==-1) {      
                  printf("\n\n\nNo se puede introducir ninguna otra suit.\nLa memoria est  llena");      
                  return;   
     }   
     lista_suits[i].posicion=1; /*PARA QUE LA POSICION i ESTE OCUPADA*/   
     lista_suits[i].habilitada=1;
     do {      
        /*Leer numero*/      
        printf("\n\nCodigo de la Habitacion: ");      
        leerchar((lista_suits+i)->codigo);      
        /*comprobar que el numero de la suit es unico*/      
        encontrado=0;      
        for(a=0;a<CANT && encontrado==0 && lista_suits[i].posicion==1;a++) {         
                        if (a!=i && compararcadenas((lista_suits+i)->codigo,(lista_suits+a)->codigo)==0) 
                           encontrado=1;      
        }
        /*comprueba que no haya dos numeros de suits iguales*/      
        if (encontrado==1) 
           printf("\n\nNo puede haber dos suits con mismo n£mero");   
     } while (encontrado==1);   
     /*Leer ubicacion*/   
     printf("\nIntroduzca la ubicacion de la suit: ");   
     leerchar((lista_suits+i)->ubicacion);
	 /*Leer servicios*/   
     printf("\nIndique los servicios disponibles en la suit\n\n");
	 do{
	    printf("Tipo de T.V: \n1: Cable \n2: Sencilla\n");
	    lista_suits[i].servicios.tv = leernum();
	 }while(lista_suits[i].servicios.tv != 1 && lista_suits[i].servicios.tv != 2);
     do{
	    printf("\nPosee jacussi:\n1: SI \n2: NO\n");
	    lista_suits[i].servicios.jacussi = leernum();
	 }while(lista_suits[i].servicios.jacussi != 1 && lista_suits[i].servicios.jacussi != 2);   
     /*Leer tipo*/
	 do{
        printf("\n\nIndique el tipo de suit: ");
	    printf("\n1- Sencilla");
	    printf("\n2- Doble");
	    printf("\n3- Matrimonial");
	    printf("\n4- Triple");
	    printf("\n5- Cuadruple\n");
	    lista_suits[i].tipo = leernum();
	 }while(lista_suits[i].tipo < 1 || lista_suits[i].tipo > 5 );
     /*Leer costo*/   
     printf("\nIntroduzca el costo de la suit: ");   
     lista_suits[i].costo= leernum();   
     return;
}

/*************************** MOSTRAR SUITS ****************************************/

void mostrarsuit(suit *lista_suits)
{
    int i;
    printf("Lista Suites: ");
    for(i=0;i<CANT && lista_suits[i].posicion == 1;i++)
	{
        
        printf("\n\nCodigo: ");puts(lista_suits[i].codigo);
		printf("Habilitada: ");
		if(lista_suits[i].habilitada == 1) printf("Si");
		else printf("No");
        printf("\nUbicacion: ");puts(lista_suits[i].ubicacion);
		printf("Servicios: ");
		printf("\nT.V: ");
		if(lista_suits[i].servicios.tv == 1) printf("Cable");
		else printf("Sencillo");
		if(lista_suits[i].servicios.jacussi == 1) printf("\nCon jacussi");
		else printf("\nSin jacussi");
		printf("\nTipo de avitacion: ");
		switch(lista_suits[i].tipo)
		{
		   case 1: printf("Sencilla"); break;
		   case 2: printf("Doble"); break;
		   case 3: printf("Matrimonial"); break;
		   case 4: printf("Triple"); break;
		   case 5: printf("Cuadruple"); break;
		}
		printf("\nCosto: %i",lista_suits[i].costo);
        printf("\n");
	} 
    return;
}


/*************************** BUSCAR SUITS ****************************************/
void buscarsuit(suit *lista_suits,char codigo[N])
{
    int i;
    for(i=0;i<CANT && lista_suits[i].posicion == 1;i++)
	{
		if(compararcadenas(lista_suits[i].codigo,codigo) == 0)
		{
			printf("\nUbicacion: ");puts(lista_suits[i].ubicacion);
			printf("\nServicios: ");
			printf("\nT.V: ");
			if(lista_suits[i].servicios.tv == 1) printf("Cable");
			else printf("Sencillo");
			if(lista_suits[i].servicios.jacussi == 1) printf("\nCon jacussi");
			else printf("\nSin jacussi");
			printf("\nTipo de avitacion: ");
			switch(lista_suits[i].tipo)
			{
			   case 1: printf("\nSencilla"); break;
			   case 2: printf("\nDoble"); break;
			   case 3: printf("\nMatrimonial"); break;
			   case 4: printf("\nTriple"); break;
			   case 5: printf("\nCuadruple"); break;
			}
			printf("\nCosto: %i",lista_suits[i].costo);
			printf("\n");
		}
	} 
    return;
}

/*************************** DESHABILITAR SUITS ****************************************/
int encontrarreserva2(reserva *lista_reservas,char *reserva_buscar, int pos){
    /*devuelve -1 si no se encuentra, y si se encuentra la posicion en la que esta en el vector i=0,1,2...*/   
    int i,encontrado;   
    encontrado=-1;   
    for(i=pos;i<CANT && lista_reservas[i].posicion==1 && encontrado==-1;i++) {      
                    if (compararcadenas(lista_reservas[i].suit,reserva_buscar)==0) 
                    encontrado=i;   
    }   
    return encontrado;
}

void deshabilitar(suit *lista_suits, reserva *lista_reservas){   
     int encontrado=0, r, k;   
     char codigo[20];
     FILE *f;   
     temp temp1;
     
     printf("Introduzca el n£mero de Suit: ");  
     leerchar(codigo);   
     encontrado=encontrarsuit(lista_suits,codigo);   
     if (encontrado==-1) 
        printf("\nNo hay ninguna suit con ese n£mero");   
     else {
        if (confirmar()==1) {      
           lista_suits[encontrado].habilitada=0;      
           printf("\nSuit deshabilitada con Çxito");   
        }
        else return;
        do{
        if(suittienereservas(codigo, lista_reservas)==1){
           printf("\nLa Suit tiene reserva\n");
           encontrado=0;
           encontrado=encontrarreserva2(lista_reservas,codigo, encontrado);
           
           libre(lista_suits,lista_reservas, lista_reservas[encontrado].inicio.dia,lista_reservas[encontrado].inicio.mes, lista_reservas[encontrado].final.dia,lista_reservas[encontrado].final.mes);
        
           f=fopen("libres.out","r+");
           
           if (fread(&temp1,sizeof(temp),1,f)==0)
           {
              printf("\nDisculpe, no hay suits disponibles por el momento");
              lista_reservas[encontrado].posicion = 0;
           }
           else {
                rewind(f);
                printf("\nDisponibles");   
                while(fread(&temp1,sizeof(temp),1,f)==1){
                   printf("\nLa suit %s Se encuentra disponible",temp1.codigo);
                   printf("\nDesea ver la informacion de esta suit? (1:Si / 2:No)");
				   r = leernum();
				   if(r == 1)
                   {
					  buscarsuit(lista_suits,temp1.codigo);
					  printf("\nDesea reservar esta habitacion? (1:Si / 2:No)");
					  r = leernum();
					  if(r == 1)
					  {
				         
                         strcpy(lista_reservas[encontrado].suit,temp1.codigo);
				         strcpy(lista_reservas[encontrado].confirmada,"No");
						 k=1;
						 break;
					  }
				   }
                   else{
                        printf("\nDesea reservar esta habitacion? (1:Si / 2:No)");
						r = leernum();
						if(r == 1)
						{
							strcpy(lista_reservas[encontrado].suit,temp1.codigo);
							strcpy(lista_reservas[encontrado].confirmada,"No");
							k=1;
							break;
						}
                   }
					
                }
			    if(k==0){
				   printf("No hay mas habitaciones disponibles");
			       lista_reservas[encontrado].posicion = 0;
			    }
           }      
		   fclose(f);
        }
        }while(suittienereservas(codigo, lista_reservas)==1);                              
     }   
     return;
}
/*************************** HABILITAR SUITS ****************************************/

void habilitar(suit *lista_suits){   
     int encontrado;   
     char codigo[20];   
     printf("Introduzca el n£mero de Suit: ");  
      leerchar(codigo);   
      encontrado=encontrarsuit(lista_suits,codigo);   
      if (encontrado==-1) 
         printf("\n\nNo hay ninguna Suit con ese n£mero");   
      else {
           if (confirmar()==1) {      
              lista_suits[encontrado].habilitada=1;      
              printf("\n\nSuit habilitada con Çxito");   
           }
           else return;
      }   
     return;
}
/*************************** FIN SUITS ****************************************/

/******************************************RESERVAS*******************************/
int posicionarreserva(reserva *lista_reservas){
    /*devuelve el indice de la primera posicion vacia*/   
    int i,resultado;   
    resultado=-1;   
    for(i=0;i<CANT;i++) {      
                         if (lista_reservas[i].posicion==0) {         
                            resultado=i;         break;      
                         }   
    }   
    return resultado;
}

/********************************************************************************/

int encontrarreserva(reserva *lista_reservas,char *reserva_buscar){
    /*devuelve -1 si no se encuentra, y si se encuentra la posicion en la que esta en el vector i=0,1,2...*/   
    int i,encontrado;   
    encontrado=-1;   
    for(i=0;i<CANT && lista_reservas[i].posicion==1 && encontrado==-1;i++) {      
                    if (compararcadenas(lista_reservas[i].CI,reserva_buscar)==0) 
                    encontrado=i;   
    }   
    return encontrado;
}

/******************************************A—ADIR RESERVAS*******************************/

void anadirreserva(reserva *lista_reservas, cliente *lista_clientes, suit *lista_suits)
{
	 int i,encontrado,k=0,r;
	 bool d;
     temp temp1;
	 FILE *f;
     
     i=posicionarreserva(lista_reservas);   
     if (i>=CANT || i==-1) {      
                  printf("\n\n\nNo se puede introducir ninguna reserva m£s.\nLa memoria est  llena");      
                  return;   
     }   
     lista_reservas[i].posicion=1;
       
     /*Leer CI cliente*/ 
     printf("\nIntroduzca el numero de CI: ");      
               leerchar((lista_reservas+i)->CI);
	 encontrado=encontrarci(lista_clientes,(lista_reservas+i)->CI);      
     if (encontrado==-1) anadircliente(lista_clientes);      
     
     /*Leer mes de inicio*/
     do{
        printf("\nIntroduzca el mes de inicio de la reservar: ");      
        lista_reservas[i].inicio.mes=leernum();
        if(lista_reservas[i].inicio.mes<1||lista_reservas[i].inicio.mes>12) printf("\nMes de inicio Invalido");
     }while(lista_reservas[i].inicio.mes<1||lista_reservas[i].inicio.mes>12);
     /*Leer dia de inicio*/
     do{
        d=true;
        printf("\nIntroduzca el dia de inicio de la reservar: ");      
        lista_reservas[i].inicio.dia=leernum();
        if(lista_reservas[i].inicio.mes==1||lista_reservas[i].inicio.mes==3||lista_reservas[i].inicio.mes==5||lista_reservas[i].inicio.mes==7||lista_reservas[i].inicio.mes==8||lista_reservas[i].inicio.mes==10||lista_reservas[i].inicio.mes==12){
           if(lista_reservas[i].inicio.dia<1||lista_reservas[i].inicio.dia>31){
              printf("\nDia de inicio Invalido");
              d=false;
           }
        }
        else if(lista_reservas[i].inicio.mes==4||lista_reservas[i].inicio.mes==6||lista_reservas[i].inicio.mes==9||lista_reservas[i].inicio.mes==11){
           if(lista_reservas[i].inicio.dia<1||lista_reservas[i].inicio.dia>30){
              printf("\nDia de inicio Invalido");
              d=false;
           }
        }
        else{
           if(lista_reservas[i].inicio.dia<1||lista_reservas[i].inicio.dia>29){
              printf("\nDia de inicio Invalido");
              d=false;
           }
        } 
     }while(d==false);      
     /*Leer mes final*/
     do{
        printf("\nIntroduzca el mes de finalizacion de la reservar: ");      
        lista_reservas[i].final.mes=leernum();            
        if(lista_reservas[i].final.mes<1||lista_reservas[i].final.mes>12||lista_reservas[i].final.mes<lista_reservas[i].inicio.mes) 
        {printf("\nMes final Invalido");}
     }while(lista_reservas[i].final.mes<1||lista_reservas[i].final.mes>12||lista_reservas[i].final.mes<lista_reservas[i].inicio.mes);
     /*Leer dia final*/
     do{
        d=true;
        printf("\nIntroduzca el dia de finalizacion de la reservar: ");
        lista_reservas[i].final.dia=leernum(); 
        if(lista_reservas[i].final.mes==lista_reservas[i].inicio.mes){
           if(lista_reservas[i].final.dia<lista_reservas[i].inicio.dia){
              printf("\nDia final Invalido");
              d=false;
           }
        }
        if(lista_reservas[i].final.mes==1||lista_reservas[i].final.mes==3||lista_reservas[i].final.mes==5||lista_reservas[i].final.mes==7||lista_reservas[i].final.mes==8||lista_reservas[i].final.mes==10||lista_reservas[i].final.mes==12){
           if(lista_reservas[i].final.dia<1||lista_reservas[i].final.dia>31){
              printf("\nDia final Invalido");
              d=false;
           }
        }
        else if(lista_reservas[i].final.mes==4||lista_reservas[i].final.mes==6||lista_reservas[i].final.mes==9||lista_reservas[i].final.mes==11){
           if(lista_reservas[i].final.dia<1||lista_reservas[i].final.dia>30){
              printf("\nDia final Invalido");
              d=false;
           }
        }
        else{
           if(lista_reservas[i].final.dia<1||lista_reservas[i].final.dia>29){
              printf("\nDia final Invalido");
              d=false;
           }
        } 
     }while(d==false);
           
     /*generar libres*/  
     libre(lista_suits,lista_reservas, lista_reservas[i].inicio.dia,lista_reservas[i].inicio.mes, lista_reservas[i].final.dia,lista_reservas[i].final.mes);
     f=fopen("libres.out","r+");
     
     if (fread(&temp1,sizeof(temp),1,f)==0)
     {
        printf("\nDisculpe, no hay suits disponibles por el momento");
		lista_reservas[i].posicion = 0;
     }
     else {
	    rewind(f);
        printf("\nDisponibles");   
        while(fread(&temp1,sizeof(temp),1,f)==1){
           printf("\nLa suit %s Se encuentra disponible",temp1.codigo);
		   do{
              printf("\nDesea ver la informacion de esta suit? (1:Si / 2:No): ");
		      r = leernum();
           }while(r!=1 && r!=2);
		   if(r == 1)
		   {
              buscarsuit(lista_suits,temp1.codigo);
		      do{
                 printf("\nDesea reservar esta habitacion? (1:Si / 2:No): ");
		         r = leernum();
		      }while(r!=1 && r!=2);
		      if(r == 1)
		      {
		         strcpy(lista_reservas[i].suit,temp1.codigo);
		         strcpy(lista_reservas[i].confirmada,"No");
		         k=1;
		         break;
		      }
		   }
		   else{
              do{
                 printf("\nDesea reservar esta habitacion? (1:Si / 2:No): ");
		         r = leernum();
              }while(r!=1 && r!=2); 
		      if(r == 1)
		      {
		         strcpy(lista_reservas[i].suit,temp1.codigo);
		         strcpy(lista_reservas[i].confirmada,"No");
	             k=1;
		         break;
		      }
		   }
		}
	 if(k==0){
	    printf("No hay mas habitaciones disponibles");
	    lista_reservas[i].posicion = 0;
	 }
  }      
  fclose(f);
  return;
}

/******************************************MOSTRAR RESERVAS*******************************/


void mostrarreserva(reserva *lista_reservas)
{
    int i;
    printf("Reservas: ");
    for(i=0;i<CANT && lista_reservas[i].posicion == 1;i++)
	{
		printf("\n\nCedula: ");puts(lista_reservas[i].CI);
		printf("Fecha de inicio: %i/%i",lista_reservas[i].inicio.dia,lista_reservas[i].inicio.mes);
		printf("\nFecha de finalizacion: %i/%i",lista_reservas[i].final.dia,lista_reservas[i].final.mes);
        printf("\nSuite: ");puts(lista_reservas[i].suit);
        printf("\nConfirmado: ");puts(lista_reservas[i].confirmada);
        printf("\n");
	} 

    
      return;
}

/******************************************ELIMINAR RESERVAS*******************************/

void eliminarreserva(reserva *lista_reservas){   
     int encontrado;   
     char CI[20];   
     printf("Introduzca el n£mero de Cedula: ");  
      leerchar(CI);   
      encontrado=encontrarreserva(lista_reservas,CI);   
      if (encontrado==-1) 
         printf("\n\nNo hay ninguna reserva con ese n£mero");   
      else {
           if (confirmar()==1) {      
              lista_reservas[encontrado].posicion=0;      
              printf("\n\nReserva eliminada con Çxito");   
           }
           else return;
      }   
     return;
}

/******************************************COMFIRMAR RESERVAS*******************************/

void confirmarreserva(reserva *lista_reservas){   
     int encontrado;   
     char CI[20];   
     printf("Introduzca el n£mero de Cedula: ");  
      leerchar(CI);   
      encontrado=encontrarreserva(lista_reservas,CI);   
      if (encontrado==-1) 
         printf("\n\nNo hay ninguna reserva con ese n£mero");   
      else {
           if (confirmar()==1) {      
              strcpy(lista_reservas[encontrado].confirmada,"Si");      
              printf("\n\nReserva confirmada con Çxito");   
           }
           else return;
      }   
     return;
}
/******************************************FIN RESERVAS*******************************/

/**************************FUNCION LIBRES*****************************/

void libre(suit *lista_suits,reserva *lista_reservas,int dia_i,int mes_i,int dia_f,int mes_f){
     
     int i,j, a;
	 bool inicio,fin,inicio_reserva,fin_reserva,inicio_busqueda,fin_busqueda;
	 temp tempo;

	 FILE *datos;

	 datos=fopen("libres.out","w+");
     
	 for(i=0;i < CANT && lista_suits[i].posicion == 1; i++)
	 {
         a=0;
		 for(j=0;j<CANT && lista_reservas[i].posicion == 1;j++)
		 {

             if(lista_suits[i].habilitada==1){
             if(compararcadenas(lista_suits[i].codigo,lista_reservas[j].suit) == 0)
			 {
                a=1;
                if(mes_i == mes_f)
				{
                   if( lista_reservas[j].inicio.mes > mes_i  || lista_reservas[j].final.mes < mes_i )
				   {
                      strcpy(tempo.codigo, lista_reservas[i].suit);
		              fwrite(&tempo,sizeof(temp),1,datos);	 
				   } 
				   if(mes_i == lista_reservas[j].inicio.mes )
				   {
                            if(dia_f < lista_reservas[j].inicio.dia)
                            {
                              strcpy(tempo.codigo, lista_reservas[i].suit);
		                      fwrite(&tempo,sizeof(temp),1,datos);	        
                            }
                   }
                   if(mes_i == lista_reservas[j].final.mes )
                   {
                            if(dia_i > lista_reservas[j].final.dia)
                            {
                              strcpy(tempo.codigo, lista_reservas[i].suit);
		                      fwrite(&tempo,sizeof(temp),1,datos);	       
                            }
                   }
				}
			    else
				{

				   inicio = validarfecha(mes_i,lista_reservas[j].inicio.mes,lista_reservas[j].final.mes);
				   fin = validarfecha(mes_f,lista_reservas[j].inicio.mes,lista_reservas[j].final.mes);
		          
				   if(inicio == false && fin == false && mes_i != lista_reservas[j].final.mes && mes_f != lista_reservas[j].inicio.mes && mes_i != lista_reservas[j].inicio.mes && mes_f != lista_reservas[j].final.mes && (mes_i > lista_reservas[j].inicio.mes || mes_f < lista_reservas[j].final.mes))
				   {
					   strcpy(tempo.codigo,lista_reservas[j].suit);
					   fwrite(&tempo,sizeof(temp),1,datos);
					
					   
				   }
				   else
				   {
					   if(mes_i == lista_reservas[j].final.mes && dia_i > lista_reservas[j].final.dia)
					   {
							strcpy(tempo.codigo,lista_reservas[j].suit);
							fwrite(&tempo,sizeof(temp),1,datos);
					   }
					   if(mes_f == lista_reservas[j].inicio.mes && dia_f < lista_reservas[j].inicio.dia)
					   {
						   strcpy(tempo.codigo,lista_reservas[j].suit);
							fwrite(&tempo,sizeof(temp),1,datos);
					   }
				   }
				}
			 }
           }
		 }
		 if(lista_suits[i].codigo != lista_reservas[i].suit && a == 0 && lista_suits[i].habilitada==1){
		    strcpy(tempo.codigo, lista_suits[i].codigo);
			fwrite(&tempo,sizeof(temp),1,datos);
		 }
     }
     fclose(datos);
}
/**************************FUNCION MOSTRA LIBRES************************************/
void mostrarlibres(suit *lista_suits,reserva *lista_reservas)
{
	int dia_i,mes_i,dia_f,mes_f;
	temp temp1;
	bool d;
	/*Leer mes de inicio*/
	do{
		printf("\nIntroduzca el mes de inicio de la busqueda: ");      
		mes_i=leernum();
		if(mes_i<1||mes_i>12) printf("\nMes de inicio Invalido");
	}while(mes_i<1||mes_i>12);
	/*Leer dia de inicio*/
	do{
		d=true;
		printf("\nIntroduzca el dia de inicio de la busqueda: ");      
		dia_i=leernum();
		if(mes_i==1||mes_i==3||mes_i==5||mes_i==7||mes_i==8||mes_i==10||mes_i==12){
		   if(dia_i<1||dia_i>31){
			  printf("\nDia de inicio Invalido");
			  d=false;
		   }
		}
		else if(mes_i==4||mes_i==6||mes_i==9||mes_i==11){
		   if(dia_i<1||dia_i>30){
			  printf("\nDia de inicio Invalido");
			  d=false;
		   }
		}
		else{
		   if(dia_i<1||dia_i>29){
			  printf("\nDia de inicio Invalido");
			  d=false;
		   }
		} 
	}while(d==false);      
	/*Leer mes final*/
	do{
		printf("\nIntroduzca el mes de finalizacion de la busqueda: ");      
		mes_f=leernum();            
		if(mes_f<1||mes_f>12||mes_f<mes_i) 
		{printf("\nMes de finalizacion Invalido");}
	}while(mes_f<1||mes_f>12||mes_f<mes_i);
	/*Leer dia final*/
	do{
		d=true;
		printf("\nIntroduzca el dia de finalizacion de la busqueda: ");
		dia_f=leernum(); 
		if(mes_f==1||mes_f==3||mes_f==5||mes_f==7||mes_f==8||mes_f==10||mes_f==12){
		   if(dia_f<1||dia_f>31){
			  printf("\nDia final Invalido");
			  d=false;
		   }
		}
		else if(mes_f==4||mes_f==6||mes_f==9||mes_f==11){
		   if(dia_f<1||dia_f>30){
			  printf("\nDia final Invalido");
			  d=false;
		   }
		}
		else{
		   if(dia_f<1||dia_f>29){
			  printf("\nDia final Invalido");
			  d=false;
		   }
		} 
	 }while(d==false);

      libre(lista_suits,lista_reservas,dia_i,mes_i,dia_f,mes_f);

	  FILE *f;
	  f=fopen("libres.out","r+");
     
     if (fread(&temp1,sizeof(temp),1,f)==0)
     {
        printf("\nDisculpe, no hay suits disponibles para la fecha");
		
     }
     else {
	    rewind(f);
        printf("\nDisponibles");   
        while(fread(&temp1,sizeof(temp),1,f)==1){
           printf("\nLa suit %s Se encuentra disponible",temp1.codigo);
		   
		}
	 }      
  fclose(f);
  return;
}

/**************************FUNCION CREAR NO CONFIRMADAS*****************************/

void noconfirmadas(reserva *lista_reservas){
   int i, dias;
   FILE *f;
   f=fopen("no_confirmadas.out","a+");
   for(i=0;i < CANT && lista_reservas[i].posicion == 1; i++)
   {
      if (lista_reservas[i].inicio.mes==hoy.mes){
         dias=lista_reservas[i].inicio.dia-hoy.dia;
         if (dias < 3){
            if (compararcadenas(lista_reservas[i].confirmada,"no")==0){
               fwrite(&lista_reservas[i],sizeof(reserva),1,f);
               lista_reservas[i].posicion=0;
            }
         }
      }
      else if (lista_reservas[i].inicio.mes-1==hoy.mes){
         if(hoy.mes==1||hoy.mes==3||hoy.mes==5||hoy.mes==7||hoy.mes==8||hoy.mes==10||hoy.mes==12){
            dias=31-hoy.dia;
         }
         else if(hoy.mes==4||hoy.mes==6||hoy.mes==9||hoy.mes==11){
            dias=30-hoy.dia;
         }
         else dias=28-hoy.dia;
         
         dias+=lista_reservas[i].inicio.dia;
         if (dias < 3){
            if (compararcadenas(lista_reservas[i].confirmada,"no")==0){
               fwrite(&lista_reservas[i],sizeof(reserva),1,f);
               lista_reservas[i].posicion=0;
            }
         }
      }
   }
   fclose(f);
   return;  
}

/**************************FUNCION MOSTAR NO CONFIRMADAS*****************************/

void mostrarnoconfirmadas(){
   
   reserva noconf;
   FILE *f;
   f=fopen("no_confirmadas.out","r+");
   while(fread(&noconf,sizeof(reserva),1,f)==1){
        printf("\n\nCedula: ");puts(noconf.CI);
		printf("Fecha de inicio: %i/%i",noconf.inicio.dia,noconf.inicio.mes);
		printf("\nFecha de finalizacion: %i/%i",noconf.final.dia,noconf.final.mes);
        printf("\nSuite: ");puts(noconf.suit);
        printf("\nConfirmado: ");puts(noconf.confirmada);
        printf("\n");
   }
   fclose(f);
   return;  
}

/******************FUNCION MAS DEMANDADAS********************************/

void masdemanda(reserva *lista_reservas)
{
	int i,dia_i,mes_i,dia_f,mes_f,transcurrido[N],mayor=0,k=0,a=0,m=0;
	int inicio_busqueda,fin_busqueda,inicio_reserva,fin_reserva,o;
	bool inicio,fin,d;
	temp tempo[N];
	
	printf("Seleccione el metodo de Busqueda:\n");
	printf("\n1 - Buscar un rango de fechas\n");
	printf("\n2 - Buscar un dia especifico\n");
	
    o = leernum();
	switch(o)
	{
	case 1:
		
		 /*Leer mes de inicio*/
		 do{
			printf("\nIntroduzca el mes de inicio de la busqueda: ");      
			mes_i=leernum();
			if(mes_i<1||mes_i>12) printf("\nMes de inicio Invalido");
		 }while(mes_i<1||mes_i>12);
		 /*Leer dia de inicio*/
		 do{
			d=true;
			printf("\nIntroduzca el dia de inicio de la busqueda: ");      
			dia_i=leernum();
			if(mes_i==1||mes_i==3||mes_i==5||mes_i==7||mes_i==8||mes_i==10||mes_i==12){
			   if(dia_i<1||dia_i>31){
				  printf("\nDia de inicio Invalido");
				  d=false;
			   }
			}
			else if(mes_i==4||mes_i==6||mes_i==9||mes_i==11){
			   if(dia_i<1||dia_i>30){
				  printf("\nDia de inicio Invalido");
				  d=false;
			   }
			}
			else{
			   if(dia_i<1||dia_i>29){
				  printf("\nDia de inicio Invalido");
				  d=false;
			   }
			} 
		 }while(d==false);      
		 /*Leer mes final*/
		 do{
			printf("\nIntroduzca el mes de finalizacion de la busqueda: ");      
			mes_f=leernum();            
			if(mes_f<1||mes_f>12||mes_f<mes_i) 
			{printf("\nMes de finalizacion Invalido");}
		 }while(mes_f<1||mes_f>12||mes_f<mes_i);
		 /*Leer dia final*/
		 do{
			d=true;
			printf("\nIntroduzca el dia de finalizacion de la busqueda: ");
			dia_f=leernum(); 
			if(mes_f==1||mes_f==3||mes_f==5||mes_f==7||mes_f==8||mes_f==10||mes_f==12){
			   if(dia_f<1||dia_f>31){
				  printf("\nDia final Invalido");
				  d=false;
			   }
			}
			else if(mes_f==4||mes_f==6||mes_f==9||mes_f==11){
			   if(dia_f<1||dia_f>30){
				  printf("\nDia final Invalido");
				  d=false;
			   }
			}
			else{
			   if(dia_f<1||dia_f>29){
				  printf("\nDia final Invalido");
				  d=false;
			   }
			} 
		 }while(d==false);
	break;

	case 2:
		/*Leer mes de busqueda*/
		 do{
			printf("\nIntroduzca el mes de la busqueda: ");      
			mes_i=leernum();
			if(mes_i<1||mes_i>12) printf("\nMes de inicio Invalido");
		 }while(mes_i<1||mes_i>12);
		 /*Leer dia de busqueda*/
		 do{
			d=true;
			printf("\nIntroduzca el dia de la busqueda: ");      
			dia_i=leernum();
			if(mes_i==1||mes_i==3||mes_i==5||mes_i==7||mes_i==8||mes_i==10||mes_i==12){
			   if(dia_i<1||dia_i>31){
				  printf("\nDia de inicio Invalido");
				  d=false;
			   }
			}
			else if(mes_i==4||mes_i==6||mes_i==9||mes_i==11){
			   if(dia_i<1||dia_i>30){
				  printf("\nDia de inicio Invalido");
				  d=false;
			   }
			}
			else{
			   if(dia_i<1||dia_i>29){
				  printf("\nDia de inicio Invalido");
				  d=false;
			   }
			} 
		 }while(d==false);
		 mes_f = mes_i;
		 dia_f = dia_i;
	break;
	}
	
	for(i=0;i < CANT && lista_reservas[i].posicion == 1; i++)
	{
		 inicio_busqueda = numdias(dia_i,mes_i);
		 fin_busqueda = numdias(dia_f,mes_f);
		 inicio_reserva = numdias(lista_reservas[i].inicio.dia,lista_reservas[i].inicio.mes);
		 fin_reserva = numdias(lista_reservas[i].final.dia,lista_reservas[i].final.mes);
		 inicio = validarfecha2(inicio_busqueda, inicio_reserva, fin_reserva);
		 fin = validarfecha2(fin_busqueda, inicio_reserva, fin_reserva);
		 if( inicio == true && fin == true)
		 {
			 transcurrido[k] = fin_busqueda - inicio_busqueda;
			 if(transcurrido[k] > mayor) mayor = transcurrido[k];
			 
			 a=1;
			
		 }
		 if( inicio == true && fin == false)
		 {
			 transcurrido[k] = fin_reserva - inicio_busqueda;
			 if(transcurrido[k] > mayor) mayor = transcurrido[k];
			 
			 a=1;
		 }
		 if( inicio == false && fin == true)
		 {
			 transcurrido[k] = fin_busqueda - inicio_reserva;
			 if(transcurrido[k] > mayor) mayor = transcurrido[k];
			 
			 a=1;
		 }
		 if( inicio == false && fin == false && inicio_busqueda < inicio_reserva && fin_busqueda > fin_reserva )
		 {
			 transcurrido[k] = fin_reserva - inicio_reserva;
			 if(transcurrido[k] > mayor) mayor = transcurrido[k];
			 
			 a=1;
		 }
		 k++;
	}
	if(a==0){
		printf("\nDisculpe, no se encontraron reservas dentro del rango provisto...");
	}
	else
	{
		for(i=0;i<k;i++)
		{
			if(transcurrido[i] == mayor)
			{
				strcpy(tempo[m].codigo,lista_reservas[i].suit);
				m++;
			}
		}
		printf("\nSuit(s) con mayor demanda para la fecha solicitada: ");
		for(i=0;i<m;i++){
			printf("\nSuit %s",tempo[i].codigo);
		}
	}


}
/*****************FUNCION NUMERO DE DIAS******************************************/
int numdias(int dia,int mes)
{
	
  int i,suma=0, calendario[]={31,28,31,30,31,30,31,31,30,31,30,31};
  for (i=0;i<mes-1;i++)
    suma+=calendario[i];
    suma+=dia;
  return(suma-1);
  
}

/*******************FUNCION VALIDAR FECHA********************************************/

bool validarfecha(int n,int fecha_inicio,int fecha_final)
{
	bool resp;
	
	if(n > fecha_inicio && n < fecha_final) resp = true;
	else{
		resp = false;
	}

	return(resp);
}

/************************FUNC VALIDAR FECHA 2*****************************************/

bool validarfecha2(int n,int fecha_inicio,int fecha_final)
{
	bool resp;
	
	if(n >= fecha_inicio && n <= fecha_final) resp = true;
	else{
		resp = false;
	}

	return(resp);
}


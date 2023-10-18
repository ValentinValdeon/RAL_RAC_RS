#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "string.h"
#include "envios.h"
#include "RAC.h"
#include "RAL.h"
#include "RS.h"
//GRUPO13
//MARIANO ARBELOA GUGLIELMINO
//VALENTIN VALDEON

//void comparacion();


int main(){
    int opcMenuOp;
    envio env;
    do{
            system("cls");
            printf("Seleccione la operacion a realizar\n");
            printf("--------------------------------------------------------------- \n");
            printf("<1> Comparacion de estructuras\n");
            printf("<2> Mostrar todos los envios (LSO)\n");
            printf("<3> Mostrar todos los envios (LSOBB)\n");
            printf("<4> Mostrar todos los envios (ABB)\n");
            printf("<5> Salir\n");
            printf("--------------------------------------------------------------- \n");
            printf("Ingrese una opcion\n");
            scanf("%d",&opcMenuOp);
            fflush(stdin);
            switch(opcMenuOp){
                case 1:
                    system("cls");
                    //comparacion(lso,lsobb,arbolito);
                    getchar();
                    break;
                case 2:
                    system("cls");
                    getchar();
                    break;
                case 3:
                    system("cls");
                    getchar();
                    break;
                case 4:
                    system("cls");
                    getchar();
                    break;
                case 5:
                    system("cls");
                    printf("Gracias por utilizar nuestro sistema");
                    exit(1);
                default:
                    system("cls");
                    printf("-------------------Opcion Incorrecta--------------------\n");
                    printf("------Presione cualquier tecla para volver al menu------");
                    getchar();
                    break;
        }
    }while(opcMenuOp !=5);
    return 0;
}

/*void comparacion(lista lso,listabb lsobb,arbol a){
        printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
        printf("       | Max. Evocar Exito | Med. Evocar Exito | Max Evocar Fracaso | Med Evocar Fracaso|\n");
        printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
        printf("  RAL  |    %.2f     |     %.2f     |     %.2f    |     %.2f     |\n",maxRALEvocEx,(costRALEvocEx/cantRALEvocEx),maxRALEvocFr,(costRALEvocFr/cantRALEvocFr));
        printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
        printf("  RAC  |     %.2f    |     %.2f     |     %.2f    |     %.2f     |\n",maxRACEvocEx,(costRACEvocEx/cantRACEvocEx),maxRACEvocFr,(costRACEvocFr/cantRACEvocFr));
        printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
        printf("  RS   |     %.2f     |     %.2f      |     %.2f     |     %.2f      |\n",maxRSEvocEx,(costRSEvocEx/cantRSEvocEx),maxRSEvocFr,(costRSEvocFr/cantRSEvocFr));
        printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
}*/
/*void memorizacionPrevia(lista *lso, listabb *lsobb, arbol *a){
    FILE *fp;
    envio env;
    int accion;
    int i=0;
    char codigo[8];
    int exito;

    if((fp = fopen("Operaciones-Envios.txt","r"))==NULL){
        printf("El archivo esta vacio\n");
        printf("Presione ENTER para continuar");
        getchar();
    }else{
        while (!(feof(fp))){
            fscanf(fp,"%d",&accion);
            fscanf(fp," %[^\n]s",env.codigo);
            if(accion==1 || accion==2){
                fscanf(fp," %ld",&env.documentoRece);
                fscanf(fp," %[^\n]s",env.nomyapeRece);
                fscanf(fp," %[^\n]s",env.domicilioRece);
                fscanf(fp," %ld",&env.documentoRemi);
                fscanf(fp," %[^\n]s",env.nomyapeRemi);
                fscanf(fp," %[^\n]s",env.fechaEnv);
                fscanf(fp," %[^\n]s",env.fechaRece);
                if(accion==1){
                    if((*lsobb).cant < MAX)
                        altaLSOBB(lsobb,env);
                    if((*lso).cant < MAX)
                        altaLSO(lso,env);
                    altaABB(a,env);

                }else{
                    bajaABB(a,env);
                    if((*lso).cant != 0)
                        bajaLSO(lso,env);
                    if((*lsobb).cant != 0)
                        bajaLSOBB(lsobb,env);
                }
            }else if (accion==3){
                evocacionABB(*a,env.codigo,&exito);
                evocacionLSO(env.codigo,*lso,&exito);
                evocacionLSOBB(env.codigo,*lsobb,&exito);
            }else{
                printf("Codigo de operacion no valido.\n");
            }
        }
    }
    if (!(feof(fp)))
        {
            printf("Se llego al limite de Envios, quedaron vendedores sin cargar del archivo.\n");
        }
        fflush(stdin);
        system("cls");
        fclose(fp);
}*/

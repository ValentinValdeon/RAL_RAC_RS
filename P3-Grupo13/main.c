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
    RAC rac;
    RAL ral;
    RS rs;
    initRAC(&rac);
    initRAL(&ral);
    initRS(&rs);
    envio env;
    do{
            system("cls");
            printf("Seleccione la operacion a realizar\n");
            printf("--------------------------------------------------------------- \n");
            printf("<1> Comparacion de estructuras\n");
            printf("<2> Mostrar todos los envios (RAC)\n");
            printf("<3> Mostrar todos los envios (RAL)\n");
            printf("<4> Mostrar todos los envios (RS)\n");
            printf("<5> Salir\n");
            printf("--------------------------------------------------------------- \n");
            printf("Ingrese una opcion\n");
            scanf("%d",&opcMenuOp);
            fflush(stdin);
            switch(opcMenuOp){
                case 1:
                    system("cls");
                    initRAC(&rac);
                    initRAL(&ral);
                    initRS(&rs);
                    memorizacionPrevia(&rac,&ral,&rs);
                    comparacion(rac,ral,rs);
                    getchar();
                    break;
                case 2:
                    system("cls");
                    mostrarRAC(rac);
                    getchar();
                    break;
                case 3:
                    system("cls");
                    mostrarRAL(ral);
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

void comparacion(RAC rac,RAL ral,RS rs){
        printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
        printf("       | Max. Evocar Exito | Med. Evocar Exito | Max Evocar Fracaso | Med Evocar Fracaso|\n");
        printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
        printf("  RAL  |    %.2f     |     %.2f     |     %.2f    |     %.2f     |\n",maxRALEvocEx,(costRALEvocEx/cantRALEvocEx),maxRALEvocFr,(costRALEvocFr/cantRALEvocFr));
        printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
        printf("  RAC  |     %.2f    |     %.2f     |     %.2f    |     %.2f     |\n",maxRACEvocEx,(costRACEvocEx/cantRACEvocEx),maxRACEvocFr,(costRACEvocFr/cantRACEvocFr));
        printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
        printf("  RS   |     %.2f     |     %.2f      |     %.2f     |     %.2f      |\n",maxRSEvocEx,(costRSEvocEx/cantRSEvocEx),maxRSEvocFr,(costRSEvocFr/cantRSEvocFr));
        printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
}
void memorizacionPrevia(RAC *rac, RAL *ral, RS *rs){
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
                    altaRAC(rac,env);
                    altaRAL(ral,env);
                    //altaRS(rs,env);

                }else{
                    //bajaRAC(rac,env);
                    //bajaRAL(ral,env);
                    //bajaRS(rs,env);
                }
            }else if (accion==3){
                //evocacionRAC(env.codigo,*rac,&exito);
                //evocacionRAL(env.codigo,*ral,&exito);
                //evocacionRS(env.codigo,*rs,&exito);
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
}

void mostrarRAC(RAC rac){
    int i=0;
    int vacio=0;
    for(i=0;i<RAC_FACTOR;i++){
        if(rac.estructura[i].isVirgen == -1 || rac.estructura[i].isVirgen == 0){
            vacio++;
        }
    }
    if(vacio == RAC_FACTOR){
        printf("No existen envios cargados");
    }else{
        for(i=0;i<RAC_FACTOR;i++){
            if(rac.estructura[i].isVirgen == -1){
                printf("\n---------------------------------------------------------------");
                printf("\nCelda virgen");
                printf("\nPresione ENTER para continuar");
                getchar();
            }else if(rac.estructura[i].isVirgen == 0){
                printf("\n---------------------------------------------------------------");
                printf("\nCelda vacia");
                printf("\nPresione ENTER para continuar");
                getchar();
            }else{
                printf("\n---------------------------------------------------------------");
                printf("\nCodigo del envio: %s", rac.estructura[i].env.codigo);
                printf("\n--------DATOS DEL RECEPTOR--------");
                printf("\nNombre y Apellido: %s", rac.estructura[i].env.nomyapeRece);
                printf("\nDNI: %ld", rac.estructura[i].env.documentoRece);
                printf("\nDomicilio: %s", rac.estructura[i].env.domicilioRece);
                printf("\n--------DATOS DEL REMITENTE--------");
                printf("\nNombre y Apellido: %s", rac.estructura[i].env.nomyapeRemi);
                printf("\nDNI: %ld", rac.estructura[i].env.documentoRemi);
                printf("\n--------DATOS DEL ENVIO--------");
                printf("\nFecha de Envio: %s", rac.estructura[i].env.fechaEnv);
                printf("\nFecha de Llegada: %s", rac.estructura[i].env.fechaRece);
                printf("\nPresione ENTER para continuar");
                getchar();
            }
        }
    }
}

void mostrarRAL(RAL ral){
    int i=0;
    int vacio=0;
    for(i=0;i<RAL_FACTOR;i++){
        if(ral.estructura[i].isVirgen == -1 || ral.estructura[i].isVirgen == 0){
            vacio++;
        }
    }
    if(vacio == RAL_FACTOR){
        printf("No existen envios cargados");
    }else{
        for(i=0;i<=RAL_FACTOR;i++){
            if(ral.estructura[i].isVirgen == -1){
                printf("\n---------------------------------------------------------------");
                printf("\nCelda virgen");
                printf("\nPresione ENTER para continuar");
                getchar();
            }else if(ral.estructura[i].isVirgen == 0){
                printf("\n---------------------------------------------------------------");
                printf("\nCelda vacia");
                printf("\nPresione ENTER para continuar");
                getchar();
            }else{
                printf("\n---------------------------------------------------------------");
                printf("\nCodigo del envio: %s", ral.estructura[i].env.codigo);
                printf("\n--------DATOS DEL RECEPTOR--------");
                printf("\nNombre y Apellido: %s", ral.estructura[i].env.nomyapeRece);
                printf("\nDNI: %ld", ral.estructura[i].env.documentoRece);
                printf("\nDomicilio: %s", ral.estructura[i].env.domicilioRece);
                printf("\n--------DATOS DEL REMITENTE--------");
                printf("\nNombre y Apellido: %s", ral.estructura[i].env.nomyapeRemi);
                printf("\nDNI: %ld", ral.estructura[i].env.documentoRemi);
                printf("\n--------DATOS DEL ENVIO--------");
                printf("\nFecha de Envio: %s", ral.estructura[i].env.fechaEnv);
                printf("\nFecha de Llegada: %s", ral.estructura[i].env.fechaRece);
                printf("\nPresione ENTER para continuar");
                getchar();
            }
        }
    }
}


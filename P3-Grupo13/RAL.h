#ifndef RAL_H_INCLUDED
#define RAL_H_INCLUDED
#define RAL_FACTOR 358

float maxRALEvocEx=0,costRALEvocEx=0,cantRALEvocEx=0,maxRALEvocFr=0,costRALEvocFr=0,cantRALEvocFr=0;

typedef struct celdaRAL{
    envio env;
    int isVirgen; // donde -1 es virgen, 0 es libre y 1 es ocupado
}celdaRAL;


typedef struct RAL{
    celdaRAL estructura[RAL_FACTOR];
    int cantCeldas;
}RAL;

void initRAL(RAL *ral){

    int i;

    for (i =0;i < RAL_FACTOR;i++ ){
        (*ral).estructura[i].isVirgen=-1;
        strcpy((*ral).estructura[i].env.codigo,"z");
    }

    (*ral).cantCeldas =0;

    return ral;
}

//HASH
int hashingRAL(char *x){
    int longitud,i;
    int contador = 0;

    longitud = strlen(x);
    for(i=0; i<longitud; i++)
        contador += ((int)x[i]) * (i+1);

    return (contador % RAL_FACTOR);
}

int localizarRAL(char cod[], RAL *ral, int *pos, int accion){
    int auxcost;
	int i = hashingRAL(cod);
	int bandera = -1;
	int iteraciones = 0;//controla si vi o no todas las M celdas

	while((iteraciones < RAL_FACTOR) && ((*ral).estructura[i].isVirgen != -1) && strcmp(cod,(*ral).estructura[i].env.codigo)!=0){
        if((*ral).estructura[i].isVirgen == 0 && bandera == -1){
            bandera = i;
        }
        if(accion = 1){
            auxcost++;
        }
        i = i % RAL_FACTOR;
        i++;
        iteraciones++;
	}

	if(strcmp(cod,(*ral).estructura[i].env.codigo)==0){
        if(maxRALEvocEx < auxcost){
            maxRALEvocEx = auxcost;
        }
        if(accion==1){
            cantRALEvocEx +=1;
            costRALEvocEx += auxcost;
        }
        (*pos) = i;
        return 1;
	}
	else{
	    if(maxRALEvocFr < auxcost){
            maxRALEvocFr = auxcost;
        }
        if(accion==1){
            cantRALEvocFr +=1;
            costRALEvocFr += auxcost;
        }
        if(bandera != -1){
            (*pos) = bandera;
        }else if((*ral).estructura[i].isVirgen == -1){
            (*pos) = i;
        }else if((*ral).estructura[i].isVirgen != -1 && bandera == -1){
            return -1;//la estructura esta llena
        }
        return 0;
	}
}

int altaRAL(RAL *ral,envio env){
    int pos = 0;
    int exito = localizarRAL(env.codigo,ral,&pos,0);
    if(exito == 1){
        return 0;
    }else if (exito == 0){
        (*ral).estructura[pos].env = env;
        (*ral).estructura[pos].isVirgen = 1;
        return 1;
    }else{
        return -1;
    }
}

int bajaRAL(RAL *ral,envio env){
    int pos = 0;
    int exito = localizarRAL(env.codigo,ral,&pos,0);
    if(exito == 0){
        return 0;
    }else{
        if(strcmpi((*ral).estructura[pos].env.codigo,env.codigo)==0 && strcmpi((*ral).estructura[pos].env.nomyapeRemi,env.nomyapeRemi)==0 && strcmpi((*ral).estructura[pos].env.nomyapeRece,env.nomyapeRece)==0 &&
           strcmpi((*ral).estructura[pos].env.domicilioRece,env.domicilioRece)==0 && strcmpi((*ral).estructura[pos].env.fechaEnv,env.fechaEnv)==0 && strcmpi((*ral).estructura[pos].env.fechaRece,env.fechaRece)==0 &&
           (*ral).estructura[pos].env.documentoRece == env.documentoRece && (*ral).estructura[pos].env.documentoRemi == env.documentoRemi){
                strcpy((*ral).estructura[pos].env.codigo,"z");//Codigo borrado
                (*ral).estructura[pos].isVirgen = 0;
                return 1;
           }else{
                return 0;
           }
    }
}

envio evocacionRAL(char cod[], RAL ral,int *exito){
    int pos;
    *exito = localizarRAL(cod,&ral,&pos,1);
    if(*exito == 1){
        return ral.estructura[pos].env;
    }
}


#endif // RAL_H_INCLUDED

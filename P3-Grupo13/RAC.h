#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
#define RAC_FACTOR 401

float maxRACEvocEx=0.0,costRACEvocEx=0.0,cantRACEvocEx=0.0,maxRACEvocFr=0.0,costRACEvocFr=0.0,cantRACEvocFr=0.0;

typedef struct celdaRAC{
    envio env;
    int isVirgen; // donde -1 es virgen, 0 es libre y 1 es ocupado
}celdaRAC;


typedef struct RAC{
    celdaRAC estructura[401];
    int cantCeldas;
}RAC;

void initRAC(RAC *rac){
    int i;

    for (i =0;i < RAC_FACTOR;i++ ){
        (*rac).estructura[i].isVirgen=-1;
        strcpy((*rac).estructura[i].env.codigo,"z");
    }

    (*rac).cantCeldas =0;

    return rac;
}

//HASH
int hashingRAC(char *x){
    int longitud,i;
    int contador = 0;

    longitud = strlen(x);
    for(i=0; i<longitud; i++)
        contador += ((int)x[i]) * (i+1);

    return (contador % RAC_FACTOR);
}


int localizarRAC(char cod[], RAC *rac, int *pos, int accion){
    int auxcost = 0;
	int i = hashingRAC(cod);
	int bandera = -1;
	int k = 0;
	int iteraciones = 0;//controla si vi o no todas las M celdas

	while((iteraciones < RAC_FACTOR) && ((*rac).estructura[i].isVirgen != -1) && strcmp(cod,(*rac).estructura[i].env.codigo)!=0){
        if((*rac).estructura[i].isVirgen == 0 && bandera == -1){
            bandera = i;
        }
        if(accion == 1){
            auxcost++;
        }
		k++;
		i = (i+k) % RAC_FACTOR;
        iteraciones++;
	}
	if(strcmp(cod,(*rac).estructura[i].env.codigo)==0){
	    if(accion == 1){
            auxcost++;
        }
        if(maxRACEvocEx < auxcost){
            maxRACEvocEx = auxcost;
        }
        if(accion==1){
            cantRACEvocEx +=1;
            costRACEvocEx += auxcost;
        }
        (*pos) = i;
        return 1;
	}
	else{
	    if(accion == 1){
            auxcost++;
        }
        if(maxRACEvocFr < auxcost){
            maxRACEvocFr = auxcost;
        }
        if(accion==1){
            cantRACEvocFr +=1;
            costRACEvocFr += auxcost;
        }
        if(bandera != -1){
            (*pos) = bandera;
            return 0;
        }else if((*rac).estructura[i].isVirgen == -1){
            (*pos) = i;
            return 0;
        }else if((*rac).estructura[i].isVirgen != -1 && bandera == -1){
            return -1;//la estructura esta llena
        }

	}
}

int altaRAC(RAC *rac,envio env){
    int pos = 0;
    int exito = localizarRAC(env.codigo,rac,&pos,0);
    if(exito == 1){
        return 0;
    }else if (exito == 0){
        (*rac).estructura[pos].env = env;
        (*rac).estructura[pos].isVirgen = 1;
        return 1;
    }else{
        return -1;
    }
}

int bajaRAC(RAC *rac,envio env){
    int pos = 0;
    int exito = localizarRAC(env.codigo,rac,&pos,0);
    if(exito == 0){
        return 0;
    }else{
        if(strcmpi((*rac).estructura[pos].env.codigo,env.codigo)==0 && strcmpi((*rac).estructura[pos].env.nomyapeRemi,env.nomyapeRemi)==0 && strcmpi((*rac).estructura[pos].env.nomyapeRece,env.nomyapeRece)==0 &&
           strcmpi((*rac).estructura[pos].env.domicilioRece,env.domicilioRece)==0 && strcmpi((*rac).estructura[pos].env.fechaEnv,env.fechaEnv)==0 && strcmpi((*rac).estructura[pos].env.fechaRece,env.fechaRece)==0 &&
           (*rac).estructura[pos].env.documentoRece == env.documentoRece && (*rac).estructura[pos].env.documentoRemi == env.documentoRemi){
                strcpy((*rac).estructura[pos].env.codigo,"z");//Codigo borrado
                (*rac).estructura[pos].isVirgen = 0;
                return 1;
           }else{
                return 0;
           }
    }
}

envio evocacionRAC(char cod[], RAC rac,int *exito){
    int pos;
    *exito = localizarRAC(cod,&rac,&pos,1);
    if(*exito == 1){
        return rac.estructura[pos].env;
    }
}



#endif // RAC_H_INCLUDED

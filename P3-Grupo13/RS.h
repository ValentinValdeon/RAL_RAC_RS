#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#define RS_FACTOR 208

float maxRSEvocEx=0,costRSEvocEx=0,cantRSEvocEx=0,maxRSEvocFr=0,costRSEvocFr=0,cantRSEvocFr=0;

typedef struct celdaRS{
	envio envio;
	struct celdaRS *siguiente;
}celdaRS;

typedef struct{
    celdaRS *acc;
}lista;

typedef struct RS{
	lista estructura[RS_FACTOR];
	celdaRS *anterior;
	celdaRS *actual;
	int cant;
}RS;

celdaRS *initCelda(envio envAux){
    celdaRS* n = (celdaRS*)malloc(sizeof(celdaRS));
    if(n == NULL)
        return n;

    n->envio = envAux;
    n->siguiente = NULL;

    return n;
}

void initRS(RS *rs){
	int i;

	for(i = 0; i < RS_FACTOR; i++){
		(*rs).estructura[i].acc = NULL;
	}

	(*rs).actual = (*rs).estructura[0].acc;
	(*rs).anterior = (*rs).estructura[0].acc;
	(*rs).cant = 0;

	return rs;
}

//HASH
int hashingRS(char *x){
    int longitud,i;
    int contador = 0;

    longitud = strlen(x);
    for(i=0; i<longitud; i++)
        contador += ((int)x[i]) * (i+1);

    return (contador % RS_FACTOR);
}

int localizarRS(char cod[], RS *rs, int *pos, int accion){
    int auxcost = 0;
    int i = hashingRS(cod);
    (*pos)=i;
    (*rs).actual=(*rs).estructura[i].acc;
    while((*rs).actual!=NULL && strcmp(cod,(*rs).actual->envio.codigo)!=0){
        (*rs).anterior=(*rs).actual;
        (*rs).actual=(*rs).actual->siguiente;
        if(accion == 1){
            auxcost++;
        }
    }
    if((*rs).actual==NULL){
        if(accion == 1){
            auxcost++;
        }
        if(maxRSEvocFr < auxcost){
            maxRSEvocFr = auxcost;
        }
        if(accion==1){
            cantRSEvocFr +=1;
            costRSEvocFr += auxcost;
        }

        return 0;
    }else{
        auxcost++;
        if(accion == 1){
            auxcost++;
        }
        if(maxRSEvocEx < auxcost){
            maxRSEvocEx = auxcost;
        }
        if(accion==1){
            cantRSEvocEx +=1;
            costRSEvocEx += auxcost;
        }
        return 1;
    }
}

int altaRS(RS *rs,envio env){
    int pos;
    int exito = localizarRS(env.codigo,rs,&pos,0);
    if(exito==0){
        celdaRS *p=(celdaRS*)malloc(sizeof(celdaRS));
        if(p==NULL){
            return -1;
        }else{
            (*p).siguiente=(*rs).estructura[pos].acc;
            (*p).envio=env;
            (*rs).estructura[pos].acc=p;
            return 1;
            }
    }else{
        return 0;
    }
}

int bajaRS(RS *rs, envio env) {
    int pos;
    int exito = localizarRS(env.codigo,rs,&pos,0);
    if (exito == 1) {
        if(strcmpi((*rs).actual->envio.codigo,env.codigo)==0 && strcmpi((*rs).actual->envio.nomyapeRemi,env.nomyapeRemi)==0 && strcmpi((*rs).actual->envio.nomyapeRece,env.nomyapeRece)==0 &&
           strcmpi((*rs).actual->envio.domicilioRece,env.domicilioRece)==0 && strcmpi((*rs).actual->envio.fechaEnv,env.fechaEnv)==0 && strcmpi((*rs).actual->envio.fechaRece,env.fechaRece)==0 &&
           (*rs).actual->envio.documentoRece == env.documentoRece && (*rs).actual->envio.documentoRemi == env.documentoRemi){
            if ((*rs).estructura[pos].acc == (*rs).actual) {
                (*rs).estructura[pos].acc = (*rs).actual->siguiente;
                free((void *) (*rs).actual);
                (*rs).actual = (*rs).estructura[pos].acc;
                (*rs).anterior = (*rs).estructura[pos].acc;
            } else {
                (*rs).anterior->siguiente = (*rs).actual->siguiente;
                free((void *) (*rs).actual);
                (*rs).actual = (*rs).actual->siguiente;
            }
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}


envio evocacionRS(char cod[],RS rs,int *exito){
    int pos=0;
    exito = localizarRS(cod,&rs,&pos,1);
    if (exito==1){
        return rs.actual->envio;
    }
}

void borrarRS(RS *rs){
    int j;
    for(j=0;j<RS_FACTOR;j++){
            (*rs).actual=(*rs).estructura[j].acc;
            (*rs).anterior=(*rs).estructura[j].acc;
            while((*rs).actual!=NULL){
                (*rs).anterior=(*rs).actual;
                (*rs).actual=(*rs).actual->siguiente;
                free((*rs).anterior);
            }
    }
}






#endif // RS_H_INCLUDED



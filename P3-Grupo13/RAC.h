#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
#define RAC_FACTOR 0.75

typedef struct celdaRAC{
    envio env;
    int isVirgen; // donde -1 es virgen, 0 es libre y 1 es ocupado
}celdaRAC;


typedef struct RAC{
    celdaRAC estructura[RAC_FACTOR];
    int cantCeldas;
}RAC;

RAC initRAC(){
    RAC rac;
    int i;

    for (i =0;i < RAC_FACTOR;i++ ){
        rac.estructura[i].isVirgen=-1;
        rac.estructura[i].env.codigo = "z";
    }

    rac.cantCeldas =0;

    return rac;
}

//HASH
int hashing(char *x, int M){
    int longitud,i;
    int contador = 0;

    longitud = strlen(x);
    for(i=0; i<longitud; i++)
        contador += ((int)x[i]) * (i+1);

    return (contador % M);
}


int localizarRAC(char cod[], RAC *rac, int *pos, int accion){

	int i = hashing(cod,RAC_FACTOR);
	int bandera = -1;
	int k = 1;
	int iteraciones = 0;//controla si vi o no todas las M celdas

	while((iteraciones < RAC_FACTOR) && (rac.estructura[i].isVirgen != -1) && strcmp(cod,rac.estructura[i].env.codigo)!=0){
        if(rac.estructura[i].isVirgen == 0 && bandera == -1)
            bandera = i;

        i = (i+k) % RAC_FACTOR;
		k++;
        iteraciones++;
	}

	if(dni == rac.estructura[i].v.dni ){
        (*pos) = i;
        return 1;
	}
	else{
        if(rac.estructura[i].isVirgen == -1){
            (*pos) = i;
        }
        if(bandera != -1)
            (*pos) = bandera;

        return 0;

        if(rac.estructura[i].isVirgen != -1 && bandera == -1){
            return -1;//la estructura esta llena
        }
	}
}



#endif // RAC_H_INCLUDED

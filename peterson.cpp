//Sebastian Azamar Aviles
//Karime Aylen de la Cruz
//Carolina Gonzalez Gonzalez
//Martin Granados Reyes
#include <cstdlib>
#include <iostream>
#include <thread>//Libreria para creacion de hilos
#include <time.h>
#include <stdio.h>
#include <string.h>

using namespace std;

#define maxdat 30//Maximo de hilos
bool proceso1_desea_entrar;//Variable que permite al proceso1 preguntar si puede ejecutar su seccion critica
bool proceso2_desea_entrar;//Variavble que permite al proceso2 preguntar si puede ejecutar su seccion critica
int proceso_favorecido;//Variable la cual indicara cual proceso tiene prioridad en su ejecucion
thread vec[maxdat];//Vector de hilos
int nom = 0;//Nombre de los procesos que se crearan
int p1 = 0;//Tiempo de espera de los procesos
int canti;//Se usara para los ejemplos de los productos que entran y salen. Indica la cantidad de productos que entraran o saldran
int cat = 0;//Se usara para los ejemplos de los productos que entran y salen. Indica la categoria de los productos que entran o salen
clock_t t, ts = clock()+CLOCKS_PER_SEC;//Variable para saber que a pasado un segundo y poder aumentar el contador p1
bool cancelar;
int pros = 0;//Numero de procesos completados

//Retardar el proceso con los milisegundos indicados
void retardar_unos_milisegundos(int velocidad) {
    for (int i = 0; i < velocidad && !cancelar; i++) {
        for (int j = 0; j < velocidad && !cancelar; j++) {
            /* no hace nada */
        }
    }
}


void retardo_aleatoreo()
{
    srand(time(NULL));

    int tiempo = (rand() % 1000) * 20;

    retardar_unos_milisegundos(20000);
}

//Ejecucion de la seccion critica1 simulando la entrada de un producto
void ejecutar_seccion_critica_1(int nomb, int p11) {
    canti = (rand() % 20) + 1;
    printf("\nEl proceso espero %d El producto que entra es %d Categoria %d Cantidad %d\n",p11,nomb,cat,canti);
    retardo_aleatoreo();
    cat++;

}

//Funcion de espera del proceso1 que pregunta si puede ejecutar su seccion critica o si debe esperar
void proceso1(int nomb) {

	while(!cancelar){
        proceso1_desea_entrar = true;//Habilita la variable para que asi pueda preguntar si puede ejecutar su seccion critica
        proceso_favorecido = (rand() % 2) + 1;
        
        while(proceso2_desea_entrar && proceso_favorecido == 2 && !cancelar){//Para poder decir que el proceso esta en espera se necesita que tanto la variable para preguntar si se puede entrar como el proceso favorecido esten orinetados al proceso 2
            /* esperar */
		if((t=clock())>=ts)
		{
			p1++;
			printf("\nEl proceso esperando %d segundos de nombre %d\n",p1,nomb);
			ts = ts+CLOCKS_PER_SEC;
		}
        }
	

        ejecutar_seccion_critica_1(nomb,p1);//seccion critica
        
        proceso1_desea_entrar = false;
	
	}
	//Termina el proceso y se indica cual es el que termino
	printf("\nEl proceso %d termino\n",nomb);
	pros++;

}

void ejecutar_seccion_critica_2(int nomb, int p22) {//Ejecucion de la seccion cirtica del proceso 2 que simula la salida de un producto
    /*Aui va proceso*/
	canti = (rand() % 20) + 1;
    printf("\nEl proceso espero %d  El producto que saldra es %d Categoria %d Cantidad %d\n",p22,nomb,cat,canti);
    retardo_aleatoreo();
    cat++;

}

//Funcion de espera del proceso2 que pregunta si puede ejecutar su seccion critica o si debe esperar
void proceso2(int nomb) {

	while(!cancelar){
        proceso2_desea_entrar = true;
        proceso_favorecido = (rand() % 2) + 1;
        
        while(proceso1_desea_entrar && proceso_favorecido == 1 && !cancelar) {//Para poder decir que el proceso esta en espera se necesita que tanto la variable para preguntar si se puede entrar como el proceso favorecido esten orinetados al proceso 1

            /* esperar*/
		if((t=clock())>=ts)
		{
			p1++;
			printf("\nProceso esperando %d segundos de nombre %d\n",p1,nomb);
			ts = t+CLOCKS_PER_SEC;
		}
        }
	


        ejecutar_seccion_critica_2(nomb,p1);//Ejecucion de la seccion critica
        
        proceso2_desea_entrar = false;
}
//Termina el proceso y se indica cual es el que se termino
printf("\nEl proceso %d termino\n",nomb);
pros++;	

}


int main(int argc, char* argv[]) {

    cancelar = false;
    int conta = 1;
    int u = stoi(argv[1]);//Numero de procesos para crear
    srand(time(NULL));
    proceso1_desea_entrar = false;//Las variables para desear entrar estan en falso indicando que ningun proceso se esta ejecutando, ya que es el inicio
    proceso2_desea_entrar = false;
    proceso_favorecido = (rand() % 2) + 1;

    //Se inician los procesos en un intervalo de 1 en 1 lo que significa que si el numero de procesos a ejecutar es par, la mitad seran proceso 1 y la otra mitad proceso 2
    for(int ko=0; ko<u; ko++)
    {
            if(conta == 1)
            {
                    conta++;
                    nom++;
                    vec[ko] = thread(proceso1,nom);//Creacion de procesos1
            }
            else
            {
                    conta--;
                    nom++;
                    vec[ko] = thread(proceso2,nom);//Creacion de procesos2
            }
    }
    printf("Salio");

    //Espera de los procesos
    for(int ki=0; ki<u; ki++)
    {
	    retardo_aleatoreo();
	    cancelar = true;
            vec[ki].join();
    }
    //Numero de procesos realizados
    printf("\nEl numero de hilos realizados es %d\n",pros);


    return EXIT_SUCCESS;
}

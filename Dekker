//Sebastian Azamar Aviles
//Karime Aylen de la Cruz
//Carolina Gonzalez Gonzalez
//Martin Granados Reyes
#include <cstdlib>
#include <iostream>
#include <thread>//Libreria para el uso de hilos
#include <time.h>
#include <stdio.h>
#include <string.h>

using namespace std;

#define maxdat 30
//Variable para confirma que el proceso1 puede preguntar si puede ejecutar su seccion critica, o esperar
bool proceso1_puede_entrar;
//Variable para confirmar que el proceso pede preguntar si puede ejecutar su seccion critica, o esperar
bool proceso2_puede_entrar;
//Variable que indica de quien es el turno para ejecutar la seccion critica
int turno;
bool cancelar = false;
//Variable que indica cuanto tiempo llevan esperando los procesos
int p11=0;
int pros=0;
int prueb=0;
int nom=0;
int cat=1;
int canti;
clock_t t, ts=clock()+CLOCKS_PER_SEC;
//Vector de hilos a ejecutar
thread tid[maxdat];

//Funcion que ratarda milisegundos a los procesos para simular el tiempo de espera
void retardar_unos_milisegundos(int velocidad) {
    for (int i = 0; i < velocidad && !cancelar; i++) {
        for (int j = 0; j < velocidad && !cancelar; j++) {
            /* no hace nada */
        }
    }
}

//Funcion que asigna un valor aleatoreo a de retraso para la funcion retardar_unos_milisegundos
void retardo_aleatoreo()
{

    int tiempo = (rand() % 1000) * 20;

    retardar_unos_milisegundos(20000);
}

//Seccion critica del proceso1 similuando la entrada de un producto
void ejecutar_seccion_critica_1(int nomb,int p1) {
    canti = (rand() % 20) + 1;
    printf("\nEl proceso espero %d segundos El producto que entrara es %d Categoria %d Cantidad %d\n",p1,nomb,cat,canti);
    cat++;
    retardo_aleatoreo();
}

//Funcion de espera del proceso1 que pregunta si puede ejecutar su seccion critica o si debe esperar
void proceso1(int nomb) {

	srand(time(NULL));

	while(!cancelar){
        proceso1_puede_entrar = true;//Le da permiso al proceso preguntar si puede ejecutar su seccion critica

        while (proceso2_puede_entrar && !cancelar) {

            if (turno == 2) {//si turno = 2 significa que el proceso uno no puede entrara y tiene que esperar
                proceso1_puede_entrar = false;
                while (turno == 2 && !cancelar) {
                    if((t=clock())>=ts)
		    {
			p11++;
			printf("\nProceso esperando %d segundos de nombre %d\n",p11,nomb);
			ts=t+CLOCKS_PER_SEC;

		    }
                }
                proceso1_puede_entrar = true;
            }
        }

        if (cancelar) break;

        ejecutar_seccion_critica_1(nomb,p11);//Si se llega hasta aqui significa que proceso2_puede_entrar=false o que turno = 1 por lo que se puede ejecutar su seccion critica

        turno = (rand() % 2) +1;//Le da el turno de forma aleatoria a los procesos
        proceso1_puede_entrar = false;//La variable de entrada de proceso 1 se pone como false indicando que el proceso termino dandole oportunidad a los demas de ejecuterse
}
printf("\nEl proceso %d termino\n",nomb);
pros++;
}

void ejecutar_seccion_critica_2(int nomb,int p2) {//ejecucion de la seccion critica 2 simulando el proceso de salida de un producto
    canti = (rand() % 20) + 1;
    printf("\nEl proceso espero %d segundos El producto que saldra es %d Categoria %d Cantidad %d\n",p2,nomb,cat,canti);
    cat++;
    retardo_aleatoreo();
}

//Funcion de espera del proceso2 que pregunta si puede ejecutar su seccion critica o si debe esperar
void proceso2(int nomb) {



	srand(time(NULL));        
	while (!cancelar) {

        proceso2_puede_entrar = true;//Le da permiso al proceso preguntar si puede ejecutar su seccion critica

        while (proceso1_puede_entrar && !cancelar) {

            if (turno == 1) {//si turno = 1 significa que el proceso uno no puede entrara y tiene que esperar
                proceso2_puede_entrar = false;
                while (turno == 1 && !cancelar) {
                    if((t=clock())>=ts)
		    {
			p11++;
			printf("\nProceso esperando %d segundos de nombre %d\n",p11,nomb);
			ts=t+CLOCKS_PER_SEC;
		    }
                }
                proceso2_puede_entrar = true;
            }
        }

        if (cancelar) break;

        ejecutar_seccion_critica_2(nomb,p11);//Si se llega hasta aqui significa que proceso1_puede_entrar=false o que turno = 2 por lo que se puede ejecutar su seccion critica

        turno = (rand() % 2) + 1;//Le da el turno de forma aleatoria a los procesos
        proceso2_puede_entrar = false;;//La variable de entrada de proceso 1 se pone como false indicando que el proceso termino dandole oportunidad a los demas de ejecuterse
    }
	printf("\nEl proceso %d termino\n",nomb);
	pros++;
	
}

int main(int argc, char *argv[]) {

    int conta = 1;
    int u;

    srand(time(NULL));
    cancelar = false;
    proceso1_puede_entrar = false;//Se inician las variables de las entradas en false ya que como ninguno se ha empezado a ejecutar se dice que las secciones critias estan disponibles
    proceso2_puede_entrar = false;
    turno = (rand() % 2) + 1;

    u = stoi(argv[1]);//Convierte el numero de hilos indicados al inicio como enteros
    printf("%d",u);
    for(int ko=0; ko<u; ko++)
    {
	    //crea los hilos en intervalos de uno de entrada y uno de salida, por lo que si el numero de hilos es par la mitad seran entradas y la otra mitad salidas
	    if(conta == 1)
	    {
		    conta++;
		    nom++;
		    tid[ko] = thread(proceso1,nom);//creacion del hilo para procesos 1 de entrada
	    }
	    else
	 {
		    conta--;
		    nom++;
		    tid[ko] = thread(proceso2,nom);//creacion del hilo para procesos 2 de salida
	    }
    }

    //Espera de los hilos creados
    for(int ki=0; ki<u; ki++)
    {
	    retardo_aleatoreo();
	    cancelar = true;
	    tid[ki].join();
    }
    //Numero de hilos ejecutados
    printf("\nEl numero de hilos realizados fue %d\n",pros);


    return EXIT_SUCCESS;
}

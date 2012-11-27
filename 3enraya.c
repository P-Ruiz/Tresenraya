#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define ESPACIO ' '


// ORDENADOR => JUGADOR 0
// JUGADOR => JUGADOR 1

void obtener_movimiento(); //funciones
int comprovar_movimiento();
int comprovar_ganador();
int tablero_completo();
int fin_partida();
void movimientoPC();
int max();
int min();
void print();

char cuadricula [3][3]={ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO,ESPACIO},cad[15];
//char cuadricula [3][3]={ESPACIO,'x','O',ESPACIO,'x',ESPACIO,ESPACIO,'O',ESPACIO},cad[15];
int jugador=1,fila,columna,x,tiradasjug1=0,tiradasjug2=0,i,j; //variables
int opcioninicial;

int main(int argc, char *argv[])
{
	inicio:
    	printf("Jugar primero? 1 => si 2=> no\n");
    	fgets(cad,sizeof(cad),stdin);
   	sscanf(cad,"%d",&opcioninicial);
    	if(opcioninicial == 1);
    	else if(opcioninicial == 2) jugador = 2;
    	else {printf("Num no valid\n");goto inicio;}
    	do{
    		if(jugador == 1)obtener_movimiento();
   		else if(jugador == 2)
    		{
        		movimientoPC();
        		tiradasjug2++;
    		}
    		if(fin_partida() == 1)
    		{
     			if(comprovar_ganador()==1 || comprovar_ganador() == 2)
        		{
        	 		system("clear");
        	 		print();
         			printf("El jugador %d ha ganado\n",jugador);
	 			goto etiqueta;
     			}
			else
			{
				printf("Tablero completo => empate\n");
				goto etiqueta;
			}		
    		}
    		system("clear");
    		if(jugador==1) jugador++;
    		else if (jugador==2) jugador--;
    	}while(1);
    	etiqueta: printf("Fin programa\n");
    	return 0;
}

void obtener_movimiento()
{
    	do
	{
    		system("clear");
    		print();
    		fgets(cad,sizeof(cad),stdin);
    		sscanf(cad,"%d",&fila);
    		printf("\nIntroduce la columna: ");
    		fgets(cad,sizeof(cad),stdin);
    		sscanf(cad,"%d",&columna);
    	}while(comprovar_movimiento()==1);
    	if(jugador == 1){cuadricula[fila-1][columna-1]='x';tiradasjug1++;}
    	else if (jugador ==2){cuadricula[fila-1][columna-1]='O';tiradasjug2++;}
}

int comprovar_movimiento()
{

    	if((cuadricula[fila-1][columna-1]=='x') || (cuadricula[fila-1][columna-1]=='O') || (fila<1 || fila>3 || columna<1 || columna>3))
	{
        	printf("\nMovimiento no valido\n");
        	printf("Apreta una tecla para continuar...\n");
        	getchar();
        	return 1;
    	}
    	else return 0;
}

int comprovar_ganador()
{
	for(i=0;i<3;i++){
        	if(cuadricula[i][0]=='x'){
            		if(cuadricula[i][1]=='x'){
                		if(cuadricula[i][2]=='x') return 1; //Compr. filas
            		}
        	}
        	if(cuadricula[i][0]=='O'){
            		if(cuadricula[i][1]=='O'){
                		if(cuadricula[i][2]=='O') return 1;
            		}			
        	}
    	}
    	for(i=0;i<3;i++){
        	if(cuadricula[0][i]=='x'){
            		if(cuadricula[1][i]=='x'){
                		if(cuadricula[2][i]=='x') return 1; //Compr. columnas
            		}
        	}
        	if(cuadricula[0][i]=='O'){
            		if(cuadricula[1][i]=='O'){
                		if(cuadricula[2][i]=='O') return 1;
            		}
        	}

    	}	
    	if(cuadricula[0][0] != ESPACIO && cuadricula[1][1] == cuadricula[0][0] && cuadricula[2][2] == cuadricula[0][0]) return 1;
    	if(cuadricula[0][2] != ESPACIO && cuadricula[1][1] == cuadricula[0][2] && cuadricula[2][0] == cuadricula[0][2]) return 1;
    return 0;
}

int tablero_completo()
{
	int m,n;
	for(m=0;m<3;m++)
	{
		for(n=0;n<3;n++)
		{
			if(cuadricula[m][n] == ESPACIO) return 0;
		}		
	}	
	return 1;
}

int fin_partida()
{
	if(tablero_completo() == 1 || comprovar_ganador() == 1) return 1;
	return 0;
}


void movimientoPC()
{
	if(fin_partida() == 0)
	{
		int fila = 0,columna = 0;
		int valor = INT_MIN;
		int aux;
		int n,m;
		for(n=0;n<3;n++)
		{
			for(m=0;m<3;m++)
			{
				if(cuadricula[n][m] == ESPACIO)
				{
					cuadricula[n][m] = 'O';
					aux = min();
					if(aux>valor)
					{
						valor = aux;
						fila = n;
						columna = m;
					}

					cuadricula[n][m] = ESPACIO;
				}
			}
		}		
	cuadricula[fila][columna] = 'O';
	}	
}

int max()
{
	if(fin_partida() == 1)
	{
		if(comprovar_ganador() == 1) return -1;
		else return 0;
	}
	int valor = INT_MIN;
	int aux;
	int n,m;
	for(n=0;n<3;n++)
	{
		for(m=0;m<3;m++)
		{
			if(cuadricula[n][m] == ESPACIO)
			{
				cuadricula[n][m] = 'O';
				aux = min();
				if(aux>valor) valor = aux;
				cuadricula[n][m] = ESPACIO;
			}
		}		
	}
	return valor;

}

int min()
{
	if(fin_partida() == 1)
	{
		if(comprovar_ganador() == 1) return 1;
       		else return 0;
	}
	int valor = INT_MAX;
	int aux;
	int n,m;
	for(n=0;n<3;n++)
	{
		for(m=0;m<3;m++)
		{
			if(cuadricula[n][m] == ESPACIO)
			{
				cuadricula[n][m] = 'x';
				aux = max();
				if(aux<valor) valor = aux;
				cuadricula[n][m] = ESPACIO;
			}
		}	
	}
	return valor;

}

void print()
{
    	printf("\t\t-------\n");
    	printf("\t\t|%c|%c|%c|\n\t\t-------\n\t\t|%c|%c|%c|\n\t\t-------\n\t\t|%c|%c|%c|\n",cuadricula[0][0],cuadricula[0][1],cuadricula[0][2],cuadricula[1][0],cuadricula[1][1],cuadricula[1][2],cuadricula[2][0],cuadricula[2][1],cuadricula[2][2]);
    	printf("\t\t-------\n");
    	printf("\n\nJugador 1: x (%d Tiradas)\nJugador 2: O (%d Tiradas)\n",tiradasjug1,tiradasjug2);
    	printf("\n\nTurno del jugador %d\nIntroduce las coordenadas de la jugada\nIngrese la fila: ",jugador);
}

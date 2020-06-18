#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mpi.h"


void stampaMatrice(char** matrix, int n_row, int n_col){
	int i,j;
	for(i = 0; i < n_row; i++){
		for(j = 0; j < n_col; j++){
			printf("%d\t",(int) matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void lifeCicle(char** univ, char** new, int n_row, int n_col, int my_rank, int numproc){
	int i,j,prox;

	if(my_rank == 0){
	/*** HO UNA RIGA IN PIÙ ALLA FINE ***/
		i = 0;
		n_row = n_row - 1;
		for(i; i < n_row; i++){
			for(j = 0; j < n_col; j++){
				if(i == 0 && j == 0) prox = (int) univ[i][j+1] + (int) univ[i+1][j] +(int) univ[i+1][j+1];
				else if(i == 0 && j != n_col - 1) prox = (int) univ[i][j-1] + (int) univ[i+1][j-1] + (int) univ[i+1][j] + (int) univ[i+1][j+1] + (int) univ[i][j+1];
				else if(i == 0 && j == n_col - 1) prox = (int) univ[i][j-1] + (int) univ[i+1][j-1] + (int) univ[i+1][j];
				else if(i == n_row - 1 && j == 0) prox = (int) univ[i-1][j] + (int) univ[i-1][j+1] + (int) univ[i][j+1] + (int) univ[i+1][j+1] + (int) univ[i+1][j];
				else if(i == n_row - 1 && j == n_col -1) prox = (int) univ[i-1][j] + (int) univ[i-1][j-1] + (int) univ[i][j-1] + (int) univ[i+1][j-1] + (int) univ[i+1][j];
				else if(j == n_col - 1) prox = (int) univ[i-1][j] + (int) univ[i-1][j-1] + (int) univ[i][j-1] + (int) univ[i+1][j-1] + (int) univ[i+1][j];
				else if(j == 0) prox = (int) univ[i-1][j] + (int) univ[i-1][j+1] + (int) univ[i][j+1] + (int) univ[i+1][j+1] + (int) univ[i+1][j];
				else prox = (int) univ[i-1][j] + (int) univ[i-1][j-1] + (int) univ[i][j-1] + (int) univ[i+1][j-1] + (int) univ[i+1][j] + (int) univ[i+1][j+1] + (int) univ[i][j+1] + (int) univ[i-1][j+1];
			
				if(prox < 2 && (int) univ[i][j] == 1) new[i][j] = (char) 0;
				if((prox == 2 || prox == 3) && (int) univ[i][j] == 1 ) new[i][j] = (char)1;
				if(prox > 3) new[i][j] = (char) 0;
				if(prox == 3 && (int) univ[i][j] == 0) new[i][j] = (char) 1;
 			}
		}	
	}else if(my_rank != numproc - 1){
		/*** HO UNA RIGA IN PIÙ SOPRA E SOTTO ***/
		i = 1;
		n_row = n_row - 1;
		for(i; i < n_row; i++){
    	for(j = 0; j < n_col; j++){
				if(i == 1 && j == n_col - 1) prox = (int) univ[i-1][j] + (int) univ[i-1][j-1] + (int) univ[i][j-1] + (int) univ[i+1][j-1] + (int) univ[i+1][j];
				else if(i == n_row - 1 && j == 0) prox = (int) univ[i-1][j] + (int) univ[i-1][j+1] + (int) univ[i][j+1] + (int) univ[i+1][j+1] + (int) univ[i+1][j];
				else if(i == n_row - 1 && j == n_col -1) prox = (int) univ [i-1][j] + (int) univ[i-1][j-1] + (int) univ[i][j-1] + (int) univ[i+1][j-1] + (int) univ[i+1][j];
				else if(j == n_col - 1) prox = (int) univ[i-1][j] + (int) univ[i-1][j-1] + (int) univ[i][j-1] + (int) univ[i+1][j-1] + (int) univ[i+1][j];
				else if(j == 0) prox = (int) univ[i-1][j] + (int) univ[i-1][j+1] + (int) univ[i][j+1] + (int) univ[i+1][j+1] + (int) univ[i+1][j];
				else prox = (int) univ[i-1][j] + (int) univ[i-1][j-1] + (int) univ[i][j-1] + (int) univ[i+1][j-1] + (int) univ[i+1][j] + (int) univ[i+1][j+1] + (int) univ[i][j+1] + (int) univ[i-1][j+1];							
				if(prox < 2 && (int) univ[i][j] == 1) new[i][j] = (char) 0;
				if((prox == 2 || prox == 3) && (int) univ[i][j] == 1 ) new[i][j] = (char) 1;
				if(prox > 3) new[i][j] = (char) 0;
				if(prox == 3 && (int) univ[i][j] == 0) new[i][j] = (char) 1;
			}
		}
	}else{
		/*** HO UNA RIGA IN PIÙ SOPRA ***/
		i = 1;
		for(i; i < n_row; i++){
			for(j = 0; j < n_col; j++){
				if(i == 1 && j == n_col - 1) prox = (int) univ[i-1][j] + (int) univ[i-1][j-1] + (int) univ[i][j-1] + (int) univ[i+1][j-1] + (int) univ[i+1][j];
				else if(i == n_row - 1 && j == 0) prox = (int) univ[i-1][j] + (int) univ[i-1][j+1] + (int) univ[i][j+1];
				else if(i == n_row - 1 && j == n_col -1) prox = (int) univ[i-1][j] + (int) univ[i-1][j-1] + (int) univ[i][j-1];
				else if(i == n_row - 1 && j != n_col -1) prox = (int) univ[i-1][j] + (int) univ[i-1][j-1] + (int) univ[i][j-1] + (int) univ[i][j+1] + (int) univ[i-1][j+1];
				else if(j == n_col - 1) prox = (int) univ[i-1][j] + (int) univ[i-1][j-1] + (int) univ[i][j-1] + (int) univ[i+1][j-1] + (int) univ[i+1][j];
				else if(j == 0) prox = (int) univ[i-1][j] + (int) univ[i-1][j+1] + (int) univ[i][j+1] + (int) univ[i+1][j+1] + (int) univ[i+1][j];
				else prox = (int) univ[i-1][j] + (int) univ[i-1][j-1] + (int) univ[i][j-1] + (int) univ[i+1][j-1] + (int) univ[i+1][j] + (int) univ[i+1][j+1] + (int) univ[i][j+1] + (int) univ[i-1][j+1];
					
				if(prox < 2 && (int) univ[i][j] == 1) new[i][j] = (char) 0;
				if((prox == 2 || prox == 3) && (int) univ[i][j] == 1 ) new[i][j] = (char) 1;
				if(prox > 3) new[i][j] = (char) 0;
				if(prox == 3 && (int) univ[i][j] == 0) new[i][j] = (char) 1;
			}
		}
	}	

	if(my_rank == 0){
		i = 0;
	}else if(my_rank != numproc - 1){
		i = 1;
	}else{
		i = 1;
	}
	for(i; i < n_row; i++){
		for(j = 0; j < n_col; j++){
			univ[i][j] = new[i][j];
		}
	}
}


int main(int argc, char** argv){
	int my_rank,numproc; //Variabili per MPI
	MPI_Status status;
	MPI_Request request[2];
	int n;
 
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numproc);
	n = atoi(argv[1]);
	if(((n/numproc) <= 1) || numproc == 1){
		if(my_rank == 0) printf("\n\nQUESTO PROGRAMMA CALCOLA IL NUMERO DI RIGHE SUL QUALE OGNI SLAVE DEVE CALCOLARE EFFETTUANDO LA DIVISIONE TRA n(numero di righe) E numproc(numero di processori)\nSE IL RISULTATO DI QUESTA OPERAZIONE È <= 1 ALLORA NON HA SENSO DIVIDERE IN PARALLELO\n\n\n\nDIVERSAMENTE SE HAI RICHIESTO DI ESEGUIRLO SU UN SOLO PROCESSORE DEVI ESEGUIRE LA VERSIONE seqLife.c\n\n\n");
		MPI_Abort(MPI_COMM_WORLD, 1);
	}


	if(my_rank==0){
		/******	SONO IL MASTER *****/
		int m,i,j;
		int quotient,rem,sub_len[numproc],sub_start[numproc],sub_lenMaster;
		int rank,round,r,rank_p;
		double startTime, endTime;

		m = atoi(argv[2]);
		round = atoi(argv[3]);

		quotient = n / numproc;
		rem = n % numproc;

		startTime = MPI_Wtime();
		/*** DICHIARAZIONE E INIZIALIZZAZIONE RANDOM DELLA MATRICE ***/
		char **univ = (char**) malloc(n*sizeof(char*));
		char **new = (char**) malloc(n*sizeof(char*));

		for(i = 0; i < n; i++){
			univ[i] = (char*) malloc(m*sizeof(char));
			new[i] = (char*) calloc(m,sizeof(char));
		}

		for(i = 0; i < n; i++){
			for(j = 0; j < m; j++){
				univ[i][j]= (char) abs(rand()%2);
			}
		}
		/****** SPLITTING DEI DATI ******/
		printf("Matrice Iniziale\n");
		stampaMatrice(univ,n,m);
		/*** CASO 1: INPUT DIVISIBILE PER NUM PROC ***/
		if(rem == 0){
			sub_lenMaster = quotient + 1;		
			for(rank = 1; rank < numproc; rank++){
				sub_start[rank] = (rank * quotient) - 1;
				if(rank != numproc - 1){
					sub_len[rank] = quotient + 2;
				}else{
					sub_len[rank] = quotient + 1;
				}
				/*** INVIO DELLE DIMENSIONI ***/
				MPI_Send(&sub_len[rank], 1, MPI_INT, rank, 0, MPI_COMM_WORLD);

				/*** INVIO DEI DATI ***/
				for(int h = 0; h < sub_len[rank]; h++){
					MPI_Send(&(univ[sub_start[rank] + h][0]), 1*m, MPI_CHAR, rank, 0, MPI_COMM_WORLD);
				}
			}
		}else{
			/*** CASO 2: INPUT NON DIVISIBILE PER NUM PROC ***/
			sub_lenMaster = quotient + 2;
			for(rank = 1; rank < numproc; rank++){
				if(rank < rem){
					/*** I PRIMI REM PROC ***/
					sub_start[rank] = (rank * (quotient+1)) - 1;
					sub_len[rank] = quotient + 3;
				}else{
					if(rank == numproc - 1){
						sub_start[rank] = n -(quotient +1);
						sub_len[rank] = quotient + 1;
					}else{
						sub_start[rank] = ( (rem *(quotient+1)) + ( ( (rank - rem) * (quotient) ) ) ) - 1;
						sub_len[rank] = quotient + 2;
					}
				}
				MPI_Send(&sub_len[rank], 1, MPI_INT, rank, 0, MPI_COMM_WORLD);
				for(int h = 0; h < sub_len[rank]; h++){
					MPI_Send(&(univ[sub_start[rank] + h][0]), 1*m, MPI_CHAR, rank, 0, MPI_COMM_WORLD);
				}
			}
		}
		
		for(r = 1; r <= round; r++){
			if(r != round){ 
				lifeCicle(univ,new,sub_lenMaster,m,my_rank,numproc);
				MPI_Send(&(univ[sub_lenMaster - 2][0]), 1*m, MPI_CHAR, my_rank + 1, 0, MPI_COMM_WORLD);
				MPI_Recv(&(univ[sub_lenMaster - 1][0]), 1*m, MPI_CHAR, my_rank + 1, 0, MPI_COMM_WORLD, &status);
			}else{
				lifeCicle(univ,new,sub_lenMaster,m,my_rank,numproc);
			}
		}

		for(rank_p = 1; rank_p < numproc; rank_p++){
			if(rem == 0){
				for(i = 1; i <= quotient; i++){
					MPI_Recv(&(univ[sub_start[rank_p]+i][0]), 1*m, MPI_CHAR, rank_p, 0, MPI_COMM_WORLD, &status);
				}
			}else if(rem != 0 && rank_p < rem){
				for(i = 1; i <= quotient + 1; i++){	
					MPI_Recv(&(univ[sub_start[rank_p]+i][0]), 1 * m, MPI_CHAR, rank_p, 0, MPI_COMM_WORLD, &status);
				}
			}else{
				for(i = 1; i <= quotient; i++){	
					MPI_Recv(&(univ[sub_start[rank_p]+i][0]), 1*m, MPI_CHAR, rank_p, 0, MPI_COMM_WORLD, &status);
				} 
			}
		}

		printf("Matrice finale\n");
		stampaMatrice(univ,n,m);
		endTime = MPI_Wtime();
		printf("\n\nHo impiegato %.4f\n",endTime-startTime);
		free(univ);
		free(new);
	}else{
		/*** SONO LO SLAVE ***/ 
		int s_rows,s_cols;
		int i,j,r,round;
		s_cols = atoi(argv[2]);
		round = atoi(argv[3]);
		MPI_Request request[2];
		int recon = 0;
		
		
		MPI_Recv(&s_rows, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		char **univ_slave = (char**) malloc(s_rows*sizeof(char*));
		char **new_slave = (char**) malloc(s_rows*sizeof(char*));
  
		for(i = 0; i < s_rows; i++){
			univ_slave[i] = (char*) malloc(s_cols*sizeof(char));
			new_slave[i] = (char*) calloc(s_cols,sizeof(char));
		}


		for(i = 0; i < s_rows; i++){
			MPI_Recv(&(univ_slave[i][0]), 1 * s_cols, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
		}
		
		for(r = 1; r <= round; r++){
			if(r != round ){
				lifeCicle(univ_slave, new_slave, s_rows, s_cols, my_rank, numproc);
				MPI_Send(&(univ_slave[1][0]), 1*s_cols, MPI_CHAR, my_rank - 1, 0, MPI_COMM_WORLD);
				if(my_rank != numproc - 1) {
					MPI_Send(&(univ_slave[s_rows - 2][0]), 1*s_cols, MPI_CHAR, my_rank + 1, 0, MPI_COMM_WORLD);
					MPI_Recv(&(univ_slave[s_rows - 1][0]), 1*s_cols, MPI_CHAR, my_rank + 1, 0, MPI_COMM_WORLD, &status);
				}
				MPI_Recv(&(univ_slave[0][0]), 1*s_cols, MPI_CHAR, my_rank - 1, 0, MPI_COMM_WORLD, &status);
			}else{
				lifeCicle(univ_slave, new_slave, s_rows, s_cols, my_rank, numproc);
			}
		}
			
			
		for(i = 1; i <= s_rows -1; i++){
			MPI_Send(&(univ_slave[i][0]), 1*s_cols, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
		}
	
		free(univ_slave);
		free(new_slave);
	}

	MPI_Finalize();
	return 0;
}

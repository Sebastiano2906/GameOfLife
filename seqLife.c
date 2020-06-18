#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void stampaMatrice(char** matrix, int n, int m){
  int i,j;
  for(i=0;i<n;i++){
    for(j=0;j<m;j++){
      printf("%d\t",(int) matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n\n");
}

void lifecicle(char** matrix, char** new, int n, int m){
	int i,j,prox;
  	for(i = 0; i < n; i++){
    		for(j = 0;j < m; j++){
			prox = 0;
      			if(i == 0 && j == 0) prox = ((int) matrix[i+1][j] + (int) matrix[i][j+1] + (int) matrix[i+1][j+1]);
      			else if(j == m-1 && i == 0) prox = ((int) matrix[i][j-1] + (int) matrix[i+1][j] + (int) matrix[i+1][j-1]);
      			else if(j == m -1 && i != n-1) prox = ((int) matrix[i][j-1] + (int) matrix[i+1][j] + (int) matrix[i-1][j] + (int) matrix[i-1][j-1] + (int) matrix[i+1][j-1]);
      			else if(i == n-1 && j == 0) prox = ((int) matrix[i-1][j] + (int) matrix[i-1][j+1] + (int) matrix[i][j+1]);
      			else if(i == n-1 && j != m-1) prox = ((int) matrix[i][j-1] + (int) matrix[i-1][j-1] + (int) matrix[i-1][j] + (int) matrix[i-1][j+1] + (int) matrix[i][j+1]);
      			else if(j == m-1 && i == n-1) prox = ((int) matrix[i][j-1] + (int) matrix[i-1][j-1] + (int) matrix[i-1][j]);
      			else if(j == 0 && (i != 0 || i != n-1)) prox = ((int) matrix[i-1][j] + (int) matrix[i+1][j] + (int) matrix[i][j+1] + (int) matrix[i-1][j+1] + (int) matrix[i+1][j+1]);
      			else if(i == 0 && (j != m-1 || j != 0)) prox = ((int) matrix[i][j-1] + (int) matrix[i+1][j] + (int) matrix[i][j+1] + (int) matrix[i+1][j-1] + (int) matrix[i+1][j+1]);
						else prox = ((int) matrix[i][j-1] + (int) matrix[i-1][j] + (int) matrix[i+1][j] + (int) matrix[i][j+1] + (int) matrix[i-1][j-1] + (int) matrix[i+1][j-1] + (int) matrix[i+1][j+1] + (int) matrix[i-1][j+1]);
    			/***APPLICAZIONE DELLE REGOLE DI SOPRAVVIVENZA***/
    			if((prox < 2) && ((int) matrix[i][j] == 1)) new[i][j] =(char) 0;
    			if(((prox == 2) || (prox == 3)) && (int) matrix[i][j] == 1) new[i][j]= (char) 1;
    			if(prox > 3) new[i][j]= (char) 0 ;
    			if((prox == 3) && ((int) matrix[i][j] == 0)) new[i][j] = (char) 1;
    		}
  	}

  	/***SWAP DELLE MATRICI**/
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++){
       			matrix[i][j] = new[i][j];
		}
	}
}
 



int main(int argc, char** argv){
	int m,n,round,u,h;
	int i,j,k,prox;

	clock_t begin = clock(); // LET's GO
	n=atoi(argv[1]);
	m=atoi(argv[2]);
	round=atoi(argv[3]);

	/**Dichiarazione e inizializzazione delle matrici**/
	char **univ = (char**)malloc(n * sizeof(char*));
	char **new = (char**)malloc(n * sizeof(char*));
  
	for(i=0;i<n;i++){
		univ[i] = (char*) malloc(m*sizeof(char));
	}
  
	for(i=0;i<n;i++){
		new[i] = (char*) malloc(m*sizeof(char));
	}


	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			univ[i][j] = (char) abs(rand()%2);
		}		
	}
 
	//printf("Matrice Iniziale\n");
	//stampaMatrice(univ,n,m); 
	/**LIFE CICLE**/
	for(k=0;k<round;k++){
		lifecicle(univ,new,n,m);
	}
	//printf("Matrice finale\n");
	//stampaMatrice(univ,n,m);
	clock_t end = clock(); // ARRIVED!!!
	double tempo = (double)(end-begin)/CLOCKS_PER_SEC;
	printf("\n\nHo impiegato %.4f\n", tempo);
  
	free(univ);
	free(new);
  
	return 0;
}

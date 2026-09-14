/*
Guilherme Ryu Ojima - 10769513

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_AMOSTRAS (100)

void inicializar_matriz(int n, int matriz[][n]);
void relatorio();
void fusao_sensores();
void distancia_segura();
void analise_risco_frontal();
void assistente_faixa();

int main(){

    int sensibilidade, menu;
    scanf("%d", &sensibilidade);

    int velocidades[MAX_AMOSTRAS][2], sensores_frontais[MAX_AMOSTRAS][3], sensores_laterais[MAX_AMOSTRAS][2];
    int processamento[MAX_AMOSTRAS][2], status[MAX_AMOSTRAS][3];

    // Menu
    do{
        scanf("%d", &menu);
        if(menu==1){ // Inicializar matrizes

        }
        else if(menu==2){ // Inserir nova amostra


        }
        else if(menu==3){ // Processar e exibir relatorio

        }
        else if(menu==4){ // Encerrar simulador
            break;
        }
        else{
            printf("Valor inválido");
        }

    }while(menu != 4);

    return 0;
}

void inicializar_matriz(int n, int matriz[][n]){
    for (int i=0; i<50; i++){
        for (int j=0; j<n; j++){
            matriz[i][j] = rand();
        }
    }
}

void relatorio(){

}
/*
Guilherme Ryu Ojima - 10769513
Gustavo
Raphael
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_AMOSTRAS (100)

void inicializar_matriz(int quantidade_linhas, int tamanho, int matriz[][tamanho]);
void relatorio();
void fusao_sensores(int linhas, int tamanho, float matriz[linhas][tamanho], int processamento[MAX_AMOSTRAS][2]);
void distancia_segura(int sensi, int atrito, int colunas, int quantidade, float vel[][colunas], float processamento[][colunas]);
void analise_risco_frontal(float velocidadeAtual, float velocidadeFrente, float distanciaSegura, float distanciaValidada, int status[][]);
void assistente_faixa(int quantidade_linhas, float velocidades[][2], float sensores[][2], int status[][3]);

int main(){

    float atrito;
    int sensibilidade, menu, quantidade_linhas;  // quantidade_linhas = quantidade de amostras nas matrizes
    scanf("%f", &atrito);
    scanf("%d", &sensibilidade);
    
    float velocidades[MAX_AMOSTRAS][2], sensores_frontais[MAX_AMOSTRAS][3], sensores_laterais[MAX_AMOSTRAS][2], processamento[MAX_AMOSTRAS][2];
    int status[MAX_AMOSTRAS][3];

    // Menu
    do{
        scanf("%d", &menu);
        if(menu==1){ // Inicializar matrizes

        }
        else if(menu==2){ // Inserir nova amostra

            quantidade_linhas++;
        }
        else if(menu==3){ // Processar e exibir relatorio
            
            distancia_segura(sensibilidade, atrito, 2, quantidade_linhas, velocidades, processamento);
            assistente_faixa(quantidade_linhas, velocidades, sensores_laterais, status);
            fusao_sensores(quantidade_linhas, 3, sensores_frontais, processamento);
            analise_risco_frontal(velocidadeAtual, velocidadeFrente, distanciaSegura, distanciaValidada, status);
        }
        else if(menu==4){ // Encerrar simulador
            break;
        }
        else{
            printf("Valor inválido/n");
        }

    }while(menu != 4);

    return 0;
}

void inicializar_matriz(int quantidade_linhas, int tamanho, int matriz[][tamanho]){
    quantidade_linhas = 50;
    for (int i=0; i<50; i++){
        for (int j=0; j<tamanho; j++){
            matriz[i][j] = rand();
        }
    }
}

void fusao_sensores(int linhas, int tamanho, float matriz[linhas][tamanho], int processamento[MAX_AMOSTRAS][2]){
    float auxiliar=0;
    //ORDENAÇÂO
    for (int i=0; i<linhas; i++){
        for (int k = 0; k < tamanho - 1; k++){
            for (int j =0; j<tamanho-1-k; j++){
                if(matriz[i][j]>matriz[i][j+1]){
                    auxiliar=matriz[i][j];
                    matriz[i][j]=matriz[i][j+1];
                    matriz[i][j+1]=auxiliar;
               }
            }
        }
    }
    for (int l=0; l<linhas;l++){
        processamento[l][0]=matriz[l][1];
    }  
    
}

void distancia_segura(int sensi, int atrito, int colunas, int quantidade, float vel[][colunas], float processamento[][colunas]){
    int reacao;
    if (sensi == 1){
        reacao = 1;
    }
    else if(sensi == 2){
        reacao = 2;
    }
    else{
        reacao = 3;
    }

    for (int i=0; i<quantidade; i++){
        float velocidade = vel[i][0] / 3.6;
        float distancia = (velocidade * reacao) + (velocidade * velocidade) / (2 * atrito * 9.81);
        processamento[i][1] = distancia;
    }
         
}

    void analise_risco_frontal(float velocidadeAtual, float velocidadeFrente, float distancia_segura, float distancia_validada, int status[]){
        distancia_validada = validada
        distancia_segura = seguro
        float velocidadeRelativa = velocidadeAtual - velocidadeFrente 
        if( velocidadeRelativa > 0){
            if (validada >= seguro){
                status[][0] = 0;
            }
            else if (validada < segura && validade >= (segura *0.5)){
                status[][0] = 1;
            }
            else{
                status[][0] = 2;
            }
        }
        else if (velocidadeRelativa <= 0){
            status[][0] = 0;
        }
    }

void assistente_faixa(int quantidade_linhas, float velocidades[][2], float sensores[][2], int status[][3]){
    float margem_dinamica;
    for (int i=0; i<quantidade_linhas; i++){
        margem_dinamica = (velocidades[i][0] - 80) * 0.01 + 0.5;
    }

    for (int i=0; i < quantidade_linhas; i++){
        float esquerda = sensores[i][0];
        float direita = sensores[i][1];
        
        if (esquerda < margem_dinamica){
            status[i][1] = 2;
        } else if (esquerda < margem_dinamica + 0.2){
            status[i][1] = 1;
        } else{
            status[i][1] = 0;
        }

        if (direita < margem_dinamica){
            status[i][2] = 2;
        } else if (direita < margem_dinamica + 0.2){
            status[i][2] = 1;
        } else{
            status[i][2] = 0;
        }

    }
}



    void relatorio(){

        
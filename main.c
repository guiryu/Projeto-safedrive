/*
Guilherme Ryu Ojima - 10769513
Gustavo
Raphael
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_AMOSTRAS (100)
#define SEPARADOR ("================\n")


void inicializar_matriz(int quantidade_linhas, int tamanho, float matriz[][tamanho]);
 void relatorio (int quantidade_linhas, float velocidades[MAX_AMOSTRAS][2], float sensores_frontais[MAX_AMOSTRAS][3] ,float sensores_laterais[MAX_AMOSTRAS][2], float processamento[MAX_AMOSTRAS][2] , float status[MAX_AMOSTRAS][3]);
void fusao_sensores(int linhas, int tamanho, float matriz[linhas][tamanho], float processamento[MAX_AMOSTRAS][2]);
void distancia_segura(int sensi, int atrito, int colunas, int quantidade, float vel[][colunas], float processamento[][colunas]);
void analise_risco_frontal(int quantidade_linhas, float velocidades[MAX_AMOSTRAS][2], float processamento[MAX_AMOSTRAS][2], float status[MAX_AMOSTRAS][3]);
void assistente_faixa(int quantidade_linhas, float velocidades[][2], float sensores[][2], float status[][3]);

int main(){

    float atrito;
    int sensibilidade, menu, quantidade_linhas = 0;  // quantidade_linhas = quantidade de amostras nas matrizes
    printf("Atrito: ");
    scanf("%f", &atrito);
    printf("Sensibilidade: ");
    scanf("%d", &sensibilidade);
    
    float velocidades[MAX_AMOSTRAS][2], sensores_frontais[MAX_AMOSTRAS][3], sensores_laterais[MAX_AMOSTRAS][2], processamento[MAX_AMOSTRAS][2];
    float status[MAX_AMOSTRAS][3];

    // Menu
    do{
        printf(SEPARADOR);
        printf("Menu: \n"
            "1- Carregar dados iniciais\n"
            "2- Inserir nova amostra\n"
            "3- Processar e exibir relatório de riscos\n"
            "4- Sair\n");
        printf(SEPARADOR);    
        printf("Escolha: ");
        scanf("%d", &menu);
        printf(SEPARADOR);

        if(menu==1){ // Inicializar matrizes
            quantidade_linhas = 50;
            inicializar_matriz(quantidade_linhas, 2, velocidades);
            inicializar_matriz(quantidade_linhas, 3, sensores_frontais);
            inicializar_matriz(quantidade_linhas, 2, sensores_laterais);
            inicializar_matriz(quantidade_linhas, 2, processamento);
            inicializar_matriz(quantidade_linhas, 3, status);     
        }
        else if(menu==2){ // Inserir nova amostra
            quantidade_linhas++;
            // Velocidades
            printf("Velocidade atual: ");
            scanf("%f", &velocidades[quantidade_linhas][0]);
            printf("Velocidade do veículo à frente: ");
            scanf("%f", &velocidades[quantidade_linhas][1]);
            // Sensores frontais
            printf("Radar: ");
            scanf("%f", &sensores_frontais[quantidade_linhas][0]);
            printf("Lidar: ");
            scanf("%f", &sensores_frontais[quantidade_linhas][1]);
            printf("Câmera: ");
            scanf("%f", &sensores_frontais[quantidade_linhas][2]);
            // Sensores laterais
            printf("Distância da faixa esquerda: ");
            scanf("%f", &sensores_laterais[quantidade_linhas][0]);
            printf("Distância da faixa direita: ");
            scanf("%f", &sensores_laterais[quantidade_linhas][1]);
        }
        else if(menu==3){ // Processar e exibir relatorio
            
            distancia_segura(sensibilidade, atrito, 2, quantidade_linhas, velocidades, processamento);
            assistente_faixa(quantidade_linhas, velocidades, sensores_laterais, status);
            fusao_sensores(quantidade_linhas, 3, sensores_frontais, processamento);
            analise_risco_frontal(quantidade_linhas,velocidades, processamento, status);
            relatorio(quantidade_linhas, velocidades, sensores_frontais, sensores_laterais, processamento ,status);
        }
        else if(menu==4){ // Encerrar simulador
            printf("FIM\n");
            break;
        }
        else{
            printf("Valor inválido\n");
        }

    }while(menu != 4);

    return 0;
}

void inicializar_matriz(int quantidade_linhas, int colunas, float matriz[][colunas]){
    quantidade_linhas = 50;
    for (int i=0; i<50; i++){
        for (int j=0; j<colunas; j++){
            matriz[i][j] = rand() % 1000 + 1;
        }
    }
}

void fusao_sensores(int linhas, int tamanho, float matriz[linhas][tamanho], float processamento[MAX_AMOSTRAS][2]){
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

    void analise_risco_frontal(int quantidade_linhas, float velocidades[MAX_AMOSTRAS][2], float processamento[MAX_AMOSTRAS][2], float status[MAX_AMOSTRAS][3]){
        float distancia_validada = processamento[1][0];
        float distancia_segura = processamento[1][1];
        float velocidadeAtual =velocidades[1][0];
        float velocidadeFrente = velocidades[1][1];        
        float velocidadeRelativa = velocidadeAtual - velocidadeFrente;
        if( velocidadeRelativa > 0){
            if (distancia_validada >= distancia_segura){
                for (int i = 0; i < quantidade_linhas; i++){
                    status[i][0] = 0;    
                    }    
                }
            else if (distancia_validada < distancia_segura && distancia_validada >= (distancia_segura *0.5)){
                for (int i = 0; i < quantidade_linhas; i++){
                    status[i][0] = 1;
                    }
                }
            else{
                for (int i = 0; i < quantidade_linhas; i++){
                    status[i][0] = 2;
                    }
                }
            }
        else if (velocidadeRelativa <= 0){
            for (int i = 0; i < quantidade_linhas; i++){
            status[i][0] = 0;
            }
        }
    }

void assistente_faixa(int quantidade_linhas, float velocidades[][2], float sensores[][2], float status[][3]){
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



    void relatorio (int quantidade_linhas, float velocidades[MAX_AMOSTRAS][2], float sensores_frontais[MAX_AMOSTRAS][3] ,float sensores_laterais[MAX_AMOSTRAS][2], float processamento[MAX_AMOSTRAS][2] , float status[MAX_AMOSTRAS][3]){

        for (int i=0; i<quantidade_linhas; i++){
            printf(SEPARADOR);
            printf("Amostra %d\n", i+1);
            printf("DADOS DE ENTRADA:\n");
            printf("=====VELOCIDADES=====\n");
            printf("Velocidade Atual: %.2f\n", velocidades[i][0]);
            printf("Velocidade do veículo à frente: %.2f\n", velocidades[i][1]);
            printf("=====SENSORES FRONTAIS=====\n");
            printf("Sensor Radar: %.2f\n", sensores_frontais[i][0]);
            printf("Sensor Lidar: %.2f\n", sensores_frontais[i][1]);
            printf("Sensor Câmera: %.2f\n", sensores_frontais[i][2]);
            printf("=====SENSORES LATERAIS=====\n");
            printf("Distância da faixa esquerda: %.2f\n", sensores_laterais[i][0]);
            printf("Distância da faixa direita: %.2f\n", sensores_laterais[i][1]);
            
            printf(SEPARADOR);
            printf("DADOS PROCESSADOS:\n ");
            printf("Distância Validada: %.2f\n", processamento[i][0]);
            printf("Distância Segura Exigida: %.2f\n", processamento[i][1]);
            
            printf(SEPARADOR);
            printf("TRADUTOR DE STATUS E MENSAGENS DE ALERTA\n");
            printf("Status frontal:\n ");
            if (status[i][0] == 0){
                printf("SEGURO\n");
            } else if(status[i][0] == 1){
                printf("ATENÇÃO\n");
            }else {
                printf("RISCO DE COLISÃO (AEB ACIONADO)\n");
            }
            printf("Faixa esquerda:\n ");
            if (status[i][1] == 0){
                printf("NORMAL\n");
            } else if (status[i][1] == 1){
                printf("ATENÇÃO\n");
            }else {
                printf("PERIGO DE INVASÃO\n");   
            }
            
            printf("Faixa direita:\n ");
            if (status[i][2] == 0){
                printf("NORMAL\n");
            } else if (status[i][2] == 1){
                printf("ATENÇÃO\n");
            }else {
                printf("PERIGO DE INVASÃO\n");   
            }

            printf(SEPARADOR);
            printf("DECISÃO GERAL DO SISTEMA\n");
        
            if (status[i][0] ==2 || status[i][1] ==2 || status[i][2]==2){
                printf("STATUS GERAL: INTERVEÇÃO CRÍTICA EXIGIDA\n");
            }else if(status[i][0] ==1 || status[i][1] ==1 || status[i][2]==1){
                printf("STATUS GERAL: ATENÇÃO\n");
            }else{
                printf("STATUS GERAL: NORMAL\n");
            }
        }

    }

        
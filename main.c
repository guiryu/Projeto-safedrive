/*
Guilherme Ryu Ojima - 10769513
Gustavo De Souza Horner HOE - 10769967
Raphael Norio Arashiro Uehara - 10774187
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_AMOSTRAS (100)
#define SEPARADOR ("================\n")


void inicializar_matriz(int quantidade_linhas, int tamanho, float matriz[][tamanho], int range);
void relatorio (int quantidade_linhas, float velocidades[MAX_AMOSTRAS][2], float sensores_frontais[MAX_AMOSTRAS][3] ,float sensores_laterais[MAX_AMOSTRAS][2], float processamento[MAX_AMOSTRAS][2] , float status[MAX_AMOSTRAS][3]);
void fusao_sensores(int linhas, int tamanho, float sensores[linhas][tamanho], float processamento[MAX_AMOSTRAS][2]);
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
            inicializar_matriz(quantidade_linhas, 2, velocidades, 200);
            inicializar_matriz(quantidade_linhas, 3, sensores_frontais, 10);
            inicializar_matriz(quantidade_linhas, 2, sensores_laterais, RAND_MAX);
            inicializar_matriz(quantidade_linhas, 2, processamento, 3);
            inicializar_matriz(quantidade_linhas, 3, status, 3);     
        }
        else if(menu==2){ // Inserir nova amostra
            // Velocidades
            printf("Velocidade atual  (km/h): ");
            scanf("%f", &velocidades[quantidade_linhas][0]);
            printf("Velocidade do veículo à frente (km/h): ");
            scanf("%f", &velocidades[quantidade_linhas][1]);
            // Sensores frontais
            printf("Radar: ");
            scanf("%f", &sensores_frontais[quantidade_linhas][0]);
            printf("Lidar: ");
            scanf("%f", &sensores_frontais[quantidade_linhas][1]);
            printf("Câmera: ");
            scanf("%f", &sensores_frontais[quantidade_linhas][2]);
            // Sensores laterais
            printf("Distância da faixa esquerda (metros): ");
            scanf("%f", &sensores_laterais[quantidade_linhas][0]);
            printf("Distância da faixa direita (metros): ");
            scanf("%f", &sensores_laterais[quantidade_linhas][1]);
            quantidade_linhas++;
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

void inicializar_matriz(int quantidade_linhas, int colunas, float matriz[][colunas], int range){
    quantidade_linhas = 50;
    if (range == RAND_MAX){  // Para os sensores laterais
        for (int i=0; i<50; i++){
            for (int j=0; j<colunas; j++){
                matriz[i][j] = (float)rand() / range; 
            }
        }
    }
    else{ // Para as outras matrizes
        for (int i=0; i<50; i++){
            for (int j=0; j<colunas; j++){
                matriz[i][j] = rand() % range; 
            }
        }
    }   
}


void fusao_sensores(int linhas, int tamanho, float sensores[linhas][tamanho], float processamento[MAX_AMOSTRAS][2]){
    float auxiliar=0;
    //ORDENAÇÂO
    for (int i=0; i<linhas; i++){
        for (int k = 0; k < tamanho - 1; k++){
            for (int j =0; j<tamanho-1-k; j++){
                if(sensores[i][j]>sensores[i][j+1]){
                    auxiliar=sensores[i][j];
                    sensores[i][j]=sensores[i][j+1];
                    sensores[i][j+1]=auxiliar;
               }
            }
        }
    }
    for (int l=0; l<linhas;l++){
        processamento[l][0]=sensores[l][1];
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

    for (int i=0; i<quantidade_linhas; i++){
        float velocidadeRelativa = velocidades[i][0] - velocidades[i][1]; 
           
        if( velocidadeRelativa > 0){  
            if (processamento[i][0] >= processamento[i][1]){
                status[i][0] = 0;    
                    }
            else if (processamento[i][0] < processamento[i][1] && processamento[i][0] >= (processamento[i][1] *0.5)){
                status[i][0] = 1;
            }
            else{
                status[i][0] = 2;
            }
        }
        else if (velocidadeRelativa <= 0){
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

        
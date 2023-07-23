/**
  * Estruturas de Dados 1 - Gerenciador de Pilhas com uma Fila
  * Desenvolvedor: Florindo Rian Silva Carreteiro
  * Objetivo: 
  *   Exemplificar um dos usos de pilhas e filas ao mesmo tempo.
  */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct NO{
    int dado;
    struct NO* prox;
    struct NO* ant;
}NO;

typedef struct PILHA{
    int tam;
    NO* ini;
    NO* fim;
    struct PILHA* prox;
    struct PILHA* ant;
}PILHA;

typedef struct FILAPILHAS{
    int tam;
    PILHA* ini;
    PILHA* fim;
}FILAPILHAS;

//Protótipos das funções das listas encadeadas
void insereNoInicio(PILHA* pi, int elemento);
int removeDoInicio(PILHA* pi, int* elementoRem);
void imprimir(PILHA* pi);
void insereNoFimFila(FILAPILHAS* fi, PILHA** pi);
int removeDoInicioFila(FILAPILHAS* fi, PILHA** pilhaRem);
void imprimirFila(FILAPILHAS* fi);

void menu(){
    printf("\n\n");
    printf("====================================\n");
    printf("1 - Inserir um inteiro no início da Pilha de trabalho;\n");
    printf("2 - Remover um inteiro do início da Pilha de trabalho;\n");
    printf("3 - Imprimir a Pilha de trabalho;\n");
    printf("4 - Inserir a Pilha de trabalho no fim da Fila de pilhas e criar nova pilha de trabalho;\n");
    printf("5 - Remover a Pilha do início da Fila de pilhas;\n");
    printf("6 - Imprimir a Fila de pilhas;\n");
    printf("0 - Encerrar.\n");
    printf("====================================\n");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int op=0, dado=0, dadoRem=0;
    
    FILAPILHAS filaPilhas;
    filaPilhas.ini = NULL; filaPilhas.fim = NULL; filaPilhas.tam = 0;
    
    PILHA* pilhaTrab = (PILHA*) malloc(sizeof(PILHA));
    pilhaTrab->ini = NULL; pilhaTrab->fim = NULL; pilhaTrab->prox = NULL; pilhaTrab->ant = NULL; pilhaTrab->tam = 0;
    do{
        menu();
        printf("Operação escolhida: "); scanf("%d", &op);
        
        switch(op){
            case 0:
                break;
            case 1:
                printf("Digite o dado a ser inserido: "); scanf("%d", &dado);
                insereNoInicio(pilhaTrab, dado);
                break;
            case 2:
                if (removeDoInicio(pilhaTrab, &dadoRem)){
                    printf("O elemento %d que estava no topo da pilha de trabalho foi removido.\n", dadoRem);
                } else{
                    printf("ERRO. Não se pode remover um elemento de uma lista vazia.\n");
                }
                break;
            case 3:
                printf("\nPILHA DE TRABALHO:\n");
                imprimir(pilhaTrab);
                break;
            case 4:
                insereNoFimFila(&filaPilhas, &pilhaTrab);
                printf("A pilha de trabalho foi inserida no fim da fila e uma nova pilha de trabalho foi gerada.\n");
                break;
            case 5:
                if (removeDoInicioFila(&filaPilhas, &pilhaTrab)){
                    printf("A pilha que estava no início da fila foi removida dela e agora está como pilha de trabalho.\n");
                } else{
                    printf("ERRO. Não se pode remover uma pilha de uma fila vazia.\n");    
                }
                break;
            case 6:
                printf("\nFILA DE PILHAS:\n");
                imprimirFila(&filaPilhas);
                break;
            default:
                printf("A operação escolhida não é válida.\n");
        }
        
    } while(op != 0);
    
    free(pilhaTrab);
    printf("Fim da execução.\n");
    return 0;
}

void insereNoInicio(PILHA* pi, int elemento){
    NO* ptr = (NO*) malloc(sizeof(NO));
    if (ptr == NULL){
        printf("ERRO na alocação!\n");
        exit(1);
    }
    ptr->dado = elemento;
    ptr->prox = NULL;
    ptr->ant = NULL;
    
    if (pi->ini == NULL){
        pi->ini = ptr;
        pi->fim = ptr;
    } else{
        ptr->prox = pi->ini;
        pi->ini = ptr;
        ptr->prox->ant = ptr;
    }
    ptr = NULL;
    pi->tam++;
}

int removeDoInicio(PILHA* pi, int* elementoRem){
    NO* ptr = pi->ini;
    if(pi->ini == NULL){
        return 0;
    } else{
        pi->ini = pi->ini->prox;
        //Caso a lista possua um único elemento
        if (pi->ini == NULL){
            pi->fim = NULL;
        } else{
            pi->ini->ant = NULL;
        }
        ptr->prox = NULL;
        *elementoRem = ptr->dado;
        free(ptr);
        pi->tam--;
        return 1;
    }
}

void imprimir(PILHA* pi){
    NO* ptr = pi->ini;
    printf("Início -> ");
    while(ptr != NULL){
        printf("%d ", ptr->dado);
        ptr = ptr->prox;
    }
    printf("<- Fim\n");
}

void insereNoFimFila(FILAPILHAS* fi, PILHA** pi){
    if (fi->ini == NULL){
        fi->ini = *pi;
        fi->fim = *pi;
    } else{
        fi->fim->prox = *pi;
        (*pi)->ant = fi->fim;
        fi->fim = *pi;
    }
    fi->tam++;
    PILHA* novaP = (PILHA*) malloc(sizeof(PILHA)); //Será que está certo, ou seria *pi
    if(novaP == NULL){
        printf("ERRO na alocacao.\n");
        exit(1);
    }
    novaP->ini = NULL; novaP->fim = NULL; novaP->prox = NULL; novaP->ant = NULL; novaP->tam = 0;
    *pi = novaP;
}

int removeDoInicioFila(FILAPILHAS* fi, PILHA** pilhaRem){
    PILHA* pi = fi->ini;
    
    if(fi->ini == NULL){
        return 0;
    } else{
        fi->ini = fi->ini->prox;
        //Caso a lista possua um único elemento
        if (fi->ini == NULL){
            fi->fim = NULL;
        } else{
            fi->ini->ant = NULL;
        }
        
        pi->prox = NULL;
        *pilhaRem = pi;
        pi = NULL;
        fi->tam--;
        return 1;
    }
}

void imprimirFila(FILAPILHAS* fi){
    PILHA* piVar = fi->ini;
    for (int i=0; i<fi->tam; i++){
        printf("Pilha %d: ", i);
        imprimir(piVar);
        piVar = piVar->prox;
    }
}
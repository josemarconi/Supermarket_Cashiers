#include "Sistema.h"

int main() 
{
    int numCaixas = 5;

    Caixa* caixas = (Caixa*)malloc(numCaixas * sizeof(Caixa));

    if (caixas == NULL) 
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    for (int i = 0; i < numCaixas; i++) 
    {
        caixas[i].id = i;
        caixas[i].aberto = 1;
        for (int j = 0; j < 3; j++) 
        {
            caixas[i].filaPrioridade[j] = NULL;
        }
    }

    int opcao;
    
    do 
    {
        printf("\nMenu:\n");
        printf("1. Cadastrar um Cliente\n");
        printf("2. Atender um Cliente\n");
        printf("3. Abrir ou Fechar um Caixa\n");
        printf("4. Imprimir a Lista de Clientes em Espera\n");
        printf("5. Imprimir o Status dos Caixas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) 
        {
            case 1:
                cadastrarCliente(caixas, numCaixas);
                break;
            case 2:
                atenderCliente(caixas, numCaixas);
                break;
            case 3: 
            {
                int idCaixa, abrir;
                printf("ID do caixa (0 a %d): ", numCaixas - 1);
                scanf("%d", &idCaixa);
                printf("1 para abrir, 0 para fechar: ");
                scanf("%d", &abrir);
                abrirFecharCaixa(caixas, numCaixas, idCaixa, abrir);
                break;
            }
            case 4:
                imprimirClientesEspera(caixas, numCaixas);
                break;
            case 5:
                imprimirStatusCaixas(caixas, numCaixas);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    free(caixas);
    return 0;
}
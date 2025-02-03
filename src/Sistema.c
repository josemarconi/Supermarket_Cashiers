#include "Sistema.h"

//Função para contar quantos caixas estão abertos//
int contarCaixasAbertos(Caixa* caixas, int numCaixas) 
{
    int count = 0;

    for (int i = 0; i < numCaixas; i++) 
    {
        if (caixas[i].aberto) 
        {
            count++;
        }
    }
    return count;
}


//Função para encontrar o caixa com menos clientes, retornando seu indice//
int caixaComMenosClientes(Caixa* caixas, int numCaixas) 
{
    int minClientes = INT_MAX;
    int caixaEscolhido = -1;

    for (int i = 0; i < numCaixas; i++) 
    {
        if (caixas[i].aberto) 
        {
            int numClientes = 0;

            for (int j = 0; j < 3; j++) 
            {
                Cliente* cliente = caixas[i].filaPrioridade[j];

                while (cliente != NULL) 
                {
                    numClientes++;
                    cliente = cliente->prox;
                }
            }
            if (numClientes < minClientes) {
                minClientes = numClientes;
                caixaEscolhido = i;
            }
        }
    }

    return caixaEscolhido;
}

//Função para verificar se o CPF já fo icadastrado no sistema//
int cpfJaCadastrado(Caixa* caixas, int numCaixas, const char* cpf) 
{
    for (int i = 0; i < numCaixas; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            Cliente* cliente = caixas[i].filaPrioridade[j];

            while (cliente != NULL) 
            {
                if (strcmp(cliente->CPF, cpf) == 0) 
                {
                    return 1;
                }

                cliente = cliente->prox;
            }
        }
    }
    return 0;
}

//Função para cadastrar um novo cliente no sistema//
void cadastrarCliente(Caixa* caixas, int numCaixas) 
{
    //Primeiro averigua se todos os caixas estão fechados//
    if (contarCaixasAbertos(caixas, numCaixas) == 0) 
    {
        printf("Todos os caixas estão fechados. Não é possível cadastrar clientes.\n");
        return;
    }

    //Aloca memória para um novo cliente//
    Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));

    if (novoCliente == NULL)
    {
        printf("Erro ao alocar memória.\n");
        return;
    }

    printf("Nome do cliente: ");
    scanf(" %[^\n]", novoCliente->nome);

    printf("CPF do cliente: ");
    scanf("%s", novoCliente->CPF);

    //Chama a função para encontrar se há um cpf igual existente//
    if (cpfJaCadastrado(caixas, numCaixas, novoCliente->CPF)) 
    {
        printf("CPF já cadastrado.\n");
        free(novoCliente);
        return;
    }

    printf("Prioridade do cliente (1: alta, 2: média, 3: baixa): ");
    scanf("%d", &novoCliente->prioridade);

    printf("Número de itens no carrinho: ");
    scanf("%d", &novoCliente->itens_Carrinho);

    novoCliente->prox = NULL;

    int caixaEscolhido;
    printf("Escolha o caixa (0 a %d): ", numCaixas - 1);
    scanf("%d", &caixaEscolhido);

    //Averigua se o caixa escolhido está aberto ou é válido//
    if (caixaEscolhido < 0 || caixaEscolhido >= numCaixas || !caixas[caixaEscolhido].aberto) 
    {
        printf("Caixa inválido ou fechado.\n");
        free(novoCliente);
        return;
    }

    //Iguala uma váriavel fila(ponteiro para um ponteiro de Cliente) a fila de prioridade existente//
    int prioridadeIndex = novoCliente->prioridade - 1;
    Cliente** fila = &caixas[caixaEscolhido].filaPrioridade[prioridadeIndex];

    //Percorre a fila até encontrar o Nulo//
    while (*fila != NULL) 
    {
        // Atualiza fila para apontar para o ponteiro prox do cliente atual //
        fila = &(*fila)->prox;
    }
    
    //Adiciona o cliente na fila de prioridade do caixa que foi escolhido//
    *fila = novoCliente;

    printf("Cliente cadastrado com sucesso no caixa %d.\n", caixaEscolhido);
}

//Função para atendimento de um cliente//
void atenderCliente(Caixa* caixas, int numCaixas) 
{
    int caixaEscolhido;
    printf("Escolha o caixa (0 a %d): ", numCaixas - 1);
    scanf("%d", &caixaEscolhido);

    if (caixaEscolhido < 0 || caixaEscolhido >= numCaixas || !caixas[caixaEscolhido].aberto) 
    {
        printf("Caixa inválido ou fechado.\n");
        return;
    }

    for (int i = 0; i < 3; i++) 
    {   
        //itera em todas as 3 filas //
        if (caixas[caixaEscolhido].filaPrioridade[i] != NULL) 
        {
            Cliente* clienteAtendido = caixas[caixaEscolhido].filaPrioridade[i];
            caixas[caixaEscolhido].filaPrioridade[i] = clienteAtendido->prox; //Atualiza o ponteiro da fila para o próximo cliente//
            printf("Atendendo cliente: %s, CPF: %s\n", clienteAtendido->nome, clienteAtendido->CPF);
            free(clienteAtendido);
            return;
        }
    }

    printf("Nenhum cliente na fila do caixa %d.\n", caixaEscolhido);
}

void abrirFecharCaixa(Caixa* caixas, int numCaixas, int idCaixa, int abrir) 
{
    if (idCaixa < 0 || idCaixa >= numCaixas) 
    {
        printf("Caixa inválido.\n");
        return;
    }

    if (!abrir) 
    {
        if (contarCaixasAbertos(caixas, numCaixas) == 1) 
        {
            printf("Não é possível fechar o último caixa aberto.\n");
            return;
        }

        for (int i = 0; i < 3; i++) 
        {
            Cliente* cliente = caixas[idCaixa].filaPrioridade[i];

            while (cliente != NULL) 
            {
                Cliente* proxCliente = cliente->prox;
                int novoCaixa = caixaComMenosClientes(caixas, numCaixas); //retorna o indice do caixa//

                if (novoCaixa != -1) 
                {
                    //Remove o Cliente da fila atual//
                    cliente->prox = NULL;
                    int prioridadeIndex = cliente->prioridade - 1;

                    //Iguala uma váriavel fila(ponteiro para um ponteiro de Cliente) a fila de prioridade existente//
                    Cliente** fila = &caixas[novoCaixa].filaPrioridade[prioridadeIndex];

                    //Percorre a fila até encontrar o Nulo//
                    while (*fila != NULL) 
                    {
                        fila = &(*fila)->prox;
                    }
                    //Adiciona o cliente na fila de prioridade do caixa que foi escolhido//
                    *fila = cliente;
                }
                //Atualiza para o próximo cliente a ser movido//
                cliente = proxCliente;
            }
            //Após mover todos, define a fila de prioridade como nula//
            caixas[idCaixa].filaPrioridade[i] = NULL;
        }
    }

    //Atualiza o estado do caixa//
    caixas[idCaixa].aberto = abrir;
    printf("Caixa %d %s com sucesso.\n", idCaixa, abrir ? "aberto" : "fechado");
}

void imprimirClientesEspera(Caixa* caixas, int numCaixas) 
{
    for (int i = 0; i < numCaixas; i++) 
    {
        if (caixas[i].aberto) 
        {
            printf("Caixa %d:\n", i);

            for (int j = 0; j < 3; j++) 
            {
                Cliente* cliente = caixas[i].filaPrioridade[j];

                while (cliente != NULL) 
                {
                    printf("  Nome: %s, CPF: %s, Prioridade: %d, Itens: %d\n",cliente->nome, cliente->CPF, cliente->prioridade, cliente->itens_Carrinho);
                    cliente = cliente->prox;
                }
            }
        }
    }
}

void imprimirStatusCaixas(Caixa* caixas, int numCaixas) 
{
    for (int i = 0; i < numCaixas; i++) 
    {
        printf("Caixa %d: %s\n", i, caixas[i].aberto ? "Aberto" : "Fechado");

        if (caixas[i].aberto) 
        {
            int numClientes = 0;
            for (int j = 0; j < 3; j++) 
            
            {
                Cliente* cliente = caixas[i].filaPrioridade[j];
                while (cliente != NULL) 
                {
                    numClientes++;
                    cliente = cliente->prox;
                }
            }

            printf("  Clientes em espera: %d\n", numClientes);
        }
    }
}
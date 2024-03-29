#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Esta é a função que verifica se o arquivo existe, e se não existir, cria
void verifica_arquivo(FILE *arq, char *nome_arquivo)
{
    if (arq == NULL)
    {
        arq = fopen("Contatos.txt", "a");
        fprintf(arq, "0");
        fclose(arq);
    }
}
// Aqui termina a função de verificar o arquivo

// Esta é a função que atualiza o número de contatos
int numero_contatos(int add_ou_rmv)
{
    char caracter;
    FILE *arq = fopen("Contatos.txt", "r");
    FILE *temp = fopen("Temp.txt", "w");
    
    while ((caracter = fgetc(arq)) != EOF)
        fputc(caracter, temp);

    fclose(arq);
    fclose(temp);
    arq = fopen("contatos.txt", "w");
    temp = fopen("Temp.txt", "r");

    char num_char = fgetc(temp);
    int num_int = (num_char - '0') + add_ou_rmv;
    num_char = num_int + '0';
    fputc(num_char, arq);

    while ((caracter = fgetc(temp)) != EOF)
        fputc(caracter, arq);

    fclose(arq);
    fclose(temp);
    remove("Temp.txt");
    return num_int;
}
// Aqui termina a função de atualizar o número de contatos

// Esta é a função que escreve no arquivo Contatos.txt
void escrever_arquivo(int num_caracteres, FILE *arq)
{
    for (int i = 0; i < num_caracteres; i++)
    {
       char caracter = getchar();
        if (caracter == '\n')
            break;
        fputc(caracter, arq);
    }
    fprintf(arq, "; ");
}
// Aqui termina a função de escrever no arquivo Contatos.txt

void adicionar_contato()
{
    FILE *arq = fopen("Contatos.txt", "a");
    printf("\nADICIONAR CONTATO\n");

    printf("Digite o nome: ");
    fputs("\n", arq);
    escrever_arquivo(45, arq);
    printf("Digite o endereco: ");
    escrever_arquivo(100, arq);
    printf("Digite o telefone residencial: ");
    escrever_arquivo(45, arq);
    printf("Digite o telefone celular: ");
    escrever_arquivo(45, arq);
    printf("Digite a data de nascimento: ");
    escrever_arquivo(15, arq);
    
    fclose(arq);
    numero_contatos(1);
}
// Aqui termina a função de adicionar contatos

// Esta é a função para remover um contato da lista
void remover_contato()
{
    char nome[20], verifica[150];
    FILE *arq = fopen("Contatos.txt", "r+");
    long int init = 0;
    init = ftell(arq);

    printf("\nREMOVER CONTATO\n");
    printf("Digite o nome do contato que voce deseja remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strlen(nome) - 1] = nome[strlen(nome)];
   
    while (fgets(verifica, sizeof(verifica), arq) != NULL)
    {
        if (strstr(verifica, nome) != NULL)
        { 
            int aux = strlen(verifica);
            fseek(arq, init, SEEK_SET);

            for (int i = 0; i < aux; i++)
               putc((int) '-', arq);
            break;
        }
        init = ftell(arq);
    }
    fclose(arq);
    arq = fopen("Contatos.txt", "r");
    FILE *temp = fopen("Temp.txt", "w");

    char num_char = fgetc(arq), caracter;
    int num_int = (num_char - '0');
    num_char = num_int + '0';
    fputc(num_char, temp);

    while ((caracter = fgetc(arq)) != EOF)
    {
        if (caracter == '-')
            continue;
        fputc(caracter, temp);
    }
    fclose(arq);
    fclose(temp);
    arq = fopen("Contatos.txt", "w");
    temp = fopen("Temp.txt", "r"); 

    while ((caracter = fgetc(temp)) != EOF)
        fputc(caracter, arq);

    fclose(arq);
    fclose(temp);
    remove("Temp.txt");
    numero_contatos(-1);
}
// Aqui termina a função de remover contatos

// Esta é a função para verificar se já existe um determinado contato
void pesquisar_contato()
{
    char nome[20], verifica[150];
    FILE *arq = fopen("Contatos.txt", "r");

    printf("\nPESQUISAR CONTATO\n");
    printf("Digite o nome do contato que voce deseja procurar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strlen(nome) - 1] = nome[strlen(nome)];

    while (fgets(verifica, sizeof(verifica), arq) != NULL)
    {
        if (strstr(verifica, nome) != NULL)
        {
            printf("\n%s", verifica);
            fclose(arq); 
            return ;
        } 
    }
    printf("\nContato nao encontrado !!!!\n"); 
    fclose(arq);
}
// Aqui termina a função de procurar contatos

// Esta é a função para alterar um contato
void alterar_contato()
{
    char nome[100], verifica[1000];
    FILE *arq = fopen("Contatos.txt", "r+");
    long int init = 0;
    init = ftell(arq);

    printf("\nALTERAR CONTATO\n");
    printf("Digite o nome do contato que voce deseja alterar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strlen(nome) - 1] = nome[strlen(nome)];

    while (fscanf(arq, "%s%*c", verifica) != EOF)
    {
        if (strstr(verifica, nome) != NULL)
        {
            int aux = strlen(verifica);
            fseek(arq, init, SEEK_SET);

            for (int i = 0; i < aux; i++)
                putc((int) '-', arq);

            fseek(arq, init, SEEK_SET);

            printf("Digite o nome: ");
            fputs("\n", arq);
            escrever_arquivo(45, arq);
            printf("Digite o endereco: ");
            escrever_arquivo(100, arq);
            printf("Digite o telefone residencial: ");
            escrever_arquivo(45, arq);
            printf("Digite o telefone celular: ");
            escrever_arquivo(45, arq);
            printf("Digite a data de nascimento: ");
            escrever_arquivo(15, arq);
            break;
        }
        init = ftell(arq);
    }
    fclose(arq);
    arq = fopen("Contatos.txt", "r");
    FILE *temp = fopen("Temp.txt", "w");

    char num_char = fgetc(arq), caracter;
    int num_int = (num_char - '0');
    num_char = num_int + '0';
    fputc(num_char, temp);

    while ((caracter = fgetc(arq)) != EOF)
    {
         if (caracter == '-')
            continue;
        fputc(caracter, temp);
    }
    fclose(arq);
    fclose(temp);
    arq = fopen("contatos.txt", "w");
    temp = fopen("Temp.txt", "r");

    while ((caracter = fgetc(temp)) != EOF)
        fputc(caracter, arq);

    fclose(arq);
    fclose(temp);
    remove("Temp.txt");
}
// Aqui termina a função de alterar contatos

// Esta é a função que lista os contatos salvos
void listar_contato()
{
    FILE *arq = fopen("contatos.txt", "r");
    char caracter, n_contatos = fgetc(arq);
   
    printf("\nLISTAR CONTATOS\n");
    printf("\n======== Voce possui %c contatos ========\n", n_contatos);

    while ((caracter = fgetc(arq)) != EOF)
    {
        if (caracter == ';')
        {
            putchar('\n');
            continue;
        }
        putchar(caracter);
    }
    printf("\n");
    fclose(arq);
}
// Aqui termina a função que lista os contatos

// Esta é a função que exibe o menu e recebe do usuário o que ele deseja fazer
int menu()
{
    int opcao;

    printf("\n======== ESTA E SUA AGENDA DE CONTATOS! ========\n");
    printf("\nO que voce gostaria de fazer?\n");

    printf("\n1. Adicionar Contato\n");
    printf("2. Remover Contato\n");
    printf("3. Pesquisar Contato\n");
    printf("4. Alterar Contato\n");
    printf("5. Listar todos os contatos\n");
    printf("6. Sair\n");

    printf("\nDigite uma opcao:");
    scanf("%d", &opcao);

    getchar();
    return opcao;
}
// Aqui termina a função menu

// Esta é a função principal, que nos guiará, conforme nossa escolha, à outras funções
int main()
{
    FILE *arq = fopen("Contatos.txt", "r");
    verifica_arquivo(arq, "Contatos.txt");

    while (1)
    {
        switch (menu())
        {
        case 1: adicionar_contato(); break;
        case 2: remover_contato(); break;
        case 3: pesquisar_contato(); break;
        case 4: alterar_contato(); break;
        case 5: listar_contato(); break;
        case 6: printf("\nSaindo da sua agenda de contatos...\n"); return 0;
        default: printf("\nOpcao invalida!\n"); break;
        }
    }
    return 0;
}
// Aqui termina a função principal

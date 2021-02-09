#include <stdio.h>
#include <stdlib.h>

//Esta é a função para escrevermos coisas no arquivo Contatos.txt
int escrever_arquivo(int num_caracteres, FILE *arq)
{
    char caracter;

    for (int i = 0; i < num_caracteres; i++)
    {
        caracter = getchar();
        if (caracter == '\n')
            break;
        fputc(caracter, arq);
    }
    fprintf(arq, "\n");

    return 0;
}
// Aqui termina a função de escrever no arquivo Contatos.txt

// Esta é a função que atualiza o número de contatos
int numero_contatos(int add_ou_rmv)
{
    char caracter;
    FILE *arq = fopen("contatos.txt", "r");
    FILE *temp = fopen("temp.dat", "w");

    while ((caracter = fgetc(arq)) != EOF)
        fputc(caracter, temp);

    fclose(arq);
    fclose(temp);
    arq = fopen("contatos.txt", "w");
    temp = fopen("temp.dat", "r");

    char num_char = fgetc(temp);
    int num_int = (num_char - '0') + add_ou_rmv;
    num_char = num_int + '0';
    fputc(num_char, arq);

    while ((caracter = fgetc(temp)) != EOF)
        fputc(caracter, arq);

    fclose(arq);
    fclose(temp);
    remove("temp.dat");
    return num_int;
}
// Aqui termina a função de atualizar o número de contatos

// Esta é a função para adicionar um novo contato à lista
int adicionar_contato()
{
    FILE *arq = fopen("Contatos.txt", "a");
    printf("\nADICIONAR CONTATO\n");

    printf("Digite o nome:");
    fputs("\nNome:", arq);
    escrever_arquivo(45, arq);

    printf("Digite o endereco:");
    fputs("Endereco:", arq);
    escrever_arquivo(100, arq);

    printf("Digite o telefone residencial:");
    fputs("Telefone residencial:", arq);
    escrever_arquivo(25, arq);

    printf("Digite o telefone celular:");
    fputs("Telefone celular:", arq);
    escrever_arquivo(25, arq);

    printf("Digite a data de nascimento:");
    fputs("Data de nascimento:", arq);
    escrever_arquivo(15, arq);
    fputs("===============================================\n", arq);

    fclose(arq);
    numero_contatos(1);
    return 0;
}
// Aqui termina a função de adicionar contatos

// Esta é a função que lista os contatos salvos
void listar_contato()
{
    FILE *arq = fopen("contatos.txt", "r");
    char caracter, n_contatos = fgetc(arq);

    printf("\n****** Voce possui %c contatos ******", n_contatos);
    while ((caracter = fgetc(arq)) != EOF)
        printf("%c", caracter);

    fclose(arq);
}

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
    while (1)
    {
        switch (menu())
        {
        case 1: adicionar_contato(); break;
        case 5: listar_contato(); break;
        case 6: return 0; 
        default: printf("Opcao invalida!\n"); break;
        }
    }
    return 0;
}
// Aqui termina a função principal

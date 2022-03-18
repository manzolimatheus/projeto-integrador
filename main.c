#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"
#include "styles.h"
#include "processor.h"
#include <locale.h>

void clear(){
    system("cls || clear");
}

void menu(int teamsCount)
{
    // Variáveis brutas
    struct Team teams[teamsCount];
    // Variáveis temporárias/auxiliares
    char team[20];
    int tempStorage;
    // Variáveis de controle
    int selectedOption;
    int hasTeams = 0;

menu:
    hr(3);
    printf("MENU \n");
    hr(3);
    printf("Escolha sua opção \n");
    hr(1);
    printf(GRN "[1]" RESET " - Cadastrar equipes \n");
    printf(GRN "[2]" RESET " - Visualizar equipes \n");
    printf(GRN "[3]" RESET " - Imprimir resultados \n");
    printf(GRN "[4]" RESET " - " RED "Sair \n" RESET);
    hr(1);
    printf("-> ");
    scanf("%i", &selectedOption);
    printf("\n");

    clear();
    
    switch (selectedOption)
    {
    case 1:
        printf(BLU "OPÇÃO ESCOLHIDA: Cadastrar equipes \n" RESET);
        goto registerTeams;
        break;
    case 2:
        printf(BLU "OPÇÃO ESCOLHIDA: Visualizar equipes \n" RESET);
        goto showTeams;
        break;
    case 3:
        printf(BLU "OPÇÃO ESCOLHIDA: Imprimir resultados \n" RESET);
        goto printToFile;
        break;
    case 4:
        printf(BLU "OPÇÃO ESCOLHIDA: Sair \n" RESET);
        goto exitProgram;
        break;

    default:
        printf(RED "Opção inválida! \n" RESET);
        goto menu;
        break;
    }

registerTeams:
    hr(3);
    printf("CADASTRAR EQUIPE\n");
    hr(1);

    printf("Quantidade de equipes inscritas: %i \n", teamsCount);

    for (int index = 0; index < teamsCount; index++)
    {
        hr(2);
        printf(BLU "Digite o nome da equipe (max. 20 caracteres): \n" RESET);
        printf("-> Nome: " GRN);
        scanf("%s", &team);
        printf(RESET);
        strcpy(teams[index].name, team);

        for (int j = 0; j < 3; j++)
        {
            printf(BLU "Digite o %iº melhor tempo da equipe: \n" RESET, j + 1);
            printf("-> Minutos do %iº Tempo : " GRN, j + 1);
            scanf("%i", &tempStorage);
            printf(RESET);
            teams[index].minutes[j] = tempStorage;

            printf("-> Segundos do %iº Tempo : " GRN, j + 1);
            scanf("%i", &tempStorage);
            printf(RESET);
            teams[index].seconds[j] = tempStorage;

            printf("-> Milisegundos do %iº Tempo : " GRN, j + 1);
            scanf("%i", &tempStorage);
            printf(RESET);
            teams[index].miliseconds[j] = tempStorage;
        }
        teams[index].mean = resolveTime(teams[index]);
    }

    // Ordenando as equipes pelo tempo médio
    for (int i = 0; i < teamsCount; i++)
    {
        for (int j = 0; j < teamsCount - 1; j++)
        {
            if (teams[j].mean > teams[j + 1].mean)
            {
                struct Team temp = teams[j];
                teams[j] = teams[j + 1];
                teams[j + 1] = temp;
            }
        }
    }

    hasTeams = 1;
    
    clear();
    goto menu;

showTeams:
    hr(3);
    printf("VISUALIZAR EQUIPES\n");
    hr(1);
    printf("Equipes cadastradas: \n");
    hr(1);

    if (hasTeams)
    {
        for (int i = 0; i < teamsCount; i++)
        {
            printf(YEL "****%i LUGAR*****\n" RESET, i + 1);
            printf(GRN "EQUIPE..........." RESET "%s \n", teams[i].name);
            printf(GRN "1º TEMPO........." RESET "%i:%i:%i \n", teams[i].minutes[0], teams[i].seconds[0], teams[i].miliseconds[0]);
            printf(GRN "2º TEMPO........." RESET "%i:%i:%i \n", teams[i].minutes[1], teams[i].seconds[1], teams[i].miliseconds[1]);
            printf(GRN "3º TEMPO........." RESET "%i:%i:%i \n", teams[i].minutes[2], teams[i].seconds[2], teams[i].miliseconds[2]);
            printf(GRN "MÉDIA............" RESET "%.2f \n", teams[i].mean);
            printf(GRN "==================================\n" RESET);
        }
    }
    else
    {
        printf("Nenhuma equipe cadastrada! \n");
    }
    
    system("pause");
    clear();

    goto menu;

printToFile:
    hr(3);
    printf("- IMPRIMIR RESULTADOS\n");
    hr(1);

    if (hasTeams)
    {
        FILE *file;
        file = fopen("resultados.txt", "w");

        if (file == NULL)
        {
            printf("Erro ao abrir arquivo! \n");
            goto menu;
        }
        for (int i = 0; i < teamsCount; i++)
        {
            fprintf(file, "==================================\n");
            fprintf(file, "**** %i LUGAR****\n", i + 1);
            fprintf(file, "EQUIPE..........%s \n", teams[i].name);
            fprintf(file, "1º TEMPO.........");
            fprintf(file, "%i:%i:%i \n", teams[i].minutes[0], teams[i].seconds[0], teams[i].miliseconds[0]);
            fprintf(file, "2º TEMPO.........");
            fprintf(file, "%i:%i:%i \n", teams[i].minutes[1], teams[i].seconds[1], teams[i].miliseconds[1]);
            fprintf(file, "3º TEMPO.........");
            fprintf(file, "%i:%i:%i \n", teams[i].minutes[2], teams[i].seconds[2], teams[i].miliseconds[2]);
            fprintf(file, "MÉDIA............%.2f \n", teams[i].mean);
        }

        fclose(file);
        printf(BLU "Resultados salvos em resultados.txt \n" RESET);
    }
    else
    {
        printf("Nenhuma equipe cadastrada! \n");
    }
    
    system("pause");
    clear();

    goto menu;

exitProgram:
    printf(BLU "Saindo...\n" RESET);
}

int main()
{
    // Atribuindo localização ao programa
    setlocale(LC_ALL, "Portuguese");

    int teamsCount;

    printf("Bem-vindo, antes de começar, digite a quantidade de equipes inscritas. \n");
    printf("-> ");
    scanf("%i", &teamsCount);
    
    clear();
    menu(teamsCount);

    return 0;
}

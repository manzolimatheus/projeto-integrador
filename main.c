#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"
#include "styles.h"
#include "processor.h"
#include <locale.h>

void clear()
{
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
    int exportOption;

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

    //Roteamento
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
        printf("Digite o número correspondente ao formato desejado.");
        printf("\n[1] - Arquivo de texto comum (.txt)");
        printf("\n[2] - Arquivo de Excel (.csv)");
        printf("\n[3] - Arquivo JSON (.json)");
        printf("\n-> ");
        scanf("%i", &selectedOption );

        FILE *file;

        switch(selectedOption)
        {
        case 1:
            //Exportando para arquivo de texto
            file = fopen("resultados.txt", "w");

            if (file == NULL)
            {
                printf("Erro ao exportar arquivo! \n");
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
            break;
        case 2:
            //Exportando para CSV
            file = fopen("resultados.csv", "w");

            if (file == NULL)
            {
                printf("Erro ao exportar arquivo! \n");
                goto menu;
            }

            fprintf(file, "Posicao, Equipe, 1o Tempo - min, 1o Tempo - seg, 1o Tempo - mil, 2o Tempo - min, 2o Tempo - seg, 2o Tempo - mil, 3o Tempo - min, 3o Tempo - seg, 3o Tempo - mil, Media\n");
            for (int i = 0; i < teamsCount; i++)
            {
                fprintf(file, "%i, %s, %i, %i, %i, %i, %i, %i, %i, %i, %i, %.2f\n", i+1, teams[i].name, teams[i].minutes[0], teams[i].seconds[0], teams[i].miliseconds[0], teams[i].minutes[1], teams[i].seconds[1], teams[i].miliseconds[1], teams[i].minutes[2], teams[i].seconds[2], teams[i].miliseconds[2], teams[i].mean);
            }

            fclose(file);
            printf(BLU "Resultados exportados com sucesso! \n" RESET);
            break;

        case 3:
            //Exportando para JSON
            file = fopen("resultados.json", "w");

            if (file == NULL)
            {
                printf("Erro ao exportar arquivo! \n");
                goto menu;
            }

            fprintf(file, "[ \n");
            for (int i = 0; i < teamsCount; i++)
            {
                fprintf(file, "{ \n");
                fprintf(file, "\t\"position\": %i, \n", i + 1);
                fprintf(file, "\t\"name\": \"%s\", \n", teams[i].name);
                fprintf(file, "\t\"minutes\": [");
                fprintf(file, "%i, ", teams[i].minutes[0]);
                fprintf(file, "%i, ", teams[i].minutes[1]);
                fprintf(file, "%i", teams[i].minutes[2]);
                fprintf(file, "],\n");
                fprintf(file, "\t\"seconds\": [");
                fprintf(file, "%i, ", teams[i].seconds[0]);
                fprintf(file, "%i, ", teams[i].seconds[1]);
                fprintf(file, "%i", teams[i].seconds[2]);
                fprintf(file, "],\n");
                fprintf(file, "\t\"miliseconds\": [");
                fprintf(file, "%i, ", teams[i].miliseconds[0]);
                fprintf(file, "%i, ", teams[i].miliseconds[1]);
                fprintf(file, "%i", teams[i].miliseconds[2]);
                fprintf(file, "],\n");
                fprintf(file, "\t\"timeMean\": \"%.2f\" \n", teams[i].mean);
                fprintf(file, "}");
                if (i + 1 < teamsCount){
                    fprintf(file, ",\n");
                }
            }
            fprintf(file, "] \n");

            fclose(file);
            printf(BLU "Resultados exportados com sucesso! \n" RESET);

            break;
        }
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

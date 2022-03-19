#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "styles.h"
#include "utils.h"
#include <locale.h>

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
    printf("Escolha sua opcao \n");
    hr(1);
    printf(GRN "[1]" RESET " - Cadastrar equipes \n");
    printf(GRN "[2]" RESET " - Visualizar equipes \n");
    printf(GRN "[3]" RESET " - Imprimir resultados \n");
    printf(GRN "[4]" RESET " - Salvar resultados na WEB \n");
    printf(GRN "[5]" RESET " - " RED "Sair \n" RESET);
    hr(1);
    printf("-> ");
    scanf("%i", &selectedOption);
    printf("\n");

    clear();

    // Roteamento
    switch (selectedOption)
    {
    case 1:
        printf(BLU "OPCAO ESCOLHIDA: Cadastrar equipes \n" RESET);
        goto registerTeams;
        break;
    case 2:
        printf(BLU "OPCAO ESCOLHIDA: Visualizar equipes \n" RESET);
        goto showTeams;
        break;
    case 3:
        printf(BLU "OPCAO ESCOLHIDA: Imprimir resultados \n" RESET);
        goto printToFile;
        break;
    case 4:
        printf(BLU "OPCAO ESCOLHIDA: Salvar resultados na WEB \n" RESET);
        goto exportToWeb;
        break;
    case 5:
        printf(BLU "OPCAO ESCOLHIDA: Sair \n" RESET);
        goto exitProgram;
        break;

    default:
        printf(RED "Opcao invalida! \n" RESET);
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
            printf(BLU "Digite o %io melhor tempo da equipe: \n" RESET, j + 1);
            printf("-> Minutos do %io Tempo : " GRN, j + 1);
            scanf("%i", &tempStorage);
            printf(RESET);
            teams[index].minutes[j] = tempStorage;

            printf("-> Segundos do %io Tempo : " GRN, j + 1);
            scanf("%i", &tempStorage);
            printf(RESET);
            teams[index].seconds[j] = tempStorage;

            printf("-> Milisegundos do %io Tempo : " GRN, j + 1);
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
            printf(YEL "****%io LUGAR*****\n" RESET, i + 1);
            printf(GRN "EQUIPE..........." RESET "%s \n", teams[i].name);
            printf(GRN "1o TEMPO........." RESET "%i:%i:%i \n", teams[i].minutes[0], teams[i].seconds[0], teams[i].miliseconds[0]);
            printf(GRN "2o TEMPO........." RESET "%i:%i:%i \n", teams[i].minutes[1], teams[i].seconds[1], teams[i].miliseconds[1]);
            printf(GRN "3o TEMPO........." RESET "%i:%i:%i \n", teams[i].minutes[2], teams[i].seconds[2], teams[i].miliseconds[2]);
            printf(GRN "MEDIA............" RESET "%.2f \n", teams[i].mean);
            printf(GRN "==================================\n" RESET);
        }
    }
    else
    {
        printf("Nenhuma equipe cadastrada! \n");
    }

    pause();
    clear();

    goto menu;

printToFile:
    hr(3);
    printf("- IMPRIMIR RESULTADOS\n");
    hr(1);

    if (hasTeams)
    {
        printf("Digite o numero correspondente ao formato desejado. (A insercao de um valor invalido voltara para o menu principal)");
        printf("\n[1] - Arquivo de texto comum (.txt)");
        printf("\n[2] - Arquivo de Excel (.csv)");
        printf("\n[3] - Arquivo JSON (.json)");
        printf("\n-> ");
        scanf("%i", &selectedOption);

        FILE *file;

        switch (selectedOption)
        {
        case 1:
            // Exportando para arquivo de texto
            file = fopen("resultados.txt", "w");
            if (file == NULL)
            {
                printf("Erro ao exportar arquivo! \n");
                goto menu;
            }
            printToText(file, teams, teamsCount);
            break;
        case 2:
            // Exportando para CSV
            file = fopen("resultados.csv", "w");
            if (file == NULL)
            {
                printf("Erro ao exportar arquivo! \n");
                goto menu;
            }
            printToCSV(file, teams, teamsCount);
            break;

        case 3:
            // Exportando para JSON
            file = fopen("resultados.json", "w");

            if (file == NULL)
            {
                printf("Erro ao exportar arquivo! \n");
                goto menu;
            }
            printToJSON(file, teams, teamsCount);
            break;
        default:
            printf("Opcaoo invalida! Voltando ao menu... \n");
            pause();
            clear();
            goto menu;
            break;
        }
        printf(BLU "Resultados exportados com sucesso! \n" RESET);
    }
    else
    {
        printf("Nenhuma equipe cadastrada! \n");
    }

    pause();
    clear();

    goto menu;

exportToWeb:
    hr(3);
    printf("- SALVAR NA WEB\n");
    hr(1);

    if (hasTeams)
    {
        FILE *file;

        // Exportando para JSON
        file = fopen("resultados.json", "w");

        if (file == NULL)
        {
            printf("Erro ao exportar arquivo! \n");
            goto menu;
        }
        printToJSON(file, teams, teamsCount);

        #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
            system("python3 delivery.py");
        #else
            system("python delivery.py");
        #endif
        printf(BLU "Resultados salvos na WEB com sucesso! \n" RESET);
    }
    else
    {
        printf("Nenhuma equipe cadastrada! \n");
    }

    pause();
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

    printf("Bem-vindo, antes de comecar, quantas equipes estao participando da competicao? -> ");
    scanf("%i", &teamsCount);

    clear();
    menu(teamsCount);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "styles.h"
#include "utils.h"

// Variáveis brutas
int teamsCount;
struct Team teams[10];
// Variáveis temporárias/auxiliares
char team[20];
int tempStorage;
// Variáveis de controle
int selectedOption;
int hasTeams = 0;
int hasNames = 0;
int hasTimes[] = {0, 0, 0};
int exportOption;

void exportToWeb()
{
    hr(3);
    printf("- SALVAR NA WEB\n");
    hr(1);

    if (hasTeams)
    {
        FILE *file;
        system("mkdir web");
        // Exportando para JSON
        file = fopen("web/results.json", "w");

        if (file == NULL)
        {
            printf("Erro ao exportar arquivo! \n");
            menu();
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
        printf("Nenhuma equipe cadastrada ou a corrida ainda nao foi finalizada! \n");
    }

    pause();
    clear();
    menu();
}

void printToFile()
{
    hr(3);
    printf("- IMPRIMIR RESULTADOS\n");
    hr(1);

    if (hasTeams)
    {
        printf("Digite o numero correspondente ao formato desejado. (A insercao de um valor invalido voltara para o menu principal)");
        printf("\n[1] - Arquivo de texto comum (.txt)");
        printf("\n[2] - Arquivo de Excel (.csv)");
        printf("\n[3] - Arquivo JSON (.json)");
        printf("\n[4] - Sair");
        printf("\n-> ");
        scanf("%i", &selectedOption);

        system("mkdir export");
        FILE *file;

        switch (selectedOption)
        {
        case 1:
            // Exportando para arquivo de texto
            file = fopen("export/resultados.txt", "w");
            if (file == NULL)
            {
                printf("Erro ao exportar arquivo! \n");
                menu();
            }
            printToText(file, teams, teamsCount);
            break;
        case 2:
            // Exportando para CSV
            file = fopen("export/resultados.csv", "w");
            if (file == NULL)
            {
                printf("Erro ao exportar arquivo! \n");
                menu();
            }
            printToCSV(file, teams, teamsCount);
            break;

        case 3:
            // Exportando para JSON
            file = fopen("export/resultados.json", "w");

            if (file == NULL)
            {
                printf("Erro ao exportar arquivo! \n");
                menu();
            }
            printToJSON(file, teams, teamsCount);
            break;
        default:
            clear();
            menu();
            break;
        }
        printf(BLU "Resultados exportados com sucesso! \n" RESET);
    }
    else
    {
        printf("Nenhuma equipe cadastrada ou a corrida ainda não foi finalizada! \n");
    }

    pause();
    clear();
    menu();
}

void showTeams()
{
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
        printf("Nenhuma equipe cadastrada ou a corrida ainda nao foi finalizada! \n");
    }

    pause();
    clear();
    menu();
}

void classifyTeams()
{
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
    menu();
}

void registerTeams(int actualRace)
{
    hr(3);
    printf("CADASTRAR EQUIPE - BATERIA %i\n", actualRace);
    hr(1);

    printf("Quantidade de equipes inscritas: %i \n", teamsCount);

    for (int index = 0; index < teamsCount; index++)
    {
        hr(2);
        if (!hasNames)
        {
            printf(BLU "Digite o nome da equipe (max. 20 caracteres): \n" RESET);
            printf("-> Nome: " GRN);
            scanf("%s", &teams[index].name);
            printf(RESET);
        }

        printf("-> Minutos da %io Bateria da equipe %s: " GRN, actualRace, teams[index].name);
        scanf("%i", &teams[index].minutes[actualRace - 1]);
        printf(RESET);

        printf("-> Segundos da %io Bateria da equipe %s : " GRN, actualRace, teams[index].name);
        scanf("%i", &teams[index].seconds[actualRace - 1]);
        printf(RESET);

        printf("-> Milisegundos da %io Bateria da equipe %s: " GRN, actualRace, teams[index].name);
        scanf("%i", &teams[index].miliseconds[actualRace - 1]);
        printf(RESET);

        if (actualRace >= 3)
        {
            teams[index].mean = resolveTime(teams[index]);
        }
    }

    hasTimes[actualRace - 1] = 1;
    hasNames = 1;

    if (actualRace >= 3)
    {
        classifyTeams();
    }
    else
    {
        clear();
        menu();
    }
}

void selectRace()
{
    clear();
    hr(3);

    int raceSelected;

    printf("\nSELECIONAR BATERIA\n");
    hr(1);
    printf(hasTimes[0] ? GRN "[1]" RESET " - Bateria 1 (Concluido)\n" : GRN "[1]" RESET " - Bateria 1 \n");
    printf(hasTimes[1] ? GRN "[2]" RESET " - Bateria 2 (Concluido)\n" : GRN "[2]" RESET " - Bateria 2 \n");
    printf(hasTimes[2] ? GRN "[3]" RESET " - Bateria 3 (Concluido)\n" : GRN "[3]" RESET " - Bateria 3 \n");
    printf(GRN "[4]" RESET " - Sair\n");
    hr(1);
    printf("Digite o numero correspondente a bateria desejada: -> ");
    scanf("%i", &raceSelected);

    clear();
    if (raceSelected != 4)
    {
        registerTeams(raceSelected);
    }
    else
    {
        menu();
    }
}

void router()
{
    // Roteamento
    switch (selectedOption)
    {
    case 1:
        printf(BLU "OPCAO ESCOLHIDA: Cadastrar equipes \n" RESET);
        selectRace();
        break;
    case 2:
        printf(BLU "OPCAO ESCOLHIDA: Visualizar equipes \n" RESET);
        showTeams();
        break;
    case 3:
        printf(BLU "OPCAO ESCOLHIDA: Imprimir resultados \n" RESET);
        printToFile();
        break;
    case 4:
        printf(BLU "OPCAO ESCOLHIDA: Salvar resultados na WEB \n" RESET);
        exportToWeb();
        break;
    case 5:
        printf(BLU "OPCAO ESCOLHIDA: Sair \n" RESET);
        printf(BLU "Saindo...\n" RESET);
        exit(0);
        break;

    default:
        printf(RED "Opcao invalida! \n" RESET);
        menu();
        break;
    }
}

void menu()
{
    hr(3);
    printf("****** MENU ******\n");
    hr(3);
    printf("Escolha sua opcao \n");
    hr(1);
    printf(GRN "[1]" RESET " - Cadastrar equipes \n");
    printf(GRN "[2]" RESET " - Visualizar equipes \n");
    printf(GRN "[3]" RESET " - Imprimir resultados \n");
    printf(GRN "[4]" RESET " - Salvar resultados na WEB \n");
    printf(GRN "[5]" RESET " - " RED "Sair \n" RESET);
    hr(1);
    printf("Digite sua opcao -> ");
    scanf("%i", &selectedOption);

    clear();
    router();
}

int main()
{
    printf("\nCriado por Ambar Labs - 2022");
    printf("\nAcesse nossa aplicacao web:" BLU "ambar-race.vercel.app\n" RESET);
    hr(2);
    printf("\nBem-vindo, antes de comecar, quantas equipes estao participando da competicao? -> ");
    scanf("%i", &teamsCount);

    clear();
    menu();

    return 0;
}

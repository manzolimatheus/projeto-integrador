#ifndef utils_h
#define utils_h

struct Team
{
    char name[20];
    int minutes[3];
    int seconds[3];
    int miliseconds[3];
    float mean;
};

// Função que faz a média de tempo de cada time
float getArithmeticMean(int firstTime, int secondTime)
{
    int arithmeticMean = (firstTime + secondTime) / 3;

    return arithmeticMean;
}

// Função que remove o tempo mais rápido e retorna os outros dois
float resolveTime(struct Team team)
{
    int firstTime = team.minutes[0] * 60 + team.seconds[0] + team.miliseconds[0] / 1000;
    int secondTime = team.minutes[1] * 60 + team.seconds[1] + team.miliseconds[1] / 1000;
    int thirdTime = team.minutes[2] * 60 + team.seconds[2] + team.miliseconds[2] / 1000;

    if (firstTime < secondTime && firstTime < thirdTime)
    {
        return getArithmeticMean(secondTime, thirdTime);
    }
    else if (secondTime < firstTime && secondTime < thirdTime)
    {
        return getArithmeticMean(firstTime, thirdTime);
    }
    else
    {
        return getArithmeticMean(firstTime, secondTime);
    }
}

// Função que limpa a tela
void clear()
{
    // Check the user system
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #else
        system("cls");
    #endif

}

void printToText(FILE *file, struct Team teams[], int teamsCount)
{
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
}

void printToCSV(FILE *file, struct Team teams[], int teamsCount)
{
    fprintf(file, "Posicao, Equipe, 1o Tempo - min, 1o Tempo - seg, 1o Tempo - mil, 2o Tempo - min, 2o Tempo - seg, 2o Tempo - mil, 3o Tempo - min, 3o Tempo - seg, 3o Tempo - mil, Media\n");
    for (int i = 0; i < teamsCount; i++)
    {
        fprintf(file, "%i, %s, %i, %i, %i, %i, %i, %i, %i, %i, %i, %.2f\n", i + 1, teams[i].name, teams[i].minutes[0], teams[i].seconds[0], teams[i].miliseconds[0], teams[i].minutes[1], teams[i].seconds[1], teams[i].miliseconds[1], teams[i].minutes[2], teams[i].seconds[2], teams[i].miliseconds[2], teams[i].mean);
    }

    fclose(file);
}

void printToJSON(FILE *file, struct Team teams[], int teamsCount)
{
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
        i + 1 < teamsCount ? fprintf(file, ", \n") : fprintf(file, "\n");
    }
    fprintf(file, "] \n");

    fclose(file);
}

void pause(){
    // Check the user system

    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("read -p \"Pressione qualquer tecla para continuar...\"");
    #else
        system("pause");
    #endif
}

#endif

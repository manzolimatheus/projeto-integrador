struct Team
{
    char name[20];
    int minutes[3];
    int seconds[3];
    int miliseconds[3];
    float mean;
};

float getArithmeticMean(int firstTime, int secondTime)
{
    int arithmeticMean = (firstTime + secondTime) / 3;

    return arithmeticMean;
}

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
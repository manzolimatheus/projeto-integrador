void hr(int style)
{
    switch (style)
    {
    case 1:
        printf(RED "-------------------------------------- \n" RESET);
        break;
    case 2:
        printf(RED "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n" RESET);
        break;
    case 3:
        printf(RED "====================================== \n" RESET);
        break;

    default:
        printf(RED "************************************** \n" RESET);
        break;
    }
}
#ifndef styles_h
#define styles_h

// Cores
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

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

#endif

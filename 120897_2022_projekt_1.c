#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// funkcia otvorenie() pre vstup 'v'
int otvorenie(FILE **fptr, int *open, long long *ID, char **modul, char **merana_velicina, float *hodnota, int *cas_merania, long long *datum, int xp, int *arrays)
{
    if (*open == 0)
    {
        // otvorenie suboru
        *fptr = fopen("dataloger.txt", "r");
        if (!open)
        {
            printf("Neotvoreny subor\n");
            return 1;
        }
        *open = 1;
    }
    char p_c[100];
    int pocitadlo = 0;

    // vypis jednotlivych riadkov r pripade, ze 'n' bolo stlacene - pamat bola alokovana
    if (arrays == 1)
    {
        for (int i = 0; i < xp; i++)
        {
            printf("ID cislo mer. osoby: %lld\n", ID[i]);
            printf("Mer. modul: %s\n", modul[i]);
            printf("Typ mer. veliciny: %s", merana_velicina[i]);
            printf("Hodnota: %f\n", hodnota[i]);
            printf("Cas merania: %d\n", cas_merania[i]);
            printf("Datum: %lld \n\n", datum[i]);
        }
    }
    else
    {
        while (fgets(p_c, 100, *fptr) != NULL)
        {
            // vypis jednotlivych riadkov v pripade, ze pamat nebola alokovana
            if (pocitadlo == 7)
            {
                pocitadlo = 0;
            }
            if (pocitadlo == 0)
            {
                printf("ID cislo mer. osoby: ");
            }
            else if (pocitadlo == 1)
            {
                printf("Mer. modul: ");
            }
            else if (pocitadlo == 2)
            {
                printf("Typ mer. veliciny: ");
            }
            else if (pocitadlo == 3)
            {
                printf("Hodnota:");
            }
            else if (pocitadlo == 4)
            {
                printf("Cas merania: ");
            }
            else if (pocitadlo == 5)
            {
                printf("Datum: ");
            }
            printf("%s", p_c);
            pocitadlo++;
        }
    }
    rewind(*fptr);
}

// funkcia porovnanie() pre vstup 'o'
int porovnanie(FILE *fptr, int open)
{
    if (!open)
    {
        printf("Neotvoreny subor\n");
        return 1;
    }
    rewind(fptr);

    // scan typu modulu z konzoly
    char m_1[50], m_v_1[50];
    scanf("%s %s", m_1, m_v_1);

    long long ID;
    char modul[50];
    char merana_velicina[50];
    float hodnota;
    int cas_merania;
    long long datum;

    // deklaracia stringov, ktore sa budu porovnavat podla zadanych typov
    int size, max_buffer = 9999;
    char c_buffer_modul[max_buffer], c_buffer_merana_velicina[max_buffer];

    // scanovanie suboru
    while (fscanf(fptr, "%lld", &ID) != EOF)
    {

        while (fgetc(fptr) != '\n')
            ;
        fgets(c_buffer_modul, max_buffer, fptr);
        size = strlen(c_buffer_modul);
        c_buffer_modul[size - 1] = '\0';

        fgets(c_buffer_merana_velicina, max_buffer, fptr);
        size = strlen(c_buffer_merana_velicina);
        c_buffer_merana_velicina[size - 1] = '\0';

        fscanf(fptr, "%f", &hodnota);

        while (fgetc(fptr) != '\n')
            ;
        fscanf(fptr, "%d", &cas_merania);

        while (fgetc(fptr) != '\n')
            ;
        fscanf(fptr, "%lld", &datum);

        while (fgetc(fptr) != '\n')
            ;

        // porovnanie kedy sa nacitane stringy rovnaju
        if (strcmp(m_1, c_buffer_modul) == 0 && strcmp(m_v_1, c_buffer_merana_velicina) == 0)
        {
            printf("%s %s\t%lld ", m_1, m_v_1, datum);

            // osetrenie casu v pripadoch, ked sa na zaciatku int nachadza nula resp. nuly
            if (cas_merania < 1000)
            {
                printf("0");
            }
            else if (cas_merania < 100)
            {
                printf("00");
            }
            else if (cas_merania < 10)
            {
                printf("000");
            }
            printf("%d\t%f\n", cas_merania, hodnota);
        }
    }
}

// funkcia d_polia() pre vstup 'n'
int d_polia(FILE *fptr, int open, long long **ID, char ***modul, char ***merana_velicina, float **hodnota, int **cas_merania, long long **datum, int *xp, int *arrays)
{
    if (!open)
    {
        printf("Neotvoreny subor\n");
        return 1;
    }
    open = 1;

    // dealokovanie v pripade, ze uz boli vytvorene
    if (*arrays == 1)
    {
        free(*ID);
        free(*modul);
        free(*merana_velicina);
        free(*cas_merania);
        free(*datum);
    }

    rewind(fptr); // ukazovatel na zaciatok riadku
    char p_c[50];
    int pocitadlo = 0;
    *xp = 0;

    while (fgets(p_c, 50, fptr) != NULL)
    {
        pocitadlo++;
    }

    *xp = pocitadlo = ((pocitadlo + 1) / 7);

    // alokovanie pamate pre jednotlive riadky zaznamu
    *ID = (long long *)malloc(sizeof(long long) * pocitadlo);
    *modul = (char **)malloc(sizeof(char *) * pocitadlo);
    *merana_velicina = (char **)malloc(sizeof(char *) * pocitadlo);
    *hodnota = (float *)malloc(sizeof(int) * pocitadlo);
    *cas_merania = (int *)malloc(sizeof(int) * pocitadlo);
    *datum = (long long *)malloc(sizeof(long long) * pocitadlo);

    int n = 0;
    rewind(fptr);

    // nahravanie udajov zo suboru do alokovanej pamate
    while (fscanf(fptr, "%lld", &(*ID)[n]) != EOF)
    {
        int size, max_buffer = 100;
        char c_buffer[max_buffer];

        while (fgetc(fptr) != '\n')
            ;
        fgets(c_buffer, max_buffer, fptr);
        size = strlen(c_buffer);
        c_buffer[size - 1] = '\0';
        (*modul)[n] = malloc(sizeof(char) * size);
        strcpy((*modul)[n], c_buffer);

        fgets(c_buffer, max_buffer, fptr);
        size = strlen(c_buffer);
        (*merana_velicina)[n] = malloc(sizeof(char) * size);
        strcpy((*merana_velicina)[n], c_buffer);

        fscanf(fptr, "%f", &(*hodnota)[n]);

        while (fgetc(fptr) != '\n')
            ;
        fscanf(fptr, "%d", &(*cas_merania)[n]);

        while (fgetc(fptr) != '\n')
            ;
        fscanf(fptr, "%lld", &(*datum)[n]);

        while (fgetc(fptr) != '\n')
            ;
        n++;
    }
    // zmena ukazovatela na premennu 'arrays', ktora urcuje ci uz boli dynamicke polia vytvorene
    *arrays = 1;
    return 0;
}

// funcia check_if_correct() pre vstup 'c'
int check_if_correct(FILE *fptr, int open)
{
    if (!open)
    {
        printf("Neotvoreny subor\n");
        return 1;
    }
    rewind(fptr);

    char str_m[50];
    char str_m_v[50];

    long long ID;
    char modul[50];
    char merana_velicina[50];
    float hodnota;
    int cas_merania;
    long long datum;

    int chyba = 0;

    // skenovanie suboru, pre kontrolu spravnosti udajov
    int size, max_buffer = 9999;
    char c_buffer_modul[max_buffer], c_buffer_merana_velicina[max_buffer];

    while (fscanf(fptr, "%lld", &ID) != EOF)
    {

        while (fgetc(fptr) != '\n')
            ;
        fgets(c_buffer_modul, max_buffer, fptr);
        size = strlen(c_buffer_modul);
        c_buffer_modul[size - 1] = '\0';

        fgets(c_buffer_merana_velicina, max_buffer, fptr);
        size = strlen(c_buffer_merana_velicina);
        c_buffer_merana_velicina[size - 1] = '\0';

        fscanf(fptr, "%f", &hodnota);

        while (fgetc(fptr) != '\n')
            ;
        fscanf(fptr, "%d", &cas_merania);

        while (fgetc(fptr) != '\n')
            ;
        fscanf(fptr, "%lld", &datum);

        while (fgetc(fptr) != '\n')
            ;

        // kontrola ID
        if (ID % 11 != 0)
        {
            printf("Nekorektne zadany vstup: %lld\n", ID);
            chyba = 1;
        }

        // kontrola modulu
        if (c_buffer_modul[0] < 'A' || c_buffer_modul[0] > 'Z' || c_buffer_modul[1] < 0 || c_buffer_modul[2] < 0 || c_buffer_modul[3] != NULL)
        {
            printf("Nekorektne zadany vstup: %s\n", c_buffer_modul);
            chyba = 1;
        }

        // kontrola meranej veliciny
        if (c_buffer_merana_velicina[0] != 'A' && c_buffer_merana_velicina[0] != 'R' && c_buffer_merana_velicina[0] != 'U' || c_buffer_merana_velicina[1] != '1' && c_buffer_merana_velicina[1] != '2' && c_buffer_merana_velicina[1] != '4')
        {
            printf("Nekorektne zadany vstup: %s\n", c_buffer_merana_velicina);
            chyba = 1;
        }

        // kontrola formatu casu
        if (cas_merania / 100 > 24 || cas_merania / 100 < 0 || cas_merania > 2359 || cas_merania % 100 > 59)
        {
            printf("Nekorektne zadany vstup: %d\n", cas_merania);
            chyba = 1;
        }

        // kontrola formatu datumu
        if (datum < 10000000 || datum > 99999999 || datum % 100 > 31 || datum % 10000 > 1231)
        {
            printf("Nekorektne zadany vstup: %lld\n", datum);
            chyba = 1;
        }
    }
    // pripad, ked data su korektne
    if (!chyba)
    {
        printf("Data su korektne\n");
    }
    return 0;
}

// funkcia vystup_s() pre vstup 's'
int vystup_s(FILE *fptr, int open, long long *ID, char **modul, char **merana_velicina, float *hodnota, int *cas_merania, long long *datum, int xp, int *arrays)
{
    if (!open)
    {
        printf("Neotvoreny subor\n");
        return 1;
    }
    if (arrays == 0)
    {
        printf("Polia nie su vytvorene\n");
        return 1;
    }
    rewind(fptr);

    // scan typu modulu z konzoly
    char m_2[50], m_v_2[50];
    scanf("%s %s", m_2, m_v_2);

    long long ID2;
    char modul2[50];
    char merana_velicina2[50];
    float hodnota2;
    int cas_merania2;
    long long datum2;

    // deklaracia stringov, ktore sa budu porovnavat podla zadanych typov
    int size, max_buffer = 9999;
    char c_buffer_modul[max_buffer];
    char c_buffer_merana_velicina[max_buffer];

    FILE *filewrite;
    filewrite = fopen("vystup_S.txt", "w");

    while (fscanf(fptr, "%lld", &ID) != EOF)
    {

        while (fgetc(fptr) != '\n')
            ;
        fgets(c_buffer_modul, max_buffer, fptr);
        size = strlen(c_buffer_modul);
        c_buffer_modul[size - 1] = '\0';

        fgets(c_buffer_merana_velicina, max_buffer, fptr);
        size = strlen(c_buffer_merana_velicina);
        c_buffer_merana_velicina[size - 1] = '\0';

        fscanf(fptr, "%f", &hodnota2);

        while (fgetc(fptr) != '\n')
            ;
        fscanf(fptr, "%d", &cas_merania2);

        while (fgetc(fptr) != '\n')
            ;
        fscanf(fptr, "%lld", &datum2);

        while (fgetc(fptr) != '\n')
            ;

        // porovnanie vstupu z modulom a velicinou zo suboru

        if (strcmp(m_2, c_buffer_modul) == 0 && strcmp(m_v_2, c_buffer_merana_velicina) == 0)
        {
            // zapis do suboru vystup_S.txt
            fprintf(filewrite, "%s %s\t%lld", m_2, m_v_2, datum2);

            if (cas_merania2 < 1000)
            {
                fprintf(filewrite, "0");
            }
            else if (cas_merania2 < 100)
            {
                fprintf(filewrite, "00");
            }
            else if (cas_merania2 < 10)
            {
                fprintf(filewrite, "000");
            }
            fprintf(filewrite, "%d\t%f\n", cas_merania2, hodnota2);
        }
    }

    if (NULL != filewrite)
    {
        fseek(filewrite, 0, SEEK_END);
        size = ftell(filewrite);

        if (0 == size)
        {
            // oznam do konzoly
            printf("Pre dany vstup neexistuju zaznamy.\n"); // neviem vsak, ako ich usporiadat chronologicky
        }
        else
        {
            printf("Pre dany vstup je vytvoreny txt subor.\n");
        }
    }
    fclose(filewrite);

    return 0;
}

// funkcia mazanie() pre vstup 'z'
int mazanie(FILE *fptr, int open, long long **ID, char ***modul, char ***merana_velicina, float **hodnota, int **cas_merania, long long **datum, int *xp, int *arrays)
{
    if (!open)
    {
        printf("Neotvoreny subor\n");
        return 1;
    }
    if (arrays == 0)
    {
        printf("Polia nie su vytvorene\n");
        return 1;
    }

    long long mazivo = 0;
    // scan ID
    scanf("%lld", &mazivo);
    int poc_vymazanych_suborov = 0;
    int nove_pocitadlo = *xp;

    // porovnanie nacitaneho ID s povodnym ID
    for (int i = 0; i < *xp; i++)
    {
        if (mazivo == (*ID)[i])
        {
            poc_vymazanych_suborov++;
            nove_pocitadlo--;
        }

        // realokovanie poli
        *ID = realloc((*ID), sizeof(long long) * nove_pocitadlo);
        *modul = realloc((*modul), sizeof(char *) * nove_pocitadlo);
        *merana_velicina = realloc((*merana_velicina), sizeof(char *) * nove_pocitadlo);
        *hodnota = realloc((*hodnota), sizeof(int) * nove_pocitadlo);
        *cas_merania = realloc((*cas_merania), sizeof(int) * nove_pocitadlo);
        *datum = realloc((*datum), sizeof(long long) * nove_pocitadlo);
    }
    printf("Vymazalo sa: %d zaznamov!\n", poc_vymazanych_suborov);
    return 0;
}

// j
int porovnanie_test(FILE *fptr, int open, int *xp)
{
    if (!open)
    {
        printf("Neotvoreny subor\n");
        return 1;
    }
    rewind(fptr);

    // scan typu modulu z konzoly
    char m_1_test[50], m_2_test[50], m_v_test[50];
    scanf("%s %s %s", m_1_test, m_2_test, m_v_test);

    float min1 = 9999, max1 = -9999, min2 = 9999, max2 = -9999, sucet_h1 = 0, sucet_h2 = 0;
    long long ID;
    char modul[50];
    char merana_velicina[50];
    float hodnota;
    int cas_merania;
    long long datum;
    float axp = 56;

    // deklaracia stringov, ktore sa budu porovnavat podla zadanych typov
    int size, max_buffer = 9999;
    char c_buffer_modul_test[max_buffer], c_buffer_merana_velicina_test[max_buffer];

    // scanovanie suboru
    while (fscanf(fptr, "%lld", &ID) != EOF)
    {

        while (fgetc(fptr) != '\n')
            ;
        fgets(c_buffer_modul_test, max_buffer, fptr);
        size = strlen(c_buffer_modul_test);
        c_buffer_modul_test[size - 1] = '\0';

        fgets(c_buffer_merana_velicina_test, max_buffer, fptr);
        size = strlen(c_buffer_merana_velicina_test);
        c_buffer_merana_velicina_test[size - 1] = '\0';

        fscanf(fptr, "%f", &hodnota);

        while (fgetc(fptr) != '\n')
            ;
        fscanf(fptr, "%d", &cas_merania);

        while (fgetc(fptr) != '\n')
            ;
        fscanf(fptr, "%lld", &datum);

        while (fgetc(fptr) != '\n')
            ;

        if (strcmp(m_1_test, c_buffer_modul_test) == 0 && strcmp(m_v_test, c_buffer_merana_velicina_test) == 0)
        {
            if (hodnota < min1)
            {
                min1 = hodnota;
            }
            else
            {
                min1;
            }
            if (hodnota > max1)
            {
                max1 = hodnota;
            }
            else
            {
                max1;
            }
            sucet_h1 = (min1 + max1) / 2;
        }
        if (strcmp(m_2_test, c_buffer_modul_test) == 0 && strcmp(m_v_test, c_buffer_merana_velicina_test) == 0)
        {
            if (hodnota < min2)
            {
                min2 = hodnota;
            }
            else
            {
                min2;
            }
            if (hodnota > max2)
            {
                max2 = hodnota;
            }
            else
            {
                max2;
            }
            sucet_h2 = (min2 + max2) / 2;
        }
    }
    float pri1, pri2, prm1, prm2, prs1, prs2, prs2_1, prs2_2;
    pri1 = ((sucet_h1 * 100) / min1) - 100;
    pri2 = ((sucet_h2 * 100) / min2) - 100;
    prm1 = ((sucet_h1 * 100) / max1) - 100;
    prm2 = ((sucet_h2 * 100) / max2) - 100;
    prs1 = ((sucet_h1 * 100) / sucet_h2) - 100;
    prs2 = ((sucet_h2 * 100) / sucet_h1) - 100;

    if (min1 == 9999 || max1 == -9999)
    {
    }
    else
    {
        printf("%s min: %.4f (%.4f) stred.hodnota: %.4f max: %.4f (%.4f)\n", m_1_test, min1, pri1 * 100, sucet_h1, max1, prm1 * 100);
    }
    if (min2 == 9999.0 || max2 == -9999.0)
    {
    }
    else
    {
        printf("%s min: %.4f (%.4f) stred.hodnota: %.4f max: %.4f (%.4f)\n", m_2_test, min2, pri2 * 100, sucet_h2, max2, prm2 * 100);
    }
    if (min1 == 9999 || max1 == -9999 || min2 == 9999.0 || max2 == -9999.0)
    {
        printf("%s %s sa nemozu porovnat", m_1_test, m_2_test);
    }
    else if (pri1 > -5 && pri1 < 5 && prm1 > -5 && prm2 < 5)
    {
        printf("%s %s su v standartnej odchilke", m_1_test, m_2_test);
    }
    else
    {
        printf("%s %s prekracuju limit povoleneho rozmedzia.\n", m_1_test, m_2_test);
    }
}

// x
void x(float *hodnota, int *xp)
{
    int n, i;
    int velkost = 57;

    // scanf("%d", &n);
    //   for (i = 0; i < n; i+n) {
    // neviem ako to spravit, preto pisem len ako by som to spravil.
    // hodnota to string
    // if (string[3] = 0) {
    // x_0++;
    //} else if (string[3] = 1) {
    // x_1++; ...
    // printf("%d %d %d\n");
    // printf("%d %d %d\n");
    // }
    printf("I dont know ho to do it.\n");
}

// Funkcia main
int main(void)
{
    FILE *fptr;
    FILE *fw;
    int open = 0;
    int open_vystup = 0;
    char vstup;
    long long *ID;
    char **modul;
    char **merana_velicina;
    float *hodnota;
    int *cas_merania;
    long long *datum;
    int xp;
    int *arrays;
    arrays = 0;

    // vstupna premenna
    while (scanf("%c", &vstup) != EOF)
    {
        switch (vstup)
        {
        case 'v':
        {
            otvorenie(&fptr, &open, ID, modul, merana_velicina, hodnota, cas_merania, datum, xp, arrays); // zavolanie funkcie pre vstup 'v'
            break;
        }
        case 'o':
        {
            porovnanie(fptr, open); // zavolanie funkcie pre vstup 'o'
            break;
        }
        case 'n':
        {
            d_polia(fptr, open, &ID, &modul, &merana_velicina, &hodnota, &cas_merania, &datum, &xp, &arrays); // zavolanie funkcie pre vstup 'n'
            break;
        }
        case 'c':
        {
            check_if_correct(fptr, open); // zavolanie funkcie pre vstup 'c'
            break;
        }
        case 's':
        {
            vystup_s(fptr, open, ID, modul, merana_velicina, hodnota, cas_merania, datum, xp, arrays); // zavolanie funkcie pre vstup 's'
            break;
        }
        case 'z':
        {
            mazanie(fptr, open, &ID, &modul, &merana_velicina, &hodnota, &cas_merania, &datum, &xp, arrays); // zavolanie funkcie pre vstup 'z'
            break;
        }
        case 'j':
        {
            porovnanie_test(fptr, open, &xp);
            break;
        }
        case 'x':
            x(&hodnota, &xp);
            break;
        case 'k': // deaalokovanie pamate a opustenie programu
        {
            if (*arrays == 0)
                ;
            {
                return 0;
            }
            free(ID);
            free(*modul);
            free(*merana_velicina);
            free(hodnota);
            free(*cas_merania);
            free(*datum);
            return 0;
        }
        }
    }
}

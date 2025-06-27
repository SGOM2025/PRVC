#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <memory.h>
#include <string.h>
#include <math.h>

#include "cabecalho.h"

#define MAX(X,Y)((X > Y) ? (X) : (Y))

const int PESO_CAP = 100;

int main()
{
    Solucao sol;
    ler_dados("instancia.txt");
    testar_dados(" ");

    /*
    sol.mat_sol[0][0] = 1;
    sol.mat_sol[0][1] = 3;
    sol.mat_sol[0][2] = 5;
    sol.mat_sol[1][0] = 2;
    sol.mat_sol[1][1] = 4;
    sol.vet_qtd_cli_vei[0] = 3;
    sol.vet_qtd_cli_vei[1] = 2;

    sol.vet_sol[0] = 0;
    sol.vet_sol[1] = 1;
    sol.vet_sol[2] = 3;
    sol.vet_sol[3] = 5;
    sol.vet_sol[4] = 0;
    sol.vet_sol[5] = 2;
    sol.vet_sol[6] = 4;
    sol.vet_sol[7] = 0;
*/

    criar_solucao(sol);
    calcular_fo(sol);

    printf("\n\n\n");
    for (int i = 0; i < num_vei; i++)
    {
        for (int j = 0; j < sol.vet_qtd_cli_vei[i]; j++)
            printf("%d ", sol.mat_sol[i][j]);
        printf("\n");
    }
    printf("\nQTD: ");
    for (int i = 0; i < num_vei; i++)
        printf("%d ", sol.vet_qtd_cli_vei[i]);

    printf("\nPESO: ");
    for (int i = 0; i < num_vei; i++)
        printf("%d ", sol.vet_pes_vei[i]);

    printf("\n\nFO: %.2f\n", sol.fo);


    calcular_fo2(sol);
    printf("\n\nFO: %.2f\n", sol.fo);

    return 0;
}

void criar_solucao(Solucao& s)
{
    int vei = 0;
    memset(&s.vet_qtd_cli_vei, 0, sizeof(s.vet_qtd_cli_vei));
    for (int j = 1; j <= num_cli; j++)
    {
        vei = vei % num_vei;
        s.mat_sol[vei][s.vet_qtd_cli_vei[vei]] = j;
        s.vet_qtd_cli_vei[vei]++;
        vei++;
        //if (vei == num_vei)
        //    vei = 0;
    }
}

void calcular_fo2(Solucao& s)
{
    int vei = 0;
    s.fo = 0;
    memset(&s.vet_pes_vei, 0, sizeof(s.vet_pes_vei));
    for (int j = 1; j < num_cli + num_vei + 1; j++)
    {
        if (s.vet_sol[j] == 0)
            vei++;
        s.fo += mat_custo[s.vet_sol[j-1]][s.vet_sol[j]];
        s.vet_pes_vei[vei] += vet_dem_cli[s.vet_sol[j]];
    }
    for (int i = 0; i < num_vei; i++)
        s.fo += PESO_CAP * MAX(0, s.vet_pes_vei[i] - vet_cap_vei[i]);
}

void calcular_fo(Solucao& s)
{
    s.fo = 0;
    memset(&s.vet_pes_vei, 0, sizeof(s.vet_pes_vei));
    for (int i = 0; i < num_vei; i++) // linha
    {
        s.fo += mat_custo[0][s.mat_sol[i][0]];
        s.vet_pes_vei[i] += vet_dem_cli[s.mat_sol[i][0]];
        for (int j = 1; j < s.vet_qtd_cli_vei[i]; j++) // coluna
        {
            s.fo += mat_custo[s.mat_sol[i][j-1]][s.mat_sol[i][j]];
            s.vet_pes_vei[i] += vet_dem_cli[s.mat_sol[i][j]];
        }
        s.fo += mat_custo[s.mat_sol[i][s.vet_qtd_cli_vei[i]-1]][0];
        //---
        s.fo += PESO_CAP * MAX(0, s.vet_pes_vei[i] - vet_cap_vei[i]);
    }
}

void testar_dados(char* arq)
{
    FILE* f;
    if (!strcmp(arq, " "))
        f = stdout;
    else
        f = fopen(arq, "w");
    fprintf(f, "%d %d\n", num_cli, num_vei);
    for (int i = 0; i < num_vei; i++)
        fprintf(f, "%d ", vet_cap_vei[i]);
    fprintf(f, "\n");
    for (int i = 0; i <= num_cli; i++)
    {
        for (int j = 0; j <= num_cli; j++)
            printf("%.2f ", mat_custo[i][j]);
        fprintf(f, "\n");
    }
    if (strcmp(arq, " "))
        fclose(f);
}

void ler_dados(char* arq)
{
    int aux;
    int vetX[MAX_CLI];
    int vetY[MAX_CLI];
    FILE* f = fopen(arq, "r");
    fscanf(f, "%d %d", &num_cli, &num_vei);
    for (int j = 0; j <= num_cli; j++)
        fscanf(f, "%d %d %d %d", &aux, &vetX[j], &vetY[j], &vet_dem_cli[j]);
    for (int i = 0; i < num_vei; i++)
        fscanf(f, "%d", &vet_cap_vei[i]);
    fclose(f);
    //---
    for (int i = 0; i <= num_cli; i++)
        for (int j = 0; j <= num_cli; j++)
            mat_custo[i][j] = sqrt(pow(vetX[i]-vetX[j],2)+pow(vetY[i]-vetY[j],2));
}

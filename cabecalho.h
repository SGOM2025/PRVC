#ifndef CABECALHO_H_INCLUDED
#define CABECALHO_H_INCLUDED

#define MAX_CLI 501
#define MAX_VEI 100

typedef struct tSolucao{
    int mat_sol[MAX_VEI][MAX_CLI];
    int vet_qtd_cli_vei[MAX_VEI];
    int vet_pes_vei[MAX_VEI];
    double fo;
}Solucao;

int num_cli, num_vei;
int vet_dem_cli[MAX_CLI];
int vet_cap_vei[MAX_VEI];
double mat_custo[MAX_CLI][MAX_CLI];
int visitado[MAX_CLI];

void heu_cons_ale(Solucao& s);
int cliente_maior_demanda();
int cliente_menor_custo(int linha);
void heu_cons_gul(Solucao& s);
void heu_cons_ale_gul(Solucao& s, const double& percentual);

void heu_BL_rand(Solucao &s, const int& iter);
void heu_BL_MM(Solucao &s);
void heu_BL_PM(Solucao &s);

void remover_cliente(Solucao& s, const int& vei, const int& pos);
void inserir_cliente(Solucao& s, const int& vei, const int& pos, const int& cli);

void gerar_vizinho(Solucao& s);
void calcular_fo(Solucao& s);
void escrever_solucao(Solucao &s);
void testar_dados(char* arq);
void ler_dados(char* arq);


#endif // CABECALHO_H_INCLUDED

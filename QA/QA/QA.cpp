/* Maximizar z = 100 x1 + 60 x2 + 70 x3 + 15 x4 + 8 x5
    s.a.     52 x1 + 23 x2 + 35 x3 + 15 x4 + 7 x5 <= 60
             x1, x2, x3, x4, x5 \in{ 0,1 }
*/

#include<stdio.h>
#include<stdlib.h>
#include<C:\glpk-4.65\src\glpk.h>

int main() {

    glp_prob* lp; // Variável que vai receber o problema
    int  ia[1 + 1000], ja[1 + 1000];
    double ar[1 + 1000], z;
    bool x1, x2, x3, x4, x5;

    /* Criar um problema inicialmente vazio */
    lp = glp_create_prob();

    /* Criar um nome para o problema */
    glp_set_obj_name(lp, "Mochila 0-1");

    /* Criar o critério de Otimização */
    glp_set_obj_dir(lp, GLP_MAX);

    /* Adicionar as linhas ao problema */
    glp_add_rows(lp, 1);

    /* Cria um nome simbólico para a linha "p" */
    glp_set_row_name(lp, 1, "p");

    /* Criar um limite superior para a primeira linha */
    glp_set_row_bnds(lp, 1, GLP_UP, 0.0, 60.0);
    glp_add_cols(lp, 5);

    /* Mudar os tipos de dados para se ter variáveis do tipo binárias */
    glp_set_col_kind(lp, 1, GLP_BV);
    glp_set_col_kind(lp, 2, GLP_BV);
    glp_set_col_kind(lp, 3, GLP_BV);
    glp_set_col_kind(lp, 4, GLP_BV);
    glp_set_col_kind(lp, 5, GLP_BV);

    /* Adicionar um nome simbólico para a primeira coluna*/
    glp_set_col_name(lp, 1, "x1");
    glp_set_col_name(lp, 2, "x2");
    glp_set_col_name(lp, 3, "x3");
    glp_set_col_name(lp, 4, "x4");
    glp_set_col_name(lp, 5, "x5");

    /* Definir o coeficiente da FO para a primeira coluna */
    glp_set_obj_coef(lp, 1, 100);
    glp_set_obj_coef(lp, 2, 60);
    glp_set_obj_coef(lp, 3, 70);
    glp_set_obj_coef(lp, 4, 15);
    glp_set_obj_coef(lp, 5, 8);

    /* Definir os coeficientes da matriz de restrições  */
    ia[1] = 1, ja[1] = 1, ar[1] = 52; // a[1,1] = 52
    ia[2] = 1, ja[2] = 2, ar[2] = 23; // a[1,2] = 23
    ia[3] = 1, ja[3] = 3, ar[3] = 35; // a[1,3] = 35
    ia[4] = 1, ja[4] = 4, ar[4] = 15; // a[1,4] = 15
    ia[5] = 1, ja[5] = 5, ar[5] = 7; // a[1,5] = 7

    /* Carrega a matriz de restricoes */
    glp_load_matrix(lp, 5, ia, ja, ar);

    /* Carrega metodo simplex para resolver o problema */
    glp_simplex(lp, NULL);

    /* Carrega o valor da Função Objetivo (FO) */
    z = glp_get_obj_val(lp);

    /* Carregar os valores das variáveis de decisão obtidos */
    x1 = glp_get_col_prim(lp, 1);
    x2 = glp_get_col_prim(lp, 2);
    x3 = glp_get_col_prim(lp, 3);
    x4 = glp_get_col_prim(lp, 4);
    x5 = glp_get_col_prim(lp, 5);

    /* Escreve o resultado */
    printf("\n z = %g; x1 = %d; x2 = %d; x3 = %d; x4 = %d; x5 = %d \n", z, x1, x2, x3, x4, x5);

    /* Libera a memória alocada para o problema */
    glp_delete_prob(lp);

    return 0;
}
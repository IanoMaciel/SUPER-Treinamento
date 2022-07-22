# Estratégias Algorítmicas para Problemas de Otimização
## Atividade 2 - Prática Resolvedor GLPK

**1. Implemente em C e no Formato LP, os seguintes problemas de programação linear ja modelados em sala:**

A) Problema da Mochila 0-1

```C
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
```

B) Problema da Mochila Francionária
```C
/* Maximizar   z = 60 x1 + 100 x2 + 120 x3
   s.a.        100 x1 + 20 x2 + 30 x3 <= 50
               0 <= xi <= 1*/

#include <stdlib.h>
#include <stdio.h>
#include <C:\glpk-4.65\src\glpk.h>

int main() {
	glp_prob* lp; // Variavel que vai receber o problema
	int ia[1 + 1000], ja[1 + 1000];
	double ar[1 + 1000], z, x1, x2, x3;

	/* Cria um problema inicialmente vazio */
	lp = glp_create_prob();

	/* Cria um nome para o problema */
	glp_set_prob_name(lp, "Mochila fracionaria");

	/* Cria criterio de otimizacao */
	glp_set_obj_dir(lp, GLP_MAX);

	/* Adiciona linhas ao problema */
	glp_add_rows(lp, 1);

	/* Cria um nome simbolico para a linha "p" */
	glp_set_row_name(lp, 1, "p");

	/* Cria um limite superior para a primeira linha */
	glp_set_row_bnds(lp, 1, GLP_UP, 0.0, 50.0);
	glp_add_cols(lp, 3);

	/* Adiciona um nome simbolico para a primeira coluna */
	glp_set_col_name(lp, 1, "x1");
	glp_set_col_name(lp, 2, "x2");
	glp_set_col_name(lp, 3, "x3");

	/* Define um limite inferior para a coluna */
	glp_set_col_bnds(lp, 1, GLP_UP, 0, 1);
	glp_set_col_bnds(lp, 2, GLP_UP, 0, 1);
	glp_set_col_bnds(lp, 3, GLP_UP, 0, 1);

	/* Define o coeficiente da FO para a primeira coluna */
	glp_set_obj_coef(lp, 1, 60);
	glp_set_obj_coef(lp, 2, 100);
	glp_set_obj_coef(lp, 3, 120);

	/* Define coeficientes da matriz de restricoes */
	ia[1] = 1, ja[1] = 1, ar[1] = 10.0; /* a[1,1] = 10 */
	ia[2] = 1, ja[2] = 2, ar[2] = 20.0; /* a[1,2] = 20 */
	ia[3] = 1, ja[3] = 3, ar[3] = 30.0; /* a[1,3] = 30 */

	/* Carrega a matriz de restricoes */
	glp_load_matrix(lp, 3, ia, ja, ar);

	/* Carrega metodo simplex para resolver o problema */
	glp_simplex(lp, NULL);

	/* Carrega o valor da Funcao Objetivo(FO) */
	z = glp_get_obj_val(lp);

	/* Carregar os valores das variaveis de decisao obtidos */
	x1 = glp_get_col_prim(lp, 1);
	x2 = glp_get_col_prim(lp, 2);
	x3 = glp_get_col_prim(lp, 3);


	/* Escreve a saida */
	printf("\nz = %g; x1 = %g; x2 = %g; x3 = %g\n", z, x1, x2, x3);

	/* Libera a memoria alocada para o problema */
	glp_delete_prob(lp);

	return 0;
}
```

C) Problema da Dieta
```C
/* Minimizar  z = 2 x1 + 4 x2 + 1.5 x3 + x4
s. a.         2 x1 + 2 x2 + 10 x3 + 20 x4 >= 11
              50 x1 + 20 x2 + 10 x3 + 30 x4 >= 70
			  80 x1 + 70 x2 + 10 x3 + 80 x4 >= 250
			  x1 >= 0, x2 >= 0, x3 >= 0, x4 >= 0*/

#include <stdlib.h>
#include <stdio.h>
#include <C:\glpk-4.65\src\glpk.h>

int main() {
	glp_prob* lp; // Variavel que vai receber o problema
	int ia[1 + 1000], ja[1 + 1000];
	double ar[1 + 1000], z, x1, x2, x3, x4;

	/* Cria um problema inicialmente vazio */
	lp = glp_create_prob();

	/* Cria um nome para o problema */
	glp_set_prob_name(lp, "Problema da Dieta");

	/* Cria criterio de otimizacao */
	glp_set_obj_dir(lp, GLP_MIN);

	/* Adiciona linhas ao problema */
	glp_add_rows(lp, 3);

	/* Cria um nome simbolico para a linha "p" */
	glp_set_row_name(lp, 1, "vit_A");
	glp_set_row_name(lp, 2, "vit_C");
	glp_set_row_name(lp, 3, "vit_D");

	/* Cria um limite superior para a primeira linha */
	glp_set_row_bnds(lp, 1, GLP_LO, 11.0, 11.0);
	glp_set_row_bnds(lp, 2, GLP_LO, 70.0, 70.0);
	glp_set_row_bnds(lp, 3, GLP_LO, 250.0, 250.0);

	glp_add_cols(lp, 4);

	/* Adiciona um nome simbolico para a primeira coluna */
	glp_set_col_name(lp, 1, "x1");
	glp_set_col_name(lp, 2, "x2");
	glp_set_col_name(lp, 3, "x3");
	glp_set_col_name(lp, 4, "x4");

	/* Define um limite inferior para a coluna */
	glp_set_col_bnds(lp, 1, GLP_LO, 0, 1);
	glp_set_col_bnds(lp, 2, GLP_LO, 0, 1);
	glp_set_col_bnds(lp, 3, GLP_LO, 0, 1);
	glp_set_col_bnds(lp, 4, GLP_LO, 0, 1);

	/* Define o coeficiente da FO para a primeira coluna */
	glp_set_obj_coef(lp, 1, 2.0);
	glp_set_obj_coef(lp, 2, 4.0);
	glp_set_obj_coef(lp, 3, 1.5);
	glp_set_obj_coef(lp, 4, 1.0);

	/* Define coeficientes da matriz de restricoes */
	ia[1] = 1, ja[1] = 1, ar[1] = 2.0; /* a[1,1] = 2 */
	ia[2] = 1, ja[2] = 2, ar[2] = 2.0; /* a[1,2] = 2 */
	ia[3] = 1, ja[3] = 3, ar[3] = 10.0; /* a[1,3] = 10 */
	ia[4] = 1, ja[4] = 4, ar[4] = 20.0; /* a[1,4] = 20 */

	ia[1] = 2, ja[1] = 1, ar[1] = 50.0; /* a[2,1] = 50 */
	ia[2] = 2, ja[2] = 2, ar[2] = 20.0; /* a[2,2] = 20 */
	ia[3] = 2, ja[3] = 3, ar[3] = 10.0; /* a[2,3] = 10 */
	ia[4] = 2, ja[4] = 4, ar[4] = 30.0; /* a[2,4] = 30 */

	ia[1] = 3, ja[1] = 1, ar[1] = 80.0; /* a[3,1] = 80 */
	ia[2] = 3, ja[2] = 2, ar[2] = 70.0; /* a[3,2] = 70 */
	ia[3] = 3, ja[3] = 3, ar[3] = 10.0; /* a[3,3] = 10 */
	ia[4] = 3, ja[4] = 4, ar[4] = 80.0; /* a[3,4] = 80 */

	/* Carrega a matriz de restricoes */
	glp_load_matrix(lp, 4, ia, ja, ar);

	/* Carrega metodo simplex para resolver o problema */
	glp_simplex(lp, NULL);

	/* Carrega o valor da Funcao Objetivo(FO) */
	z = glp_get_obj_val(lp);

	/* Carregar os valores das variaveis de decisao obtidos */
	x1 = glp_get_col_prim(lp, 1);
	x2 = glp_get_col_prim(lp, 2);
	x3 = glp_get_col_prim(lp, 3);
	x4 = glp_get_col_prim(lp, 4);


	/* Escreve a saida */
	printf("\nz = %g; x1 = %g; x2 = %g; x3 = %g; x4 = %g\n", z, x1, x2, x3, x4);

	/* Libera a memoria alocada para o problema */
	glp_delete_prob(lp);

	return 0;
}


```

D) Problema daas Ligas Metálicas
```C
/* Maximizar  z = 3000 x1 + 5000 x2
s. a.         0.5 x1 + 0.2 x2 <= 16
              0.25 x1 + 0.3 x2 <= 11
			  0.25 x1 + 0.5 x2 <= 15
			  x1 >= 0, x2 >= 0*/

#include <stdlib.h>
#include <stdio.h>
#include <C:\glpk-4.65\src\glpk.h>

int main() {
	glp_prob* lp; // Variavel que vai receber o problema
	int ia[1 + 1000], ja[1 + 1000];
	double ar[1 + 1000], z, x1, x2;

	/* Cria um problema inicialmente vazio */
	lp = glp_create_prob();

	/* Cria um nome para o problema */
	glp_set_prob_name(lp, "Problema das Ligas Metalicas");

	/* Cria criterio de otimizacao */
	glp_set_obj_dir(lp, GLP_MAX);

	/* Adiciona linhas ao problema */
	glp_add_rows(lp, 3);

	/* Cria um nome simbolico para a linha "p" */
	glp_set_row_name(lp, 1, "Cobre");
	glp_set_row_name(lp, 2, "Zinco");
	glp_set_row_name(lp, 3, "Chumbo");

	/* Cria um limite superior para a primeira linha */
	glp_set_row_bnds(lp, 1, GLP_UP, 0.0, 16.0);
	glp_set_row_bnds(lp, 2, GLP_UP, 0.0, 11.0);
	glp_set_row_bnds(lp, 3, GLP_UP, 0.0, 15.0);

	glp_add_cols(lp, 2);

	/* Adiciona um nome simbolico para a primeira coluna */
	glp_set_col_name(lp, 1, "x1");
	glp_set_col_name(lp, 2, "x2");

	/* Define um limite inferior para a coluna */
	glp_set_col_bnds(lp, 1, GLP_UP, 0, 100);
	glp_set_col_bnds(lp, 2, GLP_UP, 0, 100);

	/* Define o coeficiente da FO para a primeira coluna */
	glp_set_obj_coef(lp, 1, 3000.0);
	glp_set_obj_coef(lp, 2, 5000.0);

	/* Define coeficientes da matriz de restricoes */
	ia[1] = 1, ja[1] = 1, ar[1] = 0.50; /* a[1,1] = 0.5 */
	ia[2] = 1, ja[2] = 2, ar[2] = 0.20; /* a[1,2] = 0.2 */

	ia[1] = 2, ja[1] = 1, ar[1] = 0.25; /* a[2,1] = 0.25 */
	ia[2] = 2, ja[2] = 2, ar[2] = 0.30; /* a[2,2] = 0.3 */

	ia[1] = 3, ja[1] = 1, ar[1] = 0.25; /* a[3,1] = 0.25 */
	ia[2] = 3, ja[2] = 2, ar[2] = 0.50; /* a[3,2] = 0.5 */

	/* Carrega a matriz de restricoes */
	glp_load_matrix(lp, 2, ia, ja, ar);

	/* Carrega metodo simplex para resolver o problema */
	glp_simplex(lp, NULL);

	/* Carrega o valor da Funcao Objetivo(FO) */
	z = glp_get_obj_val(lp);

	/* Carregar os valores das variaveis de decisao obtidos */
	x1 = glp_get_col_prim(lp, 1);
	x2 = glp_get_col_prim(lp, 2);

	/* Escreve a saida */
	printf("\nz = %g; x1 = %g; x2 = %g\n", z, x1, x2);

	/* Libera a memoria alocada para o problema */
	glp_delete_prob(lp);

	return 0;
}
```

E) Modelo a Segui: 
```C
/* Maximizar   z = 4 x1 + 5 x2 + 9 x3 + 11 x4
s. a.          x1 + x2 + x3 + x4 <= 15
               7 x1 + 5 x2 + 3 x3 + 2 x4 <= 120
			   3 x1 + 5 x2 + 10 x3 + 15 x4 <= 100
			   x1 >= 0, x2 >= 0, x3 >= 0, x4 >= 0*/

#include <stdlib.h>
#include <stdio.h>
#include <C:\glpk-4.65\src\glpk.h>

int main() {
	glp_prob* lp; // Variavel que vai receber o problema
	int ia[1 + 1000], ja[1 + 1000];
	double ar[1 + 1000], z, x1, x2, x3, x4;

	/* Cria um problema inicialmente vazio */
	lp = glp_create_prob();

	/* Cria um nome para o problema */
	glp_set_prob_name(lp, "Modelo a seguir:");

	/* Cria criterio de otimizacao */
	glp_set_obj_dir(lp, GLP_MAX);

	/* Adiciona linhas ao problema */
	glp_add_rows(lp, 3);

	/* Cria um nome simbolico para a linha "p" */
	glp_set_row_name(lp, 1, "Modelo_A");
	glp_set_row_name(lp, 2, "Modelo_B");
	glp_set_row_name(lp, 3, "Modelo_C");

	/* Cria um limite superior para a primeira linha */
	glp_set_row_bnds(lp, 1, GLP_UP, 0.0, 15.0);
	glp_set_row_bnds(lp, 2, GLP_UP, 0.0, 120.0);
	glp_set_row_bnds(lp, 3, GLP_UP, 0.0, 100.0);

	glp_add_cols(lp, 4);

	/* Adiciona um nome simbolico para a primeira coluna */
	glp_set_col_name(lp, 1, "x1");
	glp_set_col_name(lp, 2, "x2");
	glp_set_col_name(lp, 3, "x3");
	glp_set_col_name(lp, 4, "x4");

	/* Define um limite inferior para a coluna */
	glp_set_col_bnds(lp, 1, GLP_UP, 0, 100);
	glp_set_col_bnds(lp, 2, GLP_UP, 0, 100);
	glp_set_col_bnds(lp, 3, GLP_UP, 0, 100);
	glp_set_col_bnds(lp, 4, GLP_UP, 0, 100);

	/* Define o coeficiente da FO para a primeira coluna */
	glp_set_obj_coef(lp, 1, 4.0);
	glp_set_obj_coef(lp, 2, 5.0);
	glp_set_obj_coef(lp, 3, 9.0);
	glp_set_obj_coef(lp, 4, 11.0);

	/* Define coeficientes da matriz de restricoes */
	ia[1] = 1, ja[1] = 1, ar[1] = 1.0; /* a[1,1] = 1.0 */
	ia[2] = 1, ja[2] = 2, ar[2] = 1.0; /* a[1,2] = 1.0 */
	ia[3] = 1, ja[3] = 3, ar[3] = 1.0; /* a[1,3] = 1.0 */
	ia[4] = 1, ja[4] = 4, ar[4] = 1.0; /* a[1,4] = 1.0 */

	ia[1] = 2, ja[1] = 1, ar[1] = 7.0; /* a[2,1] = 7.0 */
	ia[2] = 2, ja[2] = 2, ar[2] = 5.0; /* a[2,2] = 5.0 */
	ia[3] = 2, ja[3] = 3, ar[3] = 3.0; /* a[2,3] = 3.0 */
	ia[4] = 2, ja[4] = 4, ar[4] = 2.0; /* a[2,4] = 2.0 */

	ia[1] = 3, ja[1] = 1, ar[1] = 3.0; /* a[3,1] = 3.0 */
	ia[2] = 3, ja[2] = 2, ar[2] = 5.0; /* a[3,2] = 5.0 */
	ia[3] = 3, ja[3] = 3, ar[3] = 10.0; /* a[3,3] = 10.0 */
	ia[4] = 3, ja[4] = 4, ar[4] = 15.0; /* a[3,4] = 15.0 */

	/* Carrega a matriz de restricoes */
	glp_load_matrix(lp, 4, ia, ja, ar);

	/* Carrega metodo simplex para resolver o problema */
	glp_simplex(lp, NULL);

	/* Carrega o valor da Funcao Objetivo(FO) */
	z = glp_get_obj_val(lp);

	/* Carregar os valores das variaveis de decisao obtidos */
	x1 = glp_get_col_prim(lp, 1);
	x2 = glp_get_col_prim(lp, 2);
	x3 = glp_get_col_prim(lp, 3);
	x4 = glp_get_col_prim(lp, 4);

	/* Escreve a saida */
	printf("\nz = %g; x1 = %g; x2 = %g; x3 = %g; x4 = %g\n", z, x1, x2, x3, x4);

	/* Libera a memoria alocada para o problema */
	glp_delete_prob(lp);

	return 0;
}

```


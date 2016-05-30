# include <stdio.h>
# define NRPAISES 28
# define NRPARTIDOS 12


int matriz_v[NRPAISES][NRPARTIDOS]; /*Matriz que guarda os votos*/
int matriz_f[NRPAISES+1][NRPARTIDOS]; /*Matriz final com o numero de deputados eleitos de todos os paises*/
char paises[NRPAISES+1][3] = {"DE","AT","BE","BG","CY","HR","DK","SK","SI","ES","EE","FI","FR","GR",
	"HU","IE","IT","LV","LT","LU","MT","NL","PL","PT","GB","CZ","RO","SE","TE"};
char partys[55] = "   EPP PES LDE EGP ECR ELP ELD EDP EAF EMN ECP AED\n";
float linha_da_matriz_v[NRPARTIDOS];


/*
inicializa_matriz: int X int --> void
inicializa_matriz(int, int) recebe uma matriz em o numero de linhas da matriz, e coloca todos os seus valores a zero 
*/

void inicializa_matriz (int matriz[][NRPARTIDOS], int linha)
{
	int i, j;
	
	for (i=0; i < linha ; i++)
	{
		for (j=0; j < NRPARTIDOS; j++)
			matriz[i][j] = 0;
	}
}


/*
adiciona_votos: int x int x int --> void
adiciona_votos(int, int, int) recebe um pais, um partido e os respectivos votos,
 e adiciona esse numero de votos na respectiva posicao da matriz
*/

void adiciona_votos(int i, int j, int valor)
{

	matriz_v[i-1][j-1] = matriz_v[i-1][j-1] + valor;

}


/*
copia_vetor_matriz: int --> void
copia_vector_matriz(int) recebe o numero de um pais e copia da matriz que contem o numero de votos,
 o vector correspondente ao numero de votos desse pais
*/

void copia_vector_matriz (int pais)
{
    int j;
    for (j=0; j < NRPARTIDOS; j++)
    {
        linha_da_matriz_v[j] = (float) matriz_v[pais][j];
    }
}


/*
metodo_dhondt: float x int --> void
metodo_dhondt(float, int) recebe um vector e o numero de um pais, aplica o metodo dhont ao vector e 
adiciona o resultado ao pais na matriz dos deputados 
*/

void metodo_dhondt (float vector[], int pais)
{
    int nr_de_deputados[NRPARTIDOS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int Dep_pais[NRPAISES] = {96, 18, 21, 17, 6, 11, 13, 13, 8, 54, 6, 13, 74, 21, 21, 11, 73,
    8, 11, 6, 6, 26, 51, 21, 73, 21, 32, 20 };
    int deps_total = Dep_pais[pais];
    int j, indice;
    float max;

    while (deps_total > 0)
    {
        max = vector[0] /(nr_de_deputados[0] +1);
        indice = 0;
        for (j=1; j < NRPARTIDOS; j++ )
        {
            if (vector[j]/(nr_de_deputados[j] + 1) > max)
            {
                max = vector[j]/(nr_de_deputados[j]+1);
                indice = j;
            }

            else if (vector[j]/(nr_de_deputados[j] + 1) == max)
            {
                if (vector[j] < vector[indice])
                {
                    indice = j;
                }

            }
        }
        if (max != 0)
        {
            nr_de_deputados[indice]++;
            deps_total--;   
        }
        else 
        {
            deps_total = 0;
        }
        
    }
    for (j = 0; j < NRPARTIDOS; j++)
	{
        matriz_f[pais][j] = nr_de_deputados[j];
		matriz_f[NRPAISES][j] = matriz_f[NRPAISES][j] + nr_de_deputados[j];
	}
}


/*
full_dhont: void --> void
full_dhont() aplica a todas as linhas da matriz dos paises o metodo dhondt
*/

void full_dhondt()
{
    int i;
    for (i = 0; i < NRPAISES; i++)
    {
        copia_vector_matriz(i);
        metodo_dhondt(linha_da_matriz_v, i);
    }
}


/*
imprime_especifico: int --> void
imprime_especifico(int) recebe o numero de um pais e imprime no ecra o numero de 
deputados eleitos de cada partido nesse pais
*/

void imprime_especifico(int pais)
{
	int j;
	printf(partys);
	printf("%s",paises[pais-1]);
	
	for (j=0; j < NRPARTIDOS; j++)
	{
		printf(" %3d", matriz_f[pais-1][j]);
	}
	printf("\n");
}


/*
imprime_matriz_f: void --> void
imprime_matriz_f() imprime no ecra o numero de deputados eleitos de todos os paises e partidos 
*/

void imprime_matriz_f()
{
	int i, j;
	printf(partys);
	
	for ( i = 0; i < (NRPAISES+1); i++)
	{
		printf("%s", paises[i]);
	
		for (j=0; j < NRPARTIDOS; j++)
		{
			printf(" %3d", matriz_f[i][j]);
		}
		
		printf("\n");
	}
}


/*
main: void --> void
main e a funcao que faz a chamada de todas as outras funcoes, e esta estruturada
por switches que reconhecem os caracteres '+', 'm', 'e' e 'x'
*/	
	
int main()
{
   
	char command; 
	int pais, partido, n_votos;
	inicializa_matriz(matriz_v, NRPAISES);
	
    while ((command = getchar()) != 'x') { 
        switch (command) 
        {
        case '+':
            /* Chama a funcao responsavel pela execucao do comando + */
			
			scanf("%d%d%d",&pais,&partido,&n_votos);
			adiciona_votos(pais, partido, n_votos);
			
			break;
			
        case 'm':
            /* Chama a funcao responsavel pela execucao do comando m */
			
			scanf("%d",&pais);
			inicializa_matriz(matriz_f, NRPAISES+1);
			full_dhondt();
			imprime_especifico(pais);
			
            break;
			
        case 'e':
            /* Chama a funcao responsavel pela execucao do comando e */
			
			inicializa_matriz(matriz_f, NRPAISES+1);
			full_dhondt();
			imprime_matriz_f();
			
            break;
			
        default:
            printf("ERRO: Comando desconhecido\n");
        }
        getchar(); 
    }
    return 0;
}


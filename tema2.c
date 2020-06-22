//Serboi Florea-Dan 315CB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define rand_liber "\n"

void elim_trailing (char matrice[1000][1000], long numar_linii_matrice)
{
	long i, j, l, nr;
	for (i = 0; i < numar_linii_matrice; i++)
	{
		l = strlen(matrice[i]) - 2;
		//de la indicele l incolo pot exista spatii
		nr = 0;
		j = l;
		while (matrice[i][j] == ' ' || matrice[i][j] == '\t')
		{
			nr++;
			j--;
		}
		//atat timp cat avem spatii, creste contorul
		strcpy(matrice[i] + l + 1 - nr, matrice[i] + l + 1);
		//eliminam spatiile
	}
}

long lung_max_cuv(char matrice[1000][1000], long numar_linii_matrice)
{
	char cuv[1000];
	long i, j, c, sup, k = -1, max1 = -1;
	for (i = 0; i < numar_linii_matrice; i++)
	{
		sup = strlen(matrice[i]) - 1;
		for (j = 0; j <= sup; j++)
			if (matrice[i][j] != ' ' && matrice[i][j] != '\n'
				&& matrice[i][j] != '\t')
			{
				k++;
				cuv[k] = matrice[i][j];
			}
			else
			{
				cuv[k + 1] = '\0';
				c = strlen(cuv);
				if (c > max1)
					max1 = c;
				k = -1;
				strcpy(cuv, "");
			}
	}
	return max1;
}

long lung_max_linie (char matrice[1000][1000], long numar_linii_matrice)
{
	long i, j, lungime, lung_max_linie;
	char auxmatrice[1000][1000];
	for (j = 0; j < 1000; j++)
		strcpy(auxmatrice[j], "");
	lung_max_linie = -1;
	for (j = 0; j < numar_linii_matrice; j++)
		strcpy(auxmatrice[j], matrice[j]);
	elim_trailing(auxmatrice, numar_linii_matrice);
	//am eliminat trailing spaces inainte de a determina maximul
	for (i = 0; i < numar_linii_matrice; i++)
	{
		lungime = strlen(auxmatrice[i]);
		if (lungime > lung_max_linie)
			lung_max_linie = lungime;
	}
	return lung_max_linie;
}

void center(char matrice[1000][1000], long numar_linii_matrice,
	        long linie_inceput, long linie_final)
{
	long i, diferenta, rest, lungime_max, lungime;
	char aux[1000], aux2[1000];
	strcpy(aux, "");
	strcpy(aux2, "");
	if (numar_linii_matrice <= linie_final)
		linie_final = numar_linii_matrice - 1;
	elim_trailing(matrice, numar_linii_matrice);
	for (i = linie_inceput; i <= linie_final; i++)
	{
		if (strcmp(matrice[i], rand_liber) != 0)
		{
			lungime_max = lung_max_linie(matrice, numar_linii_matrice);
			lungime = strlen(matrice[i]);
			diferenta = lungime_max - lungime;
			if (diferenta % 2 == 1)rest = diferenta / 2 + 1;
			else
				rest = diferenta / 2;
			//facem un sir auxiliar la care concatenam linia curenta
			memset(aux, ' ', rest);
			aux[rest] = '\0';
			strcpy(aux2, matrice[i]);
			strcat(aux, aux2);
			strcpy(matrice[i], aux);
		}
	}
}

void align_left(char matrice[1000][1000], long numar_linii_matrice,
				long linie_inceput, long linie_final)
{
	long i, j;
	char aux[1000];
	if (numar_linii_matrice <= linie_final)
		linie_final = numar_linii_matrice - 1;
	for (i = linie_inceput; i <= linie_final; i++)
	{
		j = 0;
		while (matrice[i][j] == ' ' || matrice[i][j] == '\t')
			j++;
		strcpy(aux, matrice[i] + j);
		strcpy(matrice[i], aux);
		//eliminam spatiile de la inceputul liniei
	}
	elim_trailing(matrice, numar_linii_matrice);
}

void align_right(char matrice[1000][1000], long numar_linii_matrice,
			   	 long linie_inceput, long linie_final)
{
	long i, m, l, diferenta;
	char aux[1000];
	strcpy(aux, "");
	if (numar_linii_matrice <= linie_final)
		linie_final = numar_linii_matrice - 1;
	elim_trailing(matrice, numar_linii_matrice);
	m = lung_max_linie(matrice, numar_linii_matrice);
	for (i = linie_inceput; i <= linie_final; i++)
	{
		l = strlen(matrice[i]);
		diferenta = m - l;
		memset(aux, ' ', diferenta);
		//facem un sir cu numarul de spatii necesar la care concatenam linia
		aux[diferenta] = '\0';
		strcat(aux, matrice[i]);
		strcpy(matrice[i], aux);
	}
	elim_trailing(matrice, numar_linii_matrice);
}

void justify(char matrice[1000][1000], long numar_linii_matrice,
			 long linie_inceput, long linie_final)
{
	long i, j, lungime, lungime_max, k, curent, urmator;
	lungime_max = lung_max_linie(matrice, numar_linii_matrice);
	if (numar_linii_matrice <= linie_final)
		linie_final = numar_linii_matrice - 1;
	align_left(matrice, numar_linii_matrice, linie_inceput, linie_final);
	for (i = linie_inceput; i < linie_final; i++)
	{
		lungime = strlen(matrice[i]);
		curent = strcmp(matrice[i], rand_liber);
		urmator = strcmp(matrice[i + 1], rand_liber);
		if (curent != 0 && urmator != 0 && lungime != lungime_max)
		//linia curenta nu e goala, nu e ultima dintr-un paragraf
		//si nu e de lungime maxima
			while (lungime < lungime_max)
				//adaugam spatii cat timp nu este atinsa lungimea maxima
				for (j = 0; j <= lungime - 1; j++)
				{
					if (matrice[i][j] == ' ' && matrice[i][j + 1] != ' ')
					{
						//spatiile se adauga unde avem deja spatiu
						for (k = lungime - 1; k >= j + 1; k--)
							matrice[i][k + 1] = matrice[i][k];
						matrice[i][lungime + 1] = '\0';
						matrice[i][j + 1] = ' ';
						j++;
						lungime++;
					}
					if (lungime == lungime_max)
						break;
				}
	}
}

void wrap(char matrice[1000][1000], long *numar_linii_matrice,
		  long lungime_maxima)
{
	char intregul_text [1000000], aux[1000];
	long i, j, k, ok, curent, anterior, urmator, lungime,
	capat_initial, capat_final, capat_intregul_text;
	strcpy(intregul_text, "");
	elim_trailing(matrice, *numar_linii_matrice);
	//in intregul_text punem continutul liniilor, dar cu spatiu in loc de \n,
	//nu eliminam \n cand avem rand liber (urmeaza paragraf)
	//ulterior punem \n convenabil
	for (i = 0; i < *numar_linii_matrice; i++)
	{
		if (i != 0)
			anterior = strcmp(matrice[i - 1], rand_liber);
		curent = strcmp(matrice[i], rand_liber);
		urmator = strcmp(matrice[i + 1], rand_liber);
		if (curent == 0)
			strcat(intregul_text, matrice[i]);
		else if (anterior == 0 || i == 0)
		{
			lungime = strlen(matrice[i]) - 1;
			if (urmator != 0)
				matrice[i][lungime] = ' ';
			strcat(intregul_text, matrice[i]);
		}
		else
		{
			align_left(matrice, *numar_linii_matrice, i, i);
			lungime = strlen(matrice[i]) - 1;
			if (urmator != 0)
				matrice[i][lungime] = ' ';
			strcat(intregul_text, matrice[i]);
		}
	}
	capat_initial = 0;
	capat_final = lungime_maxima;
	k = 0;
	capat_intregul_text = strlen(intregul_text) - 1;
	while (capat_initial <= capat_final)
		//cat timp nu este modificat tot textul
	{
		ok = 0;
		//intai tratam \n si ulterior spatiul
		for (j = capat_initial; j <= capat_final; j++)
			//parcurgem de la cap la coada, deoarece nu putem "ignora" \n
			if (intregul_text[j] == '\n')
			{
				strcpy(aux, "");
				for (i = capat_initial; i <= j; i++)
					aux[i - capat_initial] = intregul_text[i];
				aux[j + 1 - capat_initial] = '\0';
				strcpy(matrice[k], aux);
				k++;
				capat_initial = j + 1;
				if (j + lungime_maxima <= capat_intregul_text)
					capat_final = j + lungime_maxima + 1;
				else
					capat_final = capat_intregul_text;
				ok = 1;
				break;
			}
		if (ok == 0)
			for (j = capat_final; j >= capat_initial; j--)
				//parcurgem de la coada la cap,
				//pentru a introduce cat mai multe spatii pe o linie
				if (intregul_text[j] == ' ')
				{
					strcpy(aux, "");
					for (i = capat_initial; i < j; i++)
						aux[i - capat_initial] = intregul_text[i];
					aux[j - capat_initial] = '\n';
					aux[j + 1 - capat_initial] = '\0';
					strcpy(matrice[k], aux);
					k++;
					capat_initial = j + 1;
					if (j + lungime_maxima <= capat_intregul_text)
						capat_final = j + lungime_maxima + 1;
					else
						capat_final = capat_intregul_text;
					break;
				}
		*numar_linii_matrice = k;
		elim_trailing(matrice, *numar_linii_matrice);
	}
}

void paragraf (char matrice[1000][1000], long numar_linii_matrice,
			   long indentare, long linie_inceput, long linie_final)
{
	long anterior, curent, i;
	char aux[1000];
	elim_trailing(matrice, numar_linii_matrice);
	if (numar_linii_matrice <= linie_final)
		linie_final = numar_linii_matrice - 1;
	for (i = linie_inceput; i <= linie_final; i++)
	{
		if (i != 0)
		{
			anterior = strcmp(matrice[i - 1], rand_liber);
			curent = strcmp(matrice[i], rand_liber);
		}
		if (i == 0 || (anterior == 0 && curent != 0))
		{
			align_left(matrice, numar_linii_matrice, i, i);
			strcpy(aux, "");
			memset(aux, ' ', indentare);
			aux[indentare] = '\0';
			strcat(aux, matrice[i]);
			strcpy(matrice[i], aux);
		}
	}
}

void lista (char matrice[1000][1000], long numar_linii_matrice, 
			char tip_lista,char caracter_special,
			long linie_inceput, long linie_final)
{
	long i;
	char aux[1000][1000];
	if (numar_linii_matrice <= linie_final)
		linie_final = numar_linii_matrice - 1;
	align_left(matrice, numar_linii_matrice, linie_inceput, linie_final);
	switch (tip_lista)
	{
	case 'n':
		for (i = linie_inceput; i <= linie_final; i++)
			sprintf(aux[i], "%ld%c %s", i - linie_inceput + 1,
				caracter_special, matrice[i]);
		break;
	case 'a':
		for (i = linie_inceput; i <= linie_final; i++)
			sprintf(aux[i], "%c%c %s", (char)(i - linie_inceput + 97),
				caracter_special, matrice[i]);
		break;
	case 'A':
		for (i = linie_inceput; i <= linie_final; i++)
			sprintf(aux[i], "%c%c %s", (char)(i - linie_inceput + 65),
				caracter_special, matrice[i]);
		break;
	case 'b':
		for (i = linie_inceput; i <= linie_final; i++)
			sprintf(aux[i], "%c %s", caracter_special, matrice[i]);
		break;
	}
	for (i = linie_inceput; i <= linie_final; i++)
		strcpy(matrice[i], aux[i]);
	elim_trailing(matrice, numar_linii_matrice);
}

void ordonare(char ordine, char matrice[1000][1000], long numar_linii_matrice,
			  long linie_inceput, long linie_final)
{
	char aux[1000];
	long i, j, compar;
	if (ordine == 'a')
	{
		for (i = linie_inceput; i < linie_final; i++)
			for (j = i + 1; j <= linie_final; j++)
			{	compar = strcmp(matrice[i], matrice[j]);
				if (compar > 0)
				{
					strcpy(aux, matrice[i]);
					strcpy(matrice[i], matrice[j]);
					strcpy(matrice[j], aux);
				}
			}
	}
	else
	{
		for (i = linie_inceput; i < linie_final; i++)
			for (j = i + 1; j <= linie_final; j++)
			{	compar = strcmp(matrice[i], matrice[j]);
				if (compar < 0)
				{
					strcpy(aux, matrice[i]);
					strcpy(matrice[i], matrice[j]);
					strcpy(matrice[j], aux);
				}

			}
	}
}

void lista_ordonata (char matrice[1000][1000], long numar_linii_matrice,
				   	 char tip_lista, char caracter_special, char ordine,
					 long linie_inceput, long linie_final)
{
	long i;
	char aux[1000][1000];
	if (numar_linii_matrice <= linie_final)
		linie_final = numar_linii_matrice - 1;
	ordonare(ordine, matrice, numar_linii_matrice, linie_inceput, linie_final);
	align_left(matrice, numar_linii_matrice, linie_inceput, linie_final);
	switch (tip_lista)
	{
	case 'n':
		for (i = linie_inceput; i <= linie_final; i++)
			sprintf(aux[i], "%ld%c %s", i - linie_inceput + 1,
				caracter_special, matrice[i]);
		break;
	case 'a':
		for (i = linie_inceput; i <= linie_final; i++)
			sprintf(aux[i], "%c%c %s", (char)(i - linie_inceput + 97),
				caracter_special, matrice[i]);
		break;
	case 'A':
		for (i = linie_inceput; i <= linie_final; i++)
			sprintf(aux[i], "%c%c %s", (char)(i - linie_inceput + 65),
				caracter_special, matrice[i]);
		break;
	case 'b':
		for (i = linie_inceput; i <= linie_final; i++)
			sprintf(aux[i], "%c %s", caracter_special, matrice[i]);
		break;
	}
	for (i = linie_inceput; i <= linie_final; i++)
		strcpy(matrice[i], aux[i]);
	elim_trailing(matrice, numar_linii_matrice);
}

void extragere_par (char sir_operatie[50], char parametri[10][10], long *n)
{
	char parametru[10];
	long k, i;
	k = -1, *n = -1;
	for (i = 0; i <= 9; i++)
		strcpy(parametri[i], "");
	for (i = 0; i <= strlen(sir_operatie); i++)
		if (sir_operatie[i] != ' ' && sir_operatie[i] != '\0')
		{
			k++;
			parametru[k] = sir_operatie[i];
		}
		else
		{
			parametru[k + 1] = '\0';
			if (strlen(parametru) > 0)
			{
				(*n)++;
				strcpy(parametri[*n], parametru);
			}
			k = -1;
			strcpy(parametru, "");
		}
	(*n)++;
}

int main(int argc, char *argv[])
{
	char buf[1000], matrice[1000][1000], rezultat[1000][1000],
		 sep_op[] = ",", operatii[15][50], *p, parametri[10][10],
		 tip_lista, caracter_special, ordine;
	long numar_linii_matrice = 0, numar_linii_rezultat = 0, i, nr_op, nr_par,
		 lungime_maxima, linie_inceput, linie_final, indentare, ok = 1;
	if (argc != 4)
	{
		fprintf(stderr,
		        "Usage: %s operations_string input_file output_file\n",
		        argv[0]);
		return -1;
	}
	FILE *input_file = fopen(argv[2], "r");
	if (input_file == NULL)
	{
		fprintf(stderr, "File \"%s\" not found\n", argv[2]);
		return -2;
	}
	while (fgets(buf, 1000, input_file))
	{
		strcpy(matrice[numar_linii_matrice], buf);
		strcpy(rezultat[numar_linii_matrice], buf);
		numar_linii_matrice++;
	}
	numar_linii_rezultat = numar_linii_matrice;
	fclose(input_file);
	i = 0;
	p = strtok(argv[1], sep_op);
	while (p)
	{
		i++;
		strcpy(operatii[i], p);
		p = strtok(NULL, sep_op);
	}
	nr_op = i;
	if (nr_op > 10)
	{
		printf("Too many operations! Only the first 10 will be applied.\n");
		nr_op = 10;
	}
	for (i = 1; i <= nr_op; i++)
	{
		extragere_par(operatii[i], parametri, & nr_par);
		if (strstr("WwCcLlRrJjPpIiOo", parametri[0]) == NULL)
		{
			printf("Invalid operation!\n");
			ok = 0;
		}
		else
		{
			if ((strcmp(parametri[0], "W") == 0 ||
		  		 strcmp(parametri[0], "w") == 0) && ok == 1)
			{
				lungime_maxima = atoi(parametri[1]);
				if (nr_par > 2)
				{
					printf("Invalid operation!\n");
					ok = 0;
				}
				else 
					if (lungime_maxima <
					lung_max_cuv(matrice, numar_linii_matrice))
					{
						printf("Cannot wrap!\n");
						ok = 0;
					}
				if (ok == 1)
					wrap(matrice, &numar_linii_matrice, lungime_maxima);
			}
			if ((strcmp(parametri[0], "C") == 0 ||
				 strcmp(parametri[0], "c") == 0) && ok == 1)
			{
				if (strcmp(parametri[1], "") == 0)
				{
					linie_inceput = 0;
					linie_final = numar_linii_matrice - 1;
				}
				else
				{
					linie_inceput = atoi(parametri[1]);
					if (strcmp(parametri[2], "") == 0)
						linie_final = numar_linii_matrice - 1;
					else
						linie_final = atoi(parametri[2]);
				}
				if (strchr("0123456789", parametri[2][0]) == NULL)
				{
					printf("Invalid operation!\n");
					ok = 0;
				}
				else
					if (linie_inceput > linie_final)
					{
						printf("Invalid operation!\n");
						ok = 0;
					}
					else
						if (linie_inceput <= linie_final && linie_inceput >= 0)
							center(matrice, numar_linii_matrice, linie_inceput,
				 		   		   linie_final);
			}
			if ((strcmp(parametri[0], "R") == 0 ||
				 strcmp(parametri[0], "r") == 0) && ok == 1)
			{
				if (strcmp(parametri[1], "") == 0)
				{
					linie_inceput = 0;
					linie_final = numar_linii_matrice - 1;
				}
				else
				{
					linie_inceput = atoi(parametri[1]);
					if (strcmp(parametri[2], "") == 0)
						linie_final = numar_linii_matrice - 1;
					else
						linie_final = atoi(parametri[2]);
				}
				if (nr_par > 3)
				{
					printf("Invalid operation!\n");
					ok = 0;
				}
				else
					if (linie_inceput <= linie_final && linie_inceput >= 0)
						align_right(matrice, numar_linii_matrice,
									linie_inceput, linie_final);
			}
			if ((strcmp(parametri[0], "L") == 0 ||
				strcmp(parametri[0], "l") == 0) && ok == 1)
			{
				if (strcmp(parametri[1], "") == 0)
				{
					linie_inceput = 0;
					linie_final = numar_linii_matrice - 1;
				}
				else
				{
					linie_inceput = atoi(parametri[1]);
					if (strcmp(parametri[2], "") == 0)
						linie_final = numar_linii_matrice - 1;
					else
						linie_final = atoi(parametri[2]);
				}
				if (linie_inceput < 0)
				{
					printf("Invalid operation!\n");
					ok = 0;
				}
				else
					if (linie_inceput <= linie_final)
						align_left(matrice, numar_linii_matrice, linie_inceput,
								   linie_final);
			}
			if ((strcmp(parametri[0], "J") == 0 ||
				 strcmp(parametri[0], "j") == 0) && ok == 1)
			{
				if (strcmp(parametri[1], "") == 0)
				{
					linie_inceput = 0;
					linie_final = numar_linii_matrice - 1;
				}
				else
				{
					linie_inceput = atoi(parametri[1]);
					if (strcmp(parametri[2], "") == 0)
						linie_final = numar_linii_matrice - 1;
					else
						linie_final = atoi(parametri[2]);
				}
				if (linie_inceput <= linie_final && linie_inceput >= 0)
					justify(matrice, numar_linii_matrice, linie_inceput,
							linie_final);
			}
			if ((strcmp(parametri[0], "P") == 0 ||
				 strcmp(parametri[0], "p") == 0) && ok == 1)
			{
				indentare = atoi(parametri[1]);
				if (strcmp(parametri[2], "") == 0)
				{
					linie_inceput = 0;
					linie_final = numar_linii_matrice - 1;
				}
				else
				{
					linie_inceput = atoi(parametri[2]);
					if (strcmp(parametri[3], "") == 0)
						linie_final = numar_linii_matrice - 1;
					else
						linie_final = atoi(parametri[3]);
				}
				if (parametri[1][0] == '\0' || atoi(parametri[1]) > 8
					|| atoi(parametri[1]) <= 0)
				{
					printf("Invalid operation!\n");
					ok = 0;
				}
				else
					if (linie_inceput <= linie_final && linie_inceput >= 0)
						paragraf(matrice, numar_linii_matrice, indentare,
								 linie_inceput, linie_final);
			}
			if ((strcmp(parametri[0], "I") == 0 ||
				 strcmp(parametri[i], "i") == 0) && ok == 1)
			{
				tip_lista = parametri[1][0];
				caracter_special = parametri[2][0];
				if (strcmp(parametri[3], "") == 0)
				{
					linie_inceput = 0;
					linie_final = numar_linii_matrice - 1;
				}
				else
				{
					linie_inceput = atoi(parametri[3]);
					if (strcmp(parametri[4], "") == 0)
						linie_final = numar_linii_matrice - 1;
					else
						linie_final = atoi(parametri[4]);
				}
				if (nr_par < 3 || strstr("naAb", parametri[1]) == NULL)
				{
					printf("Invalid operation!\n");
					ok = 0;
				}
				else
					if (linie_inceput <= linie_final && linie_inceput >= 0)
						lista (matrice, numar_linii_matrice, tip_lista,
							   caracter_special, linie_inceput, linie_final);
			}
			if ((strcmp(parametri[0], "O") == 0 ||
				 strcmp(parametri[i], "o") == 0) && ok == 1)
			{
				tip_lista = parametri[1][0];
				caracter_special = parametri[2][0];
				ordine = parametri[3][0];
				if (strcmp(parametri[4], "") == 0)
				{
					linie_inceput = 0;
					linie_final = numar_linii_matrice - 1;
				}
				else
				{
					linie_inceput = atoi(parametri[4]);
					if (strcmp(parametri[5], "") == 0)
						linie_final = numar_linii_matrice - 1;
					else
						linie_final = atoi(parametri[5]);
				}
				if (nr_par < 4 || strstr("az", parametri[3]) == NULL)
				{
					printf("Invalid operation!\n");
					ok = 0;
				}
				else
					if (linie_inceput <= linie_final && linie_inceput >= 0)
						lista_ordonata (matrice, numar_linii_matrice,
						tip_lista, caracter_special, ordine,
						linie_inceput, linie_final);
			}
		}
	}
	if (ok == 1)
	{
		for (i = 0; i < numar_linii_matrice; i++)
			strcpy(rezultat[i], matrice[i]);
		numar_linii_rezultat = numar_linii_matrice;
	}
	FILE *output_file = fopen(argv[3], "w");
	if (output_file == NULL)
	{
		fprintf(stderr, "Could not open or create file \"%s\"\n", argv[3]);
		return -2;
	}
	for (i = 0; i < numar_linii_rezultat; i++)
		fputs(rezultat[i], output_file);
	fclose(output_file);
	return 0;
}
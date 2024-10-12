//Copyright Manolache Maria-Catalina 313CAb 2023-2024
#include <stdio.h>
#include <stdlib.h>

#define MODULO 10007
#define DIE(assertion, call_description) \
    do { \
        if (assertion) { \
            fprintf(stderr, "(%s, %d): ", \
                    __FILE__, __LINE__); \
            perror(call_description); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

void allocate(int *m, int *n, int ***aux)
{
	*aux = calloc((*m), sizeof(int *));
	
	// daca esueaza alocarea, opresc executia
	DIE(!(*aux), "calloc failed");

	for (int i = 0; i < (*m); i++) {
		(*aux)[i] = calloc((*n), sizeof(int));
		if (!(*aux)[i]) {
			// daca una din alocari a esuat, eliberez tot ce am alocat
			for (int j = 0; j < i; j++)
				free((*aux)[j]);

			free(*aux);
			DIE(1, "calloc failed");
		}
	}
}

void free_mat(int ***a, int *size)
{
	// eliberare pentru fiecare rand al matricei
	for (int i = 0; i < *size; i++)
		free((*a)[i]);
	// eliberare pentru toata matricea
	free(*a);
}

void swap(int *a, int *b)
{
	// swap pentru numere
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void swap_mat(int ***a, int ***b)
{
	// swap pentru matrice
	int **aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

int sum(int **a, int *m, int *n)
{
	// calculeaza suma elem unei matrice modulo 10007
	int s = 0;
	for (int i = 0; i < *m; i++)
		for (int j = 0; j < *n; j++)
			s = (s + a[i][j]) % MODULO;
	if (s < 0)
		s += MODULO;
	return s;
}

int **mul(int **a, int **b, int size1, int size2, int size3)
{
	// inmultirea a doua matrici, cu rezultatul alocat si
	// returnat de functie mod 100007
	int **rez;
	// prima matrice are dim size1, size3
	// a doua matrice are dim size3, size2
	allocate(&size1, &size2, &rez);

	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			rez[i][j] = 0;
			for (int k = 0; k < size3; k++) {
				rez[i][j] = (rez[i][j] + a[i][k] * b[k][j]) % MODULO;
				if (rez[i][j] < 0)
					rez[i][j] += MODULO;
			}
		}
	}
	return rez;
}

int **mat_in(int *size)
{
	// creaaza matricea In (unitate)
	int **mat;
	allocate(size, size, &mat);

	for (int i = 0; i < *size; i++) {
		for (int j = 0; j < *size; j++) {
			if (i == j)
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
		}
	}
	return mat;
}

int **power(int **mat, int pow, int *v_m, int *index)
{
	// ridicarea la o putere in timp logaritmic
	int size = v_m[*index];
	// initiez rezultatul cu In in caz ca puterea este egala cu 0
	int **result = mat_in(&size);
	int **aux;

	while (pow > 0) {
		if (pow % 2 == 1) {
			aux = mul(result, mat, size, size, size);
			free_mat(&result, &size);
			result = aux;
			pow--;
		}
			aux = mul(mat, mat, size, size, size);
			free_mat(&mat, &size);
			mat = aux;
			pow /= 2;
	}

	free_mat(&mat, &size);
	// rezultatul este calc modulo 100007
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			result[i][j] = result[i][j] % MODULO;
				if (result[i][j] < 0)
					result[i][j] += MODULO;
	}
	return result;
}

void load(int ****matrix, int *indexmat, int *dim, int **v_m, int **v_n)
{
	// incarcarea in memorie a unei matrici
	int m, n;
	scanf("%d %d", &m, &n);
	// verif daca vectorii trebuie realocati deoarece s-a depasit dimensiunea
	if (*indexmat + 1 >= *dim) {
		*dim *= 2;
		*matrix = realloc(*matrix, *dim * sizeof(int **));
		*v_m = realloc(*v_m, *dim * sizeof(int *));
		*v_n = realloc(*v_n, *dim * sizeof(int *));

		// daca realocarea vreunuia esueaza, opresc executia
		if (!(*matrix) || !(*v_m) || !(*v_n)) {
			free(*matrix);
			free(*v_m);
			free(*v_n);
			(*matrix) = NULL;
			(*v_m) = NULL;
			(*v_n) = NULL;
			DIE(1, "realloc failed");
		}
	}

	// adaug matricea alocata, citesc matricea noua
	int **rez;
	allocate(&m, &n, &rez);
	(*matrix)[*indexmat] = rez;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			scanf("%d", &(*matrix)[*indexmat][i][j]);
	}
	// adaug indicii in vectorul de indici
	(*v_m)[*indexmat] = m;
	(*v_n)[*indexmat] = n;
}

void print(int **v_m, int **v_n, int ****matrix, int *indexmat)
{
	int index;
	scanf("%d", &index);

	// verificarea daca indexul este valid
	if (index < 0 || index > *indexmat || !(*matrix)[index]) {
		printf("No matrix with the given index\n");
		return;
	}

	// afisare pentru un element al vectorului de matrici
	for (int i = 0; i < (*v_m)[index]; i++) {
		for (int j = 0; j < (*v_n)[index]; j++)
			printf("%d ", (*matrix)[index][i][j]);
		printf("\n");
	}
}

void transposition(int ****matrix, int **v_m, int **v_n, int *indexmat)
{
	// transpunerea in place a unei matrici
	int index;
	scanf("%d", &index);

	// verificarea daca indexul este valid
	if (index < 0 || index > *indexmat || !(*matrix)[index]) {
		printf("No matrix with the given index\n");
		return;
	}

	// aloc memorie pt auxiliarul transpusa in care calculez transpusa
	int **trans;
	allocate(&(*v_n)[index], &(*v_m)[index], &trans);

	for (int i = 0; i < (*v_n)[index]; i++) {
		for (int j = 0; j < (*v_m)[index]; j++)
			trans[i][j] = (*matrix)[index][j][i];
	}

	// eliberez vechea matrice si pun transpusa in locul ei
	free_mat(&(*matrix)[index], &(*v_m)[index]);
	(*matrix)[index] = trans;

	// dimensiunile transpusei sunt dimensiunile matricei vechi inversate
	swap(&(*v_m)[index], &(*v_n)[index]);
}

void sort(int ****matrix, int *indexmat, int **v_m, int **v_n)
{
	// sortarea matricelor in functie de suma elementelor lor
	for (int i = 0; i < *(indexmat); ++i) {
		for (int j = 0; j < *(indexmat) - i; ++j) {
			//calculez suma pt orice 2 matrice
			int s1 = sum((*matrix)[j], &((*v_m)[j]), &((*v_n)[j]));
			int s2 = sum((*matrix)[j + 1], &((*v_m)[j + 1]), &((*v_n)[j + 1]));
			if (s1 > s2) {
				//daca ordinea este gresita, apelez swap pentru matrice si
				// pentru vectorul de dimensiuni
				swap_mat(&((*matrix)[j]), &((*matrix)[j + 1]));
				swap(&((*v_m)[j]), &((*v_m)[j + 1]));
				swap(&((*v_n)[j]), &((*v_n)[j + 1]));
			}
		}
		}
}

void multiply(int **v_m, int **v_n, int ****matrix, int *indexmat, int *dim)
{
	// realizeaza operatia de inmultire a doua matrice in place

	// citesc indexul pentru prima si a doua matrice
	int m1, m2;
	scanf("%d %d", &m1, &m2);

	// verificarea daca indecsii sunt valizi, in caz contrar opresc executia
	if (m1 < 0 || m1 > *indexmat || m2 < 0 || m2 > *indexmat) {
		printf("No matrix with the given index\n");
		return;
	}

	// daca dimensiunile sunt incompatibile, opresc executia
	if ((*v_n)[m1] != (*v_m)[m2]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}

	// cresc indexul vectorului de matrici, abordez cazul de realocare
	// cand se depaseste dimensiunea maxima a acestuia
	(*indexmat)++;
	if (*indexmat + 1 >= *dim) {
		*dim *= 2;
		*matrix = realloc(*matrix, *dim * sizeof(int **));
		DIE(!(*matrix), "realloc failed");
	
		*v_m = realloc(*v_m, *dim * sizeof(int *));
		DIE(!(*v_m), "realloc failed");

		*v_n = realloc(*v_n, *dim * sizeof(int *));
		DIE(!(*v_n), "realloc failed");
	}

	// rezultatul inmultirii matricelor este pus in locul vechii matrici
	// si vectorii de dimensiuni sunt actualizati
	int **rez;
	rez = mul((*matrix)[m1], (*matrix)[m2],
			  (*v_m)[m1], (*v_n)[m2], (*v_n)[m1]);
	(*v_m)[*indexmat] = (*v_m)[m1];
	(*v_n)[*indexmat] = (*v_n)[m2];
	(*matrix)[*indexmat] = rez;
}

void resize(int ****matrix, int *indexmat, int **v_m, int **v_n, int *index)
{
	// realizeaza redimensionarea matricei in place

	// se citeste indexul mat de redimensionat	
	scanf("%d", index);

	// nl = numarul de linii dupa care se face redimensionarea
	// v_l = vectorul ce contine indici pentru linii
	int nl, *v_l = NULL;

	// se citeste nl si se aloca spatiu pt v_l
	scanf("%d", &nl);
	v_l = calloc(nl, sizeof(int));
	DIE(!v_l, "calloc failed");
	for (int i = 0; i < nl; i++)
		scanf("%d", &v_l[i]);

	// nc = numarul de coloane dupa care se face redimensionarea
	// v_c = vectorul ce contine indici pentru coloane
	int nc, *v_c = NULL;

	// se citeste nc si se aloca spatiu pt v_c
	scanf("%d", &nc);
	v_c = calloc(nc, sizeof(int));
	DIE(!v_c, "calloc failed");
	for (int i = 0; i < nc; i++)
		scanf("%d", &v_c[i]);

	// verificarea daca indexul e valid, in caz contrar opresc executia
	if (*index < 0 || *index > *indexmat  || (*matrix)[*index] == NULL) {
		printf("No matrix with the given index\n");
		free(v_l);
		free(v_c);
		return;
	}
	int **aux;
	allocate(&nl, &nc, &aux);

	// obtinerea matricii redimensionate
	for (int i = 0; i < nl; i++) {
		for (int j = 0; j < nc; j++)
			aux[i][j] = (*matrix)[*index][(v_l)[i]][(v_c)[j]];
	}

	// eliberarea vechii matrici si inlocuirea cu cea redimensionata
	free_mat(&(*matrix)[*index], &(*v_m)[*index]);
	(*matrix)[*index] = aux;

	// vectorii dimensiunilor sunt actualizati
	(*v_m)[*index] = nl;
	(*v_n)[*index] = nc;

	// eliberam vectorii cu linii si coloane alocati dinamic
	free(v_l);
	free(v_c);
}

void F(int ****matrix, int *indexmat, int **v_m, int **v_n)
{
	int index;
	scanf("%d", &index);

	// verificarea daca indexul este valid
	if (index < 0 || index > *indexmat || (*matrix)[index] == NULL) {
		printf("No matrix with the given index\n");
		return;
	}
	
	// eliberarea din memorie a matricii de la index-ul citit
	free_mat(&(*matrix)[index], &(*v_m)[index]);

	// deplasam fiecare element al vect. de matrici si dimensiuni spre stanga
	for (int i = index; i < *indexmat; i++) {
		(*matrix)[i] = (*matrix)[i + 1];
		(*v_m)[i] = (*v_m)[i + 1];
		(*v_n)[i] = (*v_n)[i + 1];
	}
	
	// ultima matrice este inlaturata, iar pozitia curenta din vect de dim = 0
	(*matrix)[*indexmat] = NULL;
	(*v_m)[*indexmat] = 0;
	(*v_n)[*indexmat] = 0;
	
	// scade dimensiunea vectorului de matrici
	(*indexmat)--;
}

int main(void)
{
	int ***matrix = NULL, *v_m = NULL, *v_n = NULL;
	int index, indexmat = -1, dim = 1, pow;
	char c;
	
	// alocarea pt un vect de matrici, daca esueaza se elibereaza memoria
	matrix = calloc(1, sizeof(int ***));
	DIE(!matrix, "calloc failed");

	scanf(" %c", &c);
	while (c != 'Q') {
		switch (c) {
		case 'L':
			// incarcarea in memorie a unei matrici
			indexmat++;
			load(&matrix, &indexmat, &dim, &v_m, &v_n);
			break;
		case 'D':
			// tiparirea dimensiunilor unei matrici
			scanf("%d", &index);
			// verificarea daca indexul este valid
			if (index < 0 || index > indexmat || !matrix[index])
				printf("No matrix with the given index\n");
			else
				printf("%d %d\n", v_m[index], v_n[index]);
			break;
		case 'P':
			// tiparirea unei matrici
			print(&v_m, &v_n, &matrix, &indexmat);
			break;
		case 'T':
			// transpunerea unei matrici
			transposition(&matrix, &v_m, &v_n, &indexmat);
			break;
		case 'O':
			// sortarea vectorului de matrici dupa suma elementelor lor
			sort(&matrix, &indexmat, &v_m, &v_n);
			break;
		case 'M':
			// inmultirea a doua matrici
			multiply(&v_m, &v_n, &matrix, &indexmat, &dim);
			break;
		case 'F':
			// eliberarea memoriei unei matrici
			F(&matrix, &indexmat, &v_m, &v_n);
			break;
		case 'C':
			// redimensionarea unei matrici
			resize(&matrix, &indexmat, &v_m, &v_n, &index);
			break;
		case 'R':
			// ridicarea la putere a unei matrici
			scanf("%d %d", &index, &pow);

			// verificarea daca indexul este valid
			if (index < 0 || index > indexmat || !matrix[index]) {
				printf("No matrix with the given index\n");
			} else if (pow < 0) {
				printf("Power should be positive\n");
			// verificarea daca dimensiunile sunt compatibile
			} else if (v_m[index] != v_n[index]) {
				printf("Cannot perform matrix multiplication\n");
			} else {
			// matricea este ridicata la putere si adaugata in locul mat. vechi
				int **product;
				product = power(matrix[index], pow, v_m, &index);
				matrix[index] = product;
			}
			break;
		default:
			// comanda invalida
			printf("Unrecognized command\n");
			break;
		}
		scanf("\n");
		scanf("%c", &c);
	}

	// eliberarea tuturor resurselor: comanda Q
	for (int k = 0; k <= indexmat; k++) {
		if (matrix[k])
			free_mat(&(matrix)[k], &(v_m)[k]);
	}

	free(v_m);
	free(v_n);
	free(matrix);
	return 0;
}

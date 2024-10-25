#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define countof(_arr) (sizeof(_arr)/sizeof(*_arr))

int binary_search_helper(int array[], int bottom, int top, int key) {
	if (bottom > top) {
		return -1;
	}

	int mid = (bottom + top) / 2;
	if (array[mid] < key) {
		return binary_search_helper(array, mid + 1, top, key);
	}
	if (array[mid] > key) {
		return binary_search_helper(array, bottom, mid - 1, key);
	}

	return mid;
}

int binary_search(int array[], int length, int key) {
	return binary_search_helper(array, 0, length - 1, key);
}

// NOTA: Questa funzione e'cosi'complicata perche'non solo il vettore puo'essere vuoto (scanf ignora le righe vuote), ma
// anche vi e'qualche volta la combinazione in input dei caratteri ' ', '\n' uno di seguito all'altro. Questa sequenza
// di valori nel particolare fa in modo che la input sia difficilmente traducibile utilizzando solo funzioni quali
// scanf, getc, ... Si e'quindi optato per leggere l'intera riga in un buffer e lavorarci direttamente.
void parse_inputs(int array[], int array_capacity, int* array_length, int* key) {
	*array_length = 0;

#if INLINE_INPUT
	char first_char = getchar();
	if (first_char != '\n') {
		ungetc(first_char, stdin);

		char c1, c2;
		do {
			scanf("%d%c%c", &array[*array_length], &c1, &c2);
			*array_length += 1;

			if (c2 != '\n') {
				ungetc(c2, stdin);
			}
		} while(c1 != '\n' && c2 != '\n' && array_capacity < *array_length);
	}

	scanf("%d", key);

#else
	char* line = NULL;
	size_t line_cap = 0;
	ssize_t line_length = getline(&line, &line_cap, stdin);

	*array_length = 0;
	scanf("%d", key);

	const char* subline = line;
	while ((isdigit(subline[0]) || subline[0] == '-') && *array_length < array_capacity) {
		int characters_read;

		sscanf(subline, "%d%n", &array[*array_length], &characters_read);
		(*array_length)++;

		subline += characters_read + 1;
	}
	
	free(line);

#endif
}

int main() {
	int array[4096];
	int array_length;
	int key;

	parse_inputs(array, countof(array), &array_length, &key);
	int result = binary_search(array, array_length, key);

	printf("%d\n", result);

	return 0;
}

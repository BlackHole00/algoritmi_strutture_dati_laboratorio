#include <stdio.h>
#include <stdlib.h>

#define countof(_arr) (sizeof(_arr)/sizeof(*_arr))

typedef struct Range {
	int start;
	int end;
} Range;

#define SOLUTION_O_N_PLUS_M
// Expected sum to be of length >= ranges_length
void interval_sum(int array[], int array_length, Range ranges[], int ranges_length, int sums[]) {
	if (array_length <= 0 || ranges_length <= 0) {
		return;
	}

#if defined(SOLUTION_O_NM)
	for (int i = 0; i < ranges_length; i++) {
		const Range* range = &ranges[i];

		sums[i] = 0;
		for (int j = range->start; j <= range->end; j++) {
			sums[i] += array[j];
		}
	}

#elif defined(SOLUTION_O_N_PLUS_M)
	int* partial_sums = malloc((array_length + 1) * sizeof(int));

	partial_sums[0] = 0;
	for (int i = 0; i < array_length; i++) {
		partial_sums[i + 1] = partial_sums[i] + array[i];
	}

	for (int i = 0; i < ranges_length; i++) {
		const Range* range = &ranges[i];
		
		sums[i] = partial_sums[range->end + 1] - partial_sums[range->start];
	}

	free(partial_sums);
#endif
}

void parse_inputs(
	int array[],
	int array_capacity,
	int* array_length,
	Range ranges[],
	int ranges_capacity,
	int* ranges_length
) {
	*array_length = 0;
	*ranges_length = 0;

	char* numbers_line = NULL;
	size_t numbers_line_capacity;
	getline(&numbers_line, &numbers_line_capacity, stdin);

	const char* string = numbers_line;
	while (*array_length < array_capacity && string[0] != '\n' && string[0] != '\0') {
		int characters_read;
		sscanf(string, "%d%n", &array[*array_length], &characters_read);

		*array_length += 1;
		string += characters_read + 1;
	}

	char* ranges_line = NULL;
	size_t ranges_line_capacity;
	getline(&ranges_line, &ranges_line_capacity, stdin);

	string = ranges_line;
	while (*ranges_length < ranges_capacity && string[0] != '\n' && string[0] != '\0') {
		int characters_read;
		sscanf(string, "%d%d%n", &ranges[*ranges_length].start, &ranges[*ranges_length].end, &characters_read);

		*ranges_length += 1;
		string += characters_read + 1;
	}

	free(numbers_line);
	free(ranges_line);
}

int main() {
	int array[4096];
	int array_length;

	int sums[1024];
	Range ranges[1024];
	int ranges_length;

	parse_inputs(
		array,
		countof(array),
		&array_length,
		ranges,
		countof(array),
		&ranges_length
	);
	interval_sum(array, array_length, ranges, ranges_length, sums);

	for (int i = 0; i < ranges_length; i++) {
		printf("%d ", sums[i]);
	}
	printf("\n");

	return 0;
}

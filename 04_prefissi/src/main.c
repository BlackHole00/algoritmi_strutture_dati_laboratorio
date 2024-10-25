#include <stdio.h>
#include <string.h>

#define countof(_arr) (sizeof(_arr)/sizeof(*_arr))

int main() {
	char string[256];

	scanf("%255[^\n]", string);

	int i = strnlen(string, countof(string));
	while (i >= 0) {
		printf("%s\n", string);

		string[i] = '\0';
		i--;
	}

	return 0;
}

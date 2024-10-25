#include <stdio.h>
#include <string.h>

#define countof(_arr) (sizeof(_arr)/sizeof(*_arr))

int main() {
	char string[256];

	scanf("%255[^\n]", string);

	int string_length = strlen(string);
	for (int i = 0; i < string_length / 2; i++) {
		char tmp = string[i];
		string[i] = string[string_length - i - 1];
		string[string_length - i - 1] = tmp;
	}

	printf("%s\n", string);

	return 0;
}

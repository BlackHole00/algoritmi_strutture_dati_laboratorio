#include <stdio.h>

int main() {
	char buffer[256] = {};
	scanf("%255[^\n]", buffer);

	const char* string = buffer;
	while (*string != '\0') {
		printf("%s\n", string);
		string++;
	}

	return 0;
}

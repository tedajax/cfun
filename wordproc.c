#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long load_file(const char *filename, char *buffer, long maxLength) {
	if (!buffer || maxLength == 0) {
		return -1;
	}

	FILE *file = fopen(filename, "r");
	long length;

	if (!file) {
		return -1;
	}

	if (fseek(file, 0L, SEEK_END) == 0) {
		long filesize = ftell(file);
		
		if (filesize == -1 || filesize > maxLength + 1) {
			fclose(file);
			fprintf(stderr, "Insufficient buffer size for reading file %s\n", filename);
			fprintf(stderr, "Requires %lu but max is %lu\n", filesize, maxLength);
			return -1;
		}

		if (fseek(file, 0L, SEEK_SET) != 0) {
			fclose(file);
			return -1;
		}

		length = fread(buffer, sizeof(char), filesize, file);

		if (length == 0) {
			fprintf(stderr, "Error reading file %s\n", filename);
		} else {
			buffer[++length] = '\0';
		}
	}

	fclose(file);

	printf("Loaded file %s with %zu characters\n", filename, length);

	return length;
}

int main(int argc, char *argv[]) {
	long maxLength = 10000000;
	char *buffer = (char *)calloc(maxLength, sizeof(char));

	long length = load_file("wordsEn.txt", buffer, maxLength);

	free(buffer);

	return 0;
}

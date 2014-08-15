#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct word_table {
	char **words;
	int count;
} word_table_t;

long load_file(const char *filename, char *buffer, long maxLength);
bool generate_word_table(word_table_t *destination, char *buffer, long length);

int main(int argc, char *argv[]) {
	long maxLength = 10000000;
	char *buffer = (char *)calloc(maxLength, sizeof(char));

	long length = load_file("wordsEn.txt", buffer, maxLength);

	free(buffer);

	return 0;
}

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

bool generate_word_table(word_table_t *destination, char *buffer) {
	int wordCount = 0;
	long c = 0;
	size_t length = strlen(buffer);
	int currentWord = 0;
	char *token;

	for (c = 0; c < length; ++c) {
		if (buffer[c] == '\0') {
			++wordCount;
		}
	}

	destination->words = (char **)calloc(word_count, sizeof(char *));

	token = strtok(buffer, "\n");
	while (token != NULL) {
		size_t len = strlen(token) + 1;
		destination->words[currentWord] = (char *)calloc(len, sizeof(char));
		destination->words[curren
}

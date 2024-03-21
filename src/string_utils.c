#include <string_utils.h>

int8_t string_utils_is_end_char(char c) {
	if (c == '\0' || c== '\n') {
		return 1;
	}
	return 0;
}

// return how many words
size_t string_utils_split(char *str, char split, char **buffer) {
	size_t word_count = 0;

	size_t idx = 0;
	char c = str[0];
	while (!string_utils_is_end_char(c)) {
		buffer[word_count][idx] = c;

		idx++;
		c = str[idx];

		if (c == split) {
			buffer[word_count][idx] = '\0';

			word_count++;
			idx = 0;
		}
	}

	return word_count;
}
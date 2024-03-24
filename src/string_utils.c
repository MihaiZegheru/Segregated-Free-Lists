#include <string_utils.h>
#include <stdio.h>

int8_t string_utils_is_end_char(char c) {
	if (c == '\0' || c == '\n') {
		return 1;
	}
	return 0;
}

// return how many words
size_t string_utils_split(char *str, char split, char buffer[][MAX_LINE_SIZE]) {
	size_t word_count = 0;

	size_t str_idx = 0;
	size_t word_idx = 0;
	while (!string_utils_is_end_char(str[str_idx])) {
		buffer[word_count][word_idx] = str[str_idx];

		str_idx++;
		word_idx++;

		if (str[str_idx] == split) {
			buffer[word_count][word_idx] = '\0';
			str_idx++;
			word_count++;
			word_idx = 0;
		}
		else if (string_utils_is_end_char(str[str_idx])) {
			buffer[word_count][word_idx] = '\0';
			word_count++;
		}
	}

	return word_count;
}

size_t string_utils_addr_to_uint(char *addr) {
	if (addr[0] != '0' || addr[1] != 'x') {
		// this is an error
		return -1;
	}

	addr += 2;

	int64_t num = 0;
	while (*addr) {
		uint8_t byte = *addr;
		addr++;

		if (byte >= '0' && byte <= '9') {
			byte -= '0';
		}
		else if (byte >= 'a' && byte <= 'f') {
			byte -= 'a';
			byte += 10;
		}
		else if (byte >= 'A' && byte <= 'F') {
			byte -= 'A';
			byte += 10;
		}

		num = (num << 4) | (byte & 0xF);
	}

	return num;
}

size_t string_utils_str_to_uint(char *str) {
	size_t num = 0;

	size_t idx = 0;
	while (!string_utils_is_end_char(str[idx])) {
		num *= 10;
		num += str[idx] - '0';
		idx++;
	}

	return num;
}

int64_t string_utils_str_to_int(char *str) {
	int64_t num = 0;

	size_t idx = 0;
	while (!string_utils_is_end_char(str[idx])) {
		num *= 10;
		num += str[idx] - '0';
		idx++;
	}

	return num;
}
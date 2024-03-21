#include <input_handler.h>

// return word count
size_t input_handler_read_command_line(char **buffer) {
	char str[MAX_LINE_SIZE + 1];
	scanf("%[^\n]%c", buffer, &str[MAX_LINE_SIZE]);

	return string_utils_split(str, ' ', buffer);
}

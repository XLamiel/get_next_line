#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void test_file(const char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("\033[1;31mError opening file: %s\033[0m\n", filename);
		return;
	}

	printf("\n\033[1;34mTesting file: %s\033[0m\n", filename);
	printf("========================================\n");

	char *line;
	int line_count = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line %d: %s", line_count++, line);
		free(line);
	}

	close(fd);
	printf("========================================\n");
	printf("\033[1;32mEnd of file: %s\033[0m\n", filename);
}

void test_stdin()
{
	printf("\n\033[1;34mTesting STDIN (type your input, press Ctrl+D to end)\033[0m\n");
	printf("========================================\n");

	char *line;
	int line_count = 1;
	while ((line = get_next_line(STDIN_FILENO)) != NULL)
	{
		printf("Line %d: %s", line_count++, line);
		free(line);
	}

	printf("========================================\n");
	printf("\033[1;32mEnd of STDIN test\033[0m\n");
}

int main(void)
{
	// Test with various files
	test_file("texto1.txt");
	test_file("texto2.txt");
	test_file("texto3.txt");

	// Test with STDIN
	test_stdin();

	return 0;
}

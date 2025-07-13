#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd1, fd2, fd3;
	char	*line1, *line2, *line3;
	int		i;

	fd1 = open("texto1.txt", O_RDONLY);
	fd2 = open("texto2.txt", O_RDONLY);
	fd3 = open("texto3.txt", O_RDONLY);

	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
	{
		perror("Error al abrir uno de los archivos");
		return (1);
	}

	i = 1;
	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);

		if (!line1 && !line2 && !line3)
			break;

		printf("Iteración %d:\n", i);
		if (line1)
		{
			printf("texto1.txt: %s", line1);
			free(line1);
		}
		else
			printf("texto1.txt: [NULL]\n");

		if (line2)
		{
			printf("texto2.txt: %s", line2);
			free(line2);
		}
		else
			printf("texto2.txt: [NULL]\n");

		if (line3)
		{
			printf("texto3.txt: %s", line3);
			free(line3);
		}
		else
			printf("texto3.txt: [NULL]\n");

		printf("-----------\n");
		i++;
	}

	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlamiel- <xlamiel-@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:08:05 by xlamiel-          #+#    #+#             */
/*   Updated: 2025/06/22 18:43:00 by xlamiel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h> // Para open
#include <stdio.h> // Para perror y printf

// Si storage es 0x01001, el contigut pot ser o no, un punter del heap on malloc
//		ha trobat n bytes consecutius lliures per asignar, per ejemple 0x02001
// Per storage =(char *)malloc(6), retorna el primer punter del primer byte de 6 bytes
//		consecutius: 0x02001 de 0x02001, 0x02002, 0x02003, 0x02004, 0x02005 i  0x02006
// Es fa aixi perque quan es pasa un parametre a una funcio sempre es una copia,
//		i aixi es pasa les referencies de les dades originals, i ens asegurem de que
//		siguin afectades
// La part del free funcionaria pero la part de que apuntes a NULL no funcionaria
//		Evitant el "Dangling pointer"

char	*ft_free_and_null(char **prt) // Reb el punter d'un punter (ejm 0x01000 que conte 0x02000)
{
	if (*prt) // ejem. 0x02001
	{
		free(*prt); // Allibera 0x02001 (0x02002, 0x02003, 0x02004, 0x02005 i  0x02006)
		*prt = NULL; // I ara le diu que 0x01001 (l'original i no pas una copia) apunti a NULL
	}
	return (NULL); // Finalment retorna NULL
}

// Extrae una línea de 'storage' (hasta '\n' o EOF) y actualiza 'storage'
char	*ft_extract_line(char **storage)
{
	char	*line;
	char	*newline_pos;
	char	*temp_storage;

	if (!*storage) // Si storage está vacío, retornar NULL
		return (NULL);
	newline_pos = ft_strchr(*storage, '\n');
	if (newline_pos)  // Si hay un salto de línea
	{
		line = ft_substr(*storage, 0, newline_pos - *storage + 1);
		if (!line)
			return (ft_free_and_null(storage)); // Fallo en malloc
		temp_storage = ft_strdup(newline_pos + 1);
		ft_free_and_null(storage); // Liberar el storage antiguo
		*storage = temp_storage; // Asignar el nuevo storage (resto de la línea)
		return (line);
	}
	line = ft_strdup(*storage); // Si no hay salto de línea, retornar todo el storage
	ft_free_and_null(storage); // Liberar storage (ya no hay más datos)
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*buffer;
	char		*temp_storage;
	int		 bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free_and_null(&storage)); // Sortida - Fallo a malloc
	bytes_read = 1;
	while (!ft_strchr(storage, '\n') && bytes_read > 0) // Mentre no s'hagi trobat un '\n' en storage (NULL) i l'últim read() hagi llegit almenys un byte...
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE); // Llegeix i emplena el buffer
		if (bytes_read == -1) // Error a read
			return (ft_free_and_null(&buffer)); // Sortida - Alliberar buffer i retornar NULL
		buffer[bytes_read] = '\0'; // Asegura que despres de l'ultim byte llegit hi hagi '\0'
		if (!storage)
			temp_storage = ft_strjoin("", buffer);
		else
			temp_storage = ft_strjoin(storage, buffer);
		if (!temp_storage) // Fallo en malloc (ft_strjoin)
		{
			ft_free_and_null(&buffer);
			return (ft_free_and_null(&storage)); // Liberar todo y retornar NULL
		}
		ft_free_and_null(&storage); // Liberar el storage antiguo
		storage = temp_storage;	 // Asignar el nuevo storage
	}
	ft_free_and_null(&buffer); // Buffer ya no se necesita
	if (!storage || !*storage) // Si no hay datos, retornar NULL
		return (ft_free_and_null(&storage));
	return (ft_extract_line(&storage)); // Extraer y retornar la línea
}

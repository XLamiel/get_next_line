/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlamiel- <xlamiel-@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:26:50 by xlamiel-          #+#    #+#             */
/*   Updated: 2025/06/22 22:18:29 by xlamiel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# include <stdio.h>

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42 // Tamaño por defecto
# endif

// Prototipos de funciones auxiliares (en utils.c)
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

// Prototipos de get_next_line.c
int		ft_loop_until_newline(int fd, char **storage, char *buffer);
int		ft_append_read_buffer(char **storage, const char *buffer);
char	*ft_free_and_null(char **ptr);
char	*ft_extract_line(char **storage);
char	*get_next_line(int fd);
#endif

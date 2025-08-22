/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:20:58 by slimane           #+#    #+#             */
/*   Updated: 2025/08/17 16:38:16 by bbenaali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char	*ft_before(char *str)
{
	int		i;
	char	*tmp;
	int		x;

	x = 1;
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		x = 2;
	tmp = (char *)malloc(sizeof(char) * (i + x));
	if (!tmp)
		return (free(str), NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		tmp[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		tmp[i++] = '\n';
	tmp[i] = '\0';
	return (tmp);
}

static char	*after(char *sttr)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (sttr[i] && sttr[i] != '\n')
		i++;
	j = ft_strlen(sttr);
	s = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!s)
		return (free(sttr), NULL);
	if (sttr[i] == '\n')
		i++;
	j = 0;
	while (sttr[i] != '\0')
	{
		s[j] = sttr[i];
		j++;
		i++;
	}
	s[j] = '\0';
	free(sttr);
	return (s);
}

static char	*ft_read(int fd, char *x)
{
	ssize_t		a;
	char		*buffer;
	char		*temp;

	buffer = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (free(x), NULL);
	while (1)
	{
		a = read(fd, buffer, BUFFER_SIZE);
		if (a < 0)
			return (free(buffer), free(x), NULL);
		buffer[a] = '\0';
		temp = x;
		x = ft_strjoin(temp, buffer);
		free (temp);
		if (!x || a == 0 || find_new_line(buffer))
		{
			if(!x)
				free(x);
			break ;
		}
	}
	free (buffer);
	return (x);
}

char	*get_next_line(int fd)
{
	static char	*x;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX || fd > OPEN_MAX)
		return (NULL);
	x = ft_read(fd, x);
	if (!x)
		return (x = NULL, NULL);
	if (!*x)
		return (free(x), x = NULL, NULL);
	line = ft_before(x);
	if (!line)
		return (x = NULL, NULL);
	x = after(x);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epeters- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:25:41 by epeters-          #+#    #+#             */
/*   Updated: 2022/07/08 18:27:05 by epeters-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*append_prev_read(const char *buffer, char *prev_read)
{
	int		prev_read_len;
	char	*temp;

	if (!prev_read)
		prev_read = ft_strdup(buffer);
	else
	{
		prev_read_len = ft_strlen(prev_read);
		temp = (char *)(malloc(sizeof(*temp) * (prev_read_len + 1)));
		if (temp)
		{
			ft_strlcpy(temp, prev_read, ft_strlen(prev_read) + 1);
			free(prev_read);
				prev_read = ft_strjoin(temp, buffer);
			free(temp);
		}
		else
		{
			free(prev_read);
			prev_read = NULL;
		}
	}
	return (prev_read);
}

static char	*find_next_line(char **prev_read)
{
	int		len_to_nl;
	char	*line;
	char	*temp;

	len_to_nl = 0;
	line = NULL;
	while ((*prev_read)[len_to_nl] && (*prev_read)[len_to_nl] != '\n')
		len_to_nl++;
	if ((*prev_read)[len_to_nl] == '\n')
	{
		line = ft_substr(*prev_read, 0, len_to_nl + 1);
		if ((*prev_read)[len_to_nl + 1] != '\0')
		{
			temp = ft_strdup(*prev_read + len_to_nl + 1);
			free(*prev_read);
			*prev_read = ft_strdup(temp);
			free(temp);
		}
		else
		{
			free(*prev_read);
			*prev_read = NULL;
		}
	}
	return (line);
}

static int	read_buffer_size(int fd, char **prev_read)
{
	char	*buffer;
	int		read_return;

	if (fd < 0 || fd >= FD_SIZE || BUFFER_SIZE < 1)
		return (-1);
	buffer = (char *)(malloc(sizeof(*buffer) * (BUFFER_SIZE + 1)));
	if (!buffer)
	{
		if (*prev_read)
			free(*prev_read);
		return (-1);
	}
	read_return = read(fd, buffer, BUFFER_SIZE);
	if (read_return <= 0)
	{
		if (read_return < 0 && *prev_read)
			free(*prev_read);
		free(buffer);
		return (read_return);
	}
	buffer[read_return] = '\0';
	*prev_read = append_prev_read(buffer, *prev_read);
	free(buffer);
	return (read_return);
}

char	*get_next_line(int fd)
{
	static char	*prev_read[FD_SIZE];
	int			read_return;
	char		*line;

	line = NULL;
	if (fd >= 0 && fd < FD_SIZE && prev_read[fd])
		line = find_next_line(&prev_read[fd]);
	while (!line)
	{
		read_return = read_buffer_size(fd, &prev_read[fd]);
		if (read_return < 0)
			return (NULL);
		if (read_return == 0)
		{
			if (prev_read[fd])
			{
				line = ft_strdup(prev_read[fd]);
				free(prev_read[fd]);
				prev_read[fd] = NULL;
			}
			return (line);
		}
		line = find_next_line(&prev_read[fd]);
	}
	return (line);
}

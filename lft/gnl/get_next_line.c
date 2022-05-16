/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlehmann <hlehmann@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:27:18 by hlehmann          #+#    #+#             */
/*   Updated: 2022/05/16 11:27:19 by hlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_buffdel(char *dest, char *src, int n)
{
	int		pos;
	char	*temp_dest;
	char	*temp_src;

	pos = 0;
	temp_dest = (char *)dest;
	temp_src = (char *)src;
	while (pos < n && temp_src[pos])
	{
		temp_dest[pos] = temp_src[pos];
		pos ++;
	}
	temp_dest[pos] = '\0';
	return ;
}

static void	ft_buffjoin(char **line, char *s2)
{
	char	*join;
	int		count1;
	int		count2;

	count1 = 0;
	count2 = 0;
	join = ft_calloc(ft_strlen(*line) + ft_strlen(s2) + 1, sizeof(char));
	if (!join)
		return ;
	while (line[0][count1])
	{
		join[count1] = line[0][count1];
		count1 ++;
	}
	while (s2[count2] && s2[count2] != '\n')
	{
		join[count1] = s2[count2];
		count1 ++;
		count2 ++;
	}
	free(*line);
	*line = join;
	return ;
}

static void	ft_buffjoinend(char **line, char *s2, int y)
{
	char	*join;
	int		count1;
	int		count2;

	count1 = 0;
	count2 = 0;
	join = ft_calloc(ft_strlen(*line) + y + 1, sizeof(char));
	if (!join)
		return ;
	while (line[0][count1])
	{
		join[count1] = line[0][count1];
		count1 ++;
	}
	while (count2 < y)
	{
		join[count1] = s2[count2];
		count1 ++;
		count2 ++;
	}
	free(*line);
	*line = join;
	ft_bzero(s2, BUFFER_SIZE);
	return ;
}

/**
 * Write a function which returns a line read from a file descriptor, without
 * the newline.
 * @param fd [int] file discriptor to be read;
 * @param line [char **] line to be returned;
 * @return [int]
 *	[1] A line has been read;
 *	[0] EOF has been reached;
 *	[-1] An error happened;
*/
int	get_next_line(int fd, char **line)
{
	static char	buff[BUFFER_SIZE + 1];
	int			y;

	if (fd < 0 || fd >= 1000 || BUFFER_SIZE <= 0)
	{
		*line = NULL;
		return (-1);
	}
	*line = ft_calloc(sizeof(char), 1);
	while (ft_isnewchar(buff) == 0)
	{
		if (buff[0])
			ft_buffjoin(line, buff);
		y = read(fd, buff, BUFFER_SIZE);
		buff[y] = 0;
		if (!(y >= BUFFER_SIZE) && ft_isnewchar(buff) == 0)
		{
			ft_buffjoinend(line, buff, y);
			return (0);
		}
	}
	ft_buffjoin(line, buff);
	ft_buffdel(buff, ft_isnewchar(buff), BUFFER_SIZE);
	return (1);
}

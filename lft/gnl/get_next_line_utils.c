/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlehmann <hlehmann@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:27:41 by hlehmann          #+#    #+#             */
/*   Updated: 2022/05/16 11:27:42 by hlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Function ft_bzero fills pointer s with nulls till it has reached size n
*/

char	*ft_isnewchar(char *buff)
{
	unsigned int	pos;

	pos = 0;
	while (buff[pos])
	{
		if (buff[pos] == '\n')
			return (&((char *)buff)[pos + 1]);
		pos ++;
	}
	if (buff[pos] == '\n')
		return (&((char *)buff)[pos + 1]);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlehmann <hlehmann@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:22:42 by hlehmann          #+#    #+#             */
/*   Updated: 2022/05/16 11:22:43 by hlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*d;
	size_t			i;

	i = 0;
	d = (unsigned char *)s;
	while (n > i)
	{
		d[i] = c;
		i++;
	}
	return (s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_rep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlehmann <hlehmann@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:18:31 by hlehmann          #+#    #+#             */
/*   Updated: 2022/05/16 11:18:33 by hlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_char_rep(char *str, char target, char replacement)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == target)
			str[i] = replacement;
		i++;
	}
}

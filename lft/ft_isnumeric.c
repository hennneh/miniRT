/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlehmann <hlehmann@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:19:43 by hlehmann          #+#    #+#             */
/*   Updated: 2022/05/16 11:19:44 by hlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumeric(char *num)
{
	int	i;

	i = 0;
	while (num[i])
	{
		if ((!ft_isdigit(num[i]) && (i != 0)) || \
		(!ft_isdigit(num[i]) && num[i] != '+' && num[i] != '-' && i == 0))
			return (1);
		i++;
	}
	return (0);
}

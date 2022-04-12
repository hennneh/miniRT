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

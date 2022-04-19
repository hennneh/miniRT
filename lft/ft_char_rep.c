#include "libft.h"

void	ft_char_rep(char *str, char target, char replacement)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == target)
			str[i] = replacement;
		i++;
	}
}

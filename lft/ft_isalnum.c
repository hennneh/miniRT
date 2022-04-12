#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c > 47 && c < 58)
		|| (c > 64 && c < 91)
		|| (c > 96 && c < 123))
		return (1);
	else
		return (0);
}

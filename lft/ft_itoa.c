#include "libft.h"

static int	ft_digits(int n)
{
	int	digits;

	digits = 0;
	if (n <= 0)
		digits++;
	while (n)
	{
		digits++;
		n = n / 10;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	int		digits;
	char	*dest;
	long	nlong;

	digits = ft_digits(n);
	dest = malloc(sizeof(char) * digits + 1);
	nlong = n;
	if (!dest)
		return (NULL);
	if (nlong < 0)
	{
		dest[0] = '-';
		nlong *= -1;
	}
	if (n == 0)
		dest[0] = '0';
	dest[digits] = '\0';
	digits--;
	while (nlong)
	{
		dest[digits] = nlong % 10 + '0';
		digits--;
		nlong = nlong / 10;
	}
	return (dest);
}

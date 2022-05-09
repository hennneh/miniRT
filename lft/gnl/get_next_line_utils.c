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

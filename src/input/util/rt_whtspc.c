
#include "../../../inc/minirt.h"

/**
 * ft_white checks if 'c is a whitespace
 * @param c [char] char to be checked
 * @return [int] 1 if whitespace, 0 if not
*/
int	ft_white(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

/**
 * is_whspace iterates through a line till it does not find a whitespace
 * @param s [char *] string being interated
 * @param dir [int] direction of intteration, 1 front, -1 back
 * @return [int] first postion that is not whitespace
*/
int	is_whspace(char *s, int dir)
{
	int	i;

	i = 0;
	if (dir < 0)
		i = ft_strlen(s) - 1;
	while (s[i] && i >= 0 && ft_white(s[i]))
	{
		i += dir;
	}
	if (dir < 0)
		i ++;
	return (i);
}

/**
 * trim_whitespace trims whitesspaces
 * @param s [char *] string being interated
 * @param dir [int] direction of interation,
 * if dir = 1 from the front, if -1 then from the back, if 2 then from both
 * @return [char *] returns a string with whitespace trimed
*/
char	*trm_whtsp(char *s, int dir)
{
	int		pos1;
	int		pos2;

	if (!s)
		return (NULL);
	if (dir > 0)
	{
		pos1 = is_whspace(s, 1);
		if (dir == 2)
			dir = -1;
	}
	else
		pos1 = 0;
	if (dir == -1)
		pos2 = is_whspace(s, -1);
	else
		pos2 = ft_strlen(s);
	if (pos2 <= pos1)
		return ("");
	return (ft_substr(s, pos1, pos2 - pos1));
}

static	int	ft_strcount_wh(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (s[i])
	{
		if (ft_white(s[i]) && s[i + 1] && !ft_white(s[i + 1]))
			count ++;
		i++;
	}
	return (count);
}

/**
 * Allocates ft_calloc and returns an array of strings obtained by
 * splitting ’s’ using whitespace as a delimiter. The array must be
 * ended by a NULL pointer. Returns array of new strings resulting from the
 * split. NULL if the allocation fails.
 * @param s [char const *] char * to be split
 * @return [char **] split array
*/
char	**split_wh(char const *s)
{
	char	**array;
	int		count;
	int		pos1;
	int		pos2;

	if (!s)
		return (0);
	count = 0;
	pos1 = 0;
	pos2 = 0;
	array = ft_calloc((ft_strcount_wh(s) + 1), sizeof(char *));
	if (!array)
		return (0);
	while (s[pos2])
	{
		while (s[pos2] && ft_white(s[pos2]))
			pos2++;
		pos1 = pos2;
		while (s[pos2] && !ft_white(s[pos2]))
			pos2++;
		if (!ft_white(s[pos2 - 1]))
			array[count] = ft_substr(s, pos1, pos2 - pos1);
		count ++;
	}
	return (array);
}

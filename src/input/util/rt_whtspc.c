
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

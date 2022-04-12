#include "libft.h"

static int	ft_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		words++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (words);
}

static int	ft_length(char const *s, char c, int a)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] && s[i] == c)
		i++;
	while (a)
	{
		if (s[i] == c && s[i + 1] != c)
			a--;
		i++;
	}
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static char	*ft_copy(char const *s, char c, int a)
{
	char	*word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	word = (char *)ft_calloc(sizeof(char), ft_length(s, c, a) + 1);
	if (!word)
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	while (a)
	{
		if (s[i] == c && s[i + 1] != c)
			a--;
		i++;
	}
	while (s[i] && s[i] != c)
	{
		word[j] = s[i];
		j++;
		i++;
	}
	word[j] = 0;
	return (word);
}

static void	ft_free_dest(char **dest)
{
	int	i;

	i = 0;
	while (dest[i])
	{
		free(dest[i]);
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		words;
	int		i;

	if (!s)
		return (NULL);
	words = ft_words(s, c);
	dest = (char **)ft_calloc(sizeof(char *), (words + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < words)
	{
		dest[i] = ft_copy(s, c, i);
		if (!dest[i])
		{
			ft_free_dest(dest);
			free(dest);
			return (NULL);
		}
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

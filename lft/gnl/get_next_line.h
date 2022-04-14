
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

int		get_next_line(int fd, char **line);

/*Utilities*/
char	*ft_isnewchar(char *buff);
#endif
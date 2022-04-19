
#include "rt_input.h"

int	parse_input(t_mrt *mrt, t_list *lst, int count[6])
{
	
}

t_list	*import_data(char *file)
{
	int		i;
	t_list	*lst;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1 || ft_strnstr(file, ".rt", ft_strlen(file)) != &file[ft_strlen(file) - 3])
	{
		perror("Error\nNot a valid file");
		exit(close(fd));//EXIT HANDELING
	}
	i = 1;
	lst = NULL;
	while (i > 0)
	{
		i = get_next_line(fd, &line);
		if (ft_strlen(&line) > 0)
			ft_lstadd_back(&lst, ft_lstnew((void *)line));
	}
	close(fd);
	return (lst);
}

int	input(t_mrt *mrt, char *file)
{
	int		count[6];
	int		good;
	t_list	*lst;

	lst = import_data(file);
	if (!lst)
	{
		perror("Error\nEmpty file\n");
		ft_lstclear(&lst, free);
		exit(1);
	}
	ft_bzero(count, sizeof(int) * 6);
	if (!count_input(lst, &count, NULL) && !check_count(count))
		parse_input(mrt, lst, count);
	else
		exit(1);//ERROR
	
}

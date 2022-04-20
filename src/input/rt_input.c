
#include "../../inc/minirt.h"

void	init_mrt(t_mrt *mrt, int count[6])
{
	mrt->al = ft_calloc(sizeof(t_al), 1);
	mrt->l = ft_calloc(sizeof(t_lol), 1);
	mrt->cam = ft_calloc(sizeof(t_cam), 1);
	mrt->sp = ft_calloc(sizeof(t_sph *), count[3]);
	mrt->pl = ft_calloc(sizeof(t_pl *), count[4]);
	mrt->cy = ft_calloc(sizeof(t_cyl *), count[5]);
	return ;
}

int	parse_input(t_mrt *mrt, t_list *lst, int count[6])
{
	int	flag;
	int	i;
	int	x;
	int	y;

	flag = 0;
	i = 0;
	y = 0;
	x = 0;
	init_mrt(mrt, count);
	while (lst)
	{
		if (((char *)lst->content)[0] == 'A')
			flag = init_al(mrt->al, ft_split(lst->content, ' '));
		else if (((char *)lst->content)[0] == 'C')
			flag = init_cam(mrt->cam, ft_split(lst->content, ' '));
		else if (((char *)lst->content)[0] == 'L')
			flag = init_lol(mrt->l, ft_split(lst->content, ' '));
		else if (((char *)lst->content)[0] == 's')
			flag = init_sph(mrt->sp[i++], ft_split(lst->content, ' '));
		else if (((char *)lst->content)[0] == 'p')
			flag = init_pl(mrt->pl[x++], ft_split(lst->content, ' '));
		else if (((char *)lst->content)[0] == 'c')
			flag = init_cyl(mrt->cy[y++], ft_split(lst->content, ' '));
		if (flag == 1)
			return (1);
		lst = lst->next;
	}
	return (0);
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
		if (ft_strlen(line) > 0)
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
	if (!count_input(lst, count, NULL) && !check_count(count))
		good = parse_input(mrt, lst, count);
	else
		exit(1);//ERROR
	return (good);
}

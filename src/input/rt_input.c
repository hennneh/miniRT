
#include "../../inc/minirt.h"

void	init_mrt(t_mrt *mrt, int count)
{
	mrt->al = ft_calloc(sizeof(t_al), 1);
	mrt->l = ft_calloc(sizeof(t_lol), 1);
	mrt->cam = ft_calloc(sizeof(t_cam), 1);
	mrt->obj = ft_calloc(sizeof(t_obj *), count + 1);
	return ;
}

int	parse_input(t_mrt *mrt, t_list *lst, int count, int flag)
{
	char	**tmp;

	init_mrt(mrt, count);
	while (lst)
	{
		tmp = split_wh(lst->content);
		if (((char *)lst->content)[0] == 'A')
			flag = init_al(mrt->al, tmp);
		else if (((char *)lst->content)[0] == 'C')
			flag = init_cam(mrt->cam, tmp);
		else if (((char *)lst->content)[0] == 'L')
			flag = init_lol(mrt->l, tmp);
		else if (((char *)lst->content)[0] == 's')
			flag = init_sph(mrt->obj, tmp, --count);
		else if (((char *)lst->content)[0] == 'p')
			flag = init_pl(mrt->obj, tmp, --count);
		else if (((char *)lst->content)[0] == 'c')
			flag = init_cyl(mrt->obj, tmp, --count);
		free_2dstr(tmp);
		if (flag)
			return ((printf("[%d]{%s}\n", count, (char *)lst->content) * 0) + count + 1);//ERROR
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
	if (fd == -1 || ft_strnstr(file, ".rt", ft_strlen(file))
		!= &file[ft_strlen(file) - 3])
	{
		perror("Error\nNot a valid file");
		exit(close(fd));
	}
	i = 1;
	lst = NULL;
	while (i > 0)
	{
		i = get_next_line(fd, &line);
		if (ft_strlen(line) > 0 && (size_t)is_whspace(line, 1)
			< ft_strlen(line))
			ft_lstadd_back(&lst, ft_lstnew((void *)line));
		else
			free(line);
	}
	close(fd);
	return (lst);
}

int	input(t_mrt *mrt, char *file)
{
	int		count[4];
	int		good;
	t_list	*lst;

	lst = import_data(file);
	if (!lst)
	{
		perror("Error\nEmpty file\n");
		exit(1);
	}
	good = 0;
	ft_bzero(count, sizeof(int) * 4);
	if (!count_input(lst, count, NULL) && !check_count(count))
	{
		good = parse_input(mrt, lst, count[3], 0);
	}
	else
	{
		good = -1;
	}
	ft_lstclear(&lst, free);
	if (good > 0)
		rt_er_exit(mrt, good - 1, count[3]);
	return (good);
}

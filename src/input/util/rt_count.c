#include "../../../inc/minirt.h"

/**
 * @param count [int *[3]] [A][C][L][obj]
 * @param tmp [char *] always NULL;
*/
int	count_input(t_list *lst, int *count, char *tmp)
{
	while (lst)
	{
		tmp = trm_whtsp((char *)lst->content, 2);
		if (tmp[0] == 'A' && ft_white(tmp[1]))
			count[0]++;
		else if (tmp[0] == 'C' && ft_white(tmp[1]))
			count[1]++;
		else if (tmp[0] == 'L' && ft_white(tmp[1]))
			count[2]++;
		else if (!ft_strncmp(tmp, "sp", 2) && ft_white(tmp[2]))
			count[3]++;
		else if (!ft_strncmp(tmp, "pl", 2) && ft_white(tmp[2]))
			count[3]++;
		else if (!ft_strncmp(tmp, "cy", 2) && ft_white(tmp[2]))
			count[3]++;
		else
		{
			free(tmp);
			return (printf("Error\n Line invalid\n"));
		}
		free(lst->content);
		lst->content = tmp;
		lst = lst->next;
	}
	return (0);
}

/**
 * checks if there are only one Ambient Light, one Camera and one Light
 * @param count [int[6]] counter
 * @return [int] 0 if good, 1 if error
*/
int	check_count(int *count)
{
	if (count[0] != 1)
		perror("Error\nIncorrect number of Ambient Lights\n");
	else if (count[1] != 1)
		perror("Error\nIncorrect number of Cameras\n");
	else if (count[2] != 1)
		perror("Error\nIncorrect number of Lights\n");
	else
		return (0);
	return (1);
}

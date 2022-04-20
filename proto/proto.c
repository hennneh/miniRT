/* WORK IN PROGRESS; SOLUTIONTILL VINNY HAS CONTINUED */

#include "../inc/minirt.h"

t_al	*extract_ambient(char **things)
{
	t_al	*elem;

	elem = ft_calloc(1, sizeof(t_al));
	if (!things[0] || !things[1] || !things[2] || !things[3] || !things[4])
	{
		free_2dstr(things);
		free(elem);
		return (NULL);
	}
	elem->lr = ft_atof(things[1]);
	elem->r = ft_atoi(things[2]);
	elem->g = ft_atoi(things[3]);
	elem->b = ft_atoi(things[4]);
	// printf("AMBIENCE %i %i %i\n", elem->r, elem->g, elem->b);
	return(elem);
}

t_cam	*extract_camera(char **things)
{
	t_cam	*elem;

	elem = ft_calloc(1, sizeof(t_cam));
	if (!things[0] || !things[1] || !things[2] || !things[3] || !things[4] || !things[5] || !things[6] || !things[7])
	{
		free(elem);
		free_2dstr(things);
		return (NULL);
	}
	elem->cor[0] = ft_atof(things[1]);
	elem->cor[1] = ft_atof(things[2]);
	elem->cor[2] = ft_atof(things[3]);
	elem->v_o[0] = ft_atof(things[4]);
	elem->v_o[1] = ft_atof(things[5]);
	elem->v_o[2] = ft_atof(things[6]);
	elem->fov = ft_atoi(things[7]) * PI/180;
	unit(elem->v_o);
	free_2dstr(things);
	// printf("pos %lf, %lf, %lf,\ndirec %lf, %lf, %lf,\nfov %lf\n", elem->cor[0], elem->cor[1], elem->cor[2], elem->v_o[0], elem->v_o[1], elem->v_o[2], elem->fov);
	return(elem);
}

t_lol	*extract_light(char **things)
{
	t_lol	*elem;

	elem = ft_calloc(1, sizeof(t_lol));
	if (!things[0] || !things[1] || !things[2] || !things[3] || !things[4] || !things[5] || !things[6] || !things[7])
	{
		free_2dstr(things);
		free(elem);
		return (NULL);
	}
	elem->cor[0] = ft_atof(things[1]);
	elem->cor[1] = ft_atof(things[2]);
	elem->cor[2] = ft_atof(things[3]);
	elem->brit = ft_atoi(things[4]);
	// elem->r = ft_atoi(things[5]);BONUS
	// elem->g = ft_atoi(things[6]);BONUS
	// elem->b = ft_atoi(things[7]);BONUS
	free_2dstr(things);
	return(elem);
}

t_sph	*extract_sphere(char **things)
{
	t_sph	*elem;

	elem = ft_calloc(1, sizeof(t_sph));
	if (!things[0] || !things[1] || !things[2] || !things[3] || !things[4] || !things[5] || !things[6] || !things[7])
	{
		free(elem);
		free_2dstr(things);
		return (NULL);
	}
	elem->cor[0] = ft_atof(things[1]);
	elem->cor[1] = ft_atof(things[2]);
	elem->cor[2] = ft_atof(things[3]);
	elem->rad = ft_atoi(things[4]) / 2;
	elem->r = ft_atoi(things[5]);
	elem->g = ft_atoi(things[6]);
	elem->b = ft_atoi(things[7]);
	//printf("clr sphere %i %i %i \n", elem->r, elem->g, elem->b);
	free_2dstr(things);
	return(elem);
}

t_pl	*extract_plane(char **things)
{
	t_pl	*elem;

	elem = ft_calloc(1, sizeof(t_pl));
	if (!things[0] || !things[1] || !things[2] || !things[3] || !things[4] || !things[5] || !things[6] || !things[7] || !things[8] || !things[9])
	{
		free(elem);
		free_2dstr(things);
		return (NULL);
	}
	elem->cor[0] = ft_atof(things[1]);
	elem->cor[1] = ft_atof(things[2]);
	elem->cor[2] = ft_atof(things[3]);
	elem->v_o[0] = ft_atof(things[4]);
	elem->v_o[1] = ft_atof(things[5]);
	elem->v_o[2] = ft_atof(things[6]);
	elem->r = ft_atoi(things[7]);
	elem->g = ft_atoi(things[8]);
	elem->b = ft_atoi(things[9]);
	unit(elem->v_o);
	free_2dstr(things);
	return(elem);
}

t_cyl	*extract_cylinder(char **things)
{
	t_cyl	*elem;

	elem = ft_calloc(1, sizeof(t_cyl));
	if (!things[0] || !things[1] || !things[2] || !things[3] || !things[4] || !things[5] || !things[6] || !things[7] || !things[8] || !things[9] || !things[10] || !things[11])
	{
		free(elem);
		free_2dstr(things);
		return (NULL);
	}
	elem->cor[0] = ft_atof(things[1]);
	elem->cor[1] = ft_atof(things[2]);
	elem->cor[2] = ft_atof(things[3]);
	elem->v_o[0] = ft_atof(things[4]);
	elem->v_o[1] = ft_atof(things[5]);
	elem->v_o[2] = ft_atof(things[6]);
	elem->rad = ft_atof(things[7]) / 2;
	elem->hght = ft_atof(things[8]);
	elem->r = ft_atoi(things[9]);
	elem->g = ft_atoi(things[10]);
	elem->b = ft_atoi(things[11]);
	unit(elem->v_o);
	free_2dstr(things);// remember to free all of them
	return(elem);
}

void	*extract_line(char **lines, t_mrt *mrt)
{
	char **things;
	char *line;

	int i = 0;
	while (lines[i])
	{
		line = lines[i];
		ft_char_rep(line, ',', ' ');
		things = ft_split(line, ' ');
		// printf("line %s\n", line);
		// for(int l = 0; things[l]; l++)
		// 	printf("thing %s\n", things[l]);
		if (!ft_strncmp(things[0], "A", 1))
			mrt->al = (extract_ambient(things));
		else if (!ft_strncmp(things[0], "C\0", 1))
		{
			mrt->cam = (extract_camera(things));
		}
		else if (!ft_strncmp(things[0], "L\0", 1))
		{
			mrt->l = (extract_light(things));
		}
		else if (!ft_strncmp(things[0], "sp\0", 2))
		{
			mrt->sp = malloc(sizeof(t_sph *));
			mrt->sp[0] = (extract_sphere(things));
		}
		else if (!ft_strncmp(things[0], "pl\0", 2))
		{
			mrt->pl = malloc(sizeof(t_pl *));
			mrt->pl[0] = (extract_plane(things));
		}
		else if (!ft_strncmp(things[0], "cy\0", 2))
		{
			mrt->cy = malloc(sizeof(t_cyl *));
			mrt->cy[0] = (extract_cylinder(things));
		}
		else
		{
			printf("UNKNOWN OBJECT IN INPUTLINE %i\n", i);
			free_2dstr(things);
		}
		i++;
	}
	return (NULL);
}

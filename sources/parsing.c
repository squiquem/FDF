/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:09:49 by squiquem          #+#    #+#             */
/*   Updated: 2018/01/16 23:57:22 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_point	*create_point(int x, int y, char *s)
{
	t_point	*p;

	if (!((p = (t_point*)malloc(sizeof(t_point)))))
		print_error("Error malloc");
	p->x = x * SIZE_W;
	p->y = y * SIZE_H;
	p->z = ft_atoi(s);
	p->s = 1;
	p->color = p->z;
	return (p);
}

int		parse_points(char *line, int nb_line, t_point ***array_points,
		t_env *e)
{
	char	**array_str;
	int		i;

	array_str = ft_strsplit(line, ' ');
	i = 0;
	while (array_str[i])
		i++;
	if (!((*array_points) = (t_point**)malloc(sizeof(t_point) * i)))
		print_error("Error malloc");
	i = 0;
	while (array_str[i])
	{
		(*array_points)[i] = create_point(i, nb_line, array_str[i]);
		if ((*array_points)[i]->color > e->zmax)
			e->zmax = (*array_points)[i]->color;
		if ((*array_points)[i]->color < e->zmin)
			e->zmin = (*array_points)[i]->color;
		i++;
	}
	free_tab(array_str);
	free(line);
	return (i);
}

int		parse_lines(char *map)
{
	int		fd;
	int		nb_lines;
	char	buf;

	fd = 0;
	nb_lines = 0;
	if ((fd = open(map, O_RDONLY)) < 0)
		print_error("Error map");
	while (read(fd, &buf, 1))
	{
		if (buf == '\n')
			nb_lines++;
	}
	close(fd);
	return (nb_lines);
}

t_map	*parse_map(char *av, int fd, t_env *e)
{
	char	*line;
	int		nb_line;
	t_map	*map;
	t_line	*line_map;
	t_point	**array_points;

	nb_line = 0;
	if (!(map = (t_map*)malloc(sizeof(t_map))) ||
		!(map->lines = (t_line**)malloc(sizeof(t_line) * parse_lines(av))))
		print_error("Error malloc");
	map->len = 0;
	if ((fd = open(av, O_RDONLY)) <= 0)
		return (NULL);
	while ((get_next_line(fd, &line)) > 0)
	{
		if (!(line_map = (t_line*)malloc(sizeof(t_line))))
			print_error("Error malloc");
		line_map->len = parse_points(line, nb_line, &array_points, e);
		line_map->points = array_points;
		map->lines[nb_line] = line_map;
		nb_line++;
	}
	free(line);
	map->len = nb_line;
	return (map);
}

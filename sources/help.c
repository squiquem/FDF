/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:09:49 by squiquem          #+#    #+#             */
/*   Updated: 2018/01/22 18:22:45 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		quit(void)
{
	exit(1);
	return (0);
}

void	free_tab(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	get_center(t_env *e)
{
	t_point	p;
	int		yl;
	int		xl;

	p = e->center;
	yl = e->map->len;
	xl = e->map->lines[yl - 1]->len;
	p.x = (e->map->lines[yl - 1]->points[xl - 1]->x +
			e->map->lines[0]->points[0]->x) / 2;
	p.y = (e->map->lines[yl - 1]->points[xl - 1]->y +
			e->map->lines[0]->points[0]->y) / 2;
	e->center = p;
}

void	draw_reload(t_env *e)
{
	if (!(e->img = mlx_new_image(e->mlx, WINDOW_WIDTH + 100, WINDOW_HEIGTH +
	100)))
		print_error("Error mlx newimage");
	if (!(e->pixel_img = mlx_get_data_addr(e->img, &(e->bpp), &(e->s_line),
	&(e->ed))))
		print_error("Error mlx getdata");
	draw_map(e);
	if (!(mlx_put_image_to_window(e->mlx, e->win, e->img, -50, -50)))
		print_error("Error mlx putimage");
	mlx_destroy_image(e->mlx, e->img);
}

void	adapt_map(t_env *e)
{
	int		w;
	int		h;
	double	s;

	w = (WINDOW_WIDTH + 100) / 2;
	h = (WINDOW_HEIGTH + 100) / 2;
	if (e->center.x > e->center.y && e->center.x == 0)
		e->center.x = 10;
	else if (e->center.x < e->center.y && e->center.y == 0)
		e->center.y = 10;
	e->center.x > e->center.y ? (s = (w - 600) / (e->center.x))
		: (s = (h - 300) / (e->center.y));
	calcul_translat(e, -e->center.x + w, -e->center.y + h, 0);
	calcul_scale(e, s);
}

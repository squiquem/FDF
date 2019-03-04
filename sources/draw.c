/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:09:49 by squiquem          #+#    #+#             */
/*   Updated: 2018/01/09 15:27:20 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		draw_windows(char *title, int weight, int heigth, t_env *e)
{
	if (!(e->mlx = mlx_init()))
		print_error("Error mlx init");
	if (!(e->win = mlx_new_window(e->mlx, weight, heigth, title)))
		print_error("Error mlx newwindow");
}

static void	draw_point(t_point *p, double z, t_env *e)
{
	int i;
	int	color;

	color = get_color(z, e);
	i = ((int)p->x * 4) + ((int)p->y * e->s_line);
	e->pixel_img[i] = color;
	e->pixel_img[++i] = color >> 8;
	e->pixel_img[++i] = color >> 16;
}

static int	point_is_out(t_point *a)
{
	if ((int)a->x <= 0 || (int)a->y <= 0 || (int)a->x >= WINDOW_WIDTH ||
			(int)a->y >= WINDOW_HEIGTH)
		return (1);
	return (0);
}

void		draw_line(t_point *a, t_point *b, t_env *e)
{
	int		step;
	int		i;
	t_point	*pix;
	float	z;

	if (point_is_out(a) || point_is_out(b))
		return ;
	if (fabs(a->x - b->x) <= fabs(a->y - b->y))
		step = 1 + fabs(a->y - b->y);
	else
		step = 1 + fabs(a->x - b->x);
	pix = create_point(a->x / SIZE_W, a->y / SIZE_H, "0");
	z = (float)(a->color - b->color) / step;
	i = -1;
	while (++i <= step)
	{
		draw_point(pix, (double)a->color - z * i, e);
		pix->x = a->x + round((double)i * (b->x - a->x) / step);
		pix->y = a->y + round((double)i * (b->y - a->y) / step);
	}
	free(pix);
}

void		draw_map(t_env *e)
{
	int			x;
	int			y;
	t_point		p1;

	y = 0;
	while (y < e->map->len)
	{
		x = 0;
		while (x < (e->map->lines[y]->len))
		{
			p1 = (*e->map->lines[y]->points[x]);
			if (x + 1 < (e->map->lines[y]->len))
				draw_line(&p1, &(*e->map->lines[y]->points[x + 1]), e);
			if (y + 1 < e->map->len)
			{
				if (e->map->lines[y + 1]->points[x] &&
				x <= e->map->lines[y + 1]->len)
					draw_line(&p1, &(*e->map->lines[y + 1]->points[x]), e);
			}
			x++;
		}
		y++;
	}
}

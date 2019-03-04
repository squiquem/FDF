/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:09:49 by squiquem          #+#    #+#             */
/*   Updated: 2018/01/15 19:11:10 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	key_hook_rotation(int keycode, t_env *e)
{
	if (keycode == KEY_ROT_X_U)
		calcul_rotation(e, -ROT, 'x');
	else if (keycode == KEY_ROT_X_D)
		calcul_rotation(e, ROT, 'x');
	else if (keycode == KEY_ROT_Y_U)
		calcul_rotation(e, -ROT, 'y');
	else if (keycode == KEY_ROT_Y_D)
		calcul_rotation(e, ROT, 'y');
	else if (keycode == KEY_ROT_Z_U)
		calcul_rotation(e, -ROT, 'z');
	else if (keycode == KEY_ROT_Z_D)
		calcul_rotation(e, ROT, 'z');
}

static void	key_hook_translation(int keycode, t_env *e)
{
	if (keycode == KEY_UP)
		calcul_translat(e, 0, -MOVE, 0);
	else if (keycode == KEY_DOWN)
		calcul_translat(e, 0, MOVE, 0);
	else if (keycode == KEY_LEFT)
		calcul_translat(e, -MOVE, 0, 0);
	else if (keycode == KEY_RIGHT)
		calcul_translat(e, MOVE, 0, 0);
}

static void	key_hook_scale(int keycode, t_env *e)
{
	if (keycode == KEY_ZOOM_IN)
		calcul_scale(e, ZOOM_IN);
	else if (keycode == KEY_ZOOM_OUT)
		calcul_scale(e, ZOOM_OUT);
}

static void	key_hook_end(int keycode, t_env *e)
{
	int	y;
	int	x;

	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(e->mlx, e->win);
		y = 0;
		while (y < e->map->len)
		{
			x = 0;
			while (x < (e->map->lines[y]->len))
			{
				free(e->map->lines[y]->points[x]);
				x++;
			}
			free(e->map->lines[y]);
			y++;
		}
		free(e->map);
		free(e->color_min);
		free(e->color_max);
		free(e);
		exit(0);
	}
}

int			key_hook(int keycode, t_env *e)
{
	key_hook_end(keycode, e);
	key_hook_rotation(keycode, e);
	key_hook_translation(keycode, e);
	key_hook_scale(keycode, e);
	draw_reload(e);
	return (0);
}

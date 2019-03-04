/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:09:49 by squiquem          #+#    #+#             */
/*   Updated: 2018/01/22 18:22:07 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		print_error(char *cause)
{
	ft_putendl_fd(cause, 2);
	exit(1);
}

int			expose_hook(t_env *e)
{
	draw_reload(e);
	return (0);
}

static void	display_controls(void)
{
	ft_putstr("\
____________________________\n\
CONTROLS:\n\
Translation:\n\
	Y: Key: UP, DOWN\n\
	X: Key: LEFT, RIGHT\n\
\n\
Rotation:\n\
	X: Keypad: 1, 4\n\
	Y: Keypad: 2, 5\n\
	Z: Keypad: 3, 6\n\
\n\
Zoom:\n\
	IN: Keypad: +\n\
	OUT: Keypad: -\n\
____________________________\n\
");
}

static void	control_color(int ac, char *av, t_env *e)
{
	if (ac == 3
		&& !(set_color_b10(av, e))
		&& !(set_color_b16("0123456789abcdef", av, e))
		&& !(set_color_b16("0123456789ABCDEF", av, e)))
	{
		ft_putstr("\
______________________________________________________________\n\
Error color format:\n\
RRRGGGBBBAAA-RRRGGGBBBAAA with 0 <= RRR/GGG/BBB/AAA <= 255\n\
OR\n\
0xRRGGBB-0xRRGGBB with 0 <= RR/GG/BB <= 255 in hexadecimal\n\
______________________________________________________________\n\
");
	}
}

int			main(int ac, char **av)
{
	t_env	*e;

	if (ac == 2 || ac == 3)
	{
		if (!(e = (t_env*)malloc(sizeof(t_env))))
			print_error("Error malloc");
		control_color(ac, av[2], e);
		e->map = parse_map(av[1], 0, e);
		if (e->map->len == 0 || e->map->lines[0]->len == 0)
			print_error("Error map");
		get_center(e);
		adapt_map(e);
		display_controls();
		draw_windows("Fil de Fer Project", WINDOW_WIDTH, WINDOW_HEIGTH, e);
		mlx_hook(e->win, 17, 1L << 17, quit, e);
		mlx_hook(e->win, 2, 1L << 0, key_hook, e);
		mlx_expose_hook(e->win, expose_hook, e);
		mlx_loop(e->mlx);
	}
	else if (ac < 2 || ac > 3)
		write(1, "Usage: <filename> colormin-colormax (base 10 or 16)\n", 52);
	return (0);
}

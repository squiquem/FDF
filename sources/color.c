/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 15:02:29 by squiquem          #+#    #+#             */
/*   Updated: 2018/01/12 12:05:31 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_color			*init_color(int r, int g, int b, int a)
{
	t_color	*c;

	if (!(c = (t_color *)malloc(sizeof(t_color))))
		print_error("Error malloc");
	c->r = r;
	c->g = g;
	c->b = b;
	c->a = a;
	return (c);
}

static t_color	*get_color2(t_env *e, double z)
{
	t_color		*c;
	double		r;
	double		g;
	double		b;
	double		a;

	r = ((((double)e->color_max->r - e->color_min->r) / abs(e->zmin -
					e->zmax)) * (z - e->zmin)) + e->color_min->r;
	g = ((((double)e->color_max->g - e->color_min->g) / abs(e->zmin -
					e->zmax)) * (z - e->zmin)) + e->color_min->g;
	b = ((((double)e->color_max->b - e->color_min->b) / abs(e->zmin -
					e->zmax)) * (z - e->zmin)) + e->color_min->b;
	a = ((((double)e->color_max->a - e->color_min->a) / abs(e->zmin -
					e->zmax)) * (z - e->zmin)) + e->color_min->a;
	if (!(c = (t_color *)malloc(sizeof(t_color))))
		print_error("Error malloc");
	c->r = r;
	c->g = g;
	c->b = b;
	c->a = a;
	return (c);
}

int				get_color(double z, t_env *e)
{
	int	color;

	color = 0;
	if (!(e->color_min))
	{
		if (z <= 0)
			color = 0x0D6386;
		else if (z > 0 && z < 10)
			color = 0x32A862;
		else if (z >= 10 && z < 20)
			color = 0x8FC89A;
		else if (z >= 20 && z < 50)
			color = 0xFAECBE;
		else if (z >= 50 && z < 70)
			color = 0x996E56;
		else
			color = 0xE0D3CC;
	}
	else
		color = ((get_color2(e, z))->a << 24) + ((get_color2(e, z))->r << 16)
				+ ((get_color2(e, z))->g << 8) + (get_color2(e, z))->b;
	return (color);
}

char			set_color_b10(char *s, t_env *e)
{
	int	i;

	i = -1;
	if (ft_strlen(s) != 25 || s[12] != '-')
		return (0);
	while (s[++i])
	{
		if (i != 12 && (s[i] > '9' || s[i] < '0'))
			return (0);
	}
	if (!(e->color_max = (t_color *)malloc(sizeof(t_color))))
		print_error("Error malloc");
	if (!(e->color_min = (t_color *)malloc(sizeof(t_color))))
		print_error("Error malloc");
	e->color_min->r = ft_atoi(ft_strsub(s, 0, 3));
	e->color_min->g = ft_atoi(ft_strsub(s, 3, 3));
	e->color_min->b = ft_atoi(ft_strsub(s, 6, 3));
	e->color_min->a = ft_atoi(ft_strsub(s, 9, 3));
	e->color_max->r = ft_atoi(ft_strsub(s, 13, 3));
	e->color_max->g = ft_atoi(ft_strsub(s, 16, 3));
	e->color_max->b = ft_atoi(ft_strsub(s, 19, 3));
	e->color_max->a = ft_atoi(ft_strsub(s, 22, 3));
	return (1);
}

char			set_color_b16(char *base, char *s, t_env *e)
{
	int	i;

	i = 1;
	if (ft_strlen(s) != 17 || s[8] != '-' || s[0] != '0' || s[1] != 'x'
	|| s[9] != '0' || s[10] != 'x')
		return (0);
	while (s[++i])
	{
		if ((i != 9 && i != 10 && i != 8) && (s[i] > 'f' || (s[i] < 'a'
			&& s[i] > 'F') || (s[i] < 'A' && s[i] > '9') || s[i] < '0'))
			return (0);
	}
	if (!(e->color_max = (t_color *)malloc(sizeof(t_color))))
		print_error("Error malloc");
	if (!(e->color_min = (t_color *)malloc(sizeof(t_color))))
		print_error("Error malloc");
	e->color_min->r = ft_atoi_base(ft_strsub(s, 2, 2), base);
	e->color_min->g = ft_atoi_base(ft_strsub(s, 4, 2), base);
	e->color_min->b = ft_atoi_base(ft_strsub(s, 6, 2), base);
	e->color_min->a = 0;
	e->color_max->r = ft_atoi_base(ft_strsub(s, 11, 2), base);
	e->color_max->g = ft_atoi_base(ft_strsub(s, 13, 2), base);
	e->color_max->b = ft_atoi_base(ft_strsub(s, 15, 2), base);
	e->color_max->a = 0;
	return (1);
}

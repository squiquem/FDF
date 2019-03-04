/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:09:49 by squiquem          #+#    #+#             */
/*   Updated: 2018/01/04 21:23:48 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_matrice	*matrice_rotation_x(double beta)
{
	t_matrice *m;

	if (!(m = (t_matrice*)ft_memalloc(sizeof(t_matrice))))
		print_error("Error malloc");
	m->a1 = 1;
	m->b2 = cos(beta);
	m->b3 = -sin(beta);
	m->c2 = sin(beta);
	m->c3 = cos(beta);
	m->d4 = 1;
	return (m);
}

t_matrice	*matrice_rotation_y(double beta)
{
	t_matrice *m;

	if (!(m = (t_matrice*)ft_memalloc(sizeof(t_matrice))))
		print_error("Error malloc");
	m->a1 = cos(beta);
	m->a3 = sin(beta);
	m->c1 = -sin(beta);
	m->c3 = cos(beta);
	m->b2 = 1;
	m->d4 = 1;
	return (m);
}

t_matrice	*matrice_rotation_z(double beta)
{
	t_matrice *m;

	if (!(m = (t_matrice*)ft_memalloc(sizeof(t_matrice))))
		print_error("Error malloc");
	m->a1 = cos(beta);
	m->a2 = -sin(beta);
	m->b1 = sin(beta);
	m->b2 = cos(beta);
	m->c3 = 1;
	m->d4 = 1;
	return (m);
}

t_matrice	*matrice_translation(double tx, double ty, double tz)
{
	t_matrice *m;

	if (!(m = (t_matrice*)ft_memalloc(sizeof(t_matrice))))
		print_error("Error malloc");
	m->a4 = tx;
	m->b4 = ty;
	m->c4 = tz;
	m->a1 = 1;
	m->b2 = 1;
	m->c3 = 1;
	m->d4 = 1;
	return (m);
}

t_matrice	*matrice_scale(double s)
{
	t_matrice *m;

	if (!(m = (t_matrice*)ft_memalloc(sizeof(t_matrice))))
		print_error("Error malloc");
	m->a1 = s;
	m->b2 = s;
	m->c3 = s;
	m->d4 = 1;
	return (m);
}

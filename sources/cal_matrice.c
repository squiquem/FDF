/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_matrice.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:09:49 by squiquem          #+#    #+#             */
/*   Updated: 2018/01/04 18:41:59 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	calcul_matrice(t_point *p, t_matrice *m, t_env *e)
{
	double tmp_x;
	double tmp_y;
	double tmp_z;

	p->x -= e->center.x;
	p->y -= e->center.y;
	tmp_x = p->x * m->a1 + p->y * m->a2 + p->z * m->a3 + p->s * m->a4;
	tmp_y = p->x * m->b1 + p->y * m->b2 + p->z * m->b3 + p->s * m->b4;
	tmp_z = p->x * m->c1 + p->y * m->c2 + p->z * m->c3 + p->s * m->c4;
	p->z = tmp_z;
	p->y = tmp_y + e->center.y;
	p->x = tmp_x + e->center.x;
}

static void	calcul_matrice_all_points(t_matrice *m, t_env *e)
{
	int x;
	int y;

	y = 0;
	while (y < e->map->len)
	{
		x = 0;
		while (x < (e->map->lines[y]->len))
		{
			calcul_matrice(e->map->lines[y]->points[x], m, e);
			x++;
		}
		y++;
	}
}

void		calcul_rotation(t_env *e, double rot, char axe)
{
	t_matrice *m_rot;

	if (axe == 'x')
		m_rot = matrice_rotation_x(rot);
	else if (axe == 'y')
		m_rot = matrice_rotation_y(rot);
	else
		m_rot = matrice_rotation_z(rot);
	calcul_matrice_all_points(m_rot, e);
	free(m_rot);
}

void		calcul_translat(t_env *e, double x, double y, double z)
{
	t_matrice *m_tran;

	m_tran = matrice_translation(x, y, z);
	calcul_matrice_all_points(m_tran, e);
	get_center(e);
	free(m_tran);
}

void		calcul_scale(t_env *e, double s)
{
	t_matrice *m_tran;

	m_tran = matrice_scale(s);
	calcul_matrice_all_points(m_tran, e);
	free(m_tran);
}

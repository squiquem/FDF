/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:09:49 by squiquem          #+#    #+#             */
/*   Updated: 2018/01/16 23:32:00 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../mlx.h"
# include <fcntl.h>
# include <math.h>

# include "../libft/libft.h"

# define SIZE_W 2
# define SIZE_H 2

# define WINDOW_HEIGTH 1000
# define WINDOW_WIDTH 2000

# define MOVE -100
# define ZOOM_IN 1.1
# define ZOOM_OUT 0.9
# define ROT M_PI / 32

# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ZOOM_IN 69
# define KEY_ZOOM_OUT 78
# define KEY_ROT_X_U 86
# define KEY_ROT_X_D 83
# define KEY_ROT_Y_U 87
# define KEY_ROT_Y_D 84
# define KEY_ROT_Z_U 88
# define KEY_ROT_Z_D 85

# define MAX(a, b) ((a > b) ? a : b)
# define MIN(a, b) ((a < b) ? a : b)

typedef struct	s_point
{
	double		x;
	double		y;
	double		z;
	double		s;
	int			color;
}				t_point;

typedef struct	s_line
{
	t_point		**points;
	int			len;
}				t_line;

typedef struct	s_map
{
	t_line		**lines;
	int			len;
}				t_map;

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
	int			a;
}				t_color;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_point		center;
	void		*img;
	char		*pixel_img;
	int			bpp;
	int			s_line;
	int			ed;
	t_color		*color_min;
	t_color		*color_max;
	int			zmin;
	int			zmax;
}				t_env;

typedef struct	s_matrice
{
	double		a1;
	double		a2;
	double		a3;
	double		a4;
	double		b1;
	double		b2;
	double		b3;
	double		b4;
	double		c1;
	double		c2;
	double		c3;
	double		c4;
	double		d1;
	double		d2;
	double		d3;
	double		d4;
}				t_matrice;

t_point			*create_point(int x, int y, char *s);
t_map			*parse_map(char *av, int fd, t_env *e);
int				parse_points(char *line, int nb_line, t_point ***array_points,
				t_env *e);
int				parse_lines(char *map);

void			draw_windows(char *title, int weight, int height, t_env *e);
void			draw_map(t_env *e);

void			calcul_rotation(t_env *e, double rot, char axe);
void			calcul_translat(t_env *e, double x, double y, double z);
void			calcul_scale(t_env *e, double s);

t_matrice		*matrice_rotation_x(double beta);
t_matrice		*matrice_rotation_y(double beta);
t_matrice		*matrice_rotation_z(double beta);
t_matrice		*matrice_translation(double tx, double ty, double tz);
t_matrice		*matrice_scale(double s);

int				key_hook(int keycode, t_env *e);

int				get_color(double z, t_env *e);
char			set_color_b10(char *s, t_env *e);
char			set_color_b16(char *base, char *s, t_env *e);

void			free_tab(char **str);
void			get_center(t_env *e);
void			draw_reload(t_env *e);
void			adapt_map(t_env *e);

void			print_error(char *cause);

#endif

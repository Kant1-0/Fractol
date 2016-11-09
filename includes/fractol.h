/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 17:31:05 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/09 20:54:28 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FRACTOL_H
# define _FRACTOL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define API_NAME		"Fractol"

# define KEY_ESC		0x0035
# define KEY_I			0x0022
# define KEY_G			0x0005
# define KEY_P			0x0023
# define KEY_LEFT		0x007b
# define KEY_RIGHT		0x007c
# define KEY_DOWN		0x007d
# define KEY_UP			0x007e
# define KEY_W			0x000d
# define KEY_A			0x0000
# define KEY_S			0x0001
# define KEY_D			0x0002
# define KEY_Q			0x000c
# define KEY_E			0x000e
# define KEY_1			0x0012
# define KEY_2			0x0013
# define KEY_3			0x0014
# define KEY_PLUS		0x0045
# define KEY_MINUS		0x004e
# define KEY_PG_UP		0x0074
# define KEY_PG_DOWN	0x0079
# define KEY_NUM_4		0x0056
# define KEY_NUM_6		0x0058
# define KEY_NUM_8		0x005b
# define KEY_NUM_2		0x0054
# define KEY_NUM_5		0x0057

# define FRACT_OPT		"gIlh"
# define FRACT_LST		"123"
# define HELP			-2
# define ERROR			-1
# define EXIT			1

# define BLUE			0x0000FF
# define CYAN			0x00FFFF
# define RED			0xFF0000
# define GREEN			0x00FF00
# define WHITE			0xFFFFFF
# define BLACK			0x000000
# define YELLOW			0xFFFF00

typedef struct	s_coord
{
	int				pixel[2];
	struct s_coord	*next;
}				t_coord;

typedef struct	s_color
{
	unsigned char	rgba[4];
	int				id;
}				t_color;

typedef struct	s_pos
{
	long long		x;
	long long		y;
	long long		z;
	int				coord[3];
}				t_pos;

typedef struct	s_vert
{
	t_pos			pos;
	t_color			color;
	struct s_vert	*next;
}				t_vert;

typedef struct	s_param
{
	int			zoom;
	int			iter;
	float		x;
	float		y;
	int			reset;
}				t_param;

typedef struct	s_fract
{
	unsigned	*opt;
	float		x1;
	float		y1;
	float		zoom;
	int			image_x;
	int			image_y;
	int			iter_max;
}				t_fract;

typedef struct	s_img
{
	int				id;
	t_fract			fract;
	t_param			param;
	void			*img_ptr;
	char			*data;
	int				bpp;
	int				sizeline;
	int				endian;
	int				width;
	int				height;
	struct s_img	*next;
}				t_img;

typedef struct	s_opt
{
	unsigned		opt;
	struct s_opt	*next;
}				t_opt;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		*img;
	t_img		*view;
	int			window_x;
	int			window_y;
	int			elem;
	unsigned	opt1;
	unsigned 	opt2;
	unsigned 	opt3;
}				t_mlx;

t_img			*lst_img_new(t_img **img, int width, int height, t_mlx *fdf);
t_coord			*lst_coord_new(t_coord **coord, int x, int y);

t_color			create_color_rgb(int rgb);

double			norme(t_pos const a, t_pos const b);
double			interpolate(double const a, double const b, double const f);
t_color			linear_interpolation(t_color const src, t_color const end,
	double const factor);

void			draw_fractol(t_img *img);

void			move_map(t_mlx *fdf, int keycode, t_img *view);
void			zoom_map(t_mlx *fdf, int keycode, t_img *view);
void			select_map(t_mlx *fdf, int keycode, t_img **view);
void			reset_map(t_mlx *fdf, int keycode);

void			clear_image(t_img *img);
void			draw_image(t_mlx *fdf);
int				key_hook(int keycode, void *param);
int				expose_hook(void *param);

void			put_info_to_window(t_mlx *fdf, t_img *view);
void			put_pixel_to_image(t_img const img, t_vert const vertex);
t_color			new_color(unsigned char const b, unsigned char const g,
	unsigned char const r, unsigned char const a);
void			draw_line(t_img const img, t_vert const start,
	t_vert const end);
void			draw_point(t_img *img, t_vert point);
void			move_fract(t_img *view);

void			mlx_exit(int ret, t_mlx *fdf, char *error);

#endif

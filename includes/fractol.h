/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 17:31:05 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/15 17:14:26 by qfremeau         ###   ########.fr       */
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

# define MOUSE_LEFT		1
# define MOUSE_RIGHT	2
# define MOUSE_MIDLLE	3
# define MOUSE_WHEEL_U	4
# define MOUSE_WHEEL_D	5

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

typedef struct	s_algo
{
	float		c_r;
	float		c_i;
	float		z_r;
	float		z_i;
	int			i;
	float		tmp;
	int			x;
	int			y;
}				t_algo;

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
	float		zoom_x;
	float		zoom_y;
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
	float		x2;
	float		y2;
	float		zoom_x;
	float		zoom_y;
	int			image_x;
	int			image_y;
	int			iter_max;
	float		jul_cr;
	float		jul_ci;
	int			stop;
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
	unsigned	opt2;
	unsigned	opt3;
}				t_mlx;

void			pick_fractal_param(t_fract *fract, t_img img);
void			parse_op(t_mlx *fdf, char **av, int ac);

t_img			*lst_img_new(t_img **img, int width, int height, t_mlx *fdf);

t_color			add_color_rgb(int rgb);
t_color			create_color_rgb(int r, int g, int b);

void			draw_fractol(t_img *img);
void			algo_mandel(t_algo *algo, t_img *img);
void			fractol_mandelbrot(t_img *img);
void			fractol_julia(t_img *img);
void			fractol_glynn(t_img *img);

void			move_map(t_mlx *fdf, int keycode, t_img *view);
void			zoom_map(t_mlx *fdf, int keycode, int x, int y);
void			select_map(t_mlx *fdf, int keycode, t_img **view);
void			iterate_map(t_mlx *fdf, int keycode, t_img *view);

void			clear_image(t_img *img);
void			draw_image(t_mlx *fdf);
int				key_hook(int keycode, void *param);
int				mouse_hook(int button, int x, int y, void *param);
int				track_hook(int x, int y, void *param);
int				expose_hook(void *param);

void			put_info_to_window(t_mlx *fdf, t_img *view);
void			put_pixel_to_image(t_img const img, t_vert const vertex);
t_color			new_color(unsigned char const b, unsigned char const g,
	unsigned char const r, unsigned char const a);
void			draw_point(t_img *img, t_vert point);
void			move_fract(t_img *view);

void			print_list(void);
void			print_help(void);
void			mlx_exit(int ret, t_mlx *fdf, char *error);

#endif

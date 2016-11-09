/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 18:09:03 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/09 20:03:00 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*static void	init_param(t_param param, t_mov *mov)
{
	if (param.reset == 1)
	{
		mov->exp = 4;
		mov->tile = TILE_HALF;
		mov->mov_x = 0;
		mov->mov_y = 0;
		return ;
	}
	if (param.zoom == 1)
		mov->tile += 0.10;
	else if (param.zoom == -1)
		mov->tile -= 0.10;
	if (param.ratio == 1)
		mov->exp += 0.5;
	else if (param.ratio == -1)
		mov->exp -= 0.5;
	mov->mov_x += param.x;
	mov->mov_y += param.y;
}*/

static void	move_map2(t_img *view, int keycode)
{
	if (keycode == KEY_UP)
	{
		view->param.x = 0;
		view->param.y = -0.05;
		move_fract(view);
	}
	if (keycode == KEY_DOWN)
	{
		view->param.x = 0;
		view->param.y = 0.05;
		move_fract(view);
	}
}

void		move_map(t_mlx *fdf, int keycode, t_img *view)
{
	view->param.zoom = 0;
	view->param.iter = 0;
	view->param.reset = 0;
	clear_image(view);
	if (keycode == KEY_LEFT)
	{
		view->param.x = -0.05;
		view->param.y = 0;
		move_fract(view);
	}
	if (keycode == KEY_RIGHT)
	{
		view->param.x = 0.05;
		view->param.y = 0;
		move_fract(view);
	}
	move_map2(view, keycode);
	draw_fractol(view);
	expose_hook(fdf);
}

/*void		reset_map(t_mlx *fdf, int keycode)
{
	t_param		param;

	param.zoom = 0;
	param.ratio = 0;
	param.x = 0;
	param.y = 0;
	clear_image(fdf->img);
	if (keycode == KEY_NUM_5)
	{
		param.reset = 1;
		//move_vertex(&(fdf->map.vertex), param, fdf);
	}
	draw_fractol(fdf, 1);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	expose_hook(fdf);
}*/

void		move_fract(t_img *view)
{
	view->fract.x1 += view->param.x;
	view->fract.y1 += view->param.y;
	if (view->param.zoom == 1)
		view->fract.zoom += 25;
	else if (view->param.zoom == -1)
		view->fract.zoom -= 25;
	view->fract.iter_max += view->param.iter;
}

void		select_map(t_mlx *fdf, int keycode, t_img **view)
{
	int		i;

	i = 0;
	if (keycode == KEY_Q)
	{
		while (i < (fdf->elem - 1))
		{
			if ((*view)->next != NULL)
				*view = (*view)->next;
			else
				*view = fdf->img;
			++i;
		}
	}
	if (keycode == KEY_E)
	{
		if ((*view)->next != NULL)
			*view = (*view)->next;
		else
			*view = fdf->img;
	}
	expose_hook(fdf);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 18:09:03 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/11 16:39:03 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	move_map2(t_img *view, int keycode)
{
	if (keycode == KEY_UP || keycode == KEY_W)
	{
		view->param.x = 0;
		view->param.y = -0.05;
		move_fract(view);
	}
	if (keycode == KEY_DOWN || keycode == KEY_S)
	{
		view->param.x = 0;
		view->param.y = 0.05;
		move_fract(view);
	}
}

void		move_map(t_mlx *fdf, int keycode, t_img *view)
{
	view->param.iter = 0;
	clear_image(view);
	if (keycode == KEY_LEFT || keycode == KEY_A)
	{
		view->param.x = -0.05;
		view->param.y = 0;
		move_fract(view);
	}
	if (keycode == KEY_RIGHT || keycode == KEY_D)
	{
		view->param.x = 0.05;
		view->param.y = 0;
		move_fract(view);
	}
	move_map2(view, keycode);
	draw_fractol(view);
	expose_hook(fdf);
}

void		move_fract(t_img *view)
{
	view->fract.x1 += view->param.x;
	view->fract.y1 += view->param.y;
	view->fract.x2 -= view->param.x;
	view->fract.y2 -= view->param.y;
	view->fract.iter_max += view->param.iter;
}

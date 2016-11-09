/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_zoom.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 13:35:37 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/09 20:03:07 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	zoom_map2(t_img *view, int keycode)
{
	if (keycode == KEY_PG_UP)
	{
		view->param.zoom = 0;
		view->param.iter = 1;
		move_fract(view);
	}
	if (keycode == KEY_PG_DOWN)
	{
		view->param.zoom = 0;
		view->param.iter = -1;
		move_fract(view);
	}
}

void		zoom_map(t_mlx *fdf, int keycode, t_img *view)
{
	view->param.x = 0;
	view->param.y = 0;
	view->param.reset = 0;
	clear_image(view);
	if (keycode == KEY_PLUS)
	{
		view->param.zoom = 1;
		view->param.iter = 0;
		move_fract(view);
	}
	if (keycode == KEY_MINUS)
	{
		view->param.zoom = -1;
		view->param.iter = 0;
		move_fract(view);
	}
	zoom_map2(view, keycode);
	draw_fractol(view);
	expose_hook(fdf);
}

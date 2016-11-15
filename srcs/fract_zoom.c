/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_zoom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 13:35:37 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/15 16:46:57 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	new_pos2(t_img *view, int y)
{
	if (y < (view->fract.image_y / 2))
	{
		view->fract.y1 -= (1.0 - ((float)y / ((float)view->fract.image_y /
			2.0))) / ((view->fract.zoom_y / (float)view->param.zoom) * 10.0);
		view->fract.y2 -= (1.0 - ((float)y / ((float)view->fract.image_y /
			2.0))) / ((view->fract.zoom_y / (float)view->param.zoom) * 10.0);
	}
	else if (y > (view->fract.image_y / 2))
	{
		view->fract.y1 += ((((float)y - ((float)view->fract.image_y / 2.0)) /
			(view->fract.image_y / 2.0))) / ((view->fract.zoom_y /
			(float)view->param.zoom) * 10.0);
		view->fract.y2 += ((((float)y - ((float)view->fract.image_y / 2.0)) /
			(view->fract.image_y / 2.0))) / ((view->fract.zoom_y /
			(float)view->param.zoom) * 10.0);
	}
}

static void	compute_new_pos(t_img *view, int x, int y)
{
	if (x < (view->fract.image_x / 2))
	{
		view->fract.x1 -= (1.0 - ((float)x / ((float)view->fract.image_x /
			2.0))) / ((view->fract.zoom_x / (float)view->param.zoom) * 10.0);
		view->fract.x2 -= (1.0 - ((float)x / ((float)view->fract.image_x /
			2.0))) / ((view->fract.zoom_x / (float)view->param.zoom) * 10.0);
	}
	else if (x > (view->fract.image_x / 2))
	{
		view->fract.x1 += ((((float)x - ((float)view->fract.image_x / 2.0)) /
			(view->fract.image_x / 2.0))) / ((view->fract.zoom_x /
			(float)view->param.zoom) * 10.0);
		view->fract.x2 += ((((float)x - ((float)view->fract.image_x / 2.0)) /
			(view->fract.image_x / 2.0))) / ((view->fract.zoom_x /
			(float)view->param.zoom) * 10.0);
	}
	new_pos2(view, y);
}

void		zoom_map(t_mlx *fdf, int keycode, int x, int y)
{
	fdf->view->param.x = 0;
	fdf->view->param.y = 0;
	clear_image(fdf->view);
	if (keycode == MOUSE_WHEEL_U)
	{
		fdf->view->fract.zoom_x += ((fdf->view->fract.zoom_x /
			fdf->view->param.zoom) * 10);
		fdf->view->fract.zoom_y += ((fdf->view->fract.zoom_y /
			fdf->view->param.zoom) * 10);
		compute_new_pos(fdf->view, x, y);
	}
	else if (keycode == MOUSE_WHEEL_D)
	{
		fdf->view->fract.zoom_x -= ((fdf->view->fract.zoom_x /
			fdf->view->param.zoom) * 10);
		fdf->view->fract.zoom_y -= ((fdf->view->fract.zoom_y /
			fdf->view->param.zoom) * 10);
		compute_new_pos(fdf->view, x, y);
	}
	draw_fractol(fdf->view);
	expose_hook(fdf);
}

void		iterate_map(t_mlx *fdf, int keycode, t_img *view)
{
	view->param.x = 0;
	view->param.y = 0;
	clear_image(view);
	if (keycode == KEY_PG_UP && view->fract.iter_max)
	{
		view->param.iter = 1;
		move_fract(view);
	}
	if (keycode == KEY_PG_DOWN && view->fract.iter_max > 0)
	{
		view->param.iter = -1;
		move_fract(view);
	}
	draw_fractol(view);
	expose_hook(fdf);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 11:59:38 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/15 16:55:52 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	param2(int keycode, t_img *view)
{
	if (keycode == KEY_2)
	{
		*(view->fract.opt) = *(view->fract.opt) & ~(1u << 4);
		*(view->fract.opt) = *(view->fract.opt) | (1u << 5);
		*(view->fract.opt) = *(view->fract.opt) & ~(1u << 6);
		pick_fractal_param(&view->fract, *view);
	}
	else if (keycode == KEY_3)
	{
		*(view->fract.opt) = *(view->fract.opt) & ~(1u << 4);
		*(view->fract.opt) = *(view->fract.opt) & ~(1u << 5);
		*(view->fract.opt) = *(view->fract.opt) | (1u << 6);
		pick_fractal_param(&view->fract, *view);
	}
}

void		change_param(t_mlx *fdf, int keycode, t_img *view)
{
	clear_image(view);
	if (keycode == KEY_G)
		*(view->fract.opt) = *(view->fract.opt) ^ 1u;
	else if (keycode == KEY_I)
		*(view->fract.opt) = *(view->fract.opt) ^ (1u << 1);
	else if (keycode == KEY_1)
	{
		*(view->fract.opt) = *(view->fract.opt) | (1u << 4);
		*(view->fract.opt) = *(view->fract.opt) & ~(1u << 5);
		*(view->fract.opt) = *(view->fract.opt) & ~(1u << 6);
		pick_fractal_param(&view->fract, *view);
	}
	param2(keycode, view);
	draw_fractol(view);
	expose_hook(fdf);
}

int			expose_hook(void *param)
{
	t_mlx			*fdf;
	t_img			*curs;
	register int	size;

	fdf = (t_mlx*)param;
	curs = fdf->img;
	size = 0;
	while (curs != NULL)
	{
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
			curs->img_ptr, size, 0);
		size += fdf->window_x / fdf->elem;
		curs = curs->next;
	}
	put_info_to_window(fdf, fdf->view);
	return (1);
}

int			key_hook(int keycode, void *param)
{
	t_mlx		*fdf;

	fdf = (t_mlx*)param;
	if (keycode == KEY_G || keycode == KEY_I ||
		(keycode >= KEY_1 && keycode <= KEY_3))
		change_param(fdf, keycode, fdf->view);
	if (keycode == KEY_Q || keycode == KEY_E)
		select_map(fdf, keycode, &fdf->view);
	if ((keycode >= KEY_LEFT && keycode <= KEY_UP) ||
		(keycode >= KEY_A && keycode <= KEY_D) ||
		keycode == KEY_W)
		move_map(fdf, keycode, fdf->view);
	if (keycode == KEY_PG_UP || keycode == KEY_PG_DOWN)
		iterate_map(fdf, keycode, fdf->view);
	if (keycode == KEY_ESC)
		mlx_exit(1, param, "");
	return (1);
}

int			mouse_hook(int button, int x, int y, void *param)
{
	t_mlx		*fdf;

	fdf = (t_mlx*)param;
	if (button == MOUSE_RIGHT)
		fdf->view->fract.stop = fdf->view->fract.stop ^ 1u;
	if (button == MOUSE_WHEEL_U || button == MOUSE_WHEEL_D)
		zoom_map(fdf, button, x, y);
	return (1);
}

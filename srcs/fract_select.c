/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_select.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 16:35:26 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/15 16:18:01 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	general_param(t_fract *fract, t_img img)
{
	fract->image_x = img.width;
	fract->image_y = img.height;
	fract->zoom_x = fract->image_x / (fract->x2 - fract->x1);
	fract->zoom_y = fract->image_y / (fract->y2 - fract->y1);
}

static void	julia_param(t_fract *fract)
{
	fract->iter_max = 25;
	fract->x1 = -1.2;
	fract->y1 = -1.2;
	fract->x2 = 1.2;
	fract->y2 = 1.2;
	fract->jul_cr = 0.285;
	fract->jul_ci = 0.01;
	fract->stop = 1;
}

void		pick_fractal_param(t_fract *fract, t_img img)
{
	if (*(fract->opt) & (1u << 4))
	{
		fract->iter_max = 20;
		fract->x1 = -2.1;
		fract->y1 = -1.2;
		fract->x2 = 1;
		fract->y2 = 1.2;
		fract->jul_cr = 0;
		fract->jul_ci = 0;
		fract->stop = 1;
	}
	else if (*(fract->opt) & (1u << 5))
		julia_param(fract);
	if (*(fract->opt) & (1u << 6))
	{
		fract->iter_max = 30;
		fract->x1 = -1.0;
		fract->y1 = -0.9;
		fract->x2 = 1.0;
		fract->y2 = 0.9;
		fract->jul_cr = 0.291;
		fract->jul_ci = 0.006;
		fract->stop = 1;
	}
	general_param(fract, img);
}

void		select_map(t_mlx *fdf, int keycode, t_img **view)
{
	register int		i;

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

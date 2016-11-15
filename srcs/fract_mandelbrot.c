/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_mandelbrot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 15:35:34 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/15 16:21:30 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		algo_mandel(t_algo *algo, t_img *img)
{
	register t_vert	point;

	while (((algo->z_r * algo->z_r) + (algo->z_i * algo->z_i)) < 4 &&
		algo->i < img->fract.iter_max)
	{
		algo->tmp = algo->z_r;
		algo->z_r = (algo->z_r * algo->z_r) - (algo->z_i * algo->z_i) +
			algo->c_r;
		algo->z_i = 2 * algo->z_i * algo->tmp + algo->c_i;
		++(algo->i);
	}
	if (algo->i == img->fract.iter_max)
	{
		point.pos.x = algo->x;
		point.pos.y = algo->y;
		point.color = add_color_rgb(0);
		draw_point(img, point);
	}
	else if (*(img->fract.opt) & 1u)
	{
		point.pos.x = algo->x;
		point.pos.y = algo->y;
		point.color = add_color_rgb(algo->i);
		draw_point(img, point);
	}
}

void		fractol_mandelbrot(t_img *img)
{
	t_algo			algo;

	algo.x = 0;
	while (algo.x < img->fract.image_x)
	{
		algo.y = 0;
		while (algo.y < img->fract.image_y)
		{
			algo.c_r = algo.x / img->fract.zoom_x + img->fract.x1;
			algo.c_i = algo.y / img->fract.zoom_y + img->fract.y1;
			algo.z_r = img->fract.jul_cr;
			algo.z_i = img->fract.jul_ci;
			algo.i = 0;
			algo_mandel(&algo, img);
			++(algo.y);
		}
		++(algo.x);
	}
}

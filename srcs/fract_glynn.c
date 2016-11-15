/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_glynn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 15:37:15 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/15 16:09:13 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	do_algo(t_algo *algo)
{
	algo->tmp = algo->z_r;
	algo->z_r = sqrt((algo->z_r * algo->z_r - algo->z_i * algo->z_i) *
		(algo->z_r * algo->z_r - algo->z_i * algo->z_i)) + algo->c_r;
	algo->z_i = sqrt((2 * algo->tmp * algo->z_i) * (algo->z_i *
		algo->tmp * 2)) + algo->c_i;
	++(algo->i);
}

static void	algo_glynn(t_algo *algo, t_img *img)
{
	register t_vert	point;

	while (((algo->z_r * algo->z_r) + (algo->z_i * algo->z_i)) < 4 &&
		algo->i < img->fract.iter_max)
		do_algo(algo);
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

void		fractol_glynn(t_img *img)
{
	t_algo			algo;

	algo.x = 0;
	while (algo.x < img->fract.image_x)
	{
		algo.y = 0;
		while (algo.y < img->fract.image_y)
		{
			algo.c_r = img->fract.jul_cr;
			algo.c_i = img->fract.jul_ci;
			algo.z_r = algo.x / img->fract.zoom_x + img->fract.x1;
			algo.z_i = algo.y / img->fract.zoom_y + img->fract.y1;
			algo.i = 0;
			algo_glynn(&algo, img);
			++(algo.y);
		}
		++(algo.x);
	}
}

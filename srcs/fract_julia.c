/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_julia.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 15:37:09 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/15 15:19:59 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		fractol_julia(t_img *img)
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
			algo_mandel(&algo, img);
			++(algo.y);
		}
		++(algo.x);
	}
}

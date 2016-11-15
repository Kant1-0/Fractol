/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 18:50:36 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/11 15:38:05 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		clear_image(t_img *img)
{
	ft_bzero(img->data, img->width * img->height * img->bpp / 8);
}

void		draw_fractol(t_img *img)
{
	if (*(img->fract.opt) & (1u << 4))
		fractol_mandelbrot(img);
	else if (*(img->fract.opt) & (1u << 5))
		fractol_julia(img);
	else if (*(img->fract.opt) & (1u << 6))
		fractol_glynn(img);
}

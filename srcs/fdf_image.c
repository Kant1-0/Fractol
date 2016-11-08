/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 18:50:36 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/08 19:26:25 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clear_image(t_img *img)
{
	ft_bzero(img->data, img->width * img->height * img->bpp / 8);
}

void	fractol_mandelbrot(t_img *img)
{
	dprintf(2, "%s\n", __FUNCTION__);
	t_vert point;
	float c_r;
	float c_i;
	float z_r;
	float z_i;
	int i;
	float tmp;
	int x;
	int y;
	int redraw;

	x = 0;
	while (x < img->fract.image_x)
	{
		y = 0;
		while (y < img->fract.image_y)
		{
			c_r = x / img->fract.zoom + img->fract.x1;
			c_i = y / img->fract.zoom + img->fract.y1;
			z_r = 0;
			z_i = 0;
			i = 0;
			while (((z_r * z_r) + (z_i * z_i)) < 4 && i < img->fract.iter_max)
			{
				tmp = z_r;
				z_r = (z_r * z_r) - (z_i * z_i) + c_r;
				z_i = 2 * z_i * tmp + c_i;
				++i;
			}
			if (i == img->fract.iter_max)
			{
				redraw = 1;
				point.pos.x = x;
				point.pos.y = y;
				point.pos.z = 0;
				point.color = create_color_rgb(0);
				draw_point(img, point);
			}
			else if(*(img->fract.opt) & 1u)
			{
				redraw = 1;
				point.pos.x = x;
				point.pos.y = y;
				point.pos.z = 0;
				point.color = create_color_rgb(i);
				draw_point(img, point);
			}
			++y;
		}
		++x;
	}
}

void	fractol_julia(t_img *img)
{
	dprintf(2, "%s\n", __FUNCTION__);
	t_vert point;
	float c_r;
	float c_i;
	float z_r;
	float z_i;
	int i;
	float tmp;
	int x;
	int y;
	int redraw;

	x = 0;
	while (x < img->fract.image_x)
	{
		y = 0;
		while (y < img->fract.image_y)
		{
			c_r = x / img->fract.zoom + img->fract.x1;
			c_i = y / img->fract.zoom + img->fract.y1;
			z_r = 0;
			z_i = 0;
			i = 0;
			while (((z_r * z_r) + (z_i * z_i)) < 4 && i < img->fract.iter_max)
			{
				tmp = z_r;
				z_r = (z_r * z_r) - (z_i * z_i) + c_r;
				z_i = 2 * z_i * tmp + c_i;
				++i;
			}
			if (i == img->fract.iter_max)
			{
				redraw = 1;
				point.pos.x = x;
				point.pos.y = y;
				point.pos.z = 0;
				point.color = create_color_rgb(0);
				draw_point(img, point);
			}
			else if(*(img->fract.opt) & 1u)
			{
				redraw = 1;
				point.pos.x = x;
				point.pos.y = y;
				point.pos.z = 0;
				point.color = create_color_rgb(i);
				draw_point(img, point);
			}
			++y;
		}
		++x;
	}
}

void	draw_fractol(t_img *img)
{
	if (*(img->fract.opt) & (1u << 4))
		fractol_mandelbrot(img);
	else if (*(img->fract.opt) & (1u << 5))
		fractol_julia(img);
}

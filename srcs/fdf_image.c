/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 18:50:36 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/07 14:31:29 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clear_image(t_img *img)
{
	ft_bzero(img->data, img->width * img->height * img->bpp / 8);
}

void	draw_fractol(t_mlx *fdf, int param)
{

	(void)param;
	t_vert start;

	static float x1 = -2.1;
	static float y1 = -1.2;
	static float zoom = 400;
	static int iter_max = 50;

	float image_x;
	float image_y;

	image_x = fdf->window_x;
	image_y = fdf->window_y;

	float c_r;
	float c_i;
	float z_r;
	float z_i;
	float i;
	float tmp;
	int x;
	int y;
	int redraw;

	x = 0;
	while (x < image_x)
	{
		y = 0;
		while (y < image_y)
		{
			c_r = x / zoom + x1;
			c_i = y / zoom + y1;
			z_r = 0;
			z_i = 0;
			i = 0;
			while (((z_r * z_r) + (z_i * z_i)) < 4 && i < iter_max)
			{
				tmp = z_r;
				z_r = (z_r * z_r) - (z_i * z_i) + c_r;
				z_i = 2 * z_i * tmp + c_i;
				++i;
			}
			if (i == iter_max)
			{
				redraw = 1;
				start.pos.x = x;
				start.pos.y = y;
				start.pos.z = 0;
				start.color = create_color_rgb(0);
				draw_rectangle(fdf, start, start, &redraw);
			}
			/*else
			{
				redraw = 1;
				start.pos.x = x;
				start.pos.y = y;
				start.pos.z = 0;
				start.color = create_color_rgb(i);
				draw_rectangle(fdf, start, start, &redraw);
			}*/
			++y;
		}
		++x;
	}
}

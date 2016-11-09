/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 18:50:36 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/09 18:11:49 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		clear_image(t_img *img)
{
	ft_bzero(img->data, img->width * img->height * img->bpp / 8);
}

void		fractol_mandelbrot(t_img *img)
{
	t_vert point;
	float c_r;
	float c_i;
	float z_r;
	float z_i;
	int i;
	float tmp;
	int x;
	int y;

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
				point.pos.x = x;
				point.pos.y = y;
				point.pos.z = 0;
				point.color = create_color_rgb(0);
				draw_point(img, point);
			}
			else if(*(img->fract.opt) & 1u)
			{
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

void		fractol_julia(t_img *img)
{
	t_vert point;
	float c_r;
	float c_i;
	float z_r;
	float z_i;
	int i;
	float tmp;
	int x;
	int y;

	x = 0;
	while (x < img->fract.image_x)
	{
		y = 0;
		while (y < img->fract.image_y)
		{
			c_r = 0.285;
			c_i = 0.01;
			z_r = x / img->fract.zoom + img->fract.x1;
			z_i = y / img->fract.zoom + img->fract.y1;
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
				point.pos.x = x;
				point.pos.y = y;
				point.pos.z = 0;
				point.color = create_color_rgb(0);
				draw_point(img, point);
			}
			else if(*(img->fract.opt) & 1u)
			{
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

void		fractol_glynn(t_img *img)
{
	t_vert point;
	float c_r;
	float c_i;
	float z_r;
	float z_i;
	int i;
	float tmp;
	int x;
	int y;

	x = 0;
	while (x < img->fract.image_x)
	{
		y = 0;
		while (y < img->fract.image_y)
		{
			c_r = 0.291;
			c_i = 0.006;
			z_r = x / img->fract.zoom + img->fract.x1;
			z_i = y / img->fract.zoom + img->fract.y1;
			i = 0;
			while (((z_r * z_r) + (z_i * z_i)) < 4 && i < img->fract.iter_max)
			{
				tmp = z_r;
				z_r = sqrt((z_r * z_r - z_i * z_i) * (z_r * z_r - z_i * z_i))
					+ c_r;
				z_i = sqrt((2 * tmp * z_i) * (z_i * tmp * 2)) + c_i;
				++i;
			}
			if (i == img->fract.iter_max)
			{
				point.pos.x = x;
				point.pos.y = y;
				point.pos.z = 0;
				point.color = create_color_rgb(0);
				draw_point(img, point);
			}
			else if(*(img->fract.opt) & 1u)
			{
				point.pos.x = x;
				point.pos.y = y;
				point.pos.z = 0;
				point.color = create_color_rgb(i * 700 / img->fract.iter_max);
				draw_point(img, point);
			}
			++y;
		}
		++x;
	}
}

static int	**create_2d_tab(int x, int y)
{
	int		**tab;
	int		i;

	i = 0;
	tab = (int**)malloc(sizeof(int*) * x);
	while(i < x)
	{
		tab[i] = (int*)malloc(sizeof(int) * y);
		++i;
	}
	return (tab);
}

void		fractol_buddhabrot(t_img *img)
{
	t_vert point;
	float c_r;
	float c_i;
	float z_r;
	float z_i;
	int i;
	float tmp;
	int x;
	int y;
	int **pixel;
	t_coord *tmp_pixels;
	t_coord *curs;

	pixel = create_2d_tab(img->fract.image_x, img->fract.image_y);
	tmp_pixels = NULL;
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
				tmp_pixels = lst_coord_new(&tmp_pixels, (z_r - img->fract.x1) * 
					img->fract.zoom, (z_i - img->fract.y1) * img->fract.zoom);
			}
			if (i != img->fract.iter_max)
			{
				curs = tmp_pixels;
				while (curs != NULL)
				{
					if (curs->pixel[0] && curs->pixel[1])
					{
						pixel[0][1] += 1;
					}
					curs = curs->next;
				}
			}
			++y;
		}
		++x;
	}
	x = 0;
	y = 0;
	while (x < img->fract.image_x)
	{
		y = 0;
		while (y < img->fract.image_y)
		{
			point.pos.x = x;
			point.pos.y = y;
			point.pos.z = 0;
			point.color = create_color_rgb(0);
			draw_point(img, point);
			++y;
		}
		++x;
	}
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

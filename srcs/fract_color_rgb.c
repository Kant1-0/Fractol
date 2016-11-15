/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_color_rgb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 13:58:08 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/11 16:04:48 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_color		add_color_rgb(int rgb)
{
	t_color		color;

	color.rgba[0] = 200 - (rgb * 20);
	color.rgba[1] = 200 - (rgb * 20);
	color.rgba[2] = 0 + (rgb * 20);
	color.rgba[3] = 0;
	return (color);
}

t_color		create_color_rgb(int r, int g, int b)
{
	t_color		color;

	color.rgba[0] = b;
	color.rgba[1] = g;
	color.rgba[2] = r;
	color.rgba[3] = 0;
	return (color);
}

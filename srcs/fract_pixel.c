/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 16:57:49 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/08 17:56:41 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_color	new_color(unsigned char const b, unsigned char const g,
	unsigned char const r, unsigned char const a)
{
	t_color	new;

	new.rgba[0] = b;
	new.rgba[1] = g;
	new.rgba[2] = r;
	new.rgba[3] = a;
	return (new);
}

void	put_pixel_to_image(t_img const img, t_vert const vertex)
{
	if (vertex.pos.x < img.width && vertex.pos.y < img.height &&
		vertex.pos.x > 0 && vertex.pos.y > 0)
		ft_memcpy(img.data + vertex.pos.y * img.sizeline + vertex.pos.x *
			img.bpp / 8, &vertex.color, img.bpp / 8);
}

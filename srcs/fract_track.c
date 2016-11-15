/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_track.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 19:46:14 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/15 16:06:02 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		track_hook(int x, int y, void *param)
{
	t_mlx		*fdf;

	fdf = (t_mlx*)param;
	if (!fdf->view->fract.stop)
	{
		clear_image(fdf->view);
		fdf->view->fract.jul_cr = -1 + 2 / (float)fdf->view->width *
			(float)x;
		fdf->view->fract.jul_ci = -1 + 2 / (float)fdf->view->height *
			(float)y;
		draw_fractol(fdf->view);
		expose_hook(fdf);
	}
	return (1);
}

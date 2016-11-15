/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 15:38:58 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/15 17:14:05 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	help1(t_mlx *fdf, t_img *view, char **nb_tmp)
{
	register t_img			*curs;
	register int			i;
	register int			size;

	i = 1;
	size = 10;
	curs = fdf->img;
	while (i++ <= fdf->elem && fdf->elem >= 2)
	{
		*nb_tmp = ft_itoa(i - 1);
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, size, 5, YELLOW,
		*nb_tmp);
		free(*nb_tmp);
		if (*(curs->fract.opt) & (1u << 4))
			mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, size + 15, 5, YELLOW,
				": Mandelbrot");
		else if (*(curs->fract.opt) & (1u << 5))
			mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, size + 15, 5, YELLOW,
				": Julia");
		else if (*(curs->fract.opt) & (1u << 6))
			mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, size + 15, 5, YELLOW,
				": Glynn");
		curs = curs->next;
		size += view->width;
	}
}

static void	help2(t_mlx *fdf, t_img *view, char **nb_tmp)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, view->height, RED,
		"Selected fractal:");
	if (*(view->fract.opt) & (1u << 4))
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 190, view->height, YELLOW,
			"Mandelbrot");
	else if (*(view->fract.opt) & (1u << 5))
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 190, view->height, YELLOW,
			"Julia");
	else if (*(view->fract.opt) & (1u << 6))
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 190, view->height, YELLOW,
			"Glynn");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, view->height + 20, YELLOW,
		"Iteration:");
	*nb_tmp = ft_itoa(view->fract.iter_max);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 150, view->height + 20, YELLOW,
		*nb_tmp);
	free(*nb_tmp);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, view->height + 40, YELLOW,
		"Zoom:");
	*nb_tmp = ft_itoa(view->fract.zoom_x);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 150, view->height + 40, YELLOW,
		*nb_tmp);
	free(*nb_tmp);
}

static void	help3(t_mlx *fdf, t_img *view)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, view->height + 60, YELLOW,
		"Flags:");
	if (*(view->fract.opt) & 1u)
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 150, view->height + 60,
			YELLOW, "g");
	if (*(view->fract.opt) & (1u << 1))
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 160, view->height + 60,
			YELLOW, "I");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 350, view->height, RED,
		"Fractal list:");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 350, view->height + 20, YELLOW,
		"1 - Mandelbrot");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 350, view->height + 40, YELLOW,
		"2 - Julia");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 350, view->height + 60, YELLOW,
		"3 - Glynn");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 600, view->height, RED,
		"Command:");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 1000, view->height + 20, YELLOW,
		"Key G - Full color");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 1000, view->height + 40, YELLOW,
		"Key I - Isometric");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 1000, view->height + 80, YELLOW,
		"Right Click - Lock view");
}

void		put_info_to_window(t_mlx *fdf, t_img *view)
{
	char		*nb_tmp;

	help1(fdf, view, &nb_tmp);
	help2(fdf, view, &nb_tmp);
	help3(fdf, view);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 1000, view->height + 60, YELLOW,
		"Key Q / E - Next / Prev view");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 600, view->height + 20, YELLOW,
		"Key 1 / 3 - Draw fractal from list");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 600, view->height + 40, YELLOW,
		"Arrow Key - Move around");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 600, view->height + 60, YELLOW,
		"Key PgUp / PGDwn - Change iteration");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 600, view->height + 80, YELLOW,
		"Scroll Mouse - Zoom to cursor");
}

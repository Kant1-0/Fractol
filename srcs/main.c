/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 21:40:50 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/15 17:14:11 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	compute_window(t_mlx *fdf)
{
	if (fdf->elem == 3)
	{
		fdf->window_x = 2500;
		fdf->window_y = 800;
	}
	else if (fdf->elem == 2)
	{
		fdf->window_x = 2100;
		fdf->window_y = 900;
	}
	else
	{
		fdf->window_x = 1300;
		fdf->window_y = 1100;
	}
}

static void	init_fract_param(t_fract *fract, t_img *img, t_mlx *fdf)
{
	static int		i = 1;

	if (fdf->elem == 3)
	{
		if (i == 1)
			fract->opt = &fdf->opt1;
		if (i == 2)
			fract->opt = &fdf->opt2;
		if (i == 3)
			fract->opt = &fdf->opt3;
	}
	else if (fdf->elem == 2)
	{
		if (i == 1)
			fract->opt = &fdf->opt2;
		if (i == 2)
			fract->opt = &fdf->opt3;
	}
	else if (fdf->elem == 1)
		fract->opt = &fdf->opt3;
	pick_fractal_param(fract, *img);
	img->param.zoom = img->fract.zoom_x;
	++i;
}

static void	events_hook(t_mlx *fdf)
{
	mlx_key_hook(fdf->win_ptr, key_hook, fdf);
	mlx_mouse_hook(fdf->win_ptr, mouse_hook, fdf);
	mlx_hook(fdf->win_ptr, 6, 1, track_hook, fdf);
	mlx_expose_hook(fdf->win_ptr, expose_hook, fdf);
	mlx_loop(fdf->mlx_ptr);
}

void		init_fdf(t_mlx *fdf)
{
	register int		i;

	fdf->mlx_ptr = mlx_init();
	if (fdf->mlx_ptr == NULL)
		mlx_exit(-1, fdf, "mlx_init failed");
	compute_window(fdf);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->window_x,
		fdf->window_y, API_NAME);
	if (fdf->win_ptr == NULL)
		mlx_exit(-1, fdf, "mlx_new_window failed");
	i = 0;
	fdf->img = NULL;
	while (i < fdf->elem)
	{
		fdf->img = lst_img_new(&fdf->img, fdf->window_x / fdf->elem,
			fdf->window_y, fdf);
		++i;
	}
}

int			main(int ac, char **av)
{
	t_mlx				fdf;
	register t_img		*img_curs;
	register int		i;

	if (ac > 1)
	{
		parse_op(&fdf, av, ac);
		init_fdf(&fdf);
		i = 0;
		img_curs = fdf.img;
		while (i++ < fdf.elem)
		{
			init_fract_param(&(img_curs->fract), img_curs, &fdf);
			draw_fractol(img_curs);
			img_curs = img_curs->next;
		}
		fdf.view = fdf.img;
		events_hook(&fdf);
	}
	else
		mlx_exit(HELP, &fdf, "");
	return (0);
}

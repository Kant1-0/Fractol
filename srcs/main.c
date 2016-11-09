/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 21:40:50 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/09 19:56:59 by qfremeau         ###   ########.fr       */
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

static void	init_fract_param(t_fract *fract, t_img img, t_mlx *fdf)
{
	static		int i = 1;

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
	if (*(fract->opt) & (1u << 4))
	{
		fract->x1 = -1.8;
		fract->y1 = -1.0;
	}
	else if (*(fract->opt) & (1u << 5))
	{
		fract->x1 = -1.3;
		fract->y1 = -1.0;
	}
	if (*(fract->opt) & (1u << 6))
	{
		fract->x1 = -1.3;
		fract->y1 = -1.0;
	}
	fract->iter_max = 50;
	fract->zoom = img.height / 2;
	fract->image_x = img.width;
	fract->image_y = img.height;
	++i;
}

static void parse_op(t_mlx *fdf, char **av, int ac)
{
	int		i;
	int		ret;

	//fdf->opt = NULL;
	fdf->opt1 = 0;
	fdf->opt2 = 0;
	fdf->elem = 0;
	--ac;
	while (ac >= 1)
	{
		if ((ret = ft_strnchr(av[ac][0], FRACT_LST, 3)) != -1)
		{
			++fdf->elem;
			if (fdf->elem == 1)
				fdf->opt3 |=  (1u << (ret + 4));
			else if (fdf->elem == 2)
				fdf->opt2 |=  (1u << (ret + 4));
			else if (fdf->elem == 3)
				fdf->opt1 |=  (1u << (ret + 4));
		}
		else if (av[ac][0] == '-')
		{
			i = 1;
			while (av[ac][i] != '\0')
			{
				if (!av[ac][1])
					mlx_exit(HELP, fdf, "choose at least an option");
				if ((ret = ft_strnchr(av[ac][i], FRACT_OPT, 4)) == -1)
					mlx_exit(HELP, fdf, "illegal option found");
				if (fdf->elem == 0)
				{
					fdf->opt1 |=  (1u << ret);
					fdf->opt2 |=  (1u << ret);
					fdf->opt3 |=  (1u << ret);
				}
				if (fdf->elem == 1)
					fdf->opt3 |=  (1u << ret);
				else if (fdf->elem == 2)
					fdf->opt2 |=  (1u << ret);
				else if (fdf->elem == 3)
					fdf->opt1 |=  (1u << ret);
				++i;
			}
		}
		--ac;
	}
	if (fdf->elem == 0)
		mlx_exit(HELP, fdf, "choose an existing fractal");
	else if (fdf->elem > 3)
		mlx_exit(HELP, fdf, "2 fractals max allowed");
}

void		init_fdf(t_mlx *fdf)
{
	int		i;

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
	while(i < fdf->elem)
	{
		fdf->img = lst_img_new(&fdf->img, fdf->window_x / fdf->elem, 
			fdf->window_y, fdf);
		++i;
	}
}

int			main(int ac, char **av)
{
	t_mlx		fdf;
	t_img		*img_curs;
	int			i;

	if (ac > 1)
	{
		parse_op(&fdf, av, ac);
		init_fdf(&fdf);
		i = 0;
		img_curs = fdf.img;
		while (i < fdf.elem)
		{
			init_fract_param(&(img_curs->fract), *img_curs, &fdf);
			draw_fractol(img_curs);
			img_curs = img_curs->next;
			++i;
		}

		fdf.view = fdf.img;
		mlx_key_hook(fdf.win_ptr, key_hook, &fdf);
		mlx_expose_hook(fdf.win_ptr, expose_hook, &fdf);
		mlx_loop(fdf.mlx_ptr);
	}
	else
		mlx_exit(HELP, &fdf, "");
	return (0);
}

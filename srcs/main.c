/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 21:40:50 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/07 16:42:31 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	compute_window(t_mlx *fdf)
{
	fdf->window_x = 1300;
	fdf->window_y = 1000;
}

static void	init_mov_param(t_mov *mov)
{
	mov->tile = TILE_HALF;
	mov->exp = EXPONENT_Z;
	mov->mov_x = 0;
	mov->mov_y = 0;
}

static void parse_op(t_mlx *fdf, char **av, int ac)
{
	int		i;
	int		nb;

	nb = 1;
	fdf->opt = 0;
	while (nb < ac)
	{
		i = 0;
		if (av[nb][0] == '-' && av[nb][1])
		{
			while (ft_strchr(FRACT_OPT, av[nb][i++]))
				fdf->opt |=  ( 1 << ft_strnchr(av[1][i], FRACT_OPT, 7));
		}
		else if (av[nb][i] >= '1' && av[nb][i] <= '3')
		{
			while (av[nb][i++])
				fdf->opt |=  ( 1 << ft_strnchr(av[1][i], FRACT_OPT, 7));
		}
		else
			mlx_exit(HELP, fdf, "");
		++nb;
	}
}

void		init_fdf(t_mlx *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (fdf->mlx_ptr == NULL)
		mlx_exit(-1, fdf, "mlx_init failed");
	compute_window(fdf);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->window_x,
		fdf->window_y, API_NAME);
	if (fdf->win_ptr == NULL)
		mlx_exit(-1, fdf, "mlx_new_window failed");
	fdf->img = NULL;
	fdf->img = lst_img_new(&fdf->img, fdf->window_x, fdf->window_y);
	fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img->width,
		fdf->img->height);
	if (fdf->img->img_ptr == NULL)
		mlx_exit(-1, fdf, "mlx_new_image failed");
	fdf->img->data = mlx_get_data_addr(fdf->img->img_ptr, &(fdf->img->bpp),
		&(fdf->img->sizeline), &(fdf->img->endian));
}

int			main(int ac, char **av)
{
	t_mlx		fdf;

	if (ac > 1)
	{
		parse_op(&fdf, av, ac);
		init_fdf(&fdf);
		init_mov_param(&(fdf.mov));
		draw_fractol(&fdf, *av[1]);
		mlx_key_hook(fdf.win_ptr, key_hook, &fdf);
		mlx_expose_hook(fdf.win_ptr, expose_hook, &fdf);
		mlx_loop(fdf.mlx_ptr);
	}
	else
		mlx_exit(HELP, &fdf, "");
	return (0);
}

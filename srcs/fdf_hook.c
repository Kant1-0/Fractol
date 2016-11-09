/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 11:59:38 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/09 20:52:38 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_info_to_window(t_mlx *fdf, t_img *view)
{
	t_img	*curs;
	int		i;
	int		size;

	i = 1;
	size = 10;
	curs = fdf->img;
	while (i <= fdf->elem && fdf->elem >= 2)
	{
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, size, 5, YELLOW,
		ft_itoa(i));
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
		++i;
	}
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
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 150, view->height + 20, YELLOW,
		ft_itoa(view->fract.iter_max));
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, view->height + 40, YELLOW,
		"Zoom:");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 150, view->height + 40, YELLOW,
		ft_itoa(view->fract.zoom));
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, view->height + 60, YELLOW,
		"Flags:");
	if (*(view->fract.opt) & 1u)
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 150, view->height + 60,
			YELLOW, "g");
	else if (*(view->fract.opt) & (1u << 1))
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
		"Key Num5 - Reset all views");
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

void	change_param(t_mlx *fdf, int keycode, t_img *view)
{
	clear_image(view);
	if (keycode == KEY_G)
		*(view->fract.opt) = *(view->fract.opt) ^ 1u;
	if (keycode == KEY_I)
		*(view->fract.opt) = *(view->fract.opt) ^ (1u << 1);
	if (keycode == KEY_1)
	{
		*(view->fract.opt) = *(view->fract.opt) | (1u << 4);
		*(view->fract.opt) = *(view->fract.opt) & ~(1u << 5);
		*(view->fract.opt) = *(view->fract.opt) & ~(1u << 6);
	}
	if (keycode == KEY_2)
	{
		*(view->fract.opt) = *(view->fract.opt) & ~(1u << 4);
		*(view->fract.opt) = *(view->fract.opt) | (1u << 5);
		*(view->fract.opt) = *(view->fract.opt) & ~(1u << 6);
	}
	if (keycode == KEY_3)
	{
		*(view->fract.opt) = *(view->fract.opt) & ~(1u << 4);
		*(view->fract.opt) = *(view->fract.opt) & ~(1u << 5);
		*(view->fract.opt) = *(view->fract.opt) | (1u << 6);
	}
	draw_fractol(view);
	expose_hook(fdf);
}	

int		expose_hook(void *param)
{
	t_mlx		*fdf;
	t_img		*curs;
	int			size;

	fdf = (t_mlx*)param;
	curs = fdf->img;
	size = 0;
	while (curs != NULL)
	{
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
			curs->img_ptr, size, 0);
		size += fdf->window_x / fdf->elem;
		curs = curs->next;
	}
	put_info_to_window(fdf, fdf->view);
	return (1);
}

int		key_hook(int keycode, void *param)
{
	t_mlx		*fdf;

	fdf = (t_mlx*)param;
	printf("0x%04X\n", keycode);
	if (keycode == KEY_G || keycode == KEY_I || 
		(keycode >= KEY_1 && keycode <= KEY_3))
		change_param(fdf, keycode, fdf->view);
	if (keycode == KEY_Q || keycode == KEY_E)
		select_map(fdf, keycode, &fdf->view);
	if (keycode >= KEY_LEFT && keycode <= KEY_UP)
		move_map(fdf, keycode, fdf->view);
	if (keycode == KEY_PLUS || keycode == KEY_MINUS ||
		keycode == KEY_PG_UP || keycode == KEY_PG_DOWN)
		zoom_map(fdf, keycode, fdf->view);
	/*if (keycode == KEY_NUM_5)
		reset_map(fdf, keycode);*/
	if (keycode == KEY_ESC)
		mlx_exit(1, param, "");
	return (1);
}

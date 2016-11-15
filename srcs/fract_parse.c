/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 15:40:09 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/15 15:16:38 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	print_opt(int ret)
{
	if (ret == 2)
		print_list();
	else if (ret == 3)
		print_help();
}

static void	parser1(t_mlx *fdf, int ret)
{
	++fdf->elem;
	if (fdf->elem == 1)
		fdf->opt3 |= (1u << (ret + 4));
	else if (fdf->elem == 2)
		fdf->opt2 |= (1u << (ret + 4));
	else if (fdf->elem == 3)
		fdf->opt1 |= (1u << (ret + 4));
}

static void	parser2(t_mlx *fdf, char **av, int ac, int ret)
{
	register int		i;

	i = 1;
	while (av[ac][i] != '\0')
	{
		if (!av[ac][1])
			mlx_exit(HELP, fdf, "choose at least an option");
		if ((ret = ft_strnchr(av[ac][i], FRACT_OPT, 4)) == -1)
			mlx_exit(HELP, fdf, "illegal option found");
		print_opt(ret);
		if (fdf->elem == 0)
		{
			fdf->opt1 |= (1u << ret);
			fdf->opt2 |= (1u << ret);
			fdf->opt3 |= (1u << ret);
		}
		if (fdf->elem == 1)
			fdf->opt3 |= (1u << ret);
		else if (fdf->elem == 2)
			fdf->opt2 |= (1u << ret);
		else if (fdf->elem == 3)
			fdf->opt1 |= (1u << ret);
		++i;
	}
}

void		parse_op(t_mlx *fdf, char **av, int ac)
{
	int		ret;

	fdf->opt1 = 0;
	fdf->opt2 = 0;
	fdf->elem = 0;
	--ac;
	while (ac >= 1)
	{
		if ((ret = ft_strnchr(av[ac][0], FRACT_LST, 3)) != -1 &&
			!av[ac][1])
			parser1(fdf, ret);
		else if (av[ac][0] == '-')
			parser2(fdf, av, ac, ret);
		else
			mlx_exit(HELP, fdf, "wrong fractal selected");
		--ac;
	}
	if (fdf->elem == 0 && ((fdf->opt3 & (1u << 2)) || (fdf->opt3 & (1u << 3))))
		mlx_exit(0, fdf, "");
	else if (fdf->elem == 0)
		mlx_exit(HELP, fdf, "choose an existing fractal");
	else if (fdf->elem > 3)
		mlx_exit(HELP, fdf, "3 fractals max allowed");
}

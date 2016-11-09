/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 14:45:59 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/09 18:58:57 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_img		*lst_img_new(t_img **img, int width, int height, t_mlx *fdf)
{
	t_img		*new;

	new = NULL;
	new = (t_img*)malloc(sizeof(t_img));
	if (new == NULL)
		return (NULL);
	new->width = width;
	new->height = height - 100;
	new->img_ptr = mlx_new_image(fdf->mlx_ptr, width, height);
	if (new->img_ptr == NULL)
			mlx_exit(-1, fdf, "mlx_new_image failed");
	new->data = mlx_get_data_addr(new->img_ptr, &(new->bpp),
			&(new->sizeline), &(new->endian));
	new->next = NULL;
	if (*img == NULL)
		return (new);
	else
		new->next = *img;
	return (new);
}

t_coord	*lst_coord_new(t_coord **coord, int x, int y)
{
	t_coord		*new;
	t_coord		*curs;

	new = NULL;
	new = (t_coord*)malloc(sizeof(t_coord));
	if (new == NULL)
		return (NULL);
	new->pixel[0] = x;
	new->pixel[1] = y;
	new->next = NULL;
	if (*coord == NULL)
		return (new);
	else
	{
		curs = *coord;
		while (curs->next != NULL)
			curs = curs->next;
		curs->next = new;
	}
	return (new);
}

/*t_opt		*lst_opt_new(t_opt **opt, int width, int height, t_mlx *fdf)
{
	t_img		*new;
	t_img		*curs;

	new = NULL;
	new = (t_img*)malloc(sizeof(t_img));
	if (new == NULL)
		return (NULL);
	new->width = width;
	new->height = height;
	new->img_ptr = mlx_new_image(fdf->mlx_ptr, width, height);
	if (new->img_ptr == NULL)
			mlx_exit(-1, fdf, "mlx_new_image failed");
	new->data = mlx_get_data_addr(new->img_ptr, &(new->bpp),
			&(new->sizeline), &(new->endian));
	new->next = NULL;
	if (*img == NULL)
		return (new);
	else
	{
		curs = *img;
		while (curs->next != NULL)
			curs = curs->next;
		curs->next = new;
	}
	return (*img);
}*/

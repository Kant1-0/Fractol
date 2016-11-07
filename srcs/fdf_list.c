/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 14:45:59 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/07 14:19:59 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_img		*lst_img_new(t_img **img, int width, int height)
{
	t_img		*new;
	t_img		*curs;

	new = NULL;
	new = (t_img*)malloc(sizeof(t_img));
	if (new == NULL)
		return (NULL);
	new->width = width;
	new->height = height;
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
}

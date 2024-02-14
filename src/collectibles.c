/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:27:01 by rhorvath          #+#    #+#             */
/*   Updated: 2024/02/12 23:16:43 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_colls2(t_cont *cont)
{
	mlx_image_t	*img;
	int			i;
	int			x;
	int			y;

	i = -1;
	while (++i < cont->c_n)
	{
		img = cont->colls->coll[i];
		x = cont->colls->x[i] * 64;
		y = cont->colls->y[i] * 64;
		mlx_image_to_window(cont->mlx, img, x, y);
	}
}

void	ft_coll_alloc(t_cont *cont)
{
	xpm_t		*xpm;
	mlx_image_t	*img;
	int			i;

	cont->colls = malloc(sizeof(t_coll));
	cont->colls->x = malloc(sizeof(int *) * cont->c_n);
	cont->colls->y = malloc(sizeof(int *) * cont->c_n);
	cont->colls->coll = malloc(sizeof(mlx_image_t *) * cont->c_n);
	i = -1;
	while (++i < cont->c_n)
	{
		xpm = mlx_load_xpm42("textures/chip_64.xpm42");
		img = mlx_texture_to_image(cont->mlx, &xpm->texture);
		cont->colls->coll[i] = img;
		mlx_delete_xpm42(xpm);
	}
}

void	ft_colls(t_cont *cont, char **map)
{
	int	i;
	int	j;
	int	x;

	ft_coll_alloc(cont);
	i = -1;
	x = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'C')
			{
				cont->colls->x[x] = j;
				cont->colls->y[x] = i;
				x++;
			}
		}
	}
	ft_colls2(cont);
}

void	ft_remove_colls(t_cont *cont)
{
	int	i;

	i = -1;
	while (++i < cont->all)
	{
		if (cont->player_y == cont->colls->y[i]
			&& cont->player_x == cont->colls->x[i])
		{
			mlx_delete_image(cont->mlx, cont->colls->coll[i]);
			cont->c_n--;
		}
	}
}

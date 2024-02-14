/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:04:52 by rhorvath          #+#    #+#             */
/*   Updated: 2024/02/12 21:25:54 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_rebuild_player(t_cont *cont)
{
	xpm_t	*xpm;

	mlx_delete_image(cont->mlx, cont->player);
	xpm = mlx_load_xpm42("textures/player_64.xpm42");
	cont->player = mlx_texture_to_image(cont->mlx, &xpm->texture);
	mlx_delete_xpm42(xpm);
}

void	ft_build3(t_cont *cont, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'E')
				mlx_image_to_window(cont->mlx, cont->exit, j * 64, i * 64);
			else if (map[i][j] == 'P')
			{
				mlx_image_to_window(cont->mlx, cont->player, j * 64, i * 64);
				cont->player_x = j;
				cont->player_y = i;
			}
		}
	}
}

void	ft_build2(t_cont *cont, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '1')
				mlx_image_to_window(cont->mlx, cont->wall, j * 64, i * 64);
			else
				mlx_image_to_window(cont->mlx, cont->floor, j * 64, i * 64);
		}
	}
	ft_build3(cont, map);
}

void	ft_build(t_cont *cont, char **map)
{
	xpm_t	*xpm;

	xpm = mlx_load_xpm42("textures/rustedwall_64.xpm42");
	cont->wall = mlx_texture_to_image(cont->mlx, &xpm->texture);
	mlx_delete_xpm42(xpm);
	xpm = mlx_load_xpm42("textures/floor_64.xpm42");
	cont->floor = mlx_texture_to_image(cont->mlx, &xpm->texture);
	mlx_delete_xpm42(xpm);
	xpm = mlx_load_xpm42("textures/door_64.xpm42");
	cont->exit = mlx_texture_to_image(cont->mlx, &xpm->texture);
	mlx_delete_xpm42(xpm);
	xpm = mlx_load_xpm42("textures/player_64.xpm42");
	cont->player = mlx_texture_to_image(cont->mlx, &xpm->texture);
	mlx_delete_xpm42(xpm);
	ft_build2(cont, map);
}

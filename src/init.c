/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:45:23 by rhorvath          #+#    #+#             */
/*   Updated: 2024/01/30 06:55:03 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	build3(t_cont *cont, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
				mlx_image_to_window(cont->mlx, cont->exit, j * 64, i * 64);
			else if (map[i][j] == 'P')
			{
				mlx_image_to_window(cont->mlx, cont->player, j * 64, i * 64);
				cont->player_x = j;
				cont->player_y = i;
			}
			j++;
		}
		i++;
	}
}

void	build2(t_cont *cont, char **map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				mlx_image_to_window(cont->mlx, cont->wall, j * 64, i * 64);
			else
				mlx_image_to_window(cont->mlx, cont->floor, j * 64, i * 64);
			j++;
		}
		i++;
	}
	build3(cont, map);
}

void	remove_c(t_cont *cont)
{
	int i;

	i = 0;
	while (i < cont->all)
	{
		if (cont->player_y == cont->collectibles->y[i] && cont->player_x == cont->collectibles->x[i])
		{
			mlx_delete_image(cont->mlx, cont->collectibles->coll[i]);
			cont->c_n--;
		}
		i++;
	}
}

void	rebuild_p(t_cont *cont)
{
	xpm_t	*xpm;
	
	mlx_delete_image(cont->mlx, cont->player);
	xpm = mlx_load_xpm42("textures/player_64.xpm42");
	cont->player = mlx_texture_to_image(cont->mlx, &xpm->texture);
	mlx_delete_xpm42(xpm);
}

void	build(t_cont *cont, char **map)
{
	xpm_t	*xpm;
	int		i;
	int		j;

	i = 0;
	j = 0;
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
	build2(cont, map);
}

void	sz(char **map, t_cont *cont)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
		;
	j = -1;
	while (map[0][++j])
		;
	j--;
	cont->p_length = i * 64;
	cont->p_width = j * 64;
	cont->c_n = 0;
	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				cont->c_n++;
			j++;
		}
	}
	cont->c_n = cont->all;
}


void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_cont *cont;

	cont = (t_cont *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		free_bs(cont);
		mlx_terminate(cont->mlx);
	}
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_up(cont);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_left(cont);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_down(cont);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_right(cont);
}
void	coll_alloc(t_cont *cont)
{
	xpm_t		*xpm;
	mlx_image_t	*img;
	int			i;

	i = 0;
	cont->collectibles = malloc(sizeof(t_coll));
	cont->collectibles->x = malloc(sizeof(int *) * cont->c_n);
	cont->collectibles->y = malloc(sizeof(int *) * cont->c_n);
	cont->collectibles->coll = malloc(sizeof(mlx_image_t *) * cont->c_n);
	while (i < cont->c_n)
	{
		xpm = mlx_load_xpm42("textures/chip_64.xpm42");
		img = mlx_texture_to_image(cont->mlx, &xpm->texture);
		cont->collectibles->coll[i] = img;
		mlx_delete_xpm42(xpm);
		i++;
	}
}

void	collectibles2(t_cont *cont, char **map)
{
	mlx_image_t	*img;
	int			i;
	int			x;
	int			y;

	i = 0;
	while (i < cont->c_n)
	{
		img = cont->collectibles->coll[i];
		x = cont->collectibles->x[i] * 64;
		y = cont->collectibles->y[i] * 64;
		mlx_image_to_window(cont->mlx, img, x, y);
		i++;
	}
}

void	collectibles(t_cont *cont, char **map)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	x = 0;
	coll_alloc(cont);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
			{
				cont->collectibles->x[x] = j;
				cont->collectibles->y[x] = i;
				x++;
			}
			j++;
		}
		i++;
	}
	collectibles2(cont, map);
}

void	free_bs(t_cont *cont)
{
	free(cont->collectibles->x);
	free(cont->collectibles->y);
	free(cont->collectibles->coll);
	free(cont->collectibles);
	free_map(cont->map);
	free(*cont);
}

int	init(char **map)
{
	t_cont	cont;

	cont = malloc(sizeof(t_cont));
	sz(map, &cont);
	cont.moves = 0;
	cont.map = map;
	cont.mlx = mlx_init(cont.p_width, cont.p_length, "so_long", true);
	cont.img = mlx_new_image(cont.mlx, cont.p_width, cont.p_length);
	mlx_image_to_window(cont.mlx, cont.img, 0, 0);
	build(&cont, map);
	collectibles(&cont, map);
	mlx_key_hook(cont.mlx, &my_keyhook, &cont);
	mlx_loop(cont.mlx);
	free_bs(&cont);
	mlx_terminate(cont.mlx);
	return (0);
}

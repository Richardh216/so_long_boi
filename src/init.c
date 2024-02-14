/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:43:39 by rhorvath          #+#    #+#             */
/*   Updated: 2024/02/12 23:25:08 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_cont	*cont;

	cont = (t_cont *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(cont->mlx);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		ft_move_up(cont);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		ft_move_left(cont);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		ft_move_down(cont);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		ft_move_right(cont);
}

void	ft_size(char **map, t_cont *cont)
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
		j = -1;
		while (map[i][++j])
			if (map[i][j] == 'C')
				cont->c_n++;
	}
	cont->all = cont->c_n;
}

int	init(char **map, t_cont *cont)
{
	ft_size(map, cont);
	cont->moves = 0;
	cont->mlx = mlx_init(cont->p_width, cont->p_length, "so_long", true);
	cont->img = mlx_new_image(cont->mlx, cont->p_width, cont->p_length);
	mlx_image_to_window(cont->mlx, cont->img, 0, 0);
	ft_build(cont, map);
	ft_colls(cont, map);
	mlx_key_hook(cont->mlx, &my_keyhook, (void *)cont);
	mlx_loop(cont->mlx);
	mlx_terminate(cont->mlx);
	return (0);
}

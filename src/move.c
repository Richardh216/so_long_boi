/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 03:20:41 by rhorvath          #+#    #+#             */
/*   Updated: 2024/01/30 06:54:57 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	move_up(t_cont *cont)
{
	cont->coords_x = cont->player_x;
	cont->coords_y = cont->player_y;
	if (cont->map[cont->player_y - 1][cont->player_x] != '1' && cont->map[cont->player_y - 1][cont->player_x] != 'E')
	{
		cont->map[cont->player_y][cont->player_x] = '0';
		cont->player_y -= 1;
		if (cont->map[cont->player_y][cont->player_x] == 'C')
			remove_c(cont);
		cont->map[cont->player_y][cont->player_x] = 'P';
		rebuild_p(cont);
		mlx_image_to_window(cont->mlx, cont->player, cont->player_x * 64, cont->player_y * 64);
		print_moves(cont->moves);
	}
	if (cont->map[cont->coords_y - 1][cont->coords_x] == 'E' && !cont->c_n)
	{
		printf("YOU WIN!\n");
		mlx_terminate(cont->mlx);
	}
}

void	move_down(t_cont *cont)
{
	cont->coords_x = cont->player_x;
	cont->coords_y = cont->player_y;
	if (cont->map[cont->player_y + 1][cont->player_x] != '1' && cont->map[cont->player_y + 1][cont->player_x] != 'E')
	{
		cont->map[cont->player_y][cont->player_x] = '0';
		cont->player_y += 1;
		if (cont->map[cont->player_y][cont->player_x] == 'C')
			remove_c(cont);
		cont->map[cont->player_y][cont->player_x] = 'P';
		rebuild_p(cont);
		mlx_image_to_window(cont->mlx, cont->player, cont->player_x * 64, cont->player_y * 64);
		print_moves(cont->moves);
	}
	if (cont->map[cont->coords_y + 1][cont->coords_x] == 'E' && !cont->c_n)
	{
		printf("YOU WIN!\n");
		mlx_terminate(cont->mlx);
	}
}

void	move_left(t_cont *cont)
{
	cont->coords_x = cont->player_x;
	cont->coords_y = cont->player_y;
	if (cont->map[cont->player_y][cont->player_x - 1] != '1' && cont->map[cont->player_y][cont->player_x - 1] != 'E')
	{
		cont->map[cont->player_y][cont->player_x] = '0';
		cont->player_x -= 1;
		if (cont->map[cont->player_y][cont->player_x] == 'C')
			remove_c(cont);
		cont->map[cont->player_y][cont->player_x] = 'P';
		rebuild_p(cont);
		mlx_image_to_window(cont->mlx, cont->player, cont->player_x * 64, cont->player_y * 64);
		print_moves(cont->moves);
	}
	if (cont->map[cont->coords_y][cont->coords_x - 1] == 'E' && !cont->c_n)
	{
		printf("YOU WIN!\n");
		mlx_terminate(cont->mlx);
	}
}

void	move_right(t_cont *cont)
{
	cont->coords_x = cont->player_x;
	cont->coords_y = cont->player_y;
	if (cont->map[cont->player_y][cont->player_x + 1] != '1' && cont->map[cont->player_y][cont->player_x + 1] != 'E')
	{
		cont->map[cont->player_y][cont->player_x] = '0';
		cont->player_x += 1;
		if (cont->map[cont->player_y][cont->player_x] == 'C')
			remove_c(cont);
		cont->map[cont->player_y][cont->player_x] = 'P';
		rebuild_p(cont);
		mlx_image_to_window(cont->mlx, cont->player, cont->player_x * 64, cont->player_y * 64);
		print_moves(cont->moves);
	}
	if (cont->map[cont->coords_y][cont->coords_x + 1] == 'E' && !cont->c_n)
	{
		printf("YOU WIN!\n");
		mlx_terminate(cont->mlx);
	}
}

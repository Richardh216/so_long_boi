/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:04:58 by rhorvath          #+#    #+#             */
/*   Updated: 2024/02/12 23:26:09 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_move_up(t_cont *cont)
{
	int	x;
	int	y;

	x = cont->player_x;
	y = cont->player_y;
	cont->coords_x = cont->player_x;
	cont->coords_y = cont->player_y;
	if (cont->map[y - 1][x] != '1' && cont->map[y - 1][x] != 'E')
	{
		cont->map[y][x] = '0';
		cont->player_y--;
		y--;
		if (cont->map[y][x] == 'C')
			ft_remove_colls(cont);
		cont->map[y][x] = 'P';
		ft_rebuild_player(cont);
		mlx_image_to_window(cont->mlx, cont->player, x * 64, y * 64);
		cont->moves++;
		ft_print_moves(cont->moves);
	}
	if (cont->map[cont->coords_y - 1][cont->coords_x] == 'E' && !cont->c_n)
	{
		write(1, "YOU WIN!\n", 10);
		mlx_close_window(cont->mlx);
	}
}

void	ft_move_down(t_cont *cont)
{
	int	x;
	int	y;

	x = cont->player_x;
	y = cont->player_y;
	cont->coords_x = cont->player_x;
	cont->coords_y = cont->player_y;
	if (cont->map[y + 1][x] != '1' && cont->map[y + 1][x] != 'E')
	{
		cont->map[y][x] = '0';
		cont->player_y++;
		y++;
		if (cont->map[y][x] == 'C')
			ft_remove_colls(cont);
		cont->map[y][x] = 'P';
		ft_rebuild_player(cont);
		mlx_image_to_window(cont->mlx, cont->player, x * 64, y * 64);
		cont->moves++;
		ft_print_moves(cont->moves);
	}
	if (cont->map[cont->coords_y + 1][cont->coords_x] == 'E' && !cont->c_n)
	{
		write(1, "YOU WIN!\n", 10);
		mlx_close_window(cont->mlx);
	}
}

void	ft_move_left(t_cont *cont)
{
	int	x;
	int	y;

	x = cont->player_x;
	y = cont->player_y;
	cont->coords_x = cont->player_x;
	cont->coords_y = cont->player_y;
	if (cont->map[y][x - 1] != '1' && cont->map[y][x - 1] != 'E')
	{
		cont->map[y][x] = '0';
		cont->player_x--;
		x--;
		if (cont->map[y][x] == 'C')
			ft_remove_colls(cont);
		cont->map[y][x] = 'P';
		ft_rebuild_player(cont);
		mlx_image_to_window(cont->mlx, cont->player, x * 64, y * 64);
		cont->moves++;
		ft_print_moves(cont->moves);
	}
	if (cont->map[cont->coords_y][cont->coords_x - 1] == 'E' && !cont->c_n)
	{
		write(1, "YOU WIN!\n", 10);
		mlx_close_window(cont->mlx);
	}
}

void	ft_move_right(t_cont *cont)
{
	int	x;
	int	y;

	x = cont->player_x;
	y = cont->player_y;
	cont->coords_x = cont->player_x;
	cont->coords_y = cont->player_y;
	if (cont->map[y][x + 1] != '1' && cont->map[y][x + 1] != 'E')
	{
		cont->map[y][x] = '0';
		cont->player_x++;
		x++;
		if (cont->map[y][x] == 'C')
			ft_remove_colls(cont);
		cont->map[y][x] = 'P';
		ft_rebuild_player(cont);
		mlx_image_to_window(cont->mlx, cont->player, x * 64, y * 64);
		cont->moves++;
		ft_print_moves(cont->moves);
	}
	if (cont->map[cont->coords_y][cont->coords_x + 1] == 'E' && !cont->c_n)
	{
		write(1, "YOU WIN!\n", 10);
		mlx_close_window(cont->mlx);
	}
}

void	ft_print_moves(int moves)
{
	char	buffer[20];
	int		len;
	int		tmp;
	char	temp;
	int		i;

	tmp = moves;
	len = 0;
	while (tmp != 0)
	{
		buffer[len++] = tmp % 10 + '0';
		tmp /= 10;
	}
	i = -1;
	while (++i < len / 2)
	{
		temp = buffer[i];
		buffer[i] = buffer[len - i - 1];
		buffer[len - i - 1] = temp;
	}
	buffer[len++] = '\n';
	write (1, "Number of Moves : ", 19);
	write (1, buffer, len);
}

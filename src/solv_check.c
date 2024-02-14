/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solv_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:05:17 by rhorvath          #+#    #+#             */
/*   Updated: 2024/02/13 02:57:14 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	ft_check_ec(char **map)
{
	int	i;
	int	flagp;
	int	flag_e_c[2];

	flagp = 0;
	i = -1;
	flag_e_c[0] = 0;
	flag_e_c[1] = 0;
	while (map[++i])
	{
		if (!ec_process(map, &i, &flagp, flag_e_c))
			return (0);
	}
	if (flag_e_c[0] == 1 && flag_e_c[1] == 1 && flagp == 1)
		return (1);
	return (0);
}

void	ft_flood_fill(char **map, int p1, int p2)
{
	if (map[p1][p2] == 'F' || map[p1][p2] == '1')
		return ;
	map[p1][p2] = 'F';
	ft_flood_fill(map, p1 - 1, p2);
	ft_flood_fill(map, p1, p2 - 1);
	ft_flood_fill(map, p1 + 1, p2);
	ft_flood_fill(map, p1, p2 + 1);
}

void	ft_p_pos(char **tmp, int *p)
{
	int	i;
	int	j;

	i = -1;
	while (tmp[++i])
	{
		j = -1;
		while (tmp[i][++j])
		{
			if (tmp[i][j] == 'P')
			{
				p[0] = i;
				p[1] = j;
				break ;
			}
		}
	}
}

char	**map_copy(char **map)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	while (map[i])
		i++;
	res = (char **)malloc(sizeof(char *) * i + 1);
	res[i] = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		res[i] = malloc(sizeof(char) * (ft_strlen(map[i])) + 1);
		while (map[i][++j])
			res[i][j] = map[i][j];
		res[i][j] = '\0';
	}
	return (res);
}

int	ft_solvable(char **map)
{
	int		i;
	char	**tmp;
	int		*p;

	i = 0;
	tmp = map_copy(map);
	p = malloc(sizeof(int) * 2);
	ft_p_pos(tmp, p);
	ft_flood_fill(tmp, p[0], p[1]);
	free(p);
	ft_free_map(tmp);
	return (0);
}

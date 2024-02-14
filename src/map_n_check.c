/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_n_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:55:51 by rhorvath          #+#    #+#             */
/*   Updated: 2024/02/13 02:54:07 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	ft_check_borders(char **map, int map_size)
{
	int	i;
	int	len;
	int	j;

	j = -1;
	i = -1;
	len = ft_strlen(map[0]);
	while (map[++i])
		if (map[i][0] != '1')
			return (1);
	while (map[++j][len - 1] && j < map_size - 1)
		if (map[j][len - 2] != '1')
			return (1);
	return (0);
}

int	ft_check_fnl(char **map, int map_size)
{
	int	i;
	int	len;

	len = ft_strlen(map[0]);
	i = -1;
	while (map[0][++i] && i < len - 1)
		if (map[0][i] != '1')
			return (1);
	i = -1;
	while (map[map_size - 1][++i])
		if (map[map_size - 1][i] != '1')
			return (1);
	if (ft_check_borders(map, map_size))
		return (1);
	return (0);
}

int	ft_check_map(char **map, int map_size)
{
	int	i;

	i = -1;
	while (++i < map_size - 2)
		if (ft_strlen(map[i]) != ft_strlen(map[i + 1]))
			return (1);
	if ((ft_strlen(map[i]) - 1) != ft_strlen(map[i + 1]))
		return (1);
	if (ft_check_fnl(map, map_size))
		return (1);
	if (!ft_check_ec(map))
		return (1);
	return (0);
}

int	get_map_size(char *map_path)
{
	char	*map;
	int		size;
	int		fd;

	fd = open(map_path, O_RDONLY);
	size = 0;
	while (1)
	{
		map = get_next_line(fd);
		if (map && ++size > -1)
			free(map);
		else
			break ;
	}
	close(fd);
	return (size);
}

char	**get_map(char *str)
{
	char	*map_path;
	int		fd;
	char	**map;
	int		map_size;
	int		i;

	i = -1;
	map_size = 0;
	map_path = ft_strjoin("map/", str);
	map_size = get_map_size(map_path);
	fd = open(map_path, O_RDONLY);
	free(map_path);
	map = (char **)malloc(sizeof(char *) * (map_size + 1));
	while (++i < map_size)
		map[i] = get_next_line(fd);
	map[i] = 0;
	close(fd);
	if (ft_check_map(map, map_size))
		return (NULL);
	return (map);
}

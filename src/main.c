/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:38:51 by rhorvath          #+#    #+#             */
/*   Updated: 2024/01/29 23:19:24 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include <stdio.h>

// int	fill(char **map, t_point size, t_point cur, char to_check)
// {
// 	int	counter;

// 	counter = 0;
// 	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x)
// 		return (0);
// 	if (map[cur.y][cur.x] == to_check)
// 		counter++;
// 	fill(map, size, (t_point){cur.x - 1, cur.y}, to_check);
// 	fill(map, size, (t_point){cur.x + 1, cur.y}, to_check);
// 	fill(map, size, (t_point){cur.x, cur.y - 1}, to_check);
// 	fill(map, size, (t_point){cur.x, cur.y + 1}, to_check);
// 	return (counter);
// }

// int	ft_flood_check(char **map, t_point size, t_point begin)
// {
// 	char	c;
// 	char	d;
// 	char	e;

// 	c = 'C';
// 	d = 'P';
// 	e = 'E';
// 	if (fill(map, size, begin, c) == 0)
// 		return (0);
// 	else if (fill(map, size, begin, d) == 0)
// 		return (0);
// 	else if (fill(map, size, begin, e) == 0)
// 		return (0);
// 	return (1);
// }

int	ft_check_borders(char **map, int map_size)
{
	int	i;
	int	len;
	int	j;

	j = -1;
	len = ft_strlen(map[0]);
	i = -1;
	while (map[++i])
		if (map[i][0] != '1')
			return (0);
	while (map[++j][len - 1] && j < map_size - 1)
		if (map[j][len - 2] != '1')
			return (0);
	return (1);
}

int	ft_check_fnl(char **map, int map_size)
{
	int	i;
	int	len;

	len = ft_strlen(map[0]);
	i = -1;
	while (map[0][++i] && i < len - 1)
		if (map[0][i] != '1')
			return (0);
	i = -1;
	while (map[map_size - 1][++i])
		if (map[map_size - 1][i] != '1')
			return (0);
	if (ft_check_borders(map, map_size) == 0)
		return (0);
	return (1);
}

int	ft_check_map(char **map, int map_size)
{
	// int	i;
	int	j;

	j = 0;
	while (j < map_size - 2)
	{
		if (ft_strlen(map[j]) != ft_strlen(map[j + 1]))
			return (0);
		j++;
	}
	// printf("HR%d\n", j);
	if (((ft_strlen(map[j]) - 1) != ft_strlen(map[j + 1])))
		return (0);
	if (ft_check_fnl(map, map_size) == 0)
		return (0);
	return (1);
}

void	free_map(char **map)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (map[j])
	{
		free(map[j]);
		j++;
	}
	free(map);
	map = NULL;
}

void	ft_error(char *str, int flag)
{
	int	i;

	i = -1;
	if (flag == 0)
	{
		while (str[++i])
			write(1, &str[i], 1);
		write(1, "\n", 1);
	}
	// else if (flag == 1)
	// {
	// 	free shit
	// }
}

int	name_check(char *name)
{
	int		len;
	char	*file;

	file = ".ber";
	len = ft_strlen(name);
	if (ft_strncmp(file, name + len - 4, 5) != 0)
		return (-1);
	else
		return (0);
}

int	get_map_size(char *map_path)
{
	char *map;
	int	size;
	int fd;

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
	char	*tmp;
	char	*map_path;
	int		fd;
	char	**map;
	int		map_size;
	int		i;

	i = -1;
	map_size = 0;
	tmp = ft_strdup("map/");
	map_path = ft_strjoin(tmp, str);
	free(tmp);
	map_size = get_map_size(map_path);
	fd = open(map_path, O_RDONLY);
	free(map_path);
	map = (char **)malloc(sizeof(char *) * map_size + 1);
	while (++i < map_size)
		map[i] = get_next_line(fd);
	map[i] = 0;
	close(fd);
	if (ft_check_map(map, map_size) == 0)
		return (NULL);
	return (map);
}

void	leaks()
{
	system("leaks a.out");
}

int	main(int argc, char **argv)
{
	char	**map;
	// atexit(leaks);
	if (argc != 2)
	{
		ft_error("wrong input", 0);
		return (0);
	}
	if (name_check(argv[1]) == -1)
	{
		ft_error("wrong input", 0);
		return (0);
	}
	map = get_map(argv[1]);
	if (!map)
	{
		ft_error("invalid map", 0);
		// free_map(map);
	}
	if (init(map) == -1)
		ft_error("init failed", 0);
	return (0);
}

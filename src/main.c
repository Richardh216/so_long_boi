/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:38:51 by rhorvath          #+#    #+#             */
/*   Updated: 2024/02/10 17:21:13 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include <stdio.h>

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
	i = 0;
	while (map[i])
	{
		j = 0;
		res[i] = malloc(sizeof(char) * (ft_strlen(map[i])) + 1);
		while (map[i][j])
		{
			res[i][j] = map[i][j];
			j++;
		}
		res[i][j] = '\0';
		i++;
	}
	return (res);
}


void	p_pos(char **tmp, int *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
		{
			if (tmp[i][j] == 'P')
			{
				p[0] = i;
				p[1] = j;
				break ;
			}
			j++;
		}
		i++;
	}
}

void	flood_fill(char **map, int	p1, int p2)
{
	if (map[p1][p2] == 'F' || map[p1][p2] == '1')
		return ;
	map[p1][p2] = 'F';
	flood_fill(map, p1 - 1, p2);
	flood_fill(map, p1, p2 + 1);
	flood_fill(map, p1 + 1, p2);
	flood_fill(map, p1, p2 - 1);
}

int	check(char **map)
{
	int i;
	int j;
	int	f;

	f = 1;
	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C' || map[i][j] == 'E')
				f = 0;
			j++;
		}
		i++;
	}
	return (f);
}

int	solvable(char **map)
{
	int	i;
	char	**tmp;
	int		*p;

	i = 0;
	tmp = map_copy(map);
	p = malloc(sizeof(int) * 2);
	p_pos(tmp, p);
	flood_fill(tmp, p[0], p[1]);
	free(p);
	if (check(tmp) == 0)
	{
		free_map(tmp);
		return (1);
	}
	free_map(tmp);
	return (0);
}

int	ft_check_map(char **map, int map_size)
{
	int	j;

	j = 0;
	while (j < map_size - 2)
	{
		if (ft_strlen(map[j]) != ft_strlen(map[j + 1]))
			return (0);
		j++;
	}
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
	system("leaks so_long");
}

int	main(int argc, char **argv)
{
	t_cont	cont;

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
	cont.map = get_map(argv[1]);
	if (cont.map == NULL)
	{
		ft_error("invalid map", 0);
		return (0);
	}
	if (solvable(cont.map) == 1)
	{
		free_map(cont.map);
		printf("unsovable map!\n");
		return (0);
	}
	if (init(cont.map, &cont) == -1)
		ft_error("init wrong", 0);
	free_bs(&cont);
	return (0);
}

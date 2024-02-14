/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:27:16 by rhorvath          #+#    #+#             */
/*   Updated: 2024/02/13 03:02:49 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_free_stuff(t_cont *cont)
{
	if (cont->colls->coll)
		free(cont->colls->coll);
	if (cont->colls->x)
		free(cont->colls->x);
	if (cont->colls->y)
		free(cont->colls->y);
	if (cont->colls)
		free(cont->colls);
	ft_free_map(cont->map);
}

void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void	ft_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
	write(1, "\n", 1);
}

int	name_check(char *name)
{
	int		len;
	char	*file;

	file = ".ber";
	len = ft_strlen(name);
	if (len < 5)
		return (-1);
	if (ft_strncmp(file, name + len - 4, 5) != 0)
		return (-1);
	return (0);
}

int	ec_process(char **map, int *i, int *flagp, int flag_e_c[])
{
	int	j;

	j = -1;
	while (map[*i][++j])
	{
		if (map[*i][j] == 'P')
			*flagp = 1;
		if (map[*i][j] == 'C')
			flag_e_c[1] = 1;
		if (map[*i][j] == 'E' && flag_e_c[0] == 1)
			return (0);
		if (map[*i][j] == 'E')
			flag_e_c[0] = 1;
		if (map[*i][j] != 'C' && map[*i][j] != 'E' && map[*i][j] != '0'
			&& map[*i][j] != '1' && map[*i][j] != 'P' && map[*i][j] != '\n')
			return (0);
	}
	return (1);
}

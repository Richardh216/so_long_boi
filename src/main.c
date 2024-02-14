/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:38:51 by rhorvath          #+#    #+#             */
/*   Updated: 2024/02/13 02:12:37 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int argc, char **argv)
{
	t_cont	cont;

	if (argc != 2 || name_check(argv[1]) == -1)
	{
		ft_error("Wrong Input!");
		return (0);
	}
	cont.map = get_map(argv[1]);
	if (cont.map == NULL)
	{
		ft_error("Invalid Map!");
		return (0);
	}
	if (ft_solvable(cont.map))
	{
		ft_free_map(cont.map);
		ft_error("Unsolvable Map!");
		return (0);
	}
	if (init(cont.map, &cont) == -1)
		ft_error("Init Problems!");
	ft_free_stuff(&cont);
	return (0);
}

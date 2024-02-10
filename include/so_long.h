/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 08:12:02 by rhorvath          #+#    #+#             */
/*   Updated: 2024/01/30 06:54:47 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_coll
{
	mlx_image_t	**coll;
	int			*x;
	int			*y;
}	t_coll;

typedef struct s_cont
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*wall;
	mlx_image_t		*floor;
	mlx_image_t		*exit;
	mlx_image_t		*player;
	mlx_image_t		*chip;
	int				coords_x;
	int				coords_y;
	int				player_x;
	int				player_y;
	char			**map;
	int				c_n;
	int				moves;
	int				all;
	t_coll			*collectibles;
	int				p_width;
	int				p_length;
}	t_cont;

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
void	create_list(t_list **list, int fd);
int		found_newline(t_list *list);
t_list	*find_last_node(t_list *list);
void	append(t_list **list, char *buf);
int		len_till_newline(t_list *list);
void	copy_str(t_list *list, char *str);
char	*get_line1(t_list *list);
char	*clean_up_list(t_list **list);
void	dealloc(int flag, t_list **list, t_list *clean_node, char *buf);


void	remove_c(t_cont *cont);
int	main(int argc, char **argv);
char	**get_map(char *str);
int	get_map_size(char *map_path);
char	*ft_strdup(char *s1);
int	name_check(char *name);
int	ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_error(char *str, int flag);
int	ft_check_map(char **map, int map_size);
int	ft_check_fnl(char **map, int map_size);
int	ft_check_borders(char **map, int map_size);
int	ft_strlen(char *str);
int	init(char **map);
void	sz(char **map, t_cont *cont);
void	build(t_cont *cont, char **map);
void	build2(t_cont *cont, char **map);
void	build3(t_cont *cont, char **map);
void	rebuild_p(t_cont *cont);
void	move_up(t_cont *cont);
void	move_down(t_cont *cont);
void	move_left(t_cont *cont);
void	move_right(t_cont *cont);
// void	free_map(char **map);

#endif

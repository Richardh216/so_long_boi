/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:25:17 by rhorvath          #+#    #+#             */
/*   Updated: 2024/02/13 02:55:57 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_coll
{
	mlx_image_t	**coll;
	int			*x;
	int			*y;
}	t_coll;

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}	t_list;

typedef struct s_cont
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*wall;
	mlx_image_t		*floor;
	mlx_image_t		*exit;
	mlx_image_t		*player;
	mlx_image_t		*chip;
	char			**map;
	int				p_width;
	int				p_length;
	int				c_n;
	int				all;
	int				moves;
	int				player_x;
	int				player_y;
	int				coords_x;
	int				coords_y;
	t_coll			*colls;
}	t_cont;

/*  GNL Stuff  */
char		*get_next_line(int fd);
void		create_list(t_list **list, int fd);
int			found_newline(t_list *list);
t_list		*find_last_node(t_list *list);
void		append(t_list **list, char *buf);
int			len_till_newline(t_list *list);
void		copy_str(t_list *list, char *str);
char		*get_line1(t_list *list);
char		*clean_up_list(t_list **list);
void		dealloc(int flag, t_list **list, t_list *clean_node, char *buf);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
int			ft_strlen(char *str);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(char *s1);

/* 	Checks Stuff  */
int			name_check(char *name);
char		**get_map(char *str);
int			get_map_size(char *map_path);
int			ft_check_map(char **map, int map_size);
int			ft_check_fnl(char **map, int map_size);
int			ft_check_borders(char **map, int map_size);
int			ft_solvable(char **map);
char		**map_copy(char **map);
void		ft_p_pos(char **tmp, int *p);
void		ft_flood_fill(char **map, int p1, int p2);
int			ft_check_ec(char **map);
int			ec_process(char **map, int *i, int *flagp, int flag_e_c[]);

/*  Init Stuff  */
int			init(char **map, t_cont *cont);
void		ft_size(char **map, t_cont *cont);
void		ft_build(t_cont *cont, char **map);
void		ft_build2(t_cont *cont, char **map);
void		ft_build3(t_cont *cont, char **map);
void		ft_rebuild_player(t_cont *cont);
void		ft_colls(t_cont *cont, char **map);
void		ft_coll_alloc(t_cont *cont);
void		ft_colls2(t_cont *cont);
void		ft_remove_colls(t_cont *cont);
void		my_keyhook(mlx_key_data_t keydata, void *param);

/*  Moving Stuff  */
void		ft_move_up(t_cont *cont);
void		ft_move_down(t_cont *cont);
void		ft_move_left(t_cont *cont);
void		ft_move_right(t_cont *cont);
void		ft_print_moves(int moves);

/* 	Free Stuff 	*/
void		ft_free_map(char **map);
void		ft_free_stuff(t_cont *cont);
void		ft_error(char *str);

#endif
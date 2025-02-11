/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archytekt <archytekt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:04:58 by lmaria            #+#    #+#             */
/*   Updated: 2025/02/11 01:44:08 by archytekt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_map
{
	char **map;       // Tableau 2D stockant la carte
	int width;        // Largeur de la carte
	int height;       // Hauteur de la carte
	int player_x;     // Position X du joueur
	int player_y;     // Position Y du joueur
	int collectibles; // Nombre de collectibles (C)
	int exits;        // Nombre de sorties (E)
	int players;      // Nombre de joueurs (P)
}			t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	*map;
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_collectible;
	void	*img_exit;
}			t_game;

// Prototypes
t_map		*parse_map(char *filename);
bool		check_map_validity(t_map *map);
void		free_map(t_map *map);
int			key_hook(int keycode, t_game *game);
int			close_window(t_game *game);
bool		init_window(t_game *game);
bool		is_map_width_valid(t_map *map);
void		render_map(t_game *game);
bool		load_textures(t_game *game);

#endif

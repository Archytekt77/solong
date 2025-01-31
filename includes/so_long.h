/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaria <lmaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:04:58 by lmaria            #+#    #+#             */
/*   Updated: 2025/01/31 15:04:59 by lmaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
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
}		t_map;

// Prototypes
t_map	*parse_map(char *filename);
void	check_map_validity(t_map *map);
void	free_map(t_map *map);

#endif

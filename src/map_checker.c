/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archytekt <archytekt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:04:52 by lmaria            #+#    #+#             */
/*   Updated: 2025/02/11 01:05:02 by archytekt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

// Vérifie si une ligne est bien fermée par des murs
bool	is_line_closed(char *line, int width)
{
	if (line[0] != '1' || line[width - 1] != '1')
		return (false);
	return (true);
}

// Vérifier si la carte est fermée par des murs
bool	is_map_closed(t_map *map)
{
	int	i;

	if (!is_line_closed(map->map[0], map->width)
		|| !is_line_closed(map->map[map->height - 1], map->width))
		return (false);
	i = 0;
	while (i < map->height)
	{
		if (!is_line_closed(map->map[i], map->width))
			return (false);
		i++;
	}
	return (true);
}

// Vérifie et compte les éléments de la carte
bool	process_map_element(t_map *map, char c, int i, int j)
{
	if (c == 'P')
	{
		map->players++;
		map->player_x = j;
		map->player_y = i;
	}
	else if (c == 'E')
		map->exits++;
	else if (c == 'C')
		map->collectibles++;
	else if (c != '1' && c != '0')
	{
		ft_printf("Error\nInvalid character detected: '%c' at (%d, %d)\n", c, i,
			j);
		return (false);
	}
	return (true);
}

// Vérifier les caractères valides et compter les éléments
bool	check_elements(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (!process_map_element(map, map->map[i][j], i, j))
				return (false);
			j++;
		}
		i++;
	}
	ft_printf("Total Players: %d, Exits: %d, Collectibles: %d\n", map->players,
		map->exits, map->collectibles);
	return (map->players == 1 && map->exits == 1 && map->collectibles > 0);
}

// Fonction principale pour vérifier la validité de la carte
bool	check_map_validity(t_map *map)
{
	if (!is_map_closed(map))
	{
		printf("Error\nThe map is not closed by walls.\n");
		return (false);
	}
	if (!check_elements(map))
	{
		printf("Error\nInvalid elements in the map.\n");
		return (false);
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaria <lmaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:04:52 by lmaria            #+#    #+#             */
/*   Updated: 2025/02/06 14:27:01 by lmaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

// Vérifier si la carte est fermée par des murs
bool	is_map_closed(t_map *map)
{
	int	expected_width;

	expected_width = map->width;
	for (int i = 0; i < map->height; i++)
	{
		if ((int)ft_strlen(map->map[i]) != expected_width)
		{
			ft_printf("Error\nMap lines have inconsistent width.\n");
			return (false);
		}
	}
	for (int i = 0; i < map->width; i++)
		if (map->map[0][i] != '1' || map->map[map->height - 1][i] != '1')
			return (false);
	for (int i = 0; i < map->height; i++)
		if (map->map[i][0] != '1' || map->map[i][map->width - 1] != '1')
			return (false);
	return (true);
}

// Vérifier les caractères valides et compter les éléments
bool	check_elements(t_map *map)
{
	char	c;

	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			c = map->map[i][j];
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
				ft_printf("Error\nInvalid character detected: '%c' at (%d, \
					%d)\n", c, i, j);
				return (false);
			}
		}
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

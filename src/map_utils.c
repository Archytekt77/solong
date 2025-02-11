/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archytekt <archytekt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 01:32:58 by archytekt         #+#    #+#             */
/*   Updated: 2025/02/11 01:48:58 by archytekt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

// Vérifie si toutes les lignes de la carte ont la même largeur
bool	is_map_width_valid(t_map *map)
{
	int	current_width;
	int	i;

	i = 0;
	while (map->map[i])
	{
		current_width = ft_strlen(map->map[i]);
		if (current_width != map->width)
		{
			printf("Error\nMap lines have inconsistent width at line %d\n", i);
			return (false);
		}
		i++;
	}
	return (true);
}

// Libère la mémoire allouée pour la carte
void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->map)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}
	free(map);
}

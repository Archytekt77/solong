/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archytekt <archytekt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:11:52 by lmaria            #+#    #+#             */
/*   Updated: 2025/02/11 01:58:14 by archytekt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <fcntl.h>

// Compte le nombre de lignes dans le fichier
int	count_lines(char *filename)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

// Lit une ligne et enlève le '\n' à la fin si nécessaire
bool	read_map_line(int fd, t_map *map, int i)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		free_map(map);
		close(fd);
		return (false);
	}
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	map->map[i] = line;
	return (true);
}

// Remplit `map->map` avec `get_next_line`
bool	fill_map(t_map *map, char *filename)
{
	int	fd;
	int	i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (false);
	}
	i = 0;
	while (i < map->height)
	{
		if (!read_map_line(fd, map, i))
			return (false);
		i++;
	}
	map->map[i] = NULL;
	close(fd);
	return (true);
}

// Initialise la structure map
bool	init_map_structure(t_map *map, char *filename)
{
	map->height = count_lines(filename);
	if (map->height <= 0)
	{
		free(map);
		return (false);
	}
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
	{
		free(map);
		return (false);
	}
	return (true);
}

// Fonction principale pour parser la carte
t_map	*parse_map(char *filename)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	if (!init_map_structure(map, filename))
		return (NULL);
	if (!fill_map(map, filename))
		return (NULL);
	map->width = ft_strlen(map->map[0]);
	if (!is_map_width_valid(map))
	{
		free_map(map);
		return (NULL);
	}
	map->players = 0;
	map->exits = 0;
	map->collectibles = 0;
	return (map);
}

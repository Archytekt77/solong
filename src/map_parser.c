/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaria <lmaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:11:52 by lmaria            #+#    #+#             */
/*   Updated: 2025/02/05 19:52:04 by lmaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define BUFFER_SIZE 1024

// Fonction pour lire un fichier en mémoire
char	*read_file(char *filename)
{
	int		fd;
	char	*buffer;
	ssize_t	bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (NULL);
	}
	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
	if (bytes_read < 0)
	{
		perror("Error reading file");
		free(buffer);
		close(fd);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	close(fd);
	return (buffer);
}

// Fonction qui split une string en tableau 2D et enlève les '\n'
char	**ft_split_clean(char *str, char delimiter)
{
	int		count = 1, i = 0, j = 0, k;
	char	**array;

	count = 1, i = 0, j = 0, k = 0;
	for (int x = 0; str[x]; x++)
		if (str[x] == delimiter)
			count++;
	array = malloc((count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array[i] = malloc(strlen(str) + 1);
	if (!array[i])
	{
		free(array);
		return (NULL);
	}
	while (str[k])
	{
		if (str[k] == delimiter)
		{
			array[i][j] = '\0';
			i++;
			j = 0;
			array[i] = malloc(strlen(str) + 1);
			if (!array[i])
			{
				while (i-- > 0)
					free(array[i]);
				free(array);
				return (NULL);
			}
		}
		else if (str[k] != '\n')
			array[i][j++] = str[k];
		k++;
	}
	array[i][j] = '\0';
	array[i + 1] = NULL;
	return (array);
}

// Fonction principale pour parser la carte
t_map	*parse_map(char *filename)
{
	char	*file_content;
	t_map	*map;
	int		current_width;

	file_content = read_file(filename);
	if (!file_content)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
	{
		free(file_content);
		return (NULL);
	}
	map->map = ft_split_clean(file_content, '\n');
	free(file_content);
	for (int i = 0; map->map[i]; i++)
		printf("Ligne %d: [%s] (longueur: %lu)\n", i, map->map[i],
			strlen(map->map[i]));
	if (!map->map)
	{
		free(map);
		return (NULL);
	}
	map->height = 0;
	map->width = strlen(map->map[0]);
	while (map->map[map->height])
	{
		current_width = strlen(map->map[map->height]);
		if (current_width != map->width)
		{
			printf("Error\nMap lines have inconsistent width at line \
				%d (expected %d, got %d): [%s]\n", map->height, map->width,
				current_width, map->map[map->height]);
			free_map(map);
			return (NULL);
		}
		map->height++;
	}
	map->players = 0;
	map->exits = 0;
	map->collectibles = 0;
	return (map);
}

// Libère la mémoire allouée pour la carte
void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->map)
	{
		for (int i = 0; i < map->height; i++)
			free(map->map[i]);
		free(map->map);
	}
	free(map);
}

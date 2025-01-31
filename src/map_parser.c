/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaria <lmaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:04:22 by lmaria            #+#    #+#             */
/*   Updated: 2025/01/31 15:09:38 by lmaria           ###   ########.fr       */
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

#include <string.h>

// Fonction qui split une string en tableau 2D
char	**ft_split(char *str, char delimiter)
{
	int		i = 0, j = 0, k = 0, count;
	char	**array;

	i = 0, j = 0, k = 0, count = 1;
	for (int x = 0; str[x]; x++) // Compter le nombre de lignes
		if (str[x] == delimiter)
			count++;
	array = malloc((count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array[i] = malloc(strlen(str) + 1);
	if (!array[i])
		return (NULL);
	while (str[k])
	{
		if (str[k] == delimiter)
		{
			array[i][j] = '\0';
			i++;
			j = 0;
			array[i] = malloc(strlen(str) + 1);
		}
		else
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

	file_content = read_file(filename);
	if (!file_content)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->map = ft_split(file_content, '\n');
	free(file_content);
	// Calculer la hauteur et la largeur
	map->height = 0;
	while (map->map[map->height])
		map->height++;
	map->width = strlen(map->map[0]);
	map->players = 0;
	map->exits = 0;
	map->collectibles = 0;
	return (map);
}

// Libère la mémoire allouée pour la carte
void free_map(t_map *map)
{
    if (!map)
        return;

    if (map->map)
    {
        for (int i = 0; i < map->height; i++)
            free(map->map[i]);
        free(map->map);
    }
    free(map);
}

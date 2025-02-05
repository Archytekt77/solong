/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaria <lmaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:12:46 by lmaria            #+#    #+#             */
/*   Updated: 2025/02/05 19:48:23 by lmaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx-linux/mlx.h"
#include "so_long.h"

void	free_textures(t_game *game)
{
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor);
	if (game->img_player)
		mlx_destroy_image(game->mlx, game->img_player);
	if (game->img_collectible)
		mlx_destroy_image(game->mlx, game->img_collectible);
	if (game->img_exit)
		mlx_destroy_image(game->mlx, game->img_exit);
}

// Charger les textures
bool	load_textures(t_game *game)
{
	int img_width, img_height;
	game->img_wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm",
			&img_width, &img_height);
	game->img_floor = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm",
			&img_width, &img_height);
	game->img_player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm",
			&img_width, &img_height);
	game->img_collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &img_width, &img_height);
	game->img_exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm",
			&img_width, &img_height);
	if (!game->img_wall || !game->img_floor || !game->img_player
		|| !game->img_collectible || !game->img_exit)
	{
		printf("Error\nFailed to load textures\n");
		free_textures(game); // Libère les textures déjà chargées
		return (false);
	}
	return (true);
}

// Afficher la carte avec MiniLibX
void	render_map(t_game *game)
{
	char	c;
	void	*img;

	for (int y = 0; y < game->map->height; y++)
	{
		for (int x = 0; x < game->map->width; x++)
		{
			c = game->map->map[y][x];
			img = game->img_floor;
			if (c == '1')
				img = game->img_wall;
			else if (c == 'P')
				img = game->img_player;
			else if (c == 'C')
				img = game->img_collectible;
			else if (c == 'E')
				img = game->img_exit;
			mlx_put_image_to_window(game->mlx, game->win, img, x * 64, y * 64);
		}
	}
}

// Initialiser la fenêtre et charger la carte
bool	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error\nFailed to initialize MiniLibX\n");
		return (false);
	}
	game->win = mlx_new_window(game->mlx, game->map->width * 64,
			game->map->height * 64, "So Long");
	if (!game->win)
	{
		printf("Error\nFailed to create window\n");
		free(game->mlx); // Libère MiniLibX si la fenêtre échoue
		return (false);
	}
	if (!load_textures(game)) // Modifier load_textures() pour retourner `bool`
	{
		printf("Error\nFailed to load textures\n");
		mlx_destroy_window(game->mlx, game->win);
		free(game->mlx);
		return (false);
	}
	render_map(game);
	return (true);
}

// Fermer proprement
int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	free_map(game->map);
	exit(0);
}

// Gestion des touches
int	key_hook(int keycode, t_game *game)
{
	if (keycode == 65307) // Touche "Esc"
		close_window(game);
	return (0);
}

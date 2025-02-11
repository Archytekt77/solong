/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archytekt <archytekt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 01:33:13 by archytekt         #+#    #+#             */
/*   Updated: 2025/02/11 01:33:17 by archytekt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx-linux/mlx.h"
#include "so_long.h"

bool	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error\nFailed to initialize MiniLibX\n");
		return (false);
	}
	game->win = mlx_new_window(game->mlx, game->map->width * 128,
			game->map->height * 128, "So Long");
	if (!game->win)
	{
		printf("Error\nFailed to create window\n");
		free(game->mlx);
		return (false);
	}
	if (!load_textures(game))
	{
		printf("Error\nFailed to load textures\n");
		mlx_destroy_window(game->mlx, game->win);
		free(game->mlx);
		return (false);
	}
	render_map(game);
	return (true);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	free_map(game->map);
	exit(0);
}

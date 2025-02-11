/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archytekt <archytekt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:12:46 by lmaria            #+#    #+#             */
/*   Updated: 2025/02/11 01:01:40 by archytekt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archytekt <archytekt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:12:46 by lmaria            #+#    #+#             */
/*   Updated: 2025/02/11 12:00:00 by archytekt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx-linux/mlx.h"
#include "so_long.h"

// Retourne l'image correspondante au caractère de la carte
void	*get_tile_image(t_game *game, char c)
{
	if (c == '1')
		return (game->img_wall);
	if (c == 'P')
		return (game->img_player);
	if (c == 'C')
		return (game->img_collectible);
	if (c == 'E')
		return (game->img_exit);
	return (game->img_floor);
}

// Affiche une ligne de la carte
void	render_line(t_game *game, int y)
{
	int		x;
	char	c;
	void	*img;

	x = 0;
	while (x < game->map->width)
	{
		c = game->map->map[y][x];
		img = get_tile_image(game, c);
		mlx_put_image_to_window(game->mlx, game->win, img, x * 128, y * 128);
		x++;
	}
}

// Affiche la carte complète
void	render_map(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		render_line(game, y);
		y++;
	}
}

// Gestion des touches
int	key_hook(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_window(game);
	return (0);
}

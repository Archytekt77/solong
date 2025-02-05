/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaria <lmaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:03:37 by lmaria            #+#    #+#             */
/*   Updated: 2025/02/05 19:21:33 by lmaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx-linux/mlx.h"
#include "so_long.h"

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	game;

	if (argc != 2 || !strstr(argv[1], ".ber"))
	{
		printf("Error\nInvalid map file. Please use a .ber file.\n");
		return (1);
	}
	map = parse_map(argv[1]);
	if (!map)
	{
		printf("Error\nFailed to parse map\n");
		return (1);
	}
	if (!check_map_validity(map))
	{
		free_map(map);
		return (1);
	}
	game.map = map;
	if (!init_window(&game))
	{
		free_map(map);
		return (1);
	}
	mlx_key_hook(game.win, key_hook, &game);
	mlx_hook(game.win, 17, 0, (void *)close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}

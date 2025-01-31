/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaria <lmaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:03:37 by lmaria            #+#    #+#             */
/*   Updated: 2025/01/31 16:17:46 by lmaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <map.ber>\n", argv[0]);
        return (1);
    }

    t_map *map = parse_map(argv[1]);
    if (!map)
    {
        printf("Error\nFailed to parse map\n");
        return (1);
    }

    check_map_validity(map);

    t_game game;
    game.map = map;
    init_window(&game);

    mlx_key_hook(game.win, key_hook, &game);
    mlx_hook(game.win, 17, 0, (void *)close_window, &game);
    mlx_loop(game.mlx);

    return (0);
}



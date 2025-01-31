/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaria <lmaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:12:46 by lmaria            #+#    #+#             */
/*   Updated: 2025/01/31 16:18:00 by lmaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

typedef struct s_game {
    void    *mlx;
    void    *win;
    t_map   *map;
    void    *img_wall;
    void    *img_floor;
    void    *img_player;
    void    *img_collectible;
    void    *img_exit;
}   t_game;

// Charger les textures
void load_textures(t_game *game)
{
    int img_width, img_height;

    game->img_wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &img_width, &img_height);
    game->img_floor = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm", &img_width, &img_height);
    game->img_player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm", &img_width, &img_height);
    game->img_collectible = mlx_xpm_file_to_image(game->mlx, "textures/collectible.xpm", &img_width, &img_height);
    game->img_exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &img_width, &img_height);

    if (!game->img_wall || !game->img_floor || !game->img_player || !game->img_collectible || !game->img_exit)
    {
        printf("Error\nFailed to load textures\n");
        exit(EXIT_FAILURE);
    }
}

// Afficher la carte avec MiniLibX
void render_map(t_game *game)
{
    for (int y = 0; y < game->map->height; y++)
    {
        for (int x = 0; x < game->map->width; x++)
        {
            char c = game->map->map[y][x];
            void *img = game->img_floor;

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
void init_window(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        printf("Error\nFailed to initialize MiniLibX\n");
        exit(EXIT_FAILURE);
    }

    game->win = mlx_new_window(game->mlx, game->map->width * 64, game->map->height * 64, "So Long");
    if (!game->win)
    {
        printf("Error\nFailed to create window\n");
        exit(EXIT_FAILURE);
    }

    load_textures(game);
    render_map(game);
}

// Fermer proprement
int close_window(t_game *game)
{
    mlx_destroy_window(game->mlx, game->win);
    free_map(game->map);
    exit(0);
}

// Gestion des touches
int key_hook(int keycode, t_game *game)
{
    if (keycode == 65307) // Touche ESC
        close_window(game);
    return (0);
}


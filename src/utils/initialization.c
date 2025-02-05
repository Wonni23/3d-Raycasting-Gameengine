/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:34:37 by donjung           #+#    #+#             */
/*   Updated: 2025/01/26 14:34:38 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3D");
}

void	init_player(t_player *player) // debug
{
	player->pos_x = 4; // debug
	player->pos_y = 2; // debug
	player->dir_x = -1; // should be determined by the starting face
	player->dir_y = 0; // should be determined by the starting face
	player->plane_x = 0;
	player->plane_y = -0.66;
}

void	init_test_map(t_map *map) // debug
{
	char testmap[10][10] = {
    {'1','1','1','1','1','1','1','1','1','1'},
    {'1','0','0','0','0','0','1','1','1','1'},
    {'1','1','0','0','0','1','0','0','1','1'},
    {'1','0','0','0','0','0','1','1','1','1'},
    {'1','1','0','0','0','0','1','0','1','1'},
    {'1','1','1','0','1','1','1','0','1','1'},
    {'1','1','0','1','0','0','0','0','0','1'},
    {'1','0','0','0','1','0','0','1','0','1'},
    {'1','0','1','0','0','1','1','1','1','1'},
    {'1','1','1','1','1','1','1','1','1','1'}
};
	memcpy(map->map, testmap, sizeof(char) * 10 * 10);
	map->map_width = 10;  // debug
	map->map_height = 10; // debug
	map->ceiling = 0xDC6400;
	map->floor = 0xE11E00;
	map->no_path = "images/wall_n.xpm";
	map->ea_path = "images/wall_e.xpm";
	map->so_path = "images/wall_s.xpm";
	map->we_path = "images/wall_w.xpm";
}

void	initialization(t_cub *cub)
{
	init_mlx(cub);
	init_test_map(&cub->map);
	init_player(&cub->player);
	init_image(&cub->img);
	load_image(cub);
	cub->img.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->img.data = (int *)mlx_get_data_addr(cub->img.img, &cub->img.bpp,
								&cub->img.line_size, &cub->img.endian);
}

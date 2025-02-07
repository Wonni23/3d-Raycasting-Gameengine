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

void	init_player(t_player *player)
{
	if (player->status == 'N')
	{
		player->dir_x = 0; 
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (player->status == 'E')
	{
		player->dir_x = 1; 
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (player->status == 'S')
	{
		player->dir_x = 0; 
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (player->status == 'W')
	{
		player->dir_x = -1; 
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

void	initialization(t_cub *cub)
{
	init_player(&cub->player);
	cub->img.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->img.data = (int *)mlx_get_data_addr(cub->img.img, &cub->img.bpp,
								&cub->img.line_size, &cub->img.endian);
}

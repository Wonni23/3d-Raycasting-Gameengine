/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:22:17 by donjung           #+#    #+#             */
/*   Updated: 2025/02/04 14:22:21 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	paint_background(t_cub *cub)
{
	int	i;
	int	j;
	int	celling;
	int	floor;

	i = 0;
	celling = cub->img.colors[1];
	floor = cub->img.colors[0];
	while (i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
		{
			cub->img.buffer[i][j] = celling;
			cub->img.buffer[HEIGHT - i - 1][j] = floor;
			j++;
		}
		i++;
	}	
}

void	paint_img(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			cub->img.data[y * WIDTH + x] = cub->img.buffer[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}

void	fill_minimap(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < (int)(MINISCALE * TILESIZE))
	{
		i = 0;
		while (i < (int)(MINISCALE * TILESIZE))
		{
			cub->img.buffer[y + j][x + i] = color;
			i++;
		}
		j++;
	}
}

void	paint_minimap(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y < cub->map.map_height)
	{
		x = 0;
		while (x < cub->map.map_width - 1)
		{
			if (cub->map.map[y][x] == '1')
				fill_minimap(cub, (int)(MINISCALE * TILESIZE * x), (int)(MINISCALE * TILESIZE * y), 0x000000);
			else if (cub->map.map[y][x] == 'N' || cub->map.map[y][x] == 'W' || cub->map.map[y][x] == 'E' || cub->map.map[y][x] == 'S')
				fill_minimap(cub, (int)(MINISCALE * TILESIZE * x), (int)(MINISCALE * TILESIZE * y), 0x760c0c);
			else
				fill_minimap(cub, (int)(MINISCALE * TILESIZE * x), (int)(MINISCALE * TILESIZE * y), 0xffffff);
			x++;
		}
		y++;
	}
	//mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}

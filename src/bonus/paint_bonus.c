/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:22:17 by donjung           #+#    #+#             */
/*   Updated: 2025/02/10 21:05:55 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	paint_background(t_cub *cub)
{
	int	i;
	int	j;
	int	ceiling;
	int	floor;

	i = 0;
	ceiling = cub->img.colors[1];
	floor = cub->img.colors[0];
	while (i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
		{
			cub->img.buffer[i][j] = ceiling;
			cub->img.buffer[HEIGHT - i - 1][j] = floor;
			j++;
		}
		i++;
	}	
}

void	buffer_to_img_n_window(t_cub *cub)
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
	while (j < (int)(SC * SZ))
	{
		i = 0;
		while (i < (int)(SC * SZ))
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
				fill_minimap(cub, (int)(SC * SZ * x), (int)(SC * SZ * y), K);
			else if (cub->map.map[y][x] == '2')
				fill_minimap(cub, (int)(SC * SZ * x), (int)(SC * SZ * y), B);
			else if (cub->map.map[y][x] == '3')
				fill_minimap(cub, (int)(SC * SZ * x), (int)(SC * SZ * y), Y);
			else
				fill_minimap(cub, (int)(SC * SZ * x), (int)(SC * SZ * y), WT);
			x++;
		}
		fill_minimap(cub, (int)((cub->player.pos_x - 0.5) * 8 * SC),
			(int)((cub->player.pos_y -0.5) * 8 * SC), RD);
		y++;
	}
}

void	paint_sprite(t_cub *cub, int idx)
{
	int	x;
	int	y;
	int	src_x;
	int	src_y;
	int	pixel;

	y = 0;
	while (y < SPSIZE)
	{
		x = 0;
		while (x < SPSIZE)
		{
			src_x = (x * TEX_WIDTH) / SPSIZE;
			src_y = (y * TEX_HEIGHT) / SPSIZE;
			pixel = cub->img.sprites[idx][(src_y * TEX_WIDTH) + src_x];
			if (((pixel >> 24) & 0xFF) == 0)
				cub->img.buffer[SP_Y + y][(int)(SP_X + x)] = pixel;
			x++;
		}
		y++;
	}
}

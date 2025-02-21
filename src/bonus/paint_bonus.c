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

#include "../../include/cub3d_bonus.h"

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

void	paint_minimap(t_cub *c)
{
	int	y;
	int	x;

	y = 0;
	while (y < c->map.map_height)
	{
		x = 0;
		while (c->map.map[y][x] && c->map.map[y][x]
			!= '\n' && x < c->map.map_width)
		{
			if (c->map.map[y][x] == '1')
				fill_minimap(c, (int)(SC * SZ * x), (int)(SC * SZ * y), K);
			else if (c->map.map[y][x] == '2')
				fill_minimap(c, (int)(SC * SZ * x), (int)(SC * SZ * y), B);
			else if (c->map.map[y][x] == '3')
				fill_minimap(c, (int)(SC * SZ * x), (int)(SC * SZ * y), Y);
			else if (c->map.map[y][x] == '0'
				|| orientation_player(c->map.map[y][x]))
				fill_minimap(c, (int)(SC * SZ * x), (int)(SC * SZ * y), WT);
			x++;
		}
		fill_minimap(c, (int)((c->player.pos_x - 0.5) * 8 * SC),
			(int)((c->player.pos_y -0.5) * 8 * SC), RD);
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
	if (idx > 4)
		return ;
	while (y < cub->img.spsize)
	{
		x = 0;
		while (x < cub->img.spsize)
		{
			src_x = (x * TEX_WIDTH) / cub->img.spsize;
			src_y = (y * TEX_HEIGHT) / cub->img.spsize;
			pixel = cub->img.sprites[idx][(src_y * TEX_WIDTH) + src_x];
			if (((pixel >> 24) & 0xFF) == 0)
				cub->img.buffer[cub->img.sp_y + y] \
				[(int)(cub->img.sp_x + x)] = pixel;
			x++;
		}
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:22:17 by donjung           #+#    #+#             */
/*   Updated: 2025/02/10 21:06:44 by donjung          ###   ########.fr       */
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

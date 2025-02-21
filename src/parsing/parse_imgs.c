/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_imgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:09 by donjung           #+#    #+#             */
/*   Updated: 2025/02/06 14:44:47 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	init_image(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			img->buffer[i][j++] = 0;
		i++;
	}
	img->walls = (int **)malloc(5 * sizeof(int *));
	if (!img->walls)
		err_exit("walls malloc error");
	i = 0;
	while (i < 4)
	{
		img->walls[i] = (int *)malloc(sizeof(int) * TEX_WIDTH * TEX_HEIGHT);
		if (!img->walls[i])
			err_exit("walls malloc error");
		ft_memset(img->walls[i], 0, (sizeof(int) * TEX_WIDTH * TEX_HEIGHT));
		i++;
	}
	return (0);
}

void	fill_wall_arr_pixel(t_cub *cub, int i)
{
	int	y;
	int	x;

	y = 0;
	while (y < cub->img.h)
	{
		x = 0;
		while (x < cub->img.w)
		{
			cub->img.walls[i][cub->img.w * y + x] = \
				cub->img.data[cub->img.h * y + x];
			x++;
		}
		y++;
	}
}

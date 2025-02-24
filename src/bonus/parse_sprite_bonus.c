/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:30:58 by donjung           #+#    #+#             */
/*   Updated: 2025/02/21 19:31:00 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	init_sprite(t_cub *cub)
{
	int	i;

	i = 0;
	cub->img.spsize = (WIDTH / 3);
	cub->img.sp_x = (WIDTH - cub->img.spsize * 1.2);
	cub->img.sp_y = (HEIGHT - cub->img.spsize);
	cub->img.sprites = (int **)malloc(6 * sizeof(int *));
	if (!cub->img.sprites)
		err_exit("sprites malloc error");
	i = 0;
	while (i < 5)
	{
		cub->img.sprites[i] = \
			(int *)malloc(sizeof(int) * TEX_WIDTH * TEX_HEIGHT);
		if (!cub->img.sprites[i])
			err_exit("sprites malloc error");
		ft_memset(cub->img.sprites[i], 0, (sizeof(int) * TEX_WIDTH \
			* TEX_HEIGHT));
		i++;
	}
	return (0);
}

void	fill_sprite_arr_pixel(t_cub *cub, int i)
{
	int	y;
	int	x;

	y = 0;
	while (y < cub->img.h)
	{
		x = 0;
		while (x < cub->img.w)
		{
			cub->img.sprites[i][cub->img.w * y + x] = \
				cub->img.data[cub->img.h * y + x];
			x++;
		}
		y++;
	}
}

void	load_sprite_image(t_cub *c)
{
	char	*path;
	int		i;

	i = -1;
	while (++i < 5)
	{
		if (i == 0)
			path = "images/sprites/1.xpm";
		else if (i == 1)
			path = "images/sprites/2.xpm";
		else if (i == 2)
			path = "images/sprites/3.xpm";
		else if (i == 3)
			path = "images/sprites/4.xpm";
		else
			path = "images/sprites/5.xpm";
		c->img.img = mlx_xpm_file_to_image(c->mlx, path, &c->img.w, &c->img.h);
		if (c->img.w != TEX_WIDTH || c->img.h != TEX_HEIGHT
			|| c->img.img == NULL)
			exit_parse(c, 1, "sprites xpm file error", NULL);
		c->img.data = (int *)mlx_get_data_addr(c->img.img, \
					&c->img.bpp, &c->img.line_size, &c->img.endian);
		fill_sprite_arr_pixel(c, i);
		mlx_destroy_image(c->mlx, c->img.img);
	}
}

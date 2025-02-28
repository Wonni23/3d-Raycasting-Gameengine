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

int	init_enemy(t_cub *cub)
{
	int	i;

	i = 0;
	cub->zbuffer = (double *)malloc(sizeof(double) * (WIDTH + 1));
	cub->img.enemy = (int **)malloc(3 * sizeof(int *));
	if (!cub->img.enemy)
		err_exit("enemy malloc error");
	i = 0;
	while (i < 3)
	{
		cub->img.enemy[i] = \
			(int *)malloc(sizeof(int) * TEX_WIDTH * TEX_HEIGHT);
		if (!cub->img.enemy[i])
			err_exit("enemy malloc error");
		ft_memset(cub->img.enemy[i], 0, (sizeof(int) * TEX_WIDTH \
			* TEX_HEIGHT));
		i++;
	}
	return (0);
}

void	fill_enemy_arr_pixel(t_cub *cub, int i)
{
	int	y;
	int	x;

	y = 0;
	while (y < cub->img.h)
	{
		x = 0;
		while (x < cub->img.w)
		{
			cub->img.enemy[i][cub->img.w * y + x] = \
				cub->img.data[cub->img.h * y + x];
			x++;
		}
		y++;
	}
}

void	load_enemy_image(t_cub *c, char **p_path)
{
	char	*path;
	int		i;

	i = -1;
	while (++i < 3)
	{
		if (i == 0)
			path = "textures/enemy/full.xpm";
		else if (i == 1)
			path = "textures/enemy/half.xpm";
		else if (i == 2)
			path = "textures/enemy/dead.xpm";
		c->img.img = mlx_xpm_file_to_image(c->mlx, path, &c->img.w, &c->img.h);
		if (c->img.w != TEX_WIDTH || c->img.h != TEX_HEIGHT
			|| c->img.img == NULL)
			memory_clean_exit_bonus(c, p_path, 1, "enemy load error");
		c->img.data = (int *)mlx_get_data_addr(c->img.img, \
					&c->img.bpp, &c->img.line_size, &c->img.endian);
		fill_enemy_arr_pixel(c, i);
		mlx_destroy_image(c->mlx, c->img.img);
	}
}

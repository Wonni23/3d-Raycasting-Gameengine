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

void	load_image(t_cub *cub, char **path_to_image)
{
	char	*path;
	int		i;

	i = 0;
	while (i < 4)
	{
		if (i == N)
			path = path_to_image[0];
		else if (i == S)
			path = path_to_image[1];
		else if (i == W)
			path = path_to_image[2];
		else
			path = path_to_image[3];
		cub->img.img = mlx_xpm_file_to_image(cub->mlx, path, \
			&cub->img.w, &cub->img.h);
		if (cub->img.w != TEX_WIDTH || cub->img.h != TEX_HEIGHT
			|| cub->img.img == NULL)
			exit_parse(cub, 1, "image_load xpm file error", NULL);
		cub->img.data = (int *)mlx_get_data_addr(cub->img.img, \
					&cub->img.bpp, &cub->img.line_size, &cub->img.endian);
		fill_wall_arr_pixel(cub, i);
		mlx_destroy_image(cub->mlx, cub->img.img);
		i++;
	}
}

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
		ft_memset(cub->img.sprites[i], 0, \
		(sizeof(int) * TEX_WIDTH * TEX_HEIGHT));
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
			exit_parse(c, 1, "image_load xpm file error", NULL);
		c->img.data = (int *)mlx_get_data_addr(c->img.img, \
					&c->img.bpp, &c->img.line_size, &c->img.endian);
		fill_sprite_arr_pixel(c, i);
		mlx_destroy_image(c->mlx, c->img.img);
	}
}

void	fill_door_arr_pixel(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y < cub->img.h)
	{
		x = 0;
		while (x < cub->img.w)
		{
			cub->img.door[cub->img.w * y + x] = \
				cub->img.data[cub->img.h * y + x];
			x++;
		}
		y++;
	}
}

void	load_door(t_cub *cub)
{
	char	*path;

	path = "./images/door.xpm";
	cub->img.door = (int *)malloc(sizeof(int) * TEX_WIDTH * TEX_HEIGHT);
	cub->img.img = mlx_xpm_file_to_image(cub->mlx, path, \
			&cub->img.w, &cub->img.h);
	if (cub->img.w != TEX_WIDTH || cub->img.h != TEX_HEIGHT
		|| cub->img.img == NULL)
		exit_parse(cub, 1, "image_load xpm file error", NULL);
	cub->img.data = (int *)mlx_get_data_addr(cub->img.img, \
			&cub->img.bpp, &cub->img.line_size, &cub->img.endian);
	fill_door_arr_pixel(cub);
	mlx_destroy_image(cub->mlx, cub->img.img);
}

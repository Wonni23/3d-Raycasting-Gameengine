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

	//initialization_img(img);
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			img->buffer[i][j++] = 0;
		i++;
	}
	img->wallimgs = (int **)malloc(5 * sizeof(int *));
	if (!img->wallimgs)
		ft_exit("wallimgs malloc error");
	i = 0;
	while (i < 4)
	{
		img->wallimgs[i] = (int *)malloc(sizeof(int) * TEX_WIDTH * TEX_HEIGHT);
		if (!img->wallimgs[i])
			ft_exit("wallimgs malloc error");
		ft_memset(img->wallimgs[i], 0, (sizeof(int) * TEX_WIDTH * TEX_HEIGHT));
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
			cub->img.wallimgs[i][cub->img.w * y + x] = \
				cub->img.data[cub->img.h * y + x];
			x++;
		}
		y++;
	}
}

void	load_image(t_cub *cub)
{
	char	*path;
	int		i;

	i = 0;
	while (i < 4)
	{
		if (i == N)
			path = cub->map.no_path;
		else if (i == E)
			path = cub->map.ea_path;
		else if (i == S)
			path = cub->map.so_path;
		else
			path = cub->map.we_path;
		cub->img.img = \
			mlx_xpm_file_to_image(cub->mlx, path, &cub->img.w, &cub->img.h);
		if (cub->img.w != TEX_WIDTH || cub->img.h != TEX_HEIGHT
			|| cub->img.img == NULL)
			ft_exit("image_load xpm file error");
		cub->img.data = (int *)mlx_get_data_addr(cub->img.img, \
					&cub->img.bpp, &cub->img.line_size, &cub->img.endian);
		fill_wall_arr_pixel(cub, i);
		mlx_destroy_image(cub->mlx, cub->img.img);
		i++;
	}
}

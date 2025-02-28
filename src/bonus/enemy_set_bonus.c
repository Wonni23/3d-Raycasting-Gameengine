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

/* sort_sprites: Bubble sort sprites in descending order by distance */
void	sort_sprites(t_sprite *sprites, int count)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (sprites[j].distance < sprites[j + 1].distance)
			{
				temp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

/* fill_sprite_array: Iterate over the map and fill sprite data
   for enemy positions */
void	fill_sprite_array(t_cub *cub, t_sprite *sprites, int *sprite_count)
{
	int		map_y;
	int		map_x;
	double	dx;
	double	dy;

	map_y = -1;
	while (cub->map.map[++map_y] != NULL)
	{
		map_x = 0;
		while (cub->map.map[map_y][map_x] != '\0')
		{
			if (cub->map.map[map_y][map_x] == '4' \
			|| cub->map.map[map_y][map_x] == '5' \
			|| cub->map.map[map_y][map_x] == '6')
			{
				dx = map_x + 0.5 - cub->player.pos_x;
				dy = map_y + 0.5 - cub->player.pos_y;
				sprites[*sprite_count] = (t_sprite){map_x + 0.5, map_y + 0.5, \
					dx * dx + dy * dy, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
					0, cub->map.map[map_y][map_x]};
				(*sprite_count)++;
			}
			map_x++;
		}
	}
}

/* transform_sprites: Transform each sprite into camera space and compute
   transform_x, transform_y, screen_x, and width */
void	transform_sprites(t_cub *cub, t_sprite *sprites, int count)
{
	int		i;
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	i = 0;
	while (i < count)
	{
		sprite_x = sprites[i].x - cub->player.pos_x;
		sprite_y = sprites[i].y - cub->player.pos_y;
		inv_det = 1.0 / (cub->player.plane_x * cub->player.dir_y - \
			cub->player.dir_x * cub->player.plane_y);
		sprites[i].transform_x = inv_det * (cub->player.dir_y * sprite_x - \
			cub->player.dir_x * sprite_y);
		sprites[i].transform_y = inv_det * (-cub->player.plane_y * sprite_x + \
			cub->player.plane_x * sprite_y);
		sprites[i].screen_x = (int)((WIDTH / 2) * \
			(1 + sprites[i].transform_x / sprites[i].transform_y));
		sprites[i].width = abs((int)(HEIGHT / sprites[i].transform_y));
		i++;
	}
}

/* compute_sprite_projection: Calculate the sprite's perspective projection 
   (height and vertical range) and store these values. The sprite is scaled 
   to 2/3 of its original size. */
void	compute_sprite_projection(t_sprite *sprite)
{
	sprite->sprite_height = abs((int)(HEIGHT / sprite->transform_y));
	sprite->draw_start_y = -sprite->sprite_height / 2 + HEIGHT / 2;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	sprite->draw_end_y = sprite->sprite_height / 2 + HEIGHT / 2;
	if (sprite->draw_end_y >= HEIGHT)
		sprite->draw_end_y = HEIGHT - 1;
}

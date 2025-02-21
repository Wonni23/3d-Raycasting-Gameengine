/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:34:58 by donjung           #+#    #+#             */
/*   Updated: 2025/02/21 19:35:00 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	collide_door(t_cub *cub, double x, double y)
{
	if (cub->map.map[(int)(y + 0.5)][(int)(x + 0.5)] == '2' ||
		cub->map.map[(int)(y + 0.5)][(int)(x + 0.5)] == '3')
		return (1);
	if (cub->map.map[(int)(y - 0.5)][(int)(x - 0.5)] == '2' ||
		cub->map.map[(int)(y - 0.5)][(int)(x - 0.5)] == '3')
		return (2);
	if (cub->map.map[(int)(y + 0.5)][(int)(x - 0.5)] == '2' ||
		cub->map.map[(int)(y + 0.5)][(int)(x - 0.5)] == '3')
		return (3);
	if (cub->map.map[(int)(y - 0.5)][(int)(x + 0.5)] == '2' ||
		cub->map.map[(int)(y - 0.5)][(int)(x + 0.5)] == '3')
		return (4);
	return (0);
}

void	door_coordination(t_cub *cub, int *map_x, int *map_y, int res)
{
	if (res == 1)
	{
		*map_x = (int)(cub->player.pos_x + 0.5);
		*map_y = (int)(cub->player.pos_y + 0.5);
	}
	else if (res == 2)
	{
		*map_x = (int)(cub->player.pos_x - 0.5);
		*map_y = (int)(cub->player.pos_y - 0.5);
	}
	else if (res == 3)
	{
		*map_x = (int)(cub->player.pos_x - 0.5);
		*map_y = (int)(cub->player.pos_y + 0.5);
	}
	else
	{
		*map_x = (int)(cub->player.pos_x + 0.5);
		*map_y = (int)(cub->player.pos_y - 0.5);
	}
}

void	interact_door(t_cub *cub)
{
	int	res;
	int	map_x;
	int	map_y;

	map_x = 0;
	map_y = 0;
	res = collide_door(cub, cub->player.pos_x, cub->player.pos_y);
	if (res < 1 || res > 4)
		return ;
	door_coordination(cub, &map_x, &map_y, res);
	if (cub->map.map[(int)cub->player.pos_y][(int)cub->player.pos_x] != '2' && \
	cub->map.map[(int)cub->player.pos_y][(int)cub->player.pos_x] != '3')
	{
		if (cub->map.map[map_y][map_x] == '2')
			cub->map.map[map_y][map_x] = '3';
		else if (cub->map.map[map_y][map_x] == '3')
			cub->map.map[map_y][map_x] = '2';
	}
}

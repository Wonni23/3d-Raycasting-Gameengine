/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:34:37 by donjung           #+#    #+#             */
/*   Updated: 2025/02/10 21:05:37 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

//void	interact_door(t_cub *cub)
//{
//	t_ray	ray;
//	float	max_dist = 1; // 상호작용 최대 거리

//	ray.ray_dir_x = cub->player.dir_x;
//	ray.ray_dir_y = cub->player.dir_y;
//	ray.map_x = (int)cub->player.pos_x;
//	ray.map_y = (int)cub->player.pos_y;
//	setup_dda(cub, &ray);
//	perform_dda(&ray, cub->map.map);
//	if ((ray.hit == 2 || ray.hit == 3) && ray.perp_wall_dist <= max_dist)
//	{
//		if (cub->map.map[ray.map_y][ray.map_x] == '2')
//			cub->map.map[ray.map_y][ray.map_x] = '3';
//		else if (cub->map.map[ray.map_y][ray.map_x] == '3')
//			cub->map.map[ray.map_y][ray.map_x] = '2';
//	}
//}

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

int	keypress_hook(int key_code, t_cub *cub)
{
	printf("%d\n", key_code);
	if (key_code == KEY_W)
		move_w(cub);
	else if (key_code == KEY_A)
		move_a(cub);
	else if (key_code == KEY_S)
		move_s(cub);
	else if (key_code == KEY_D)
		move_d(cub);
	else if (key_code == KEY_LEFT)
		rotate_left(cub);
	else if (key_code == KEY_RIGHT)
		rotate_right(cub);
	else if (key_code == KEY_E)
		interact_door(cub);
	else if (key_code == KEY_ESC)
	{
		printf("Exiting cub3D.\n");
		exit(0);
	}
	return (0);
}

int	loop(t_cub *cub)
{
	paint_background(cub);
	raycasting(cub);
	paint_minimap(cub);
	paint_img(cub);
	return (0);
}

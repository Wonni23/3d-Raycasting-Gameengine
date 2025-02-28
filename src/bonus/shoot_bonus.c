/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:34:21 by donjung           #+#    #+#             */
/*   Updated: 2025/02/21 19:34:22 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	process_ray_hit(char **map, t_ray ray)
{
	char	cell;

	if (ray.side == WALL_X)
		ray.perp_wall_dist = ray.side_dist_x - ray.delta_dist_x;
	else
		ray.perp_wall_dist = ray.side_dist_y - ray.delta_dist_y;
	cell = map[ray.map_y][ray.map_x];
	if (cell == '4')
	{
		if (ray.perp_wall_dist >= 2.5)
			map[ray.map_y][ray.map_x] = '5';
		else
			map[ray.map_y][ray.map_x] = '6';
	}
	else if (cell == '5')
		map[ray.map_y][ray.map_x] = '6';
}

static void	perform_shoot_dda(t_ray *ray, char **map)
{
	char	cell;

	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = WALL_X;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = WALL_Y;
		}
		cell = map[ray->map_y][ray->map_x];
		if (cell == '4' || cell == '5')
			ray->hit = 3;
		else if (cell == '1' || cell == '2')
			return ;
	}
}

void	shoot_ray(t_cub *cub, char **map)
{
	t_ray	ray;
	int		x;

	x = WIDTH / 2;
	init_ray(cub, &ray, x);
	setup_dda_deltadist(&ray);
	setup_dda_step_n_sidedist(cub, &ray);
	ray.hit = 0;
	perform_shoot_dda(&ray, map);
	if (ray.hit == 0)
		return ;
	if (ray.side == WALL_X)
		ray.perp_wall_dist = ray.side_dist_x - ray.delta_dist_x;
	else
		ray.perp_wall_dist = ray.side_dist_y - ray.delta_dist_y;
	process_ray_hit(map, ray);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:36:27 by donjung           #+#    #+#             */
/*   Updated: 2025/02/04 15:38:29 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	init_ray(t_cub *cub, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = cub->player.dir_x + cub->player.plane_x * camera_x;
	ray->ray_dir_y = cub->player.dir_y + cub->player.plane_y * camera_x;
	ray->map_x = (int)cub->player.pos_x;
	ray->map_y = (int)cub->player.pos_y;
}

/*	delta_dist_x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x))
	delta_dist_y = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y))

	But this can be simplified to:
	delta_dist_x = abs(|v| / ray_dir_x)
	delta_dist_y = abs(|v| / ray_dir_y)

	Where |v| is the length of the vector ray_dir_x, ray_dir_y
	(that is sqrt(ray_dir_x * ray_dir_x + ray_dir_y * ray_dir_y)).
	
	However, we can use 1 instead of |v|, 
	because only the *ratio* between them matters (not the actual distance)
	so we get:

	delta_dist_x = abs(1 / ray_dir_x)
	delta_dist_y = abs(1 / ray_dir_y)	*/

void	setup_dda_deltadist(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

/*	Using similarity between right triangles to get side_dist_x
	so we get:

	side_dist_x : delta_dist_x = (map + 1) - pos_x : 1
	side_dise_t = delta_dist_x(map + 1 - pos_x) */

void	setup_dda_step_n_sidedist(t_cub *cub, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cub->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cub->player.pos_x) \
		* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cub->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cub->player.pos_y) \
		* ray->delta_dist_y;
	}
}

void	setup_dda(t_cub *cub, t_ray *ray, int x)
{
	init_ray(cub, ray, x);
	setup_dda_deltadist(ray);
	setup_dda_step_n_sidedist(cub, ray);
}

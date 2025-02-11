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

#include "../../include/cub3d.h"

void	init_ray(t_cub *cub, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = cub->player.dir_x + cub->player.plane_x * camera_x;
	ray->ray_dir_y = cub->player.dir_y + cub->player.plane_y * camera_x;
	ray->map_x = (int)cub->player.pos_x;
	ray->map_y = (int)cub->player.pos_y;
}

void	setup_dda(t_cub *cub, t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
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

void	perform_dda(t_ray *ray, char **map)
{
	ray->hit = 0;
	while (!ray->hit)
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
		if (map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
		else if (map[ray->map_y][ray->map_x] == '2')
			ray->hit = 2;
	}
	if (ray->side == WALL_X)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

void	calculate_line_height(t_ray *ray, t_texturing *tex)
{
	tex->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	tex->draw_start = (-tex->line_height / 2) + (HEIGHT / 2);
	tex->draw_end = (tex->line_height / 2) + (HEIGHT / 2);
	if (tex->draw_start < 0)
	{
		tex->draw_start = 0;
	}
	if (tex->draw_end >= HEIGHT)
	{
		tex->draw_end = HEIGHT - 1;
	}
}

void	calculate_texture_coords(t_cub *cub, t_ray *ray, t_texturing *tex)
{
	if (ray->side == WALL_X)
		tex->wall_x = cub->player.pos_y \
		+ (ray->perp_wall_dist * ray->ray_dir_y);
	else
		tex->wall_x = cub->player.pos_x \
		+ (ray->perp_wall_dist * ray->ray_dir_x);
	tex->wall_x -= floor(tex->wall_x);
	tex->tex_x = (int)(tex->wall_x * (double)TEX_WIDTH);
	if (ray->side == WALL_X && ray->ray_dir_x < 0)
		tex->tex_x = TEX_WIDTH - tex->tex_x - 1;
	if (ray->side == WALL_Y && ray->ray_dir_y > 0)
		tex->tex_x = TEX_WIDTH - tex->tex_x - 1;
	tex->step = 1.0 * TEX_HEIGHT / tex->line_height;
	tex->tex_pos = (tex->draw_start - HEIGHT / 2 \
		+ tex->line_height / 2) * tex->step;
}

void	set_buffer(t_cub *cub, t_ray *ray, t_texturing *tex, int x)
{
	int		color;
	int		y;

	y = tex->draw_start;
	while (y < tex->draw_end)
	{
		tex->tex_y = (int)tex->tex_pos & (TEX_HEIGHT - 1);
		if (ray->hit == 2)
			color = cub->img.door[TEX_HEIGHT * tex->tex_y + tex->tex_x];
		else if (ray->side == WALL_X)
		{
			if (ray->ray_dir_x >= 0)
				color = cub->img.walls[E][TEX_HEIGHT * tex->tex_y + tex->tex_x];
			else
				color = cub->img.walls[W][TEX_HEIGHT * tex->tex_y + tex->tex_x];
		}
		else if (ray->side == WALL_Y)
		{
			if (ray->ray_dir_y >= 0)
				color = cub->img.walls[S][TEX_HEIGHT * tex->tex_y + tex->tex_x];
			else
				color = cub->img.walls[N][TEX_HEIGHT * tex->tex_y + tex->tex_x];
		}
		cub->img.buffer[y][x] = color;
		tex->tex_pos += tex->step;
		y++;
	}
}

void	raycasting(t_cub *cub)
{
	int			x;
	t_ray		ray;
	t_texturing	tex;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(cub, &ray, x);
		setup_dda(cub, &ray);
		perform_dda(&ray, cub->map.map);
		calculate_line_height(&ray, &tex);
		calculate_texture_coords(cub, &ray, &tex);
		set_buffer(cub, &ray, &tex, x);
		x++;
	}
}

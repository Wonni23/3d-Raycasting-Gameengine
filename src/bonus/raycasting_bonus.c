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
		tex->tex_x = (TEX_WIDTH - 1) - tex->tex_x;
	if (ray->side == WALL_Y && ray->ray_dir_y > 0)
		tex->tex_x = (TEX_WIDTH - 1) - tex->tex_x;
	tex->step = 1.0 * TEX_HEIGHT / tex->line_height;
	tex->tex_pos = (tex->draw_start - HEIGHT / 2 \
		+ tex->line_height / 2) * tex->step;
}

int	set_buffer_choose_img(t_cub *cub, t_ray *ray, t_texturing *tex)
{
	if (ray->hit == 2)
		return (cub->img.door[TEX_HEIGHT * tex->tex_y + tex->tex_x]);
	else if (ray->side == WALL_X)
	{
		if (ray->ray_dir_x >= 0)
			return (cub->img.walls[E][TEX_HEIGHT * tex->tex_y + tex->tex_x]);
		else
			return (cub->img.walls[W][TEX_HEIGHT * tex->tex_y + tex->tex_x]);
	}
	else if (ray->side == WALL_Y)
	{
		if (ray->ray_dir_y >= 0)
			return (cub->img.walls[S][TEX_HEIGHT * tex->tex_y + tex->tex_x]);
		else
			return (cub->img.walls[N][TEX_HEIGHT * tex->tex_y + tex->tex_x]);
	}
	return (0);
}

void	set_buffer(t_cub *cub, t_ray *ray, t_texturing *tex, int x)
{
	int		color;
	int		y;

	y = tex->draw_start;
	while (y < tex->draw_end)
	{
		tex->tex_y = (int)tex->tex_pos & (TEX_HEIGHT - 1);
		color = set_buffer_choose_img(cub, ray, tex);
		cub->img.buffer[y][x] = color;
		tex->tex_pos += tex->step;
		y++;
	}
}

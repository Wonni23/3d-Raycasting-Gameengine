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

void	raycasting(t_cub *cub)
{
	int			x;
	t_ray		ray;
	t_texturing	tex;

	x = 0;
	while (x < WIDTH)
	{
		setup_dda(cub, &ray, x);
		perform_dda(&ray, cub->map.map);
		cub->zbuffer[x] = ray.perp_wall_dist;
		calculate_line_height(&ray, &tex);
		calculate_texture_coords(cub, &ray, &tex);
		set_buffer(cub, &ray, &tex, x);
		x++;
	}
}

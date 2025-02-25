/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:07:23 by donjung           #+#    #+#             */
/*   Updated: 2025/02/07 17:07:24 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
	2D Rotation Matrix

	[x'] = {cos(θ)	-sin(θ)}
	[y']   {sin(θ)	 cos(θ)}
*/

void	rotate_left(t_cub *cub)
{
	double	old_dirx;
	double	old_diry;
	double	old_planex;
	double	old_planey;

	old_dirx = cub->player.dir_x;
	old_diry = cub->player.dir_y;
	old_planex = cub->player.plane_x;
	old_planey = cub->player.plane_y;
	cub->player.dir_x = old_dirx * cos(RTSPEED_L) - old_diry * sin(RTSPEED_L);
	cub->player.dir_y = old_dirx * sin(RTSPEED_L) + old_diry * cos(RTSPEED_L);
	cub->player.plane_x = old_planex * cos(RTSPEED_L) \
		- old_planey * sin(RTSPEED_L);
	cub->player.plane_y = old_planex * sin(RTSPEED_L) \
		+ old_planey * cos(RTSPEED_L);
}

void	rotate_right(t_cub *cub)
{
	double	old_dirx;
	double	old_diry;
	double	old_planex;
	double	old_planey;

	old_dirx = cub->player.dir_x;
	old_diry = cub->player.dir_y;
	old_planex = cub->player.plane_x;
	old_planey = cub->player.plane_y;
	cub->player.dir_x = old_dirx * cos(RTSPEED_R) - old_diry * sin(RTSPEED_R);
	cub->player.dir_y = old_dirx * sin(RTSPEED_R) + old_diry * cos(RTSPEED_R);
	cub->player.plane_x = old_planex * cos(RTSPEED_R) \
		- old_planey * sin(RTSPEED_R);
	cub->player.plane_y = old_planex * sin(RTSPEED_R) \
		+ old_planey * cos(RTSPEED_R);
}

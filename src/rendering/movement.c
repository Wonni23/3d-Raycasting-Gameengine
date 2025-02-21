/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:39:15 by donjung           #+#    #+#             */
/*   Updated: 2025/02/06 18:39:17 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	collide_wall(t_cub *cub, double x, double y)
{
	return (
		cub->map.map[(int)(y + 0.2)][(int)(x + 0.2)] == '1' ||
		cub->map.map[(int)(y - 0.2)][(int)(x - 0.2)] == '1' ||
		cub->map.map[(int)(y + 0.2)][(int)(x - 0.2)] == '1' ||
		cub->map.map[(int)(y - 0.2)][(int)(x + 0.2)] == '1' ||
		cub->map.map[(int)(y + 0.2)][(int)(x + 0.2)] == '2' ||
		cub->map.map[(int)(y - 0.2)][(int)(x - 0.2)] == '2' ||
		cub->map.map[(int)(y + 0.2)][(int)(x - 0.2)] == '2' ||
		cub->map.map[(int)(y - 0.2)][(int)(x + 0.2)] == '2'
	);
}

void	move_w(t_cub *cub)
{
	double	mv_pos_x;
	double	mv_pos_y;

	mv_pos_x = cub->player.pos_x + cub->player.dir_x * MVSPEED;
	mv_pos_y = cub->player.pos_y + cub->player.dir_y * MVSPEED;
	if (!collide_wall(cub, mv_pos_x, mv_pos_y))
	{
		cub->player.pos_x = mv_pos_x;
		cub->player.pos_y = mv_pos_y;
	}
}

void	move_s(t_cub *cub)
{
	double	mv_pos_x;
	double	mv_pos_y;

	mv_pos_x = cub->player.pos_x - cub->player.dir_x * MVSPEED;
	mv_pos_y = cub->player.pos_y - cub->player.dir_y * MVSPEED;
	if (!collide_wall(cub, mv_pos_x, mv_pos_y))
	{
		cub->player.pos_x = mv_pos_x;
		cub->player.pos_y = mv_pos_y;
	}
}

void	move_a(t_cub *cub)
{
	double	perp_x;
	double	perp_y;
	double	mv_pos_x;
	double	mv_pos_y;

	perp_x = -cub->player.dir_y;
	perp_y = cub->player.dir_x;
	mv_pos_x = cub->player.pos_x - perp_x * MVSPEED;
	mv_pos_y = cub->player.pos_y - perp_y * MVSPEED;
	if (!collide_wall(cub, mv_pos_x, mv_pos_y))
	{
		cub->player.pos_x = mv_pos_x;
		cub->player.pos_y = mv_pos_y;
	}
}

void	move_d(t_cub *cub)
{
	double	perp_x;
	double	perp_y;
	double	mv_pos_x;
	double	mv_pos_y;

	perp_x = cub->player.dir_y;
	perp_y = -cub->player.dir_x;
	mv_pos_x = cub->player.pos_x - perp_x * MVSPEED;
	mv_pos_y = cub->player.pos_y - perp_y * MVSPEED;
	if (!collide_wall(cub, mv_pos_x, mv_pos_y))
	{
		cub->player.pos_x = mv_pos_x;
		cub->player.pos_y = mv_pos_y;
	}
}

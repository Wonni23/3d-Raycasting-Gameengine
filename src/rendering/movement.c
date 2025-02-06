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

void	move_w(t_cub *cub)
{
	//if (!collide_wall)
	//{
		cub->player.pos_x += cub->player.dir_x * MVSPEED;
		cub->player.pos_y += cub->player.dir_y * MVSPEED;
	//}
}

void	move_s(t_cub *cub)
{
	//if (!collide_wall)
	//{
		cub->player.pos_x -= cub->player.dir_x * MVSPEED;
		cub->player.pos_y -= cub->player.dir_y * MVSPEED;
	//}
}

void	move_a(t_cub *cub)
{
	//if (!collide_wall)
	//{
		cub->player.pos_x -= cub->player.dir_x * MVSPEED;
		cub->player.pos_y -= cub->player.dir_y * MVSPEED;
	//}
}

void	move_d(t_cub *cub)
{
	//if (!collide_wall)
	//{
		cub->player.pos_x -= cub->player.dir_x * MVSPEED;
		cub->player.pos_y -= cub->player.dir_y * MVSPEED;
	//}
}
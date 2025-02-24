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

int	ft_click(int button, int x, int y, void *param)
{
	t_cub	*cub;

	(void)x;
	(void)y;
	cub = (t_cub *)param;
	if (button == 1)
	{
		cub->b.anim_on = 1;
		cub->b.anim_frame = 1;
		cub->b.anim_lasttime = get_current_time_micro();
	}
	return (0);
}

int	ft_mouse(int x, int y, t_cub *cub)
{
	int	mv_pos;

	mlx_mouse_hide(cub->mlx, cub->win);
	if (x == WIDTH / 2 && y == HEIGHT / 2)
		return (0);
	mv_pos = x - (WIDTH / 2);
	if (abs(mv_pos) < 10)
		return (0);
	if (mv_pos > 0)
		rotate_right(cub);
	else
		rotate_left(cub);
	mlx_mouse_move(cub->mlx, cub->win, WIDTH / 2, HEIGHT / 2);
	loop(cub);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisopark <lotooska@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:21:38 by jisopark          #+#    #+#             */
/*   Updated: 2025/02/06 13:47:19 by jisopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	orientation_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

int	valid_chars(char c)
{
	return (ft_isspace(c) || orientation_player(c) || \
	c == '0' || c == '1');

static void	set_player(t_cub *cub, int x, int y)
{
	cub->player.status = cub->map.map[y][x];
	cub->map.map[y][x] = '0';
	cub->player.pos_x = x * 64 + 5.5;
	cub->player.pos_y = y * 64 + 5.5;
	cub->num_player = 1;
}

static int	check_invalid_char(t_cub *cub)
{
	int	y;
	int	x;

	y = -1;
	x = 0;
	while (cub->map.map[++y])
	{
		x = -1;
		while (cub->map.map[y][++x])
		{
			if (!valid_chars(cub->map.map[y][x]))
				return (1);
			if (orientation_player(cub->map.map[y][x]))
				set_player(cub, x, y);
		}
		cub->map.map_width = (x * 64) * (cub->map.map_width / 64 < x) + \
		(cub->map.map_width / 64 >= x) * (cub->map.map_width);
	}
	cub->map.map_height = y * 64;
	return (cub->num_player != 1);
}

void	check_map(t_cub *cub, char **path)
{
	if (check_invalid_char(cub))
		exit_f();
}

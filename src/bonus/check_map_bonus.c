/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisopark <lotooska@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:54:15 by jisopark          #+#    #+#             */
/*   Updated: 2025/02/11 20:55:09 by jisopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	orientation_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static int	valid_chars(char c)
{
	return (ft_isspace(c) || orientation_player(c) || \
	c == '0' || c == '1' || c == '2');
}

static void	set_player(t_cub *cub, int x, int y)
{
	cub->player.status = cub->map.map[y][x];
	cub->player.pos_x = x + 0.5;
	cub->player.pos_y = y + 0.5;
}

static int	check_invalid_char(t_cub *cub)
{
	int	y;
	int	x;

	y = -1;
	x = 0;
	cub->map.num_player = 0;
	while (cub->map.map[++y])
	{
		x = -1;
		while (cub->map.map[y][++x])
		{
			if (!valid_chars(cub->map.map[y][x]))
				return (1);
			if (orientation_player(cub->map.map[y][x]))
			{
				cub->map.num_player++;
				if (cub->map.num_player != 1)
					return (1);
				set_player(cub, x, y);
			}
		}
	}
	cub->map.map_height = y;
	return (0);
}

void	check_map(t_cub *c, char **path)
{
	int	y;

	if (check_invalid_char(c))
	{
		printf("The map must valid chars and one player position\n");
		ft_exit(c, path, 0);
	}
	if (c->map.num_player == 0)
	{
		printf("The player must exist\n");
		ft_exit(c, path, 0);
	}
	y = -1;
	c->map.map_width = ft_strlen(c->map.map[0]);
	while (c->map.map[++y])
	{
		if (y >= 1 && ft_strlen(c->map.map[y]) > ft_strlen(c->map.map[y - 1]) \
		&& (int)ft_strlen(c->map.map[y]) > c->map.map_width)
			c->map.map_width = ft_strlen(c->map.map[y]);
	}
	check_map_closed(c, path);
	check_map_empty(c, path);
}

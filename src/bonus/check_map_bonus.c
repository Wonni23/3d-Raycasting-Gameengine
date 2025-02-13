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

#include "../../include/cub3d.h"

static int	orientation_player(char c)
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
	//cub->map.map[y][x] = '0';
	cub->player.pos_x = x + 0.5;
	cub->player.pos_y = y + 0.5;
}

static int	check_invalid_char(t_cub *cub)
{
	int	y;
	int	x;

	y = -1;
	x = 0;
	cub->num_player = 0;
	while (cub->map.map[++y])
	{
		x = -1;
		while (cub->map.map[y][++x])
		{
			if (!valid_chars(cub->map.map[y][x]))
				return (1);
			if (orientation_player(cub->map.map[y][x]))
			{
				cub->num_player++;
				if (cub->num_player != 1)
					return (1);
				set_player(cub, x, y);
			}
		}
	}
	cub->map.map_height = y;
	return (0);
}

void	check_map(t_cub *cub)
{
	int	y;

	if (check_invalid_char(cub))
	{
		printf("The map must valid chars and one player position\n");
		free_matrix((void ***)&cub->map.map);
		exit(1);
	}
	if (cub->num_player == 0)
	{
		printf("The player must exist\n");
		free_matrix((void ***)&cub->map.map);
		exit(1);
	}
	y = -1;
	cub->map.map_width = ft_strlen(cub->map.map[0]);
	while (cub->map.map[++y])
	{
		if (y >= 1 && ft_strlen(cub->map.map[y]) > ft_strlen(cub->map.map[y - 1]) \
		&& (int)ft_strlen(cub->map.map[y]) > cub->map.map_width)
			cub->map.map_width = ft_strlen(cub->map.map[y]);
	}
	check_map_closed(cub);
	check_map_empty(cub);
}

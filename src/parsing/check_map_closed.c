/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisopark <lotooska@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:24:23 by jisopark          #+#    #+#             */
/*   Updated: 2025/02/07 23:19:21 by jisopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	check_line_change_r(t_cub *c, char **path)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (c->map.map[++y])
	{
		x = 0;
		if (ft_strlen(c->map.map[y]) < ft_strlen(c->map.map[y - 1]))
		{
			x = ft_strlen(c->map.map[y]) - 1;
			while (c->map.map[y - 1][x++])
				if (c->map.map[y - 1][x] == '0' || c->map.map[y - 1][x] == ' ')
					ft_exit(c, path, 1);
		}
		if (ft_strlen(c->map.map[y]) > ft_strlen(c->map.map[y - 1]))
		{
			x = ft_strlen(c->map.map[y - 1]) - 1;
			while (c->map.map[y][x++])
				if (c->map.map[y][x] == '0' || c->map.map[y][x] == ' ')
					ft_exit(c, path, 1);
		}
	}
}

static void	check_line_change_l(t_cub *c, char **path)
{
	int	x;
	int	y;

	y = 0;
	x = -1;
	while (c->map.map[++y])
	{
		if (!ft_isspace(c->map.map[y][0]) && ft_isspace(c->map.map[y - 1][0]))
		{
			x = -1;
			while (ft_isspace(c->map.map[y - 1][++x]))
				if (c->map.map[y][x] == '0' || c->map.map[y][x] == ' ')
					ft_exit(c, path, 1);
		}
		if (ft_isspace(c->map.map[y][0]) && !ft_isspace(c->map.map[y - 1][0]))
		{
			x = -1;
			while (ft_isspace(c->map.map[y][++x]))
				if (c->map.map[y - 1][x] == '0' || c->map.map[y - 1][x] == ' ')
					ft_exit(c, path, 1);
		}
	}
}

static void	check_front_back(t_cub *c, char **path)
{
	int	y;

	y = 0;
	if (ft_strchr(c->map.map[y], '0') || ft_strchr(c->map.map[y], 'N') \
	|| ft_strchr(c->map.map[y], 'S') || ft_strchr(c->map.map[y], 'W') \
	|| ft_strchr(c->map.map[y], 'E'))
		ft_exit(c, path, 1);
	while (c->map.map[y])
		y++;
	if (ft_strchr(c->map.map[y - 1], '0') || ft_strchr(c->map.map[y - 1], 'N') \
	|| ft_strchr(c->map.map[y - 1], 'S') || ft_strchr(c->map.map[y - 1], 'W') \
	|| ft_strchr(c->map.map[y - 1], 'E'))
		ft_exit(c, path, 1);
}

static void	check_first_c_last_c(t_cub *cub, char **path)
{
	int	x;
	int	y;

	x = 0;
	y = -1;
	while (cub->map.map[++y])
	{
		x = 0;
		while (ft_isspace(cub->map.map[y][x]))
			x++;
		if (cub->map.map[y][x] == '0')
			ft_exit(cub, path, 1);
	}
	x = 0;
	y = -1;
	while (cub->map.map[++y])
	{
		x = 0;
		while (cub->map.map[y][x])
			x++;
		if (cub->map.map[y][x - 2] == '0')
			ft_exit(cub, path, 1);
	}
}

void	check_map_closed(t_cub *cub, char **path)
{
	int	y;
	int	x;

	x = -1;
	while (cub->map.map[0][++x])
		if (orientation_player(cub->map.map[0][x]))
			ft_exit(cub, path, 1);
	y = 0;
	while (cub->map.map[y])
		y++;
	y--;
	x = -1;
	while (cub->map.map[y][++x])
		if (orientation_player(cub->map.map[y][x]))
			ft_exit(cub, path, 1);
	if (!ft_strchr(cub->map.map[y], '1'))
		ft_exit(cub, path, 1);
	check_first_c_last_c(cub, path);
	check_front_back(cub, path);
	check_line_change_l(cub, path);
	check_line_change_r(cub, path);
}

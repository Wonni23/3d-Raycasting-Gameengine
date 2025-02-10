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

#include "cub3d"

static void	check_line_change(t_cub *cub)
{
	int	x;
	int	y;

	

static void	check_front_back(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (ft_strchr(cub->map.map[y], '0'))
		ft_exit(cub);
	while (cub->map.map[y][x] != '\n')
		x++;
	if (cub->map.map[y + 1][x] == '0')
		ft_exit(cub);
	x = 0;
	while (cub->map.map[y][x])
		y++;
	if (ft_strchr(cub->map.map[y], '0'))
		ft_exit(cub);
	while (cub->map.map[y][x])
		x++;
	if (cub->map.map[y - 1][x] == '0')
		ft_exit(cub);
}

static void	check_first_c_last_c(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y = -1;
	while (cub->map.map[++y])
	{
		while (ft_issapce(cub->map.map[y][x]))
			x++;
		if (cub->map.map[y][x] == '0')
			ft_exit(cub);
	}
	x = 0;
	y = -1;
	while (cub->map.map[++y])
	{
		while (cub->map.map[y][x])
			x++;
		if (cub->map.map[y][x - 2] == '0')
			ft_exit(cub);
	}
}

void	check_map_closed(t_cub *cub)
{
	check_first_c_last_c(cub);
	check_front_back(cub);
	check_line_change(cub);
}

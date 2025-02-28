/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_empty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisopark <lotooska@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:14:06 by jisopark          #+#    #+#             */
/*   Updated: 2025/02/11 18:14:10 by jisopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	check_midlines_space(t_cub *cub, char **path, char *s, int y)
{
	int	x;

	x = 0;
	while (s[0] && s[++x])
	{
		if (s[x] == ' ' && (s[x - 1] == '0' || s[x + 1] == '0' || \
		s[x - 1] == '2' || s[x + 1] == '2' || \
		s[x - 1] == '4' || s[x + 1] == '4' || \
		cub->map.map[y - 1][x] == '0' || cub->map.map[y + 1][x] == '0' || \
		cub->map.map[y - 1][x] == '2' || cub->map.map[y + 1][x] == '2' || \
		cub->map.map[y - 1][x] == '4' || cub->map.map[y + 1][x] == '4'))
			ft_exit(cub, path, 1);
	}
}

void	check_map_empty(t_cub *cub, char **path)
{
	int		y;
	char	*s;

	check_first_line_space(cub, path);
	check_last_line_space(cub, path);
	check_player_around_space(cub, path);
	y = 0;
	while (cub->map.map[y + 1])
		y++;
	while (y-- > 1)
	{
		s = cub->map.map[y];
		check_midlines_space(cub, path, s, y);
	}
}

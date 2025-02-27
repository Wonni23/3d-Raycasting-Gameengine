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
	while (s[0] && ++x != cub->map.s_len)
	{
		if ((ft_strchr(s, ' ') && ft_strchr(cub->map.map[y - 1], '0')) || \
		(ft_strchr(s, ' ') && ft_strchr(cub->map.map[y + 1], '0')))
		{
			if (s[x] == ' ' && (s[x - 1] == '0' || s[x + 1] == '0' || \
			cub->map.map[y - 1][x] == '0' || cub->map.map[y + 1][x] == '0'))
			{
				free_array(s);
				ft_exit(cub, path, 2);
			}
		}
	}
}

static void	checking_idx_init(t_cub *cub, char *s, int y)
{
	cub->map.s_len = ft_strlen(s);
	cub->map.forward_len = ft_strlen(cub->map.map[y - 1]);
	cub->map.back_len = ft_strlen(cub->map.map[y + 1]);
	if (cub->map.s_len > cub->map.forward_len || \
	cub->map.s_len > cub->map.back_len)
	{
		if (cub->map.forward_len > cub->map.back_len)
			cub->map.s_len = cub->map.back_len;
		else
			cub->map.s_len = cub->map.forward_len;
	}
}

// static void	check_again(t_cub *cub, char **path, char *s)
// {
// 	int	x;

// 	x = 0;
// 	while (s[++x] != '\n')
// 	{
// 		if (s[x] && s[x + 1] && s[x] == '0' && (s[x - 1] == ' ' || s[x + 1] == ' '))
// 			ft_exit(cub, path, 2);
// 	}
// }

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
		s = trim_it(cub->map.map[y], " \n\t");
		checking_idx_init(cub, s, y);
		check_midlines_space(cub, path, s, y);
		//check_again(cub, path, s);
		free_array(s);
	}
}

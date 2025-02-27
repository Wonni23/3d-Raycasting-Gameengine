/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisopark <lotooska@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:44:14 by jisopark          #+#    #+#             */
/*   Updated: 2025/02/27 15:44:17 by jisopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*trim_it(char *s1, char *set)
{
	size_t	s1_len;
	size_t	i;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	s1_len = ft_strlen(s1);
	while (s1_len > 0 && ft_strchr(set, s1[s1_len - 1]))
		s1_len--;
	dest = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		dest[i] = s1[i];
	dest[s1_len] = '\0';
	return (dest);
}

void	check_player_around_space(t_cub *cub, char **path)
{
	int	x;
	int	y;

	x = 0;
	y = 1;
	while (cub->map.map[y + 1])
	{
		x = -1;
		while (cub->map.map[y][++x])
		{
			if (orientation_player(cub->map.map[y][x]) && \
			(ft_isspace(cub->map.map[y][x + 1])
			|| ft_isspace(cub->map.map[y][x - 1])))
				ft_exit(cub, path, 2);
			if (orientation_player(cub->map.map[y][x]) && \
			ft_strlen(cub->map.map[y + 1]) < 2)
				ft_exit(cub, path, 2);
			if (orientation_player(cub->map.map[y][x]) && \
			(cub->map.map[y + 1][x] == '\n'
			|| cub->map.map[y + 1][x] == 0))
				ft_exit(cub, path, 2);
		}
		y++;
	}
}

void	check_last_line_space(t_cub *cub, char **path)
{
	int		x;
	int		y;
	char	*s;

	y = 0;
	while (cub->map.map[y])
		y++;
	y--;
	s = trim_it(cub->map.map[y], " \n\t");
	x = -1;
	while (s[++x])
	{
		if (ft_isspace(s[x]) && cub->map.map[y - 1][x] == '0')
		{
			free_array(s);
			ft_exit(cub, path, 2);
		}
	}
	if (!s[x] && cub->map.map[y - 1][x] == '0')
	{
		free_array(s);
		ft_exit(cub, path, 2);
	}
	free_array(s);
}

void	check_first_line_space(t_cub *cub, char **path)
{
	int		x;
	char	*s;

	x = -1;
	s = trim_it(cub->map.map[0], " \n\t");
	while (s[++x])
	{
		if (ft_isspace(s[x]) && cub->map.map[1][x] == '0')
		{
			free_array(s);
			ft_exit(cub, path, 2);
		}
	}
	free_array(s);
}

int	line_len_check(t_cub *c, int y)
{
	if ((ft_strlen(c->map.map[y]) < ft_strlen(c->map.map[y - 1])) && \
	ft_strchr(c->map.map[y], '1'))
		return (1);
	if ((ft_strlen(c->map.map[y]) > ft_strlen(c->map.map[y - 1])) && \
	ft_strchr(c->map.map[y], '1'))
		return (2);
	return (0);
}

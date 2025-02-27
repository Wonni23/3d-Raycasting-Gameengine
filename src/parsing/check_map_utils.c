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
			|| ft_isspace(cub->map.map[y][x - 1]) \
			|| ft_isspace(cub->map.map[y - 1][x]) \
			|| ft_isspace(cub->map.map[y + 1][x])))
				ft_exit(cub, path, 24);
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
	s = cub->map.map[y];
	x = -1;
	while (s[++x])
	{
		if (ft_isspace(s[x]) && cub->map.map[y - 1][x] == '0')
			ft_exit(cub, path, 1);
	}
	if (!s[x] && cub->map.map[y - 1][x] == '0')
		ft_exit(cub, path, 23);
}

void	check_first_line_space(t_cub *cub, char **path)
{
	int		x;
	char	*s;

	x = -1;
	s = cub->map.map[0];
	while (s[++x])
	{
		if (ft_isspace(s[x]) && cub->map.map[1][x] == '0')
			ft_exit(cub, path, 22);
	}
}

void	dup_tmp_map(t_cub *c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < c->map.map_height && c->map.map[i] != NULL)
	{
		j = 0;
		while (j < c->map.map_width && c->map.map[i][j] != '\0')
		{
			if (c->map.map[i][j] == '\n')
				c->map.tmp[i][j] = ' ';
			else
				c->map.tmp[i][j] = c->map.map[i][j];
			j++;
		}
		i++;
	}
	free_matrix((void ***)&c->map.map);
	c->map.map = c->map.tmp;
	c->map.tmp = NULL;
}

void	fill_space_n_dup_map(t_cub *c, char **path)
{
	int	i;

	c->map.tmp = (char **)malloc(sizeof(char *) * (c->map.map_height + 1));
	if (!c->map.tmp)
	{
		printf("Error\nmalloc failed\n");
		ft_exit(c, path, 0);
	}
	i = 0;
	while (i < c->map.map_height)
	{
		c->map.tmp[i] = (char *)malloc(sizeof(char) * (c->map.map_width + 1));
		if (!c->map.tmp[i])
		{
			printf("Error\nmalloc failed\n");
			ft_exit(c, path, 0);
		}
		ft_memset(c->map.tmp[i], ' ', c->map.map_width);
		c->map.tmp[i][c->map.map_width] = '\0';
		i++;
	}
	c->map.tmp[c->map.map_height] = NULL;
	dup_tmp_map(c);
}

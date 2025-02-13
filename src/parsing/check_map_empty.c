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

static void check_last_line_space(t_cub *cub, char **path)
{
    int x;
    int y;

    y = 0;
    while (cub->map.map[y])
        y++;
    y--;
    x = -1;
    while (cub->map.map[y][++x])
    {
        if (ft_isspace(cub->map.map[y][x]) && cub->map.map[y - 1][x] == '0')
            {
                    printf("11\n");
                    ft_exit(cub, path, 1);
                }
    }
}

static void check_first_line_space(t_cub *cub, char **path)
{
    int x;

    x = -1;
    while (cub->map.map[0][++x])
    {
        if (ft_isspace(cub->map.map[0][x]) && cub->map.map[1][x] == '0')
            {
                    printf("12\n");
                    ft_exit(cub, path, 1);
                }
    }
}

void    check_map_empty(t_cub *cub, char **path)
{
    int x;
    int y;

    check_first_line_space(cub, path);
    check_last_line_space(cub, path);
    x = 0;
    y = 0;
    while (cub->map.map[y])
        y++;
    y -= 1;
    while (y-- > 1)
    {
        x = 0;
        while (cub->map.map[y][++x])
        {
            if (ft_isspace(cub->map.map[y][x]) && (cub->map.map[y - 1][x] == '0'\
            || cub->map.map[y + 1][x] == '0' || cub->map.map[y][x - 1] == '0'\
            || cub->map.map[y][x + 1] == '0'))
            {
                printf("13\n");
                ft_exit(cub, path, 1);
            }
        }
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisopark <lotooska@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:33:31 by jisopark          #+#    #+#             */
/*   Updated: 2025/02/17 19:33:52 by jisopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    check_including_letter(t_parse *parse, char *s)
{
    int i;

    i = -1;
    if (s[0] == ',')
        exit_parse(NULL, 1, \
			"C or F must have 3 intergers separeted by a coma", parse);
    while (s[++i])
    {
        if (!ft_isdigit(s[i]) && s[i] != ',' && !(s[i] > 8 && s[i] < 14))
            exit_parse(NULL, 1, \
			"C or F must not contain any characters", parse);
    }
}

void	check_image_order(t_parse *parse, char *s)
{
	if (*s == 'N')
		parse->num_vars = 0;
	if (*s == 'S')
		parse->num_vars = 1;
	if (*s == 'W')
		parse->num_vars = 2;
	if (*s == 'E')
		parse->num_vars = 3;
}

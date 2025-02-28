/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:22:17 by donjung           #+#    #+#             */
/*   Updated: 2025/02/10 21:05:55 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/* draw_vertical_stripe: Render one vertical pixel of a sprite stripe 
   using the sprite's tex_x, stripe, and sprite_height */
static void	draw_vertical_stripe(t_cub *cub, int y, t_sprite *sprite)
{
	int	d;
	int	tex_y;
	int	color;

	d = y * 256 - HEIGHT * 128 + sprite->sprite_height * 128;
	tex_y = ((d * TEX_HEIGHT) / sprite->sprite_height) / 256;
	color = cub->img.enemy[sprite->status - '0' - 4] \
	[(TEX_HEIGHT * tex_y) + sprite->tex_x];
	if ((color & 0x00FFFFFF) != 0)
		cub->img.buffer[y][sprite->stripe] = color;
}

/* render_sprite_stripe: For a given vertical stripe, set the sprite's 
   texture X coordinate and stripe index, then render pixels for that stripe */
void	render_sprite_stripe(t_cub *cub, t_sprite sprite, int stripe)
{
	int	y;

	sprite.tex_x = (int)(256 * (stripe - (-sprite.width / 2 \
		+ sprite.screen_x)) * TEX_WIDTH / sprite.width) / 256;
	sprite.stripe = stripe;
	y = sprite.draw_start_y;
	while (y < sprite.draw_end_y)
	{
		draw_vertical_stripe(cub, y, &sprite);
		y++;
	}
}

/* render_single_sprite: Render an individual sprite on screen */
void	render_single_sprite(t_cub *cub, t_sprite sprite, double *z_buffer)
{
	int	draw_start_x;
	int	draw_end_x;
	int	stripe;

	compute_sprite_projection(&sprite);
	draw_start_x = -sprite.width / 2 + sprite.screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = sprite.width / 2 + sprite.screen_x;
	if (draw_end_x >= WIDTH)
		draw_end_x = WIDTH - 1;
	stripe = draw_start_x;
	while (stripe < draw_end_x)
	{
		if (sprite.transform_y > 0 && sprite.transform_y <= z_buffer[stripe])
			render_sprite_stripe(cub, sprite, stripe);
		stripe++;
	}
}

/* render_enemy_sprites: 
	Allocate, sort, transform, and render all enemy sprites */
void	render_enemy_sprites(t_cub *cub, double *z_buffer)
{
	t_sprite	*sprites;
	int			sprite_count;
	int			total;
	int			i;

	total = cub->map.map_width * cub->map.map_height;
	sprites = malloc(sizeof(t_sprite) * total);
	if (!sprites)
		return ;
	sprite_count = 0;
	fill_sprite_array(cub, sprites, &sprite_count);
	sort_sprites(sprites, sprite_count);
	transform_sprites(cub, sprites, sprite_count);
	i = 0;
	while (i < sprite_count)
	{
		render_single_sprite(cub, sprites[i], z_buffer);
		i++;
	}
	free(sprites);
}

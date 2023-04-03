/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_texture.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 15:59:50 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/13 14:11:34 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42/MLX42_Int.h>
#include <so_long.h>

uint8_t	*split_text(mlx_texture_t *text, uint32_t xy[2], uint32_t wh[2])
{
	uint8_t			*pixelx;
	uint8_t			*pixeli;
	uint8_t			*pixels;
	int				y;

	if (wh[0] > text->width || wh[1] > text->height)
		return ((void *)mlx_error(MLX_INVDIM));
	if (xy[0] > text->width || xy[1] > text->height)
		return ((void *)mlx_error(MLX_INVPOS));
	pixels = malloc(wh[0] * wh[1] * sizeof(uint32_t));
	if (!pixels)
		ft_error("so_long", ENOMEM);
	y = -1;
	while ((uint32_t)++y < wh[1])
	{
		pixelx = &text->pixels[((xy[1] + y) * text->width + xy[0]) * BPP];
		pixeli = &pixels[y * wh[0] * BPP];
		ft_memmove(pixeli, pixelx, wh[0] * BPP);
	}
	return (pixels);
}

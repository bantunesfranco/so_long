/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_texture.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 15:59:50 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/10 11:06:24 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../MLX42/include/MLX42/MLX42_Int.h"
#include "../../MLX42/include/MLX42/MLX42.h"
#include "../../libft/incs/libft.h"

mlx_texture_t	*mlx_texture_area_to_texture(mlx_texture_t *texture, \
uint32_t xy[2], uint32_t wh[2])
{
	mlx_texture_t	*text;
	uint8_t			*pixelx;
	uint8_t			*pixeli;
	uint32_t		y;

	if (wh[0] > texture->width || wh[1] > texture->height)
		return ((void *)mlx_error(MLX_INVDIM));
	if (xy[0] > texture->width || xy[1] > texture->height)
		return ((void *)mlx_error(MLX_INVPOS));
	text = ft_calloc(1, sizeof(mlx_texture_t));
	if (!text)
		return ((void *)mlx_error(MLX_MEMFAIL));
	(*(uint32_t *)&text->width) = wh[0];
	(*(uint32_t *)&text->height) = wh[1];
	text->pixels = ft_calloc(wh[0] * wh[1], sizeof(int32_t));
	text->bytes_per_pixel = BPP;
	y = -1;
	while (++y < wh[1])
	{
		pixelx = &texture->pixels[((xy[1] + y) * texture->width + xy[0]) * BPP];
		pixeli = &text->pixels[y * wh[0] * BPP];
		ft_memmove(pixeli, pixelx, wh[0] * BPP);
	}
	return (text);
}

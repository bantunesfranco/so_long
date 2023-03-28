/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_to_img.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/28 17:07:10 by bfranco       #+#    #+#                 */
/*   Updated: 2023/03/28 17:39:00 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>
#include <MLX42/MLX42_Int.h>

void	str_to_img(char *str, mlx_image_t *image, \
						uint8_t **charset, size_t xy[2])
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]))
			char_to_img(charset[(int)(str[i])], image, xy, TEXT_COLOR);
		else
			char_to_img(charset['?'], image, xy, TEXT_COLOR);
		xy[0] += FONT_W;
		i++;
	}
}

void	str_to_img_right(char *str, mlx_image_t *image, \
							uint8_t **charset, size_t xy[2])
{
	size_t	i;
	size_t	len;

	len = ft_strlen(str);
	i = 1;
	while (i <= len)
	{
		if (ft_isprint(str[len - i]))
			char_to_img(charset[(int)(str[len - i])], image, xy, TEXT_COLOR);
		else
			char_to_img(charset['?'], image, xy, TEXT_COLOR);
		xy[0] -= FONT_W;
		i++;
	}
}

void	str_to_img_center(char *str, mlx_image_t *image, \
								uint8_t **charset, size_t y)
{
	size_t	i;
	size_t	xy[2];
	size_t	len;

	len = ft_strlen(str);
	xy[0] = (image->width / 2) - ((len * FONT_W) / 2);
	xy[1] = y;
	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]))
			char_to_img(charset[(int)(str[i])], image, xy, TEXT_COLOR);
		else
			char_to_img(charset['?'], image, xy, TEXT_COLOR);
		xy[0] += FONT_W;
		i++;
	}
}

void	char_to_img(uint8_t *chr, mlx_image_t *image, \
						size_t xy[2], uint32_t color)
{
	size_t		i;
	uint32_t	*src;

	i = 0;
	src = (uint32_t *) chr;
	while (i < SIZE * SIZE)
	{
		if (src[i] == 0xFFFFFFFF)
			mlx_put_pixel(image, xy[0] + (i % SIZE), \
							xy[1] + (i / SIZE), color);
		i++;
	}
}
 
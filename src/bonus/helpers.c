/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:11:29 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/19 19:58:08 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int32_t	create_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float	distance_to_wall(float px, float py, float wx, float wy)
{
	return (sqrt((wy - py) * (wy - py) + (wx - px) * (wx - px)));
}

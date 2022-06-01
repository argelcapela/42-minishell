/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtx_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 01:30:29 by argel             #+#    #+#             */
/*   Updated: 2022/06/01 01:30:32 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	**ft_mtx_dup(char **duped_mtx)
{
	int		i;
	char	**matrix;
	int		height;

	if (duped_mtx == NULL)
		return (NULL);
	matrix = NULL;
	height = 0;
	while (duped_mtx[height])
		height++;
	i = -1;
	matrix = (char **) ft_calloc (height + 1, sizeof(char *));
	while (++i < height)
		matrix[i] = ft_strdup(duped_mtx[i]);
	return (matrix);
}

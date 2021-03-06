/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 01:32:16 by argel             #+#    #+#             */
/*   Updated: 2022/06/01 01:33:36 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_fd_print(int fd)
{
	char	tmp[2];

	while (read(fd, tmp, 2) != 0)
		write(1, tmp, 2);
}

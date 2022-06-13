/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:25 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/12 23:00:50 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cmpstr(void *v1, void *v2)
{
	char	*a1;
	char	*a2;

	a1 = *(char **) v1;
	a2 = *(char **) v2;
	return (ft_strncmp(a1, a2, ft_strlen(a1)));
}

static void	swap(t_qs *qs, void *v1, void *v2, int size)
{
	char	*buffer;

	buffer = malloc(size * sizeof(char));
	ft_memcpy(buffer, v1, size);
	ft_memcpy(v1, v2, size);
	ft_memcpy(v2, buffer, size);
	if (qs->free_qs == NULL)
	{
		qs->free_qs = malloc(1 * sizeof(t_qs));
		qs->free_qs->prev = NULL;
		qs->free_qs->next = NULL;
		qs->free_qs->buffer = buffer;
	}
	else
	{
		while (qs->free_qs->next != NULL)
			qs->free_qs = qs->free_qs->next;
		qs->free_qs->next = malloc(1 * sizeof(t_qs));
		qs->free_qs->next->prev = qs->free_qs;
		qs->free_qs->next->next = NULL;
		qs->free_qs->next->buffer = buffer;
	}
}

void	quicksort(t_qs *qs, int left, int right,
						int (*comp)(void*, void*))
{
	int		i;

	qs->mid = (left + right) / 2;
	if (left >= right)
		return ;
	qs->vl = (char *)(qs->v + (left * qs->size));
	qs->vr = (char *)(qs->v + (qs->mid * qs->size));
	swap(qs, qs->vl, qs->vr, qs->size);
	qs->last = left;
	i = left;
	while (i <= right)
	{
		qs->vt = (char *)(qs->v + (i * qs->size));
		if ((*comp)(qs->vl, qs->vt) > 0)
		{
			++(qs->last);
			qs->v3 = (char *)(qs->v + (qs->last * qs->size));
			swap(qs, qs->vt, qs->v3, qs->size);
		}
		i++;
	}
	qs->v3 = (char *)(qs->v + (qs->last * qs->size));
	swap(qs, qs->vl, qs->v3, qs->size);
	quicksort(qs, left, qs->last - 1, comp);
	quicksort(qs, qs->last + 1, right, comp);
}

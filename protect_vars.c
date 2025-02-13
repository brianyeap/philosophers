/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:24:11 by brian             #+#    #+#             */
/*   Updated: 2025/01/15 20:24:34 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx	*mutex, bool *dst, bool value)
{
	handle_mutex(mutex, LOCK);
	*dst = value;
	handle_mutex(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	retrieved;

	handle_mutex(mutex, LOCK);
	retrieved = *value;
	handle_mutex(mutex, UNLOCK);
	return (retrieved);
}

void	set_long(t_mtx *mutex, long *dst, long value)
{
	handle_mutex(mutex, LOCK);
	*dst = value;
	handle_mutex(mutex, UNLOCK);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	retrieve;

	handle_mutex(mutex, LOCK);
	retrieve = *value;
	handle_mutex(mutex, UNLOCK);
	return (retrieve);
}

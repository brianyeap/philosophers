/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_mutexes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:17:01 by brian             #+#    #+#             */
/*   Updated: 2025/01/15 20:11:20 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// Check Error helper funcs
static void	mutex_check_error(int status, t_opcode opcode)
{
	if (status != 0 && (opcode == LOCK || opcode == UNLOCK
			|| opcode == INIT || opcode == DESTROY))
	{
		error_exit("Mutex error!");
		return ;
	}
}

static void	thread_error_check(int status, t_opcode opcode)
{
	if (status != 0 && (opcode == CREATE || opcode == JOIN
			|| opcode == DETACH))
	{
		error_exit("Thread error!");
		return ;
	}
}

void	handle_mutex(t_mtx *mtx, t_opcode opcode)
{
	if (opcode == LOCK)
		mutex_check_error(pthread_mutex_lock(mtx), opcode);
	else if (opcode == UNLOCK)
		mutex_check_error(pthread_mutex_unlock(mtx), opcode);
	else if (opcode == INIT)
		mutex_check_error(pthread_mutex_init(mtx, NULL), opcode);
	else if (opcode == DESTROY)
		mutex_check_error(pthread_mutex_destroy(mtx), opcode);
	else
	{
		error_exit("opcode options: LOCK, UNLOCK, INIT, DESTROY");
		return ;
	}
}

void	handle_thread(pthread_t *thread_info, void *(*foo)(void *),
		void *t_data, t_opcode opcode)
{
	if (opcode == CREATE)
		thread_error_check(pthread_create(thread_info, NULL, foo, t_data),
			opcode);
	else if (opcode == JOIN)
		thread_error_check(pthread_join(*thread_info, NULL), opcode);
	else if (opcode == DETACH)
		thread_error_check(pthread_detach(*thread_info), opcode);
	else
	{
		error_exit("opcode options: CREATE, JOIN, DETACH");
		return ;
	}
}
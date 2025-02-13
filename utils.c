/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:36:47 by brian             #+#    #+#             */
/*   Updated: 2025/01/18 19:20:02 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(const char *error_msg)
{
	printf(RED "%s\n" RESET, error_msg);
	exit(1);
}

void	*ft_malloc(size_t bytes)
{
	void	*mem;

	mem = malloc(bytes);
	if (mem == NULL)
	{
		error_exit("Failed memory allocation!");
		return (NULL);
	}
	return (mem);
}

long	get_time(t_time_unit time_unit)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) != 0)
	{
		error_exit("Error: gettimeofday failed");
		return (1);
	}
	if (time_unit == MILLISECONDS)
		return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	else if (time_unit == MICROSECONDS)
		return (current_time.tv_sec * 1000000 + current_time.tv_usec);
	else if (time_unit == SECONDS)
		return (current_time.tv_sec + current_time.tv_usec / 1000000);
	else
	{
		error_exit("Invalid time unit specified");
		return (1);
	}
	return (-1);
}

void	ft_usleep(long sleep_time, t_data *data)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time(MICROSECONDS);
	while (get_time(MICROSECONDS) - start < sleep_time)
	{
		if (get_bool(&data->access_mutex, &data->end_time))
			break ;
		elapsed = get_time(MICROSECONDS) - start;
		remaining = sleep_time - elapsed;
		if (remaining > 10000)
			usleep(remaining / 2);
		else
			while (get_time(MICROSECONDS) - start < sleep_time)
				;
	}
}

void	free_everything(t_data *data)
{
	t_ph	*philo;
	int		i;

	i = 0;
	while (i < data->ph_total)
	{
		philo = data->philos_arr + i;
		handle_mutex(&philo->ph_mutex, DESTROY);
		i++;
	}
	handle_mutex(&data->write_mutex, DESTROY);
	handle_mutex(&data->access_mutex, DESTROY);
	free(data->forks_arr);
	free(data->philos_arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:02:52 by brian             #+#    #+#             */
/*   Updated: 2025/01/18 18:50:57 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		parse_input(&data, argv);
		data_init(&data);
		sim_start(&data);
		free_everything(&data);
	}
	else
		error_exit("Input Error!\n"
		YELLOW " Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"RESET);
	return (0);
}
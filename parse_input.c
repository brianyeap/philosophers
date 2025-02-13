/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:33:16 by brian             #+#    #+#             */
/*   Updated: 2025/01/18 18:48:21 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	isSpace(char c)
{
	return (c == '+' || (c >= 9 && c <= 13) || 32 == c);
}

static bool	is_number(char c)
{
	return (c >= '0' && c <= '9');
}

static int	input_error(int code)
{
	if (code == 1)
	{
		error_exit("Input Error: Positive values only");
		return (1);
	}
	if (code == 2)
	{
		error_exit("Input Error: Numbers only");
		return (1);
	}
	if (code == 3)
	{
		error_exit("Input Error: The value cannot exceed 2147483647");
		return (1);
	}
	return (0);
}

static long	ft_atol(const char *s)
{
	int		len;
	long	res;

	while (isSpace(*s))
		++s;
	if (*s == '-')
		input_error(1);
	if (!is_number(*s))
		input_error(2);
	len = 0;
	res = 0;
	while (is_number(*s))
	{
		res = (res * 10) + (*s++ - '0');
		len++;
	}
	if (len > 10 || res > INT_MAX)
		input_error(3);
	return (res);
}

void	parse_input(t_data *data, char **argv)
{
	data->ph_total = ft_atol(argv[1]);
	if (data->ph_total > PH_MAX)
	{
		error_exit("Input Error: Number of philosophers cannot exceed 200 !");
		return ;
	}
	data->time_to_die = ft_atol(argv[2]) * 1000;
	data->time_to_eat = ft_atol(argv[3]) * 1000;
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (data->time_to_die < 60000 || data->time_to_sleep < 60000
		|| data->time_to_eat < 60000)
	{
		error_exit("Input Error: Each of the 'time_to' values must exceed 60");
		return ;
	}
	if (argv[5])
		data->meals_total = ft_atol(argv[5]);
	else
		data->meals_total = -1;
}
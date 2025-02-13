/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:03:13 by brian             #+#    #+#             */
/*   Updated: 2025/01/18 18:42:24 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//Libaries
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

// MAx is 200 philos
# define PH_MAX 200

// ANSI escape sequence colors
# define RESET		"\033[0m"
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define MAGENTA	"\033[1;35m"
# define CYAN		"\033[1;36m"
# define WHITE		"\033[1;37m"

// Define it earlier at the top
typedef struct s_data t_data;

// Shortened version
typedef pthread_mutex_t	t_mtx;

// Fork
typedef struct s_fork
{
	t_mtx		fork_mutex;
	int			fork_id;
}				t_fork;

// Philosopher
typedef struct s_ph
{
	int			ph_id;
	long		meal_count;
	bool		max_meals;
	long		meal_time;
	pthread_t	ph_thread;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_mtx		ph_mutex;
	t_data		*data;
}				t_ph;

typedef struct s_data
{
	long			ph_total;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_total;
	long			start_time;
	bool			end_time;
	bool			threads_ready;
	long			active_philos_count;
	pthread_t		death_check;
	t_fork			*forks_arr;
	t_ph			*philos_arr;
	t_mtx			access_mutex;
	t_mtx			write_mutex;
}					t_data;

// Enums 
typedef enum e_opcode
{
	INIT,
	CREATE,
	LOCK,
	UNLOCK,
	JOIN,
	DETACH,
	DESTROY,
}			t_opcode;

typedef enum e_time_unit
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS,
}		t_time_unit;

typedef enum e_status
{
	THINKING,
	TAKES_LEFTFORK,
	TAKES_RIGHTFORK,
	EATING,
	SLEEPING,
	DIED,
}			t_ph_status;

// Data Init
void	data_init(t_data *data);

// Start Simulation
void	sim_start(t_data *data);


// Utils
void	error_exit(const char *error_msg);
void	*ft_malloc(size_t bytes);
long	get_time(t_time_unit time_unit);
void	ft_usleep(long sleep_time, t_data *data);
void	free_everything(t_data *data);

// Parse input
void	parse_input(t_data *data, char **argv);

// Threads and mutexes
void	handle_mutex(t_mtx *mtx, t_opcode opcode);
void	handle_thread(pthread_t *thread_info, void *(*foo)(void *),
		void *t_data, t_opcode opcode);

// Protected vars
void	set_bool(t_mtx *mutex, bool *dst, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dst, long value);
long	get_long(t_mtx *mutex, long *value);

// Monitor
void	wait_all_threads(t_data *data);
void	active_thread_counter(t_mtx *mutex, long *value);
void	*death_affirm(void *ph_data);

// Print status
void	ph_status(t_ph_status status, t_ph *philo);

// Data Innit
void	*single_philo(void *index);

#endif
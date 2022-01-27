/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 09:58:39 by user42            #+#    #+#             */
/*   Updated: 2022/01/27 20:36:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stddef.h>
# include <pthread.h>

typedef enum e_bool
{
	False,
	True
}	t_bool;

typedef struct s_info
{
	int						nb_total;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat;
	long int				start_t;
	pthread_mutex_t			finish;
	pthread_mutex_t			eat_time;
	pthread_mutex_t			end;
	pthread_mutex_t			write_mutex;
	int						nb_finish;
	int						dead;
}							t_info;

typedef struct s_thread
{
	pthread_t				thread_id;
	pthread_t				thread_death;
	pthread_mutex_t			l_fork;
	pthread_mutex_t			*r_fork;
	t_info					*p_info;
	int						id;
	long int				ms_eat;
	long int				nb_eat;
	int						end;
}							t_thread;

typedef struct s_philo
{
	t_info					info;
	t_thread				*thread;
}							t_philo;

/*
**	Main
*/

int							ft_error(char *msg);
void						ft_end(t_philo		*philo);

/*
** Utils
*/

int							ft_atoi(const char *str);
long int					get_time(void);
void						ft_usleep(long int time, t_info *info);
int							check_death(t_thread *thread, int stop);
void						display_message(char *msg, t_thread *thread);

/*
**	Init
*/

int							init_info(t_philo *philo, int argc, char **argv);
int							init_philo(t_philo *philo);
int							init_thread(t_philo *philo);

/*
**	routine
*/

void						routine(t_thread *thread);

/*
**	thread
*/

void						*thread(void *data);
void						ft_end(t_philo		*philo);
void						ft_stop(t_philo *philo);

#endif
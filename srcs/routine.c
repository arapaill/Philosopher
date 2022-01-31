/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:29:27 by user42            #+#    #+#             */
/*   Updated: 2022/01/31 12:38:26 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo.h"

void	ft_take_fork_and_eat(t_thread *thread)
{
	pthread_mutex_lock(&thread->l_fork);
	display_message("has taken a fork\n", thread);
	if (!thread->r_fork)
	{
		ft_usleep(thread->p_info->time_to_die * 2, thread->p_info);
		return ;
	}
	pthread_mutex_lock(thread->r_fork);
	display_message("has taken a fork\n", thread);
	display_message("is eating\n", thread);
	pthread_mutex_lock(&thread->p_info->eat_time);
	thread->ms_eat = get_time();
	pthread_mutex_unlock(&thread->p_info->eat_time);
	ft_usleep(thread->p_info->time_to_eat, thread->p_info);
	pthread_mutex_unlock(&thread->l_fork);
	pthread_mutex_unlock(thread->r_fork);
}

int	check_nb_eat(t_thread *thread)
{
	pthread_mutex_lock(&thread->p_info->nb_eat_mutex);
	if (++thread->nb_eat == thread->p_info->must_eat)
	{
		pthread_mutex_unlock(&thread->p_info->nb_eat_mutex);
		return (0);
	}
	pthread_mutex_unlock(&thread->p_info->nb_eat_mutex);
	return (1);
}

void	routine(t_thread *thread)
{
	while (!check_death_info(thread->p_info))
	{
		ft_take_fork_and_eat(thread);
		display_message("is sleeping\n", thread);
		ft_usleep(thread->p_info->time_to_sleep, thread->p_info);
		display_message("is thinking\n", thread);
		if (thread->p_info->must_eat)
			if (!check_nb_eat(thread))
				return ;
	}
}

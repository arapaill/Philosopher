/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:29:27 by user42            #+#    #+#             */
/*   Updated: 2021/12/29 15:56:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo.h"

void    ft_take_fork_and_eat(t_thread *thread)
{
	pthread_mutex_lock(&thread->l_fork);
	display_message("has taken to his left fork\n", thread);
	if (!thread->r_fork)
	{
		ft_usleep(thread->p_info->dead * 2);
		return ;
	}
	pthread_mutex_lock(thread->r_fork);
	display_message("has taken to his right fork\n", thread);
	display_message("is eating \n", thread);
	pthread_mutex_lock(&thread->p_info->eat_time);
	thread->ms_eat = get_time();
	pthread_mutex_unlock(&thread->p_info->eat_time);
	ft_usleep(thread->p_info->time_to_eat);
	pthread_mutex_unlock(&thread->l_fork);
	pthread_mutex_unlock(thread->r_fork);
}

void    ft_sleep(t_thread *thread)
{
	display_message("is sleeping\n", thread);
	ft_usleep(thread->p_info->time_to_sleep);
	display_message("is thinking\n", thread);  
}

void    routine(t_thread *thread)
{
	ft_take_fork_and_eat(thread);
	ft_sleep(thread);
}
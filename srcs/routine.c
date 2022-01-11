/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:29:27 by user42            #+#    #+#             */
/*   Updated: 2022/01/11 20:59:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo.h"

void    ft_take_fork_and_eat(t_thread *thread)
{
	pthread_mutex_lock(&thread->l_fork);
	pthread_mutex_lock(&thread->p_info->write_mutex);
	display_message("has taken the fork to his left\n", thread);
	pthread_mutex_unlock(&thread->p_info->write_mutex);
	if (!thread->r_fork)
	{
		ft_usleep(thread->p_info->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(thread->r_fork);
	pthread_mutex_lock(&thread->p_info->write_mutex);
	display_message("has taken the fork to his right\n", thread);
	pthread_mutex_unlock(&thread->p_info->write_mutex);
	pthread_mutex_lock(&thread->p_info->write_mutex);
	display_message("is eating \n", thread);
	pthread_mutex_unlock(&thread->p_info->write_mutex);
	pthread_mutex_lock(&thread->p_info->eat_time);
	thread->ms_eat = get_time();
	pthread_mutex_unlock(&thread->p_info->eat_time);
	ft_usleep(thread->p_info->time_to_eat);
	pthread_mutex_unlock(&thread->l_fork);
	pthread_mutex_unlock(thread->r_fork);
}

void    ft_sleep(t_thread *thread)
{
	pthread_mutex_lock(&thread->p_info->write_mutex);
	display_message("is sleeping\n", thread);
	pthread_mutex_unlock(&thread->p_info->write_mutex);
	ft_usleep(thread->p_info->time_to_sleep);
	pthread_mutex_lock(&thread->p_info->write_mutex);
	display_message("is thinking\n", thread);
	pthread_mutex_unlock(&thread->p_info->write_mutex);
}

void    routine(t_thread *thread)
{
	ft_take_fork_and_eat(thread);
	ft_sleep(thread);
}
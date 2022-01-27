/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 10:41:34 by user42            #+#    #+#             */
/*   Updated: 2022/01/27 18:01:12 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo.h"

void	display_message(char *msg, t_thread *thread)
{
	long int	time;

	time = -1;
	time = get_time() - thread->p_info->start_t;
	pthread_mutex_lock(&thread->p_info->write_mutex);
	if (thread->p_info->dead != 1 && time >= 0 && time <= 2147483647)
		printf("%ld %d %s", time, thread->id, msg);
	pthread_mutex_unlock(&thread->p_info->write_mutex);
}

int	check_death(t_thread *thread, int stop)
{
	pthread_mutex_lock(&thread->p_info->end);
	if (stop)
		thread->p_info->dead = stop;
	if (thread->p_info->dead)
	{
		pthread_mutex_unlock(&thread->p_info->end);
		return (1);
	}
	pthread_mutex_unlock(&thread->p_info->end);
	return (0);
}

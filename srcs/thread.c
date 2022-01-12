/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:59:48 by user42            #+#    #+#             */
/*   Updated: 2022/01/12 13:21:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo.h"

void	*ft_end(void *data)
{
	t_thread		*thread;

	thread = (t_thread *)data;
	ft_usleep(thread->p_info->time_to_die + 1, thread->p_info);
	pthread_mutex_lock(&thread->p_info->eat_time);
	pthread_mutex_lock(&thread->p_info->finish);
	if (!check_death(thread, 0) && !thread->end
		&& ((get_time() - thread->ms_eat)
			>= (long)(thread->p_info->time_to_die)))
	{
		pthread_mutex_unlock(&thread->p_info->eat_time);
		pthread_mutex_unlock(&thread->p_info->finish);
		pthread_mutex_lock(&thread->p_info->write_mutex);
		display_message("died\n", thread);
		pthread_mutex_unlock(&thread->p_info->write_mutex);
		check_death(thread, 1);
	}
	pthread_mutex_unlock(&thread->p_info->eat_time);
	pthread_mutex_unlock(&thread->p_info->finish);
	return (NULL);
}

void	*thread(void *data)
{
	t_thread	*thread;

	thread = (t_thread *)data;
	if (thread->id % 2 == 0)
		ft_usleep(thread->p_info->time_to_eat / 10, thread->p_info);
	while (!check_death(thread, 0))
	{
		pthread_create(&thread->thread_death, NULL, &ft_end, data);
		routine(thread);
		pthread_detach(thread->thread_death);
		if ((int)++thread->nb_eat == thread->p_info->must_eat)
		{
			pthread_mutex_lock(&thread->p_info->finish);
			thread->end = 1;
			thread->p_info->nb_finish++;
			if (thread->p_info->nb_finish == thread->p_info->nb_total)
			{
				pthread_mutex_unlock(&thread->p_info->finish);
				check_death(thread, 2);
			}
			pthread_mutex_unlock(&thread->p_info->finish);
			return (NULL);
		}
	}
	return (NULL);
}

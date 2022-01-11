/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:59:48 by user42            #+#    #+#             */
/*   Updated: 2022/01/11 16:34:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo.h"

void	*ft_end(void *data)
{
	t_thread		*thread;
	
	thread = (t_thread *)data;
	printf("ft_end START\n");
	ft_usleep(thread->p_info->time_to_die + 1);
	printf("ft_end TEST1\n");
	pthread_mutex_lock(&thread->p_info->eat_time);
	pthread_mutex_lock(&thread->p_info->finish);
	printf("ft_end TEST2\n");
	if (!check_death(thread, 0) && !thread->end && ((get_time() - thread->ms_eat)
		>= (long)(thread->p_info->time_to_die)))
	{
		printf("ft_end TEST3\n");
		pthread_mutex_unlock(&thread->p_info->eat_time);
		pthread_mutex_unlock(&thread->p_info->finish);
		pthread_mutex_lock(&thread->p_info->write_mutex);
		display_message("died\n", thread);
		pthread_mutex_unlock(&thread->p_info->write_mutex);
		check_death(thread, 1);
	}
	printf("ft_end TEST4\n");
	pthread_mutex_unlock(&thread->p_info->eat_time);
	pthread_mutex_unlock(&thread->p_info->finish);
	return (NULL);
}

void	*thread(void *data)
{
	t_thread	*thread;

	printf("thread START\n");
	thread = (t_thread *)data;
	if (thread->id % 2 == 0)
		ft_usleep(thread->p_info->time_to_eat / 10);
	printf("thread TEST 1\n");
	while (!check_death(thread, 0))
	{
		printf("thread LOOP START\n");
		pthread_create(&thread->thread_death, NULL, ft_end, data);
		printf("thread TEST 2\n");
		routine(thread);
		printf("thread TEST 3\n");
		pthread_detach(thread->thread_death);
		printf("thread TEST 4\n");
		if ((int)++thread->nb_eat == thread->p_info->must_eat)
		{
			pthread_mutex_lock(&thread->p_info->finish);
			printf("thread TEST 5\n");
			thread->end = 1;
			thread->p_info->nb_finish++;
			if (thread->p_info->nb_finish == thread->p_info->nb_total)
			{
				pthread_mutex_unlock(&thread->p_info->finish);
				check_death(thread, 2);
			}
			printf("thread TEST 6\n");
			pthread_mutex_unlock(&thread->p_info->finish);
			printf("thread LOOP END 1\n");
			return (NULL);
		}
		printf("thread LOOP END 2\n");
	}
	printf("thread END\n");
	return (NULL);
}

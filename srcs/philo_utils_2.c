/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 10:41:34 by user42            #+#    #+#             */
/*   Updated: 2022/01/11 16:32:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo.h"

void    display_message(char *msg, t_thread *thread)
{
	long int	time;

	time = -1;
	time = get_time() - thread->p_info->start_t;
	if (time >= 0 && time <= 2147483647 && !check_death(thread, 0))
	{
		printf("[%ld] ", time);
		printf("Philo nb: %d %s", thread->id, msg);
	}
}

int     check_death(t_thread *thread, int stop)
{
	printf("CHECK_DEATH1\n");
	pthread_mutex_lock(&thread->p_info->end);
	if (stop)
		thread->p_info->dead = stop;
	printf("CHECK_DEATH2\n");
	if (thread->p_info->dead)
	{
		pthread_mutex_unlock(&thread->p_info->end);
		return (1);
	}
	printf("CHECK_DEATH3\n");
	pthread_mutex_unlock(&thread->p_info->end);
	return (0);
}
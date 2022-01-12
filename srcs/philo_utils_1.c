/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:21:52 by user42            #+#    #+#             */
/*   Updated: 2022/01/12 11:28:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo.h"

#define SPACES " \t\v\f\r\n"

t_bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (True);
	return (False);
}

static size_t	check_spaces(const char *str)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (str[i] && SPACES[j])
	{
		if (str[i] == SPACES[j])
		{
			i++;
			j = -1;
		}
		j++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int				ret;
	int				sign;
	size_t			i;

	ret = 0;
	sign = 1;
	i = check_spaces(str);
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]) == True)
	{
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	return (sign * ret);
}

long int	get_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		ft_error("Gettimeofday returned -1\n");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time)
{
	long int	start_time;

	start_time = 0;
	start_time = get_time();
	while ((get_time() - start_time) < time)
		usleep(time / 10);
}

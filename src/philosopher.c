/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toespino <toespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 02:47:46 by toespino          #+#    #+#             */
/*   Updated: 2026/08/20 08:42:57 by toespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static bool	p_check_death(t_philo *philo)
{
	bool	res;

	pthread_mutex_lock(philo->death_lock);
	res = *philo->death_con;
	pthread_mutex_unlock(philo->death_lock);
	return (res);
}

static bool	p_eat(t_philo *philo)
{
	int32_t	time;

	while (!(*((bool *) get_info(philo->av_l_fork_lock, philo->av_l_fork))))
		;
	if (p_check_death(philo))
		return (false);
	p_l_lock_fork(philo, true);
	while (!(*((bool *)get_info(philo->av_r_fork_lock, philo->av_r_fork))))
		;
	if (p_check_death(philo))
		p_l_lock_fork(philo, false);
	if (p_check_death(philo))
		return (false);
	p_r_lock_fork(philo, true);
	time = getmsofday();
	p_printf(time - philo->start_time, P_EAT, philo);
	pthread_mutex_lock(philo->last_eat_lock);
	*philo->last_eat = time;
	pthread_mutex_unlock(philo->last_eat_lock);
	usleep(philo->eat_time * 1000);
	if (p_check_death(philo))
		return (false);
	p_r_lock_fork(philo, false);
	p_l_lock_fork(philo, false);
	return (true);
}

static bool	p_sleep(t_philo *philo)
{
	int64_t	ellapsed;

	ellapsed = 0;
	p_printf(getmsofday() - philo->start_time, P_THINK, philo);
	while (ellapsed < philo->sleep_time * 1000 + 1)
	{
		ellapsed += 500;
		usleep(500);
		if (p_check_death(philo))
			return (false);
	}
	return (true);
}

static void	p_think(t_philo *philo)
{
	p_printf(getmsofday() - philo->start_time, P_THINK, philo);
}

void	philo(t_philo *philo)
{
	while (!p_check_death(philo))
	{
		if (!p_eat(philo))
			break ;
		if (!p_sleep(philo))
			break ;
		p_think(philo);
	}
}

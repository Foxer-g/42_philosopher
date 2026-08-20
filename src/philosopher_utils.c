/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toespino <toespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 04:00:58 by toespino          #+#    #+#             */
/*   Updated: 2026/08/20 08:30:12 by toespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	p_l_lock_fork(t_philo *philo, bool status)
{
	pthread_mutex_lock(philo->l_fork_lock);
	*philo->l_fork = status;
	pthread_mutex_unlock(philo->l_fork_lock);
	pthread_mutex_lock(philo->av_l_fork_lock);
	*philo->av_l_fork = status;
	pthread_mutex_unlock(philo->av_l_fork_lock);
	if (status)
		p_printf(getmsofday() - philo->start_time, P_FORK, philo);
}

void	p_r_lock_fork(t_philo *philo, bool status)
{
	pthread_mutex_lock(philo->r_fork_lock);
	*philo->r_fork = status;
	pthread_mutex_unlock(philo->r_fork_lock);
	pthread_mutex_lock(philo->av_r_fork_lock);
	*philo->av_r_fork = status;
	pthread_mutex_unlock(philo->av_r_fork_lock);
	if (status)
		p_printf(getmsofday() - philo->start_time, P_FORK, philo);
}

void	*get_info(pthread_mutex_t *lock, void *info)
{
	void	*res;

	pthread_mutex_lock(lock);
	res = info;
	pthread_mutex_unlock(lock);
	return (res);
}

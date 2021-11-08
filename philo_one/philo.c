/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomes <egomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:11:20 by egomes            #+#    #+#             */
/*   Updated: 2021/11/08 18:32:01 by egomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philo *philo)
{
	t_arg	*arg;

	arg = philo->arg;
	pthread_mutex_lock(&(arg->forks[philo->l_f]));
	print(arg, philo->id, "has taken a fork");
	pthread_mutex_lock(&(arg->forks[philo->r_f]));
	print(arg, philo->id, "has taken a fork");
	pthread_mutex_lock(&(arg->meal_check));
	print(arg, philo->id, "is eating");
	philo->last_meal = actual_time();
	pthread_mutex_unlock(&(arg->meal_check));
	smart_sleep(arg->eat, arg);
	(philo->x_ate)++;
	pthread_mutex_unlock(&(arg->forks[philo->l_f]));
	pthread_mutex_unlock(&(arg->forks[philo->r_f]));
}

void	*thread(void	*p)
{
	t_philo		*philo;
	t_arg		*arg;
	int			i;

	philo = (t_philo *)p;
	arg = philo->arg;
	if (philo->id % 2)
		usleep(15000);
	i = 0;
	while (!(arg->dieded))
	{
		philo_eats(philo);
		if (arg->all_eat)
			break ;
		print(arg, philo->id, "is sleeping");
		smart_sleep(arg->sleep, arg);
		print(arg, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	death_checker(t_obj *obj)
{
	int	i;

	while (!(obj->arg.all_eat))
	{
		i = -1;
		while (++i < obj->arg.philos && !(obj->arg.dieded))
		{
			pthread_mutex_lock(&(obj->arg.meal_check));
			if ((actual_time() - obj->philo[i].last_meal) == obj->arg.die)
			{
				print(&obj->arg, i, "died");
				obj->arg.dieded = 1;
				usleep(5);
			}
			pthread_mutex_unlock(&(obj->arg.meal_check));
		}
		if (obj->arg.dieded)
			break ;
		i = 0;
		while (obj->arg.nb_eat != -1 && i < obj->arg.philos
			&& obj->philo[i].x_ate >= obj->arg.nb_eat)
			i++;
		if (i == obj->arg.philos)
			obj->arg.all_eat = 1;
	}
}

void	init_function(t_obj *obj)
{
	int	i;

	obj->arg.first_time = actual_time();
	i = 0;
	while (i < obj->arg.philos)
	{
		pthread_create(&(obj->philo[i].thread_id),
			NULL, thread, &(obj->philo[i]));
		obj->philo[i].last_meal = actual_time();
		i++;
	}
	death_checker(obj);
	exit_function(obj);
}

int	main(int ac, char **av)
{
	t_obj		obj;

	if (!init_philo(&obj, ac, av))
		return (0);
	obj.philo = malloc(sizeof(t_philo) * obj.arg.philos);
	if (!obj.philo)
		return (error("Malloc"));
	init_mutex(&obj);
	init_philos(&obj);
	init_function(&obj);
	return (0);
}

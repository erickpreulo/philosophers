/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomes <egomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:11:45 by egomes            #+#    #+#             */
/*   Updated: 2021/11/18 17:10:57 by egomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t				thread_id;
	int						r_f;
	int						l_f;
	long					last_meal;
	int						id;
	int						x_eat;
	struct s_arg			*arg;
}							t_philo;

typedef struct s_arg
{
	int						philos;
	long					die;
	long					eat;
	int						sleep;
	int						stop;
	int						dieded;
	int						all_eat;
	int						time_sleep;
	long					nb_eat;
	long long				first_time;
	pthread_mutex_t			meal_check;
	pthread_mutex_t			forks[255];
	pthread_mutex_t			writing;
	t_philo					philo[255];
}							t_arg;

typedef struct s_obj
{
	t_arg					arg;
	t_philo					*philo;
}							t_obj;

int			init_philo(t_obj *obj, int ac, char **av);
int			error(char *str);
int			ft_atoi(const char *str);
long int	actual_time(void);
void		init_mutex(t_obj *obj);
void		init_philos(t_obj *obj);
void		print(t_arg *arg, int id, char *str);
void		smart_sleep(long long time, t_arg *arg);
void		exit_function(t_obj *obj);
void		init_function(t_obj *obj);
void		death_checker(t_obj *obj);

#endif

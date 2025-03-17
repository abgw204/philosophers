#include "philo.h"

void	set_bool(pthread_mutex_t *mutex, bool *variable, bool value)
{
	pthread_mutex_lock(mutex);
	*variable = value;
	pthread_mutex_unlock(mutex);
}

bool	get_bool(pthread_mutex_t *mutex, bool *variable)
{
	bool	ret;

	pthread_mutex_lock(mutex);
	ret = *variable;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_long(pthread_mutex_t *mutex, long *variable, long value)
{
	pthread_mutex_lock(mutex);
	*variable = value;
	pthread_mutex_unlock(mutex);
}

bool	get_long(pthread_mutex_t *mutex, long *variable)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *variable;
	pthread_mutex_unlock(mutex);
	return (ret);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}

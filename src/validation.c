#include "philo.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static long	has_no_more_than_8_digits(char *str)
{
	long	len;
	char	*original_str;

	len = ft_strlen(str);
	if (len > 8)
	{
		ft_putstr_fd("Error: Number must have no more than 8 digits.\n", 2);
		exit(1);
	}
	original_str = str;
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
		{
			ft_putstr_fd("Error: Non-numeric of negative character found.\n", 2);
			exit(1);
		}
		str++;
	}
	return (ft_atol(original_str));
}

bool	is_args_valid(int argc, char **argv, t_table *table)
{
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Usage: %s number_of_philosophers "
			"time_to_die time_to_eat time_to_sleep\n", 2);
		exit(1);
	}
	table->size = has_no_more_than_8_digits(argv[1]);
	table->die = (t_time)has_no_more_than_8_digits(argv[2]);
	table->eat = (t_time)has_no_more_than_8_digits(argv[3]);
	table->sleep = (t_time)has_no_more_than_8_digits(argv[4]);
	if (argc == 6)
		table->meal_count = has_no_more_than_8_digits(argv[5]);
	else
		table->meal_count = -1;
	table->action_gap = calculate_action_gap(table->die,
			table->eat, table->sleep);
	return (true);
}

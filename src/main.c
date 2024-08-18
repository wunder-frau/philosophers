#include "philo.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static long has_no_more_than_8_digits(char *str) {
    // Check length of the number
    long len = ft_strlen(str);
    if (len > 8) {
        fprintf(stderr, "Error: Number must have no more than 8 digits.\n");
        exit(1);
    }

    // Validate each character to ensure it's a digit
    char *original_str = str;
    while (*str) {
        if (!ft_isdigit((unsigned char)*str)) {
            fprintf(stderr, "Error: Non-numeric of negative character found.\n");
            exit(1); // Non-numeric characters found
        }
        str++;
    }
    // Convert to long and return
    return ft_atol(original_str);
}

// static long has_no_more_than_8_digits(char *str)
// {
//     //int digit_count = 0;
//     //long number = 0;

// 	long len = ft_strlen(str);
// 	if (len > 8)
// 	{
// 		fprintf(stderr, "Error: Number must have no more than 8 digits.\n");
// 		exit(1);
// 	}
// 	while (*str) {
//         if (!ft_isdigit(*str)) {
//             fprintf(stderr, "Error: Non-numeric character found.\n");
//             exit(1); // Non-numeric characters found
//         }
//         str++;
// 		printf("str: %c\n", *str);
//     }
// 	 return ft_atol(str);
// }

/**
 * TODO: add validation logic later...
 */
bool	is_args_valid(int argc, char **argv, t_table *table)
{
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep\n", 2);
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
	// if (table->size < 1 || table->die < 1 || table->eat < 1 || table->sleep < 1)
	// {
	// 	printf("hello___:%ld", table->sleep);
	// 	ft_putstr_fd("Error: All arguments must be positive integers.\n", 2);
	// 	return (false);
	// }
	table->action_gap = calculate_action_gap(table->die, table->eat, table->sleep);
	return (true);
}

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(table));
	if (!is_args_valid(argc, argv, &table))
		return (1);
	if (!allocate(&table))
		return (1);
	if (!init(&table))
	{
		destroy_and_free(&table);
		return (1);
	}
	destroy_and_free(&table);
	return (0);
}

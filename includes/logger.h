// 42 header //

#ifndef LOGGER_H
# define LOGGER_H

# include "../libft/includes/libft.h"

# define FROM log_from(__FILE__, __FUNCTION__, __LINE__)

# ifndef NMO_DEBUG
#  define NMO_DEBUG 0
# endif

# define ERROR_CLR "\033[4;31m"
# define CLEAR_CLR "\033[0m\n"

typedef enum	e_error_type {
	ERR_FILE = 0,
	ERR_MMAP,
	ERR_MUNMAP,
	ERR_MALLOC,
	ERR_THROW,
	ERR_N
}				t_error_type;

/*
** logger.c		=> 2 function
*/
char			*log_from(char const *file, char const *func, uint32_t line);
bool			log_error(enum e_error_type type, char const *err, char *from);

#endif
#include "expander.h"
#include "utils.h"

void expander_init(t_expander *exper, char *input)
{
	exper->str = ft_strdup(input);
	if (exper->str == NULL)
		error_exit();
	exper->str_i = 0;
	exper->state = STATE_GENERAL;
}
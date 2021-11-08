#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//This function takes a char * and returns whether it is a float.
bool is_float(char const * const str)
{
	int i = 0;

	if (!str)
		return (false);

	//ensure str starts with a digit, or with '-' followed by a digit
	if (isdigit(str[i]))
		i++;
	else if (str[i] == '-' && isdigit(str[i + 1]))
		i += 2;
	else
		return (false);

	//skip until end of digits is found
	while (isdigit(str[i]))
		i++;

	//ensure digits are followed by '.' (the decimal point)
	if (str[i] != '.')
		return (false);
	i++;

	//ensure the decimal point is followed by the decimal digits
	if (!isdigit(str[i]))
		return (false);
	i++;

	//skip over decimal digits
	while (str[i] && isdigit(str[i]))
		i++;
	
	//ensure last digit is not followed by a letter
	if (isalpha(str[i]) || str[i] == '.')
		return (false);

	return (true);
}

//This function takes a char * and returns whether it is an int.
bool is_uint(char const * const str)
{
	int i = 0;

	if (!str)
		return (false);

	//ensure str starts with a digit
	if (!isdigit(str[i]))
		return (false);
	i++;
	
	//skip until end of digits is found
	while (isdigit(str[i]))
		i++;

	//ensure last digit is not followed by a '.' and a digit
	//(which would indicate that it's a float)
	if (str[i] == '.' && isdigit(str[i + 1]))
		return (false);

	//ensure last digit is not followed by a letter
	if (isalpha(str[i]))
		return (false);
	
	return (true);
}

//This function takes a char * starting with a float,
//and returns a char * to the element after the float.
//returns NULL if str is not a float
char *skip_float(char * const str)
{
	int i = 0;

	if (!str)
		return (NULL);

	//ensure str starts with a digit, or with '-' followed by a digit
	if (isdigit(str[i]))
		i++;
	else if (str[i] == '-' && isdigit(str[i + 1]))
		i += 2;
	else
		return (NULL);

	//skip until end of digits is found
	while (isdigit(str[i]))
		i++;

	//ensure digits are followed by '.' (the decimal point)
	if (str[i] != '.')
		return (NULL);
	i++;

	//ensure the decimal point is followed by the decimal digits
	if (!isdigit(str[i]))
		return (NULL);
	i++;

	//skip over decimal digits
	while (isdigit(str[i]))
		i++;

	if (isalpha(str[i]) || str[i] == '.')
		return NULL;

	return (str + i);
}

//This function takes a char * starting with an int,
//and returns a char * to the element after the int.
char *skip_uint(char * const str)
{
	int i = 0;

	if (!str)
		return (NULL);

	//ensure str starts with a digit
	if (!isdigit(str[i]))
		return (NULL);
	i++;
	
	//skip until end of digits is found
	while (str[i] && isdigit(str[i]))
		i++;

	//ensure last digit is not followed by a '.' and a digit
	//(which would indicate that it's a float)
	if (str[i] == '.' && isdigit(str[i + 1]))
		return (NULL);

	//ensure last digit is not followed by a letter
	if (isalpha(str[i]))
		return (NULL);
	
	return (&str[i]);
}

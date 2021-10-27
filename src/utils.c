#include "main.h"

void set_bool(GLuint shader_program, const char *name, const bool value)
{
	glUniform1i(glGetUniformLocation(shader_program, name), (int)value);
}

void set_int(GLuint shader_program, const char *name, const int value)
{
	glUniform1i(glGetUniformLocation(shader_program, name), value);
}

void set_float(GLuint shader_program, const char *name, const float value)
{
	glUniform1f(glGetUniformLocation(shader_program, name), value);
}

//This function takes a char * starting with a float,
//and returns a char * to the element after the float.
char *skip_float(char const*const str)
{
	char *walker = str;

	if (!walker)
		return str;

	//ensure walker starts with a digit, or with '-' followed by a digit
	if (isdigit(*walker))
		walker++;
	else if (*walker == '-' && isdigit(*(walker + 1)))
		walker += 2;
	else
		return str;

	//skip until end of digits is found
	while (isdigit(*walker))
		walker++;

	//ensure digits are followed by '.' (the decimal point)
	if (*walker != '.')
		return str;
	walker++;

	//ensure the decimal point is followed by the decimal digits
	if (!isdigit(*walker))
		return str;
	walker++;

	//skip over decimal digits
	while (*walker && isdigit(*walker))
		walker++;

	return walker;
}

//This function takes a char * and returns whether it is a float.
bool is_float(char const*const str)
{
	char *walker = str;

	if (!walker)
		return false;

	//ensure walker starts with a digit, or with '-' followed by a digit
	if (isdigit(*walker))
		walker++;
	else if (*walker == '-' && isdigit(*(walker + 1)))
		walker += 2;
	else
		return false;

	//skip until end of digits is found
	while (isdigit(*walker))
		walker++;

	//ensure digits are followed by '.' (the decimal point)
	if (*walker != '.')
		return false;
	walker++;

	//ensure the decimal point is followed by the decimal digits
	if (!isdigit(*walker))
		return false;
	walker++;

	//skip over decimal digits
	while (*walker && isdigit(*walker))
		walker++;
	
	//ensure last digit is not followed by a letter
	if (isalpha(*walker))
		return false;

	return true;
}

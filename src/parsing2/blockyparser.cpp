#include <cctype>

#include <parsing2/blockyparser.hpp>

bool BlockyParser::try_parse
(
    const char* buffer,
    int offset,
    int count
)
{
    // REGEX: [+-]\d+\.?\d*[eE]*[+-]*\d*\s
    int checked = 0;

    if (count < 1)
        return false;

    std::string number;

	if (buffer[offset + checked] == '+')
	{
		number += '+';
		checked++;
	}

	if (buffer[offset + checked] == '-')
	{
		number += '-';
		checked++;
	}

	if (!isdigit(buffer[offset + checked]))
		return false;
    
	while(isdigit(buffer[offset + checked]))
    {
        number += buffer[offset + checked];
        checked++;

        if (count < checked + 1)
            return false;
    }

    if (buffer[offset + checked] != '.')
        if (!isspace(buffer[offset + checked]))
            return false;

    if (buffer[offset + checked] == '.')
    {
        number += '.';
        checked++;

        if (count < checked + 1)
            return false;

        while
		(
			isdigit(buffer[offset + checked]) 
		 || buffer[offset + checked] == 'e'
		 || buffer[offset + checked] == 'E'
		 || buffer[offset + checked] == '+'
		 || buffer[offset + checked] == '-'
		)
        {
            number += buffer[offset + checked];
            checked++;

            if (count < checked + 1)
                return false;
        }
    }

    if (isspace(buffer[offset + checked]))
    {
        // TODO: validate, if number really is blockynumber
        // but should be true

        return true;
    }

    return false;
}

int BlockyParser::parse_constant
(
    const char* buffer,
    int offset,
    int count
)
{
    int parsed = 0;

    if (count < 1)
        // TODO: return unexpected end of buffer
        return -1;

    while
    (
        count > parsed
     && !isspace(buffer[offset + parsed])
    )
        parsed++;

    if (count < parsed)
        // TODO: return unexpected end of buffer
        return -1;

    std::string number(buffer + offset, parsed);
    std::cout << "number: " << number << '\n';

    hooker.handle_list_entry(number);

	while (count > parsed && isspace(buffer[offset + parsed]))
		parsed++;

    return parsed;
}
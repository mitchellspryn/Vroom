#ifndef VROOM_STRINGUTILITIES_H
#define VROOM_STRINGUTILITIES_H

#include <string>

static class StringUtilities
{
	public:
		static std::string ToLower(std::string input)
		{
			std::string returnValue;
			size_t size = input.size();
			returnValue.reserve(size);
			for (size_t i = 0; i < size; ++i)
			{
				returnValue += std::tolower(input[i]);
			}
			return returnValue;
		}
};

#endif
﻿#include "namespace.h"

using anisimov::DataStruct;

int main()
{
  try
  {
    setlocale(LC_ALL, "ru");
    std::string input = "";
    std::vector< DataStruct > data;

    while (std::getline(std::cin, input))
    {
      std::istringstream iss(input);
      DataStruct tmp;
      if (iss >> tmp)
      {
        data.push_back(tmp);
      }
    }

    std::sort(std::begin(data), std::end(data), anisimov::compareDataStruct);

    std::copy(std::begin(data), std::end(data), std::ostream_iterator< DataStruct >(std::cout, "\n"));
  }
  catch (std::exception& ex)
  {
    std::cerr << ex.what();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

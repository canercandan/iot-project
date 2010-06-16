#include <fstream>
#include <iostream>
#include <ctime>

int	main(void)
{
  std::ofstream	filestr("log.txt");
  std::streambuf* backup = std::clog.rdbuf();
  std::clog.rdbuf(filestr.rdbuf());

  std::clog << "write out a line into log file" << std::endl;

  std::clog.rdbuf(backup);
  filestr.close();

  return 0;
}

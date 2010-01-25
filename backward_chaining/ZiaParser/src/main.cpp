#include <iostream>
#include "RequestHeaderParser.h"
#include "RequestHeaderGrammar.hpp"

using namespace BOOST_SPIRIT_CLASSIC_NS;

int	main(void)
{
  ParsingResult			result;
  request_header_grammar	myGrammar;

  static const char*		request =
    "GET / HTTP/1.1\r\n"
    "Host: 127.0.0.1:3000\r\n"
    "User-Agent: Mozilla/5.0 (X11; U; Linux i686; fr; rv:1.9.0.13) "
    "Gecko/2009080315 Ubuntu/9.04 (jaunty) Firefox/3.0.13\r\n"
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
    "Accept-Language: fr\r\n"
    "Accept-Encoding: gzip,deflate\r\n"
    "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n"
    "Keep-Alive: 300\r\n"
    "Connection: keep-alive\r\n"
    "\r\n";

  std::cout << request << std::endl;
  std::string str;
  while (std::getline(std::cin, str))
    {
      if (str.empty() || str[0] == 'q' || str[0] == 'Q')
	break;

      parse_info<> info = parse(request, myGrammar[var(result) = arg1]);
      //parse_info<> info = parse(str.c_str(), myGrammar[var(result) = arg1]);

      if (info.full)
        {
	  std::cout << "-------------------------\n";
	  std::cout << "Parsing succeeded\n";
	  std::cout << "-------------------------\n";
        }
      else
        {
	  std::cout << "-------------------------\n";
	  std::cout << "Parsing failed\n";
	  std::cout << "stopped at: \": " << info.stop << "\"\n";
	  std::cout << "-------------------------\n";
        }
    }
  return (0);
}

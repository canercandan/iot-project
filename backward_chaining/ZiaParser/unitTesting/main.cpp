#include <iostream>
#include "BasicRules.h"
#include "DateRules.h"
#include "TestRules.h"

using namespace BOOST_SPIRIT_CLASSIC_NS;

static void	basicUnitTesting(void)
{
  BasicRules	basicRules;
  DateRules	dateRules;
  
  try
    {
      std::cout<< "rule<> ALPHA :";
      std::string str = "L";
      std::cout<< "parsing :" << str << std::endl;

      if (!parse(str.c_str(), basicRules.ALPHA).full)
	throw "Alpha rule failed";

      str[0] = '-';
      std::cout<< "parsing :" << str << std::endl;
      if (parse(str.c_str(), basicRules.ALPHA).full)
	throw "Alpha rule failed";

      // rule CHAR
      std::cout<< "rule<> CHAR :";
      str = "-";
      std::cout<< "parsing :" << str << std::endl;
      if (!parse(str.c_str(), basicRules.CHAR).full)
	throw "CHAR rule failed";

      str = "\b";
      std::cout<< "parsing :" << str << std::endl;
      if (!parse(str.c_str(), basicRules.CHAR).full)
	throw "CHAR rule failed";

      // char depassant 127 doit fail
      str[0] = 255;
      std::cout<< "parsing : " << str << std::endl;
      if (parse(str.c_str(), basicRules.CHAR).full)
	throw "CHAR rule failed";

      // rule OCTET
      std::cout << "rule<> OCTET :";
      str[0] = 255;
      std::cout<< "parsing : " << str << std::endl;
      if (!parse(str.c_str(), basicRules.OCTET).full)
	throw "OCTET rule failed";

      // DIGIT
      std::cout << "rule<> DIGIT :" << std::endl;
      str = "0";
      if (!parse(str.c_str(), basicRules.DIGIT).full)
	throw "DIGIT rule failed";
      str = "99";
      if (parse(str.c_str(), basicRules.DIGIT).full)
	throw "DIGIT rule failed";

      // CTL
      std::cout << "rule<> CTL :" << std::endl;
      str = "\b";
      if (!parse(str.c_str(), basicRules.CTL).full)
	throw "CTL rule failed";

      str = "o";
      if (parse(str.c_str(), basicRules.CTL).full)
	throw "CTL rule failed";

      //CTL_N
      std::cout << "rule<> CTL_N :" << std::endl;
      str = "0";
      if (!parse(str.c_str(), basicRules.CTL_N).full)
	throw "CTL_N rule failed";

      str = "\b";
      if (parse(str.c_str(), basicRules.CTL_N).full)
	throw "CTL_N rule failed";

      // CTLS
      std::cout << "rule<> CTLS :" << std::endl;
      str = "\b\b\t\n";
      if (!parse(str.c_str(), basicRules.CTLS).full)
	throw "CTLS rule failed";

      str = "\b lol \t\n";
      if (parse(str.c_str(), basicRules.CTLS).full)
	throw "CTLS rule failed";

      // CTLS_N
      std::cout << "rule<> CTLS_N :" << std::endl;
      str = "\b\b\t\n";
      if (parse(str.c_str(), basicRules.CTLS_N).full)
	throw "CTLS_N 1 rule failed";

      str = " lol ";
      if (!parse(str.c_str(), basicRules.CTLS_N).full)
	throw "CTLS_N  2 rule failed";
      // HT
      std::cout << "rule<> HT :" << std::endl;
      str = "\t";
      if (!parse(str.c_str(), basicRules.HT).full)
	throw "HT rule failed";

      str = "\n";
      if (parse(str.c_str(), basicRules.HT).full)
	throw "HT rule failed";

      // HT_N
      std::cout << "rule<> HT_N :" << std::endl;
      str = "\t";
      if (parse(str.c_str(), basicRules.HT_N).full)
	throw "HT_N rule failed";

      str = "\n";
      if (!parse(str.c_str(), basicRules.HT_N).full)
	throw "HT_N rule failed";

      // SP
      std::cout << "rule<> SP :" << std::endl;
      str = "\t";
      if (parse(str.c_str(), basicRules.SP).full)
	throw " rule failed";

      str = " ";
      if (!parse(str.c_str(), basicRules.SP).full)
	throw " rule failed";

      // SP_N
      std::cout << "rule<> SP_N :" << std::endl;
      str = " ";
      if (parse(str.c_str(), basicRules.SP_N).full)
	throw "SP_N rule failed";

      str = "\t";
      if (!parse(str.c_str(), basicRules.SP_N).full)
	throw "SP_N rule failed";

      // CR
      std::cout << "rule<> CR :" << std::endl;
      str = "o";
      if (parse(str.c_str(), basicRules.CR).full)
	throw "CR rule failed";

      str = "\r";
      if (!parse(str.c_str(), basicRules.CR).full)
	throw "CR rule failed";

      // LF
      std::cout << "rule<> LF :" << std::endl;
      str = "y";
      if (parse(str.c_str(), basicRules.LF).full)
	throw "LF rule failed";

      str = "\n";
      if (!parse(str.c_str(), basicRules.LF).full)
	throw "LF rule failed";

      // CRLF
      std::cout << "rule<> CRLF :" << std::endl;
      str = "\n\r";
      if (parse(str.c_str(), basicRules.CRLF).full)
	throw "CRLF rule failed";

      str = "\r\n";
      if (!parse(str.c_str(), basicRules.CRLF).full)
	throw "CRLF rule failed";

      // LWS
      std::cout << "rule<> LWS :" << std::endl;
      str = "\r\n";
      if (parse(str.c_str(), basicRules.LWS).full)
	throw "LWS 1 rule failed";

      str = "\r\n ";
      if (!parse(str.c_str(), basicRules.LWS ).full)
	throw "LWS 2 rule failed";
      str = "\r\n\t";
      if (!parse(str.c_str(), basicRules.LWS ).full)
	throw "LWS 3 rule failed";

      // TEXT  <any OCTET except CTLs,but including LWS>
      std::cout << "rule<> TEXT :" << std::endl;
      str = "\b";
      if (parse(str.c_str(), basicRules.TEXT).full)
	throw "TEXT 1 rule failed";

      str = "\r\n\t";
      if (!parse(str.c_str(), basicRules.TEXT).full)
	throw "TEXT 2 rule failed";


      str = "Q";
      if (!parse(str.c_str(), basicRules.TEXT).full)
	throw "TEXT 2 rule failed";

      // HEX
      std::cout << "rule<> HEX :" << std::endl;
      str = "T";
      if (parse(str.c_str(), basicRules.HEX).full)
	throw "HEX rule failed";

       str = "9";
       if (!parse(str.c_str(), basicRules.HEX).full)
	 throw "HEX rule failed";

       str = "A";
       if (!parse(str.c_str(), basicRules.HEX).full)
	 throw "HEX rule failed";

      // separators
       std::cout << "rule<> separators :" << std::endl;
      str = "-";
      if (parse(str.c_str(), basicRules.separators).full)
	throw "separators rule failed";

       str = "(";
       if (!parse(str.c_str(), basicRules.separators).full)
	 throw "separators rule failed";

       // separators_n
       std::cout << "rule<> separators_n :" << std::endl;
       str = ")";
       if (parse(str.c_str(), basicRules.separators_n).full)
	 throw "separators_n rule failed";

       str = "-";
       if (!parse(str.c_str(), basicRules.separators_n).full)
	 throw "separators_n  rule failed";

      // token
      std::cout << "rule<> token :" << std::endl;
      str = "(";
      if (parse(str.c_str(), basicRules.token).full)
	throw "token rule failed";

      str = "c";
      if (!parse(str.c_str(), basicRules.token).full)
	throw "token rule failed";

       // ctext
      std::cout << "rule<> ctext :" << std::endl;
       str = "(";
       if (parse(str.c_str(), basicRules.ctext).full)
	 throw "ctext rule failed";

       str = "f";
       if (!parse(str.c_str(), basicRules.ctext).full)
	 throw "ctext rule failed";

      // quoted pair
      std::cout << "rule<> quoted_pair :" << std::endl;
      str = "p";
      if (parse(str.c_str(), basicRules.quoted_pair).full)
	throw "quoted_pair 1 rule failed";

      str = "\\ ";
      if (!parse(str.c_str(), basicRules.quoted_pair).full)
	throw "quoted_pair rule failed";


       // qd text
       std::cout << "rule<> qdtext:" << std::endl;
       str = "\"";
       if (parse(str.c_str(), basicRules.qdtext).full)
	 throw "qdtext rule failed";

       str = "<";
       if (!parse(str.c_str(), basicRules.qdtext).full)
	 throw "qdtext rule failed";

      // quoted string
      std::cout << "rule<> quoted_string :" << std::endl;
      str = "\"fgfgfgfg";
      if (parse(str.c_str(), basicRules.quoted_string).full)
	throw "quoted_string rule failed";

      str = "\"rtrt\"";
      if (!parse(str.c_str(), basicRules.quoted_string).full)
	throw "quoted_string rule failed";

      // comment
      std::cout << "rule<> comment :" << std::endl;
      str = "(()";
      if (parse(str.c_str(), basicRules.comment).full)
	throw "comment rule failed";
      str = "(this is a comment)";
      if (!parse(str.c_str(), basicRules.comment).full)
	throw "comment rule failed";
      
      //month
      std::cout<< "rule<> month "<< std::endl;
      str = "Jan";
      if (!parse(str.c_str(), dateRules.month).full)
	throw "month rule failed";

      //date1
      std::cout << "rule<> date1 #1:" << std::endl;
      str = "17 Jan 1983";
      if (!parse(str.c_str(), dateRules.date1).full)
	throw "date1 #1 rule failed";
      std::cout << "rule<> date1 #2:" << std::endl;
      str = "177 Feb 1983";
      if (parse(str.c_str(), dateRules.date1).full)
	throw "date1 #2 rule failed";
      
      //date2
      std::cout << "rule<> date2 :" << std::endl;
      str = "17-Jun-99 ";
      if (!parse(str.c_str(), dateRules.date2).full)
	throw "date2 rule failed";
      
      str = "34-Jun-99 ";
      if (parse(str.c_str(), dateRules.date2).full)
	throw "date2 rule failed";
      
      //date3
      std::cout << "rule<> date3 :" << std::endl;
      str = "Jan 17";
      if (!parse(str.c_str(), dateRules.date3).full)
	throw "date3 rule failed";

      str= "Jan  1";
      if (!parse(str.c_str(), dateRules.date3).full)
	throw "date3 rule failed";

      str = "Aug   89";
      if (parse(str.c_str(), dateRules.date3).full)
	throw "date3 rule failed";
 
      // time
      std::cout << "rule<> time :" << std::endl;
      str = "23:59:59";
      if (!parse(str.c_str(), dateRules.time).full)
	throw "time rule failed";
      
      str = "24:-1:-02";
      if (parse(str.c_str(), dateRules.time).full)
	throw "time rule failed";
      
      //asctime_date
      //rfc_850_date
      //rfc1123_date
      //HTTP_date

    }
  catch(const char* e)
    {
      std::cerr << e <<std::endl;
    }
}

int	main(void)
{
  basicUnitTesting();
  return (0);
}

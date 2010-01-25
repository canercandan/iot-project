#ifndef BASIC_RULES_H_
#define BASIC_RULES_H_

#define BOOST_SPIRIT_THREADSAFE /* Always before including spirit headers */
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_dynamic.hpp>

using namespace BOOST_SPIRIT_CLASSIC_NS;

struct	BasicRules
{
  BasicRules(void)
  {
    OCTET		= anychar_p; /*(any 8-bit sequence of data)*/
    CHAR		= range_p(0, 127); /*(any US-ASCII character (octets 0 - 127))*/
    UPALPHA		= upper_p; /*(any US-ASCII uppercase letter "A".."Z")*/
    LOALPHA		= lower_p; /*(any US-ASCII lowercase letter "a".."z")*/
    ALPHA		= (UPALPHA | LOALPHA);
    DIGIT		= digit_p; /*(any US-ASCII digit "0".."9")*/
    CTL			= cntrl_p; /*(any US-ASCII control character (octets 0 - 31) and DEL (127))*/
    CTLS		= +(cntrl_p);
    CTL_N		= ~range_p(0, 31) & ~ch_p(127); /*non control char*/
    CTLS_N		= +(CTL_N); /*non control chars*/
    HT			= ch_p('\t'); /*(US-ASCII HT, horizontal-tab (9))*/
    HT_N		= ~ch_p('\t'); /* non HT*/
    SP			=  ch_p(' '); /* <US-ASCII SP, space (32)>*/
    SP_N		= ~ch_p(' ');
    CR			= ch_p('\r');
    LF			= ch_p('\n');
    CRLF		= CR >> LF;
    LWS			= !(CRLF) && +( SP | HT );

    TEXT		= (CTLS_N | LWS) | (OCTET & CTLS_N); /*<any OCTET except CTLs, but including LWS>*/
    HEX			= xdigit_p;
    separators		= (ch_p('(') | ch_p(')') | ch_p('<') | ch_p('>') |
			   ch_p('@') | ch_p(',') | ch_p(';') | ch_p(':') |
			   ch_p('\\') | ch_p('\"') | ch_p('/') | ch_p('[') |
			   ch_p(']') | ch_p('?') | ch_p('=') | ch_p('{') |
			   ch_p('}') | SP | HT);
    separators_n	= (~ch_p('(') & ~ch_p(')') & ~ch_p('<') & ~ch_p('>') &
			   ~ch_p('@') & ~ch_p(',') & ~ch_p(';') & ~ch_p(':') &
			   ~ch_p('\\') & ~ch_p('\"') & ~ch_p('/') & ~ch_p('[') &
			   ~ch_p(']') & ~ch_p('?') & ~ch_p('=') & ~ch_p('{') &
			   ~ch_p('}') & SP_N & HT_N);
    token		= +(CTLS_N  & separators_n & CHAR); /* 1*<any CHAR except CTLs or separators>*/
    ctext		= (~(ch_p('(')) & ~(ch_p(')')) & TEXT); /*<any TEXT excluding "(" and ")">;*/
    quoted_pair		= ch_p('\\') >> CHAR; /* ch_p(\" >> CHAR */
    qdtext		= (~(ch_p('\"')) & TEXT ); /*<any TEXT except <">>*/
    quoted_string	=  (ch_p('\"') >>*(qdtext | quoted_pair)  >> ch_p('\"')); /*( <"> *(qdtext | quoted-pair ) <"> )*/
    comment		=  ch_p('(') >> *(ctext | quoted_pair | comment) >> ch_p(')'); /*"(" *( ctext | quoted-pair | comment ) ")"*/
  }

  stored_rule<>	OCTET, CHAR, UPALPHA, LOALPHA, ALPHA, DIGIT;
  stored_rule<>	CTL, CTLS, CTL_N, CTLS_N, HT, HT_N, SP, SP_N;
  stored_rule<>	CR, LF, CRLF, LWS, TEXT, HEX, separators;
  stored_rule<>	separators_n, token, ctext, quoted_pair, qdtext;
  stored_rule<>	quoted_string, comment;
};

#endif

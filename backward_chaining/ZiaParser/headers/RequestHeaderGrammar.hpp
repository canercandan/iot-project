#ifndef REQUEST_HEADER_GRAMMAR_H_
#define REQUEST_HEADER_GRAMMAR_H_

#define BOOST_SPIRIT_THREADSAFE /* Always before including spirit headers */
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_attribute.hpp>
#include <boost/spirit/include/classic_dynamic.hpp>
#include <boost/spirit/include/phoenix1.hpp>
#include "BasicRules.h"
#include "ParsingResult.h"

using namespace phoenix;
using namespace BOOST_SPIRIT_CLASSIC_NS;

struct request_header_grammar_closure
  : BOOST_SPIRIT_CLASSIC_NS::closure<request_header_grammar_closure, ParsingResult>
{
  member1 val;
};

static BasicRules	basicRules;

// Les regles qui contiennent un underscore contienne un tiret dans la RFC.
struct request_header_grammar
  : public grammar<request_header_grammar,
		   request_header_grammar_closure::context_t>
{
  template <typename ScannerT>
  struct definition
  {
    definition(request_header_grammar const& /*self*/)
    {
      generic_message =
	start_line >> *(message_header >> basicRules.CRLF) >> !(message_body);

      start_line = Request_Line | Status_Line;

      message_header = field_name >> ch_p(':') >> !(field_value);

      field_name = basicRules.token;
      field_value = *( field_content | basicRules.LWS );

      // a verifier
      field_content =
	*(basicRules.TEXT) | +(basicRules.token | basicRules.separators | basicRules.quoted_string);

      message_body =
	entity_body; //|<entity-body encoded as per Transfer-Encoding>;

      entity_body = *(basicRules.OCTET);

      /* Request_Line */
      Request_Line =
	Method >> basicRules.SP >> Request_URI >> basicRules.SP >> HTTP_Version >> basicRules.CRLF;

      Method = str_p("OPTIONS") | "GET" | "HEAD" | "POST" | "PUT" |
	"DELETE" | "TRACE" | "CONNECT" | extension_method;

      extension_method = basicRules.token;

      Request_URI = ch_p('*') | absoluteURI | abs_path | authority;

      /* absoluteURI */
      absoluteURI =
	scheme >> ch_p(':') >> ( hier_part | opaque_part );

      scheme = basicRules.ALPHA >>
	*( basicRules.ALPHA | basicRules.DIGIT | ch_p('+') | ch_p('-') | ch_p('.') );

      hier_part = ( net_path | abs_path ) >> !( ch_p('?') >> query );

      net_path = str_p("//") >> authority >> !( abs_path );

      authority = server | reg_name;

      server = !( !(userinfo >> ch_p('@')) >> hostport );

      userinfo = *( unreserved | escaped | ch_p(';') | ':' | '&' | '=' | '+' | '$' | ',' );

      unreserved = alphanum | mark;

      mark = ch_p('-') | '_' | '.' | '!' | '~' | '*' | '\'' | '(' | ')';

      escaped = ch_p('%') >> xdigit_p >> xdigit_p;

      hostport = host >> !( ch_p(':') >> port );

      host = hostname | IPv4address;

      hostname =
	*( domainlabel >> ch_p('.') ) >> toplabel >> !( ch_p('.') );

      domainlabel =
	alphanum | alphanum >> *( alphanum | ch_p('-') ) >> alphanum;

      toplabel =
	basicRules.ALPHA | basicRules.ALPHA >> *( alphanum | ch_p('-') ) >> alphanum;

      IPv4address =
	+(basicRules.DIGIT) >> ch_p('.') >> +(basicRules.DIGIT) >> ch_p('.') >> +(basicRules.DIGIT) >> ch_p('.') >> +(basicRules.DIGIT);

      port = +(basicRules.DIGIT);

      reg_name =
	+( unreserved | escaped | ch_p('$') | ',' | ';' | ':' | '@' | '&' | '=' | '+' );

      abs_path = ch_p('/') >> path_segments;

      path_segments = segment >> *( ch_p('/') >> segment );

      segment = *(pchar) >> *( ch_p(';') >> param );

      pchar =
	unreserved | escaped | ch_p(':') | '@' | '&' | '=' | '+' | '$' | ',';

      param = *(pchar);

      query = *(uric);

      uric = reserved | unreserved | escaped;

      opaque_part = uric_no_slash >> *(uric);

      uric_no_slash = unreserved | escaped | ch_p(';') | '?' | ':' |
	'@' | '&' | '=' | '+' | '$' | ',';
      /* absoluteURI */

      HTTP_Version =
	str_p("HTTP") >> ch_p('/') >> +(basicRules.DIGIT) >> ch_p('.') >> +(basicRules.DIGIT);
      /* Request_Line */

      /* Status_Line */
      Status_Line = HTTP_Version >> basicRules.SP >> Status_Code >> basicRules.SP >> Reason_Phrase >> basicRules.CRLF;

      Status_Code =
	str_p("100") | // Section 10.1.1: Continue
	"101" | // Section 10.1.2: Switching Protocols
	"200" | // Section 10.2.1: OK
	"201" | // Section 10.2.2: Created
	"202" | // Section 10.2.3: Accepted
	"203" | // Section 10.2.4: Non-Authoritative Information
	"204" | // Section 10.2.5: No Content
	"205" | // Section 10.2.6: Reset Content
	"206" | // Section 10.2.7: Partial Content
	"300" | // Section 10.3.1: Multiple Choices
	"301" | // Section 10.3.2: Moved Permanently
	"302" | // Section 10.3.3: Found
	"303" | // Section 10.3.4: See Other
	"304" | // Section 10.3.5: Not Modified
	"305" | // Section 10.3.6: Use Proxy
	"307" | // Section 10.3.8: Temporary Redirect
	"400" | // Section 10.4.1: Bad Request
	"401" | // Section 10.4.2: Unauthorized
	"402" | // Section 10.4.3: Payment Required
	"403" | // Section 10.4.4: Forbidden
	"404" | // Section 10.4.5: Not Found
	"405" | // Section 10.4.6: Method Not Allowed
	"406"// Section 10.4.7: Not Acceptable
	;

      // a verifier.
      Reason_Phrase = *(CR_N & LF_N & basicRules.TEXT);

      CR_N = ~ch_p('\r');
      LF_N = ~ch_p('\n');
      /* Status_Line */

      // Common Rules (a ranger...)
      alphanum	= alnum_p;
    }

    rule<ScannerT>	generic_message;
    rule<ScannerT>	start_line, message_header, Request_Line, Status_Line;
    rule<ScannerT>	field_name, field_value, field_content;
    rule<ScannerT>	message_body, entity_body, Method, Request_URI;
    rule<ScannerT>	HTTP_Version, extension_method, absoluteURI;
    rule<ScannerT>	abs_path, authority, scheme, hier_part, opaque_part;
    rule<ScannerT>	net_path, query, server, reg_name, userinfo, hostport;
    rule<ScannerT>	unreserved, escaped, alphanum, mark, host, port;
    rule<ScannerT>	hostname, IPv4address, domainlabel, toplabel;
    rule<ScannerT>	path_segments, segment, pchar, param, uric, reserved;
    rule<ScannerT>	uric_no_slash, Status_Code, Reason_Phrase;
    rule<ScannerT>	CR_N, LF_N;

    const rule<ScannerT>& start() const { return generic_message; }
  };
};

#endif

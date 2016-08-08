#include "pgpauth.h"

#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

int main(int argc, char* argv[])
{
	try
	{
		PGPAuthInitialize();

		cgicc::Cgicc cgi;
		std::string data = cgi("data");

		std::cout << cgicc::HTTPHTMLHeader();
		std::cout << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << cgicc::html() << cgicc::head(cgicc::title("PGPAuth handler")) << cgicc::body();

		if(data.length() == 0)
		{
			std::cout << "No data-parameter!";
		}
		else
		{
			PGPAuth(data);
		}

		std::cout << cgicc::body() << cgicc::html();
	}
	catch(const std::exception& e)
	{
		std::cout << "an exception occured!";
	}

	return EXIT_SUCCESS;
}

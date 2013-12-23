#include "pgpauth.h"

#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

using namespace cgicc;

int main(int argc, char* argv[])
{
	try
	{
		PGPAuthInitialize();

		Cgicc cgi;
		string data =  cgi("data");

		cout << HTTPHTMLHeader();
		cout << HTMLDoctype(HTMLDoctype::eStrict) << html() << head(title("PGPAuth handler")) << body();

		if(data.length() == 0)
		{
			cout << "No data-paramter!";
		}
		else
		{
			PGPAuth(data);
		}

		cout << body() << html();
	}
	catch(const std::exception& e)
	{
		cout << "an exception occured!";
	}

	return EXIT_SUCCESS;
}

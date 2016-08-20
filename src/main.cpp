#include "../config.h"

#include <libconfig.h++>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

#include "FCgiIO.h"
#include "pgpauth.h"

int main(int argc, char* argv[])
{
    libconfig::Config config;
    config.readFile(CONFIG_FILE_LOCATION);

    try {
        const char* openCommand  = config.lookup("commands/open");
        const char* closeCommand = config.lookup("commands/close");
        const char* listenSocket = config.lookup("listen/address");

        PGPAuth pgpAuth(openCommand, closeCommand);

        int socket = FCGX_OpenSocket(listenSocket, 0);

        FCGX_Request request;
        FCGX_Init();
        FCGX_InitRequest(&request, socket, 0);

        while(FCGX_Accept_r(&request) == 0) {
            cgicc::FCgiIO cgiIO(request);

            try
            {
                cgicc::Cgicc cgi(&cgiIO);
                std::string data = cgi("data");

                cgiIO << cgicc::HTTPHTMLHeader();
                cgiIO << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << cgicc::html() << cgicc::head(cgicc::title("PGPAuth handler")) << cgicc::body();

                if(data.length() == 0)
                {
                    cgiIO << "No data-parameter!";
                }
                else
                {
                    pgpAuth.parseData(data);
                }

                cgiIO << cgicc::body() << cgicc::html();
            }
            catch(const std::exception& e)
            {
                std::cerr << "Something went wrong: " << e.what() << std::endl;
            }
        }
    }
    catch(const libconfig::SettingNotFoundException & e) {
        std::cerr << "Config not found: " << e.what() << std::endl;
        exit(-1);
    }

	return EXIT_SUCCESS;
}

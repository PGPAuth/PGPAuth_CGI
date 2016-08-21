#include "../config.h"

#include <libconfig.h++>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

#include "FCgiIO.h"
#include "pgpauth.h"

#ifndef CONFIG_FILE_LOCATION
    #define CONFIG_FILE_LOCATION "/etc/pgpauth_cgi.cfg"
#endif

int main(int argc, char* argv[])
{
    libconfig::Config config;
    config.readFile(CONFIG_FILE_LOCATION);

    try {
        const char* openCommand    = config.lookup("commands/open");
        const char* closeCommand   = config.lookup("commands/close");
        const char* listenSocket   = config.lookup("listen/address");
        const char* pgpHomedir     = config.lookup("pgpauth/homedir");
        int maxTimestampDifference = config.lookup("pgpauth/max_timestamp_difference");

        PGPAuth pgpAuth(openCommand, closeCommand, pgpHomedir, maxTimestampDifference);

        int socket = FCGX_OpenSocket(listenSocket, 0);

        FCGX_Request request;
        FCGX_Init();
        FCGX_InitRequest(&request, socket, 0);

        while(FCGX_Accept_r(&request) == 0) {
            cgicc::FCgiIO cgiIO(request);

            try
            {
                cgicc::Cgicc cgi(&cgiIO);
                cgicc::CgiEnvironment environment = cgi.getEnvironment();

                if(environment.getRequestMethod() == "POST") {
                    std::string data = cgi("data");

                    cgiIO << "Content-Type: text/html; charset=utf8";
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
                else if(environment.getRequestMethod() == "GET") {
                    std::string url  = (environment.usingHTTPS() ? "https" : "http");
                                url += "://" + environment.getServerName();

                    if((environment.usingHTTPS() && environment.getServerPort() != 443) ||
                       (!environment.usingHTTPS() && environment.getServerPort() != 80)) {
                        url += ":" + environment.getServerPort();
                    }

                    url += environment.getScriptName();

                    // unescaped: {"name": serverName, "url": serverURL} it's just JSON :)
                    std::string configData = "{\"name\":\"" + environment.getServerName() + "\",\"url\":\"" + url + "\"}";
                    std::string configUrl = "https://pgpauth.lf-net.org/serverConfig?config=" + cgicc::form_urlencode(configData);

                    cgiIO << cgicc::HTTPHTMLHeader();
                    cgiIO << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << cgicc::html() << cgicc::head(cgicc::title("PGPAuth")) << cgicc::body();

                    cgiIO << cgicc::h1() << "PGPAuth" << cgicc::h1();
                    cgiIO << cgicc::p() << "This is a server endpoint for PGPAuth. Click the link below to add this server to your device:" << cgicc::br()
                          << "<a href=\"" + configUrl + "\">PGPAuth configuration link</a>" << cgicc::p();

                    cgiIO << cgicc::p() << "You can install PGPAuth for Android from "
                          << "<a href=\"http://www.amazon.com/gp/mas/dl/android?p=org.lf_net.pgpunlocker\">Amazon App Store</a>, "
                          << "<a href=\"https://f-droid.org/repository/browse/?fdid=org.lf_net.pgpunlocker\">F-Droid</a> " << "or "
                          << "<a href=\"https://play.google.com/store/apps/details?id=org.lf_net.pgpunlocker\">Google Play</a>." << cgicc::p();

                    cgiIO << cgicc::p() << "More platforms planned, will be implemented when requested by enough users."
                          << "Please send your nag-mails to <a href=\"mailto:littlefox@lf-net.org\">littlefox@lf-net.org</a>."
                          << "Since the only real other platform (something with fruits) requires me to pay 99&euro; per year, "
                          << "sending money would also work."
                          << cgicc::p();

                    cgiIO << cgicc::body() << cgicc::html();
                }
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

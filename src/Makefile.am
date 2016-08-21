AM_CXXFLAGS = -std=c++11 --pedantic -Wall -Werror -O2
AM_LDFLAGS  = -std=c++11
EXTRA_DIST  = pgpauth_cgi.cfg

bin_PROGRAMS         = pgpauth_cgi
pgpauth_cgi_CPPFLAGS = ${LIBCONFIGXX_CFLAGS} ${CGICC_CFLAGS} -DCONFIG_FILE_LOCATION=\"$(sysconfdir)/pgpauth_cgi.cfg\"
pgpauth_cgi_LDADD    = -lgpgme -lfcgi -lfcgi++ -lcgicc ${CGICC_LIBS} ${LIBCONFIGXX_LIBS}
pgpauth_cgi_SOURCES  = main.cpp pgpauth.cpp pgpauth.h FCgiIO.cpp FCgiIO.h

sysconf_DATA         = pgpauth_cgi.cfg

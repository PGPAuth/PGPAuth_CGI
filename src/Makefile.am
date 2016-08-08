AM_CPPFLAGS = -std=c++03 --pedantic -Wall -Werror -O2 $(GPGME_CFLAGS) -I $(cgicc_includedir)
AM_LDFLAGS  = -std=c++03

bin_PROGRAMS        = pgpauth_cgi
pgpauth_cgi_LDADD   = -L$(cgicc_libdir) -lcgicc $(GPGME_LIBS)
pgpauth_cgi_SOURCES = main.cpp pgpauth.cpp pgpauth.h

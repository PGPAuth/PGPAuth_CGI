AM_CPPFLAGS = -std=c++03 --pedantic -Wall -Werror -O2
AM_LDFLAGS  = -std=c++03

bin_PROGRAMS        = pgpauth_cgi
pgpauth_cgi_LDADD   = -lcgicc -lgpgme
pgpauth_cgi_SOURCES = main.cpp pgpauth.cpp pgpauth.h

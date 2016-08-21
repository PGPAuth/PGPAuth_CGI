# PGPAuth_cgi

This is the server-side CGI program to react on requests by the PGPAuth apps (https://github.com/PGPAuth).

See this program more as a Proof of Concept and please check it carefully before using it in a productive environment. It is known to work, but isn't audited. If you want to check the code of PGPAuth for security issues, start here.

# Compile-time-requirements

* Gnu CGICC
* GPGME
* libconfig++
* libfcgi

## Runtime-requirements

* FastCGI-capable HTTP-server
* PGPAuth App (see link provided up there)

## Known bugs

* only the first signature is checked

## Install

* create PGP homedir and give your pgpauth-account the only access rights (GnuPG checks them)
* su to pgpauth-account and fetch/import the keys allowed to do requests (don't forget --homedir)
* trust the keys allowed to do requests (don't forget --homedir)
* ```./configure && make && sudo make install```
 * use all the flags you like, it's standard autoconf
* edit the config file
 * path determined by autoconf, depends on the prefix. Default is ```/usr/local/etc/pgpauth_cgi.cfg```
* configure webserver to connect to pgpauth_cgi via FastCGI
* configure your system to start pgpauth_cgi at boot automagically
* enjoy :)
* send all bugs to littlefox@fsfe.org (0x97FC6451)

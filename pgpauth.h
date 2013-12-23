#ifndef _PGPAUTH_H_INCLUDED
#define _PGPAUTH_H_INCLUDED

#define GPG_HOME_DIR "/home/moritz/pgpauth_home_dir"
#define MAX_TIMESTAMP_CHANGE 300 // 5 minutes

#include <string>
#include <exception>
#include <iostream>
#include <cstdlib>

#include <gpgme.h>

using namespace std;

void PGPAuthInitialize();

void PGPAuth(string data);

void open();

void close();

#endif

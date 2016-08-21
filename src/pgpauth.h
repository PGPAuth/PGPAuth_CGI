#ifndef _PGPAUTH_H_INCLUDED
#define _PGPAUTH_H_INCLUDED

#define GPG_HOME_DIR "/home/moritz/pgpauth_home_dir"
#define MAX_TIMESTAMP_CHANGE 300 // 5 minutes

#include <string>
#include <exception>
#include <iostream>
#include <cstdlib>

#include <gpgme.h>

class PGPAuth {
    public:
        PGPAuth(const char* openCommand, const char* closeCommand, const char* homedir, int maxTimestampDifference);

        void parseData(const std::string& data);

    private:
        const char* _openCommand;
        const char* _closeCommand;
        int _maxTimestampDifference;

        gpgme_ctx_t _gpgmeContext;
};

#endif

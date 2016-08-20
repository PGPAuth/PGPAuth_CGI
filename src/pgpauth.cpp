#include <libconfig.h++>
#include "pgpauth.h"

// Code based on this introduction:
// http://www.nico.schottelius.org/docs/a-small-introduction-for-using-gpgme/

gpgme_ctx_t _gpgmeContext;

void PGPAuthInitialize()
{
	// needed to initialize multi-threading support by gpgme
	gpgme_check_version(NULL);

	// setting locale, because the tutorial also does it ;)
	gpgme_set_locale(NULL, LC_CTYPE, setlocale (LC_CTYPE, NULL));

	// checking OpenPGP support
	gpgme_error_t err = gpgme_engine_check_version(GPGME_PROTOCOL_OpenPGP);
   	if(err != GPG_ERR_NO_ERROR)
		throw std::exception();

	// getting engine info
	gpgme_engine_info_t enginfo;
	err = gpgme_get_engine_info(&enginfo);
  	if(err != GPG_ERR_NO_ERROR)
		throw std::exception();

	// creating a context
	err = gpgme_new(&_gpgmeContext);
   	if(err != GPG_ERR_NO_ERROR)
		throw std::exception();

   	/* setting protocol to use in our context */
   	err = gpgme_set_protocol(_gpgmeContext,GPGME_PROTOCOL_OpenPGP);
   	if(err != GPG_ERR_NO_ERROR)
		throw std::exception();

	// setting engine info (keystorage and executable)
	err = gpgme_ctx_set_engine_info (_gpgmeContext, GPGME_PROTOCOL_OpenPGP,
               enginfo->file_name, GPG_HOME_DIR);
	if(err != GPG_ERR_NO_ERROR)
		throw std::exception();

	// setting ASCII-armor
	gpgme_set_armor(_gpgmeContext, 1);
}

void PGPAuth(std::string data)
{
	gpgme_data_t gpgmeSigData;
	gpgme_data_t gpgmePlainData;

	// initializing data buffer
	gpg_error_t err = gpgme_data_new_from_mem(&gpgmeSigData, data.c_str(), data.length(), 0);
	if(err != GPG_ERR_NO_ERROR)
		throw std::exception();

	err = gpgme_data_new(&gpgmePlainData);
	if(err != GPG_ERR_NO_ERROR)
		throw std::exception();

	err = gpgme_op_verify(_gpgmeContext, gpgmeSigData, NULL, gpgmePlainData);

	if(err != GPG_ERR_NO_ERROR)
		throw std::exception();

	gpgme_verify_result_t result = gpgme_op_verify_result(_gpgmeContext);

	if((result->signatures[0].summary & GPGME_SIGSUM_VALID) == 0)
	{
		std::cout << "Invalid signature! " << result->signatures[0].summary;
		return;
	}

	off_t length = gpgme_data_seek(gpgmePlainData, 0, SEEK_END);
	char *buffer = new char[length];
	gpgme_data_seek(gpgmePlainData, 0, SEEK_SET);
	gpgme_data_read(gpgmePlainData, buffer, length);

	std::string plainData(buffer);

	std::string request = plainData.substr(0, plainData.find_first_of(":"));

	if(request != "open" && request != "close")
		throw std::exception();

	std::string tstring = plainData.substr(plainData.find_first_of(":") + 1);

	time_t timestamp = strtol(tstring.c_str(), NULL, 10);
	time_t currentTime = time(NULL);

	if((currentTime - timestamp) > MAX_TIMESTAMP_CHANGE)
		throw std::exception();

    libconfig::Config cfg;
    cfg.readFile(CONFIG_FILE_LOCATION);

	if(request == "open") {
		system(cfg.lookup("open_command").c_str());
    }
	else if(request == "close") {
		system(cfg.lookup("close_command").c_str());
    }
}


#pragma once

#include <cryptopp/seckey.h>
#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/cryptlib.h>

#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/base64.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/hex.h>
#include <cryptopp/ccm.h>
#include <atlsecurity.h> 
#include <strsafe.h> 
#include <windows.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <curl/curl.h>
#include <shellapi.h>
#include <sstream> 
#include <iomanip> 
#include <fstream> 
#include <nlohmann/json.hpp>
#pragma comment(lib, "rpcrt4.lib")

#include "Includes.h"
#include "CheatEncryption.h"

namespace Auth
{
	int Role = 1337;
}

char MessageText;
char TextToSendContent[256];
struct msg
{
	std::string message;
	std::string author;
	std::string timestamp;
};

namespace Security {

	class encryption {
	public:
		std::string name;

		static std::string sha256(const std::string& plain_text) {
			std::string hashed_text;
			CryptoPP::SHA256 hash;

			try {
				CryptoPP::StringSource hashing(plain_text, true,
					new CryptoPP::HashFilter(hash,
						new CryptoPP::HexEncoder(
							new CryptoPP::StringSink(hashed_text),
							false
						)
					)
				);
			}
			catch (CryptoPP::Exception& ex) {
				system(TEXT("cls"));
				std::cout << ex.what();
				exit(5000);
			}

			return hashed_text;
		}

		static std::string encode(const std::string& plain_text) {
			std::string encoded_text;

			try {
				CryptoPP::StringSource encoding(plain_text, true,
					new CryptoPP::HexEncoder(
						new CryptoPP::StringSink(encoded_text),
						false
					)
				);
			}
			catch (CryptoPP::Exception& ex) {
				system(XorStr("cls").c_str());
				std::cout << ex.what();
				exit(5000);
			}

			return encoded_text;
		}

		static std::string decode(const std::string& encoded_text) {
			std::string out;

			try {
				CryptoPP::StringSource decoding(encoded_text, true,
					new CryptoPP::HexDecoder(
						new CryptoPP::StringSink(out)
					)
				);
			}
			catch (CryptoPP::Exception& ex) {
				system(XorStr("cls").c_str());
				std::cout << ex.what();
				exit(5000);
			}

			return out;
		}

		static std::string iv_key() {
			UUID uuid = { 0 };
			std::string guid;

			::UuidCreate(&uuid);

			RPC_CSTR szUuid = NULL;
			if (::UuidToStringA(&uuid, &szUuid) == RPC_S_OK)
			{
				guid = (char*)szUuid;
				::RpcStringFreeA(&szUuid);
			}

			return guid.substr(0, 16);
		}

		static std::string encrypt(std::string message, std::string enc_key, std::string iv) {
			enc_key = sha256(enc_key).substr(0, 32);
			iv = sha256(iv).substr(0, 16);


			std::string cipher_text;

			try {
				CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption;
				encryption.SetKeyWithIV((CryptoPP::byte*)enc_key.c_str(), enc_key.size(), (CryptoPP::byte*)iv.c_str());

				CryptoPP::StringSource encryptor(message, true,
					new CryptoPP::StreamTransformationFilter(encryption,
						new CryptoPP::HexEncoder(
							new CryptoPP::StringSink(cipher_text),
							false
						)
					)
				);
			}
			catch (CryptoPP::Exception& ex) {
				system(XorStr("cls").c_str());
				std::cout << ex.what();
				exit(5000);
			}
			return cipher_text;
		}

		static std::string decrypt(std::string message, std::string enc_key, std::string iv) {
			enc_key = sha256(enc_key).substr(0, 32);

			iv = sha256(iv).substr(0, 16);

			std::string plain_text;
			
			try {
				CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryption;
				decryption.SetKeyWithIV((CryptoPP::byte*)enc_key.c_str(), enc_key.size(), (CryptoPP::byte*)iv.c_str());

				CryptoPP::StringSource decryptor(message, true,
					new CryptoPP::HexDecoder(
						new CryptoPP::StreamTransformationFilter(decryption,
							new CryptoPP::StringSink(plain_text)
						)
					)
				);
			}
			catch (CryptoPP::Exception& ex) {
				system(XorStr("cls").c_str());
				std::cout << ex.what();
				exit(5000);
			}
			return plain_text;
		}
	};

	class utils {
	public:

		static std::string get_hwid() {
			/*ATL::CAccessToken accessToken;
			ATL::CSid currentUserSid;
			if (accessToken.GetProcessToken(TOKEN_READ | TOKEN_QUERY) &&
				accessToken.GetUser(&currentUserSid))
				return std::string(CT2A(currentUserSid.Sid()));
			else*/
				return "";
		}

		static std::time_t string_to_timet(std::string timestamp) {
			auto cv = strtol(timestamp.c_str(), NULL, 10);

			return (time_t)cv;
		}

		static std::tm timet_to_tm(time_t timestamp) {
			std::tm context;

			localtime_s(&context, &timestamp);

			return context;
		}

	};


	auto iv = encryption::sha256(encryption::iv_key());
	class api {


	public:

		std::string name, ownerid, secret, version;

		api(std::string name, std::string ownerid, std::string secret, std::string version)
			: name(name), ownerid(ownerid), secret(secret), version(version) {}

		void init()
		{
			enckey = encryption::sha256(encryption::iv_key());
			auto data =
				XorStr("type=").c_str() + encryption::encode(XorStr("init").c_str()) +
				XorStr("&ver=").c_str() + encryption::encrypt(version, encryption::decode(secret), iv) +
				XorStr("&enckey=").c_str() + encryption::encrypt(enckey, encryption::decode(secret), iv) +
				XorStr("&name=").c_str() + encryption::encode(name) +
				XorStr("&ownerid=").c_str() + encryption::encode(ownerid) +
				XorStr("&init_iv=").c_str() + iv;

			auto response = req(data);
			response = encryption::decrypt(response, encryption::decode(secret), iv);
			auto json = response_decoder.parse(response);

			if (json[(XorStr("success").c_str())])
			{
				sessionid = json[("sessionid")];
				// optional success message
			}
			else if (json[(XorStr("message").c_str())] == XorStr("invalidver").c_str())
			{
				std::string dl = json[("download")];
				ShellExecuteA(0, XorStr("open").c_str(), dl.c_str(), 0, 0, SW_SHOWNORMAL);
				exit(0);
			}
			else
			{
				error(json[(XorStr("message").c_str())]);
			}
		}

		bool login(std::string username, std::string password)
		{
			std::string hwid = utils::get_hwid();
			auto iv = encryption::sha256(encryption::iv_key());
			auto datav2 =
				XorStr("type=").c_str() + encryption::encode(XorStr("login").c_str()) +
				XorStr("&username=").c_str() + encryption::encrypt(username, enckey, iv) +
				XorStr("&pass=").c_str() + encryption::encrypt(password, enckey, iv) +
				XorStr("&hwid=").c_str() + encryption::encrypt(hwid, enckey, iv) +
				XorStr("&sessionid=").c_str() + encryption::encode(sessionid) +
				XorStr("&name=").c_str() + encryption::encode(name) +
				XorStr("&ownerid=").c_str() + encryption::encode(ownerid) +
				XorStr("&init_iv=").c_str() + iv;
			auto response = req(datav2);
			response = encryption::decrypt(response, enckey, iv);

			//std::cout << response << std::endl;

			auto json = response_decoder.parse(response);
			nlohmann::json data = json[("info")];
			if (json[(XorStr("success").c_str())])
			{
				user_data.username = data[TEXT("username")];
				user_data.expiry = utils::timet_to_tm(
					utils::string_to_timet(data[TEXT("subscriptions")][0][TEXT("expiry")])
				);
				for (int i = 0; i < data[TEXT("subscriptions")].size(); i++)
				{
					std::string sub = data[TEXT("subscriptions")][i][TEXT("subscription")];
					if (sub == TEXT("User"))
						Auth::Role = 0;
					else if (sub == TEXT("Tester"))
						Auth::Role = 1;
					else if (sub == TEXT("Reseller"))
						Auth::Role = 2;
					else if (sub == TEXT("Staff"))
						Auth::Role = 3;
					else if (sub == TEXT("Admin"))
						Auth::Role = 4;
					else if (sub == TEXT("Developer"))
						Auth::Role = 5;
					else if (sub == TEXT("Owner"))
						Auth::Role = 6;
					else
						Auth::Role = 1337;
				}

				return true;
			}
			else
			{
				//error(json[(XorStr("message").c_str())]);
				return false;
			}
		}

		bool regstr(std::string username, std::string password, std::string key) {

			std::string hwid = utils::get_hwid();
			auto iv = encryption::sha256(encryption::iv_key());
			auto data =
				XorStr("type=").c_str() + encryption::encode(XorStr("register").c_str()) +
				XorStr("&username=").c_str() + encryption::encrypt(username, enckey, iv) +
				XorStr("&pass=").c_str() + encryption::encrypt(password, enckey, iv) +
				XorStr("&key=").c_str() + encryption::encrypt(key, enckey, iv) +
				XorStr("&hwid=").c_str() + encryption::encrypt(hwid, enckey, iv) +
				XorStr("&sessionid=").c_str() + encryption::encode(sessionid) +
				XorStr("&name=").c_str() + encryption::encode(name) +
				XorStr("&ownerid=").c_str() + encryption::encode(ownerid) +
				XorStr("&init_iv=").c_str() + iv;
			auto response = req(data);
			response = encryption::decrypt(response, enckey, iv);
			auto json = response_decoder.parse(response);

			if (json[(XorStr("success").c_str())])
			{
				// optional success message
				//load_user_data(json[("info")]);
				return true;
			}
			else
			{
				//error(json[(XorStr("message").c_str())]);
				return false;
			}
		}

		void upgrade(std::string username, std::string key) {

			auto iv = encryption::sha256(encryption::iv_key());
			auto data =
				XorStr("type=").c_str() + encryption::encode(XorStr("upgrade").c_str()) +
				XorStr("&username=").c_str() + encryption::encrypt(username, enckey, iv) +
				XorStr("&key=").c_str() + encryption::encrypt(key, enckey, iv) +
				XorStr("&sessionid=").c_str() + encryption::encode(sessionid) +
				XorStr("&name=").c_str() + encryption::encode(name) +
				XorStr("&ownerid=").c_str() + encryption::encode(ownerid) +
				XorStr("&init_iv=").c_str() + iv;
			auto response = req(data);
			response = encryption::decrypt(response, enckey, iv);
			auto json = response_decoder.parse(response);

			if (json[(XorStr("success").c_str())])
			{
				// optional success message
			}
			else
			{
				error(json[(XorStr("message").c_str())]);
			}
		}

		bool license(std::string key) {

			auto iv = encryption::sha256(encryption::iv_key());
			std::string hwid = utils::get_hwid();
			auto data =
				XorStr("type=").c_str() + encryption::encode(XorStr("license").c_str()) +
				XorStr("&key=").c_str() + encryption::encrypt(key, enckey, iv) +
				XorStr("&hwid=").c_str() + encryption::encrypt(hwid, enckey, iv) +
				XorStr("&sessionid=").c_str() + encryption::encode(sessionid) +
				XorStr("&name=").c_str() + encryption::encode(name) +
				XorStr("&ownerid=").c_str() + encryption::encode(ownerid) +
				XorStr("&init_iv=").c_str() + iv;
			auto response = req(data);
			response = encryption::decrypt(response, enckey, iv);
			auto json = response_decoder.parse(response);

			if (json[(XorStr("success").c_str())])
			{
				// optional success message
				load_user_data(json[("info")]);

				return true;
			}

			return false;
		}

		void setvar(std::string var, std::string vardata) {

			auto iv = encryption::sha256(encryption::iv_key());
			auto data =
				XorStr("type=").c_str() + encryption::encode(XorStr("setvar").c_str()) +
				XorStr("&var=").c_str() + encryption::encrypt(var, enckey, iv) +
				XorStr("&data=").c_str() + encryption::encrypt(vardata, enckey, iv) +
				XorStr("&sessionid=").c_str() + encryption::encode(sessionid) +
				XorStr("&name=").c_str() + encryption::encode(name) +
				XorStr("&ownerid=").c_str() + encryption::encode(ownerid) +
				XorStr("&init_iv=").c_str() + iv;
			auto response = req(data);
			response = encryption::decrypt(response, enckey, iv);
			auto json = response_decoder.parse(response);

			if (json[(XorStr("success").c_str())])
			{
				// optional success message
			}
			else
			{
				error(json[(XorStr("message").c_str())]);
			}
		}

		std::string getvar(std::string var) {

			auto iv = encryption::sha256(encryption::iv_key());
			auto data =
				XorStr("type=").c_str() + encryption::encode(XorStr("getvar").c_str()) +
				XorStr("&var=").c_str() + encryption::encrypt(var, enckey, iv) +
				XorStr("&sessionid=").c_str() + encryption::encode(sessionid) +
				XorStr("&name=").c_str() + encryption::encode(name) +
				XorStr("&ownerid=").c_str() + encryption::encode(ownerid) +
				XorStr("&init_iv=").c_str() + iv;
			auto response = req(data);
			response = encryption::decrypt(response, enckey, iv);
			auto json = response_decoder.parse(response);

			if (json[(XorStr("success").c_str())])
			{
				return json[(XorStr("response").c_str())];
			}
			else
			{
				error(json[(XorStr("message").c_str())]);
			}
		}

		void ban() {

			auto iv = encryption::sha256(encryption::iv_key());
			std::string hwid = utils::get_hwid();
			auto data =
				XorStr("type=").c_str() + encryption::encode(XorStr("ban").c_str()) +
				XorStr("&sessionid=").c_str() + encryption::encode(sessionid) +
				XorStr("&name=").c_str() + encryption::encode(name) +
				XorStr("&ownerid=").c_str() + encryption::encode(ownerid) +
				XorStr("&init_iv=").c_str() + iv;
			auto response = req(data);
			response = encryption::decrypt(response, enckey, iv);
			auto json = response_decoder.parse(response);

			if (json[(XorStr("success").c_str())])
			{
				// optional success message
			}
			else
			{
				error(json[(XorStr("message").c_str())]);
			}
		}
		std::vector<msg> chatget(std::string channelname) {

			auto iv = encryption::sha256(encryption::iv_key());
			auto data =
				XorStr("type=").c_str() + encryption::encode("chatget") +
				XorStr("&channel=").c_str() + encryption::encrypt(channelname, enckey, iv) +
				XorStr("&sessionid=").c_str() + encryption::encode(sessionid) +
				XorStr("&name=").c_str() + encryption::encode(name) +
				XorStr("&ownerid=").c_str() + encryption::encode(ownerid) +
				XorStr("&init_iv=").c_str() + iv;
			auto response = req(data);
			response = encryption::decrypt(response, enckey, iv);
			auto json = response_decoder.parse(response);

			if (json[("success")])
			{
				std::vector<msg> buff;
				for (const auto message : json[("messages")]) {
					buff.push_back(msg{ message["message"],message["author"] ,message["timestamp"] });
				}
				return buff;
			}
			else
			{
				error(json[("message")]);
			}
		}
		bool chatsend(std::string msg, std::string channelname) {

			auto iv = encryption::sha256(encryption::iv_key());
			auto data =
				XorStr("type=").c_str() + encryption::encode("chatsend") +
				XorStr("&message=").c_str() + encryption::encrypt(msg, enckey, iv) +
				XorStr("&channel=").c_str() + encryption::encrypt(channelname, enckey, iv) +
				XorStr("&sessionid=").c_str() + encryption::encode(sessionid) +
				XorStr("&name=").c_str() + encryption::encode(name) +
				XorStr("&ownerid=").c_str() + encryption::encode(ownerid) +
				XorStr("&init_iv=").c_str() + iv;
			auto response = req(data);
			response = encryption::decrypt(response, enckey, iv);
			auto json = response_decoder.parse(response);

			if (json[("success")])
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		bool checkblack() {
			std::string hwid = utils::get_hwid();
			auto iv = encryption::sha256(encryption::iv_key());
			auto data =
				XorStr("type=").c_str() + encryption::encode(XorStr("checkblacklist").c_str()) +
				XorStr("&hwid=").c_str() + encryption::encrypt(hwid, enckey, iv) +
				XorStr("&sessionid=").c_str() + encryption::encode(sessionid) +
				XorStr("&name=").c_str() + encryption::encode(name) +
				XorStr("&ownerid=").c_str() + encryption::encode(ownerid) +
				XorStr("&init_iv=").c_str() + iv;
			auto response = req(data);
			response = encryption::decrypt(response, enckey, iv);
			auto json = response_decoder.parse(response);

			if (json[(XorStr("success").c_str())])
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		std::string var(std::string varid) {

			auto iv = encryption::sha256(encryption::iv_key());
			auto data =
				XorStr("type=").c_str() + encryption::encode("var") +
				XorStr("&varid=").c_str() + encryption::encrypt(varid, enckey, iv) +
				XorStr("&sessionid=").c_str() + encryption::encode(sessionid) +
				XorStr("&name=").c_str() + encryption::encode(name) +
				XorStr("&ownerid=").c_str() + encryption::encode(ownerid) +
				XorStr("&init_iv=").c_str() + iv;
			auto response = req(data);
			response = encryption::decrypt(response, enckey, iv);
			auto json = response_decoder.parse(response);

			if (json[(XorStr("success").c_str())])
			{
				return json[(XorStr("message").c_str())];
			}
			else
			{
				error(json[(XorStr("message").c_str())]);
			}
		}

		void log(std::string message) {

			auto iv = encryption::sha256(encryption::iv_key());

			char acUserName[100];
			DWORD nUserName = sizeof(acUserName);
			GetUserNameA(acUserName, &nUserName);
			std::string UsernamePC = acUserName;

			auto data =
				XorStr("type=").c_str() + encryption::encode(XorStr("log").c_str()) +
				XorStr("&pcuser=").c_str() + encryption::encrypt(UsernamePC, enckey, iv) +
				XorStr("&message=").c_str() + encryption::encrypt(message, enckey, iv) +
				XorStr("&sessionid=").c_str() + encryption::encode(sessionid) +
				XorStr("&name=").c_str() + encryption::encode(name) +
				XorStr("&ownerid=").c_str() + encryption::encode(ownerid) +
				XorStr("&init_iv=").c_str() + iv;

			req(data);
		}

		std::vector<unsigned char> download(std::string fileid) {
			auto iv = encryption::sha256(encryption::iv_key());
			auto to_uc_vector = [](std::string value) {
				return std::vector<unsigned char>(value.data(), value.data() + value.length() + 1);
			};

			auto data =
				XorStr("type=").c_str() + encryption::encode("file") +
				XorStr("&fileid=").c_str() + encryption::encrypt(fileid, enckey, iv) +
				XorStr("&sessionid=").c_str() + encryption::encode(sessionid) +
				XorStr("&name=").c_str() + encryption::encode(name) +
				XorStr("&ownerid=").c_str() + encryption::encode(ownerid) +
				XorStr("&init_iv=").c_str() + iv;

			auto response = req(data);
			response = encryption::decrypt(response, enckey, iv);
			auto json = response_decoder.parse(response);

			if (!json["success"])
			{
				error(json[(XorStr("message").c_str())]);
			}

			auto file = encryption::decode(json["contents"]);

			return to_uc_vector(file);
		}

		std::string webhook(std::string id, std::string params) {

			auto iv = encryption::sha256(encryption::iv_key());

			auto data =
				XorStr("type=").c_str() + encryption::encode(XorStr("webhook").c_str()) +
				XorStr("&webid=").c_str() + encryption::encrypt(id, enckey, iv) +
				XorStr("&params=").c_str() + encryption::encrypt(params, enckey, iv) +
				XorStr("&sessionid=").c_str() + encryption::encode(sessionid) +
				XorStr("&name=").c_str() + encryption::encode(name) +
				XorStr("&ownerid=").c_str() + encryption::encode(ownerid) +
				XorStr("&init_iv=").c_str() + iv;

			auto response = req(data);

			response = encryption::decrypt(response, enckey, iv);


			auto json = response_decoder.parse(response);

			if (json[(XorStr("success").c_str())])
			{
				return json[(XorStr("response").c_str())];
			}
			else
			{
				error(json[(XorStr("message").c_str())]);
			}
		}

		class user_data_class {
		public:
			std::string username;
			std::string ip;
			std::string hwid;
			std::tm createdate;
			std::tm lastlogin;
			std::tm expiry;
			int timeleft;
		};

		user_data_class user_data;

	private:
		std::string sessionid, enckey;

		static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
			((std::string*)userp)->append((char*)contents, size * nmemb);
			return size * nmemb;
		}

		static void error(std::string error)
		{
			system(XorStr("cls").c_str());

			printf("[E] -> %s", error.c_str());

			Sleep(1000);

			exit(0);
		}

		static std::string req(std::string data) {
			CURL* curl = curl_easy_init();

			if (!curl)
				return "null";

			std::string to_return;


			curl_easy_setopt(curl, CURLOPT_URL, XorStr("https://breadauth.com/api/1.0/").c_str());

			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);

			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &to_return);

			auto code = curl_easy_perform(curl);

			if (code != CURLE_OK)
				MessageBoxA(0, curl_easy_strerror(code), 0, MB_ICONERROR);

			curl_easy_cleanup(curl);

			long http_code = 0;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

			if (http_code == 429) // client was rate limited
			{
				error(XorStr("You're connecting too fast to loader, slow down.").c_str());
			}

			return to_return;
		}

		class user_data_structure {
		public:
			std::string username;
			std::string ip;
			std::string hwid;
			std::string createdate;
			std::string lastlogin;
			std::string expiry;
			int timeleft;
		};

		void load_user_data(nlohmann::json data) {
			user_data.username = data[XorStr("username").c_str()];

			if (user_data.username.length() <= 1)
				exit(0);

			user_data.ip = data[XorStr("ip").c_str()];
			if (user_data.ip.length() <= 1)
				exit(0);

			//Games::InternetPort = user_data.ip;

			user_data.expiry = utils::timet_to_tm(
				utils::string_to_timet(data["subscriptions"][0]["expiry"])
			);
			user_data.hwid = data[XorStr("hwid").c_str()];
			user_data.createdate = utils::timet_to_tm(
				utils::string_to_timet(data[XorStr("createdate").c_str()])
			);
			user_data.lastlogin = utils::timet_to_tm(
				utils::string_to_timet(data[XorStr("lastlogin").c_str()])
			);


			for (int i = 0; i < data["subscriptions"].size(); i++)
			{
				std::string sub = data["subscriptions"][i]["subscription"];
				if (sub == "f")
				{
					user_data.expiry = utils::timet_to_tm(
						utils::string_to_timet(data["subscriptions"][i]["expiry"])
					);
					user_data.timeleft = data["subscriptions"][i]["timeleft"];

					//Games::Product = 2;
				}
				else if (sub == "v")
				{
					user_data.expiry = utils::timet_to_tm(
						utils::string_to_timet(data["subscriptions"][i]["expiry"])
					);
					user_data.timeleft = data["subscriptions"][i]["timeleft"];

					//Games::Product = 3;
				}
			}
		}




		nlohmann::json response_decoder;

	};
}
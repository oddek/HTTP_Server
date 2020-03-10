#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <cstring>

class Http
{
public:
	Http(std::string _request);
	~Http();
	
	bool handle_message();
	std::string build_answer(bool valid_request);
	void print_parsed_message();

private:
	bool valid_path();
	std::string get_body();
	std::string get_time();

	std::string request;
	std::string http_version = "HTTP/1.0";
	std::vector<std::string> accepted_functions{ "GET" };
	std::string host = "213.162.241.177";
	std::string server = "OddeServer";
	std::vector<std::string> paths{ "index.html", "contact.html" };

	std::string requested_method;
	std::string requested_path;
	std::string requested_http_version;
	std::string requested_host;
	std::string trash;
};


#define _CRT_SECURE_NO_WARNINGS
#include "Http.h"

Http::Http(std::string _request): request(_request)
{
	handle_message();
}

Http::~Http()
{
}

bool Http::handle_message()
{
	std::stringstream ss(request);
	std::getline(ss, requested_method, ' ');
	std::getline(ss, requested_path, ' ');
	requested_path.erase(requested_path.begin());
	if (requested_path.empty()) requested_path = "index.html";
	std::getline(ss, requested_http_version, '\n');
	std::getline(ss, trash, ' ');
	std::getline(ss, requested_host, ' ');	
	return true;
}

std::string Http::build_answer(bool valid_request)
{
	std::string code = "400 Bad Request";
	std::string body;
	if (valid_request)
	{
		if(valid_path())
		{
			code = "200 OK";
			body = get_body();
		}
		else
		{
			code = "404 Page Not Found";
		}	
	}
	std::string message = (
		http_version + " " + code + "\n" +
		"Date: " + get_time() +"\n" +
		"Server: " + server + "\n" +
		"Location: " + host + "\n" +
		"Content-length: " + std::to_string(strlen(body.c_str())) + "\n" +
		"Connection: close\n" +
		"Content-type: text/html\n\n" +
		body
		);
	return message;
}

bool Http::valid_path()
{
	for (int i = 0; i < paths.size(); i++)
	{
		if (requested_path == paths[i])
			return true;
	}
	return false;
}

std::string Http::get_body()
{
	std::string line;
	std::string body;
	std::ifstream s(requested_path);
	if (s.is_open())
	{
		while (std::getline(s, line))
		{
			body += (line + "\n");
		}
		s.close();
	}
	return body;
}

void Http::print_parsed_message()
{
	std::cout << "Method: " << requested_method << std::endl;
	std::cout << "Path: " << requested_path << std::endl;
	std::cout << "Http-verison: " << requested_http_version << std::endl;
	std::cout << "Host: " << requested_host << std::endl;
}

//Ikke min kode. Ikke verdt å bruke tid på dette marerittet i C/C++
std::string Http::get_time()
{
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	std::ostringstream oss;
	oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
	auto str = oss.str();
	return str;
}
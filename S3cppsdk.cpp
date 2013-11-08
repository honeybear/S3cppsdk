// S3cppsdk.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <curl/curl.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	CURL *curl; 
	CURLcode res; 

	curl = curl_easy_init(); 
	if(curl) { 
		curl_easy_setopt(curl, CURLOPT_URL, "http://www.cnn.com/"); 
		res = curl_easy_perform(curl); 

		/* always cleanup */ 
		curl_easy_cleanup(curl); 
	} 
	while(1){}
	return 0;
}


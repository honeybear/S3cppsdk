// S3cppsdk.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string.h>
#include <curl/curl.h>
#include "tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

void SampleOfTinyxml2();
void SampleOfCurllib();
int SampleOfCurllibHttpGet();
int SampleOfCurllibHttpPost();

int _tmain(int argc, _TCHAR* argv[])
{
	//SampleOfCurllib();
	//SampleOfTinyxml2();
	//SampleOfCurllibHttpGet();
	SampleOfCurllibHttpPost();
	while(1){}
	return 0;
}

void SampleOfTinyxml2()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("test.xml");
	const char* content = doc.FirstChildElement("Hello")->GetText();
	cout<<content<<endl;
}

void SampleOfCurllib()
{
	CURL *curl; 
	CURLcode res; 

	curl = curl_easy_init(); 
	if(curl) { 
		curl_easy_setopt(curl, CURLOPT_URL, "http://www.cnn.com/"); 
		res = curl_easy_perform(curl); 

		// always cleanup  
		curl_easy_cleanup(curl); 
	} 
}

int SampleOfCurllibHttpGet()
{
	/* Exit status to return */
	int exitStatus = 0;
	/* Base URL for the service */
	const char* baseUrl = "http://www.ebi.ac.uk/Tools/dbfetch/dbfetch";
	// Parameters for call
	const char* db = "UNIPROT";
	const char* id = "ADH1A_HUMAN";
	const char* format = "fasta";
 
	/* Construct resource URL */
	int urlLen = strlen(baseUrl) + strlen(db) + strlen(id) + 4;
	if(strlen(format) > 0) 
	{
		urlLen += strlen(format);
	}
	char* url = (char*)malloc(sizeof(char) * (urlLen));
	if(url == NULL) 
	{
		printf("Error: unable to allocate memory for URL\n");
	}
	strcpy_s(url,urlLen,baseUrl);
	strncat_s(url, urlLen, "/", 1);
	strncat_s(url, urlLen, db, strlen(db));
	strncat_s(url, urlLen, "/", 1);
	strncat_s(url, urlLen, id, strlen(id));
	if(strlen(format) > 0) 
	{
		strncat_s(url, urlLen, "/", 1);
		strncat_s(url, urlLen, format, strlen(format));
	}
 
	/* Initialise libcurl */
	curl_global_init(CURL_GLOBAL_ALL);
	char* curlErrStr = (char*)malloc(CURL_ERROR_SIZE);

	/* Get a curl handle */
	CURL* curlHandle = curl_easy_init();

	if(curlHandle) 
	{
		curl_easy_setopt(curlHandle, CURLOPT_ERRORBUFFER, curlErrStr);
		/* Get resouce from URL and send to STDOUT */
		curl_easy_setopt(curlHandle, CURLOPT_URL, url);
		CURLcode curlErr = curl_easy_perform(curlHandle);
		if(curlErr) 
		{
			printf("%s\n", curl_easy_strerror(curlErr));
		}
		/* Clean-up libcurl */
		curl_global_cleanup();
	}
	else 
	{
		exitStatus = 1;
	}
	free(url);

	/* Return the exit status */
	return exitStatus;
}

int SampleOfCurllibHttpPost()
{
	/* Exit status to return */
	int exitStatus = 0;
	/* Endpoint for POST */
	const char* endpointUrl = "http://www.ebi.ac.uk/cgi-bin/dbfetch";
	// Parameters for call
	const char* db = "UNIPROT";
	const char* id = "WAP_MOUSE,WAP_RAT";
	const char* format = "fasta";
	const char* style = "raw";
	/* Construct resource POST data */
	int postDataLen = strlen(db) + strlen(id) + 26;

	if(strlen(format) > 0) 
	{
		postDataLen += strlen(format);
	}
	if(strlen(style) > 0) 
	{
		postDataLen += strlen(style);
	}
	
	char* postData = (char*)malloc(sizeof(char) * (postDataLen));
	
	if(postData == NULL) 
	{
		printf("Error: unable to allocate memory for POST data\n");
	}
	strcpy_s(postData, postDataLen, "db=");
	strncat_s(postData, postDataLen, db, strlen(db));
	strncat_s(postData, postDataLen, "&id=", 4);
	strncat_s(postData, postDataLen, id, strlen(id));
	if(strlen(format) > 0) 
	{
		strncat_s(postData, postDataLen, "&format=", 8);
		strncat_s(postData, postDataLen, format, strlen(format));
	}
	if(strlen(style) > 0) 
	{
		strncat_s(postData, postDataLen, "&style=", 8);
		strncat_s(postData, postDataLen, style, strlen(style));
	}
	/* printf("%s\n", postData); */
 
	/* Initialise libcurl */
	curl_global_init(CURL_GLOBAL_ALL);
	char* curlErrStr = (char*)malloc(CURL_ERROR_SIZE);
	/* Get a curl handle */
	CURL* curlHandle = curl_easy_init(); 
	if(curlHandle) 
	{
		curl_easy_setopt(curlHandle, CURLOPT_ERRORBUFFER, curlErrStr);
		/* Set the endpoint to send the POST to */
		curl_easy_setopt(curlHandle, CURLOPT_URL, endpointUrl);
		/* Specify the POST data */
		curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, postData);
		/* Execute the POST, response goes to STDOUT */
		CURLcode curlErr = curl_easy_perform(curlHandle);
		/* Report any errors */
		if(curlErr) 
		{
			printf("%s\n", curl_easy_strerror(curlErr));
		}
		/* Clean-up libcurl */
		curl_global_cleanup();
	}
	else 
	{
		exitStatus = 1;
	}
	free(postData);
	/* Return the exit status */
	return exitStatus;
}
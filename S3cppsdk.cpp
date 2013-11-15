// S3cppsdk.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string.h>
#include <curl/curl.h>
#include "tinyxml2/tinyxml2.h"
#include <time.h>
#include "HMAC_SHA1.h"
#include "base64.h"
#include <vector>

using namespace std;
using namespace tinyxml2;

void SampleOfTinyxml2();
void SampleOfCurllib();
int SampleOfCurllibHttpGet();
int SampleOfCurllibHttpPost();
void SampleOfS3Get();
char* getDateForHeader();
char* getAuthorizationForHeader(const char* AWSAccessKeyId, const char* AWSSecretKey,const char* date);
wstring UTF8ToUnicode( const string& str);
string UnicodeToUTF8( const wstring& str);
std::string ws2s(const std::wstring& ws);
std::wstring s2ws(const std::string& s);

int _tmain(int argc, _TCHAR* argv[])
{
	//SampleOfCurllib();
	//SampleOfTinyxml2();
	//SampleOfCurllibHttpGet();
	//SampleOfCurllibHttpPost();
	SampleOfS3Get();
	//cout<<getDateForHeader();
	//getAuthorizationForHeader("AKIAISZALBSYEIIWKXGQ","tIzCCFh1+WOnVA0/Jsn5KqTfuCAWyD1eyeOKStx0");
	//cout<<"finish"<<endl;
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
		curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com/"); 
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
		cout<<"Error: unable to allocate memory for URL"<<endl;
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
			cout<<curl_easy_strerror(curlErr)<<endl;
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
		cout<<"Error: unable to allocate memory for POST data"<<endl;
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
			cout<<curl_easy_strerror(curlErr)<<endl;
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

void SampleOfS3Get()
{
	vector<int> a;
	//Init curl 
	curl_global_init(CURL_GLOBAL_ALL);
	CURL* curlHandle = curl_easy_init();
	
	//Init var
	char* curlErrStr = (char*)malloc(CURL_ERROR_SIZE);
	curl_slist* httpHeaders = NULL; 
	const char* date = getDateForHeader();
	//cout<<date;
	httpHeaders = curl_slist_append(httpHeaders, "Host: s3.amazonaws.com");//Set Host
	httpHeaders = curl_slist_append(httpHeaders, date);//Set Date
	httpHeaders = curl_slist_append(httpHeaders, getAuthorizationForHeader("AKIAISZALBSYEIIWKXGQ","tIzCCFh1+WOnVA0/Jsn5KqTfuCAWyD1eyeOKStx0",date));//Set authorization

	//Execute
	if(curlHandle) 
	{
		curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, CURLOPT_STDERR);//Set verbose mode
		curl_easy_setopt(curlHandle, CURLOPT_FOLLOWLOCATION,1);//Set automaticallly redirection
		curl_easy_setopt(curlHandle, CURLOPT_MAXREDIRS,1);//Set max redirection times
		curl_easy_setopt(curlHandle, CURLOPT_ERRORBUFFER, curlErrStr);//Set error buffer
		curl_easy_setopt(curlHandle, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);//Set http version 1.1
		curl_easy_setopt(curlHandle, CURLOPT_HEADER, httpHeaders);//Set headers
		curl_easy_setopt(curlHandle, CURLOPT_URL, "http://s3.amazonaws.com/");//Set URL

		CURLcode curlErr = curl_easy_perform(curlHandle);//Perform

		if(curlErr) 
		{
			cout<<curl_easy_strerror(curlErr)<<endl;
		}

		//Output redirection url
		if(CURLE_OK == curlErr) 
        {
             char *url;
             curlErr = curl_easy_getinfo(curlHandle, CURLINFO_EFFECTIVE_URL, &url);

             if((CURLE_OK == curlErr) && url)
                 cout<<"CURLINFO_EFFECTIVE_URL: "<<url<<endl;
        }

		/* Clean-up libcurl */
		curl_global_cleanup();
	}
}

char* getDateForHeader()
{
	time_t lt;
	time(&lt);
	struct tm tmTmp = {0};
	gmtime_s(&tmTmp,&lt);
	char* buf = (char*)malloc(sizeof(char) * 37);
	strftime(buf,37,"Date: %a, %d %b  %Y %X GMT",&tmTmp);
	return buf;
}

char* getAuthorizationForHeader(const char* AWSAccessKeyId,const char* AWSSecretKey,const char* date)
{
	//Signature = Base64( HMAC-SHA1( YourSecretAccessKeyID, UTF-8-Encoding-Of( StringToSign ) ) );
	CHMAC_SHA1 hmac_sha1;
	char* stringToSign = (char*)malloc(sizeof(char) * 200);
	BYTE digest[20];

	strcpy_s(stringToSign,strlen(stringToSign),"GET\n");
	strncat(stringToSign,"\n",1);
	strncat(stringToSign,"\n",1);
	strncat(stringToSign,date,strlen(date));
	strncat(stringToSign,"\n",1);
	strncat(stringToSign,"/",1);

	string stringOfStringToSign(stringToSign);
	//cout<<"string "<<stringOfStringToSign<<endl;
	string utf8OfStringToSign(UnicodeToUTF8(s2ws(stringOfStringToSign)));//bug
	//cout<<"utf8 "<<utf8OfStringToSign<<endl;

	hmac_sha1.HMAC_SHA1((BYTE*)utf8OfStringToSign.c_str(),strlen(utf8OfStringToSign.c_str()),(BYTE*)AWSSecretKey,strlen(AWSSecretKey),digest);

	string signature(base64_encode((unsigned char*)digest,20));
	char* buf = (char*)malloc(sizeof(char) * 100);
	strcpy(buf,"Authorization: AWS ");
	strncat(buf,AWSAccessKeyId,strlen(AWSAccessKeyId));
	strncat(buf,":",1);
	strncat(buf,signature.c_str(),strlen(signature.c_str()));
	//cout<<buf<<endl;
	/*test for hmac_sha1 and base64_encode
	char *test = "456" ; 
	BYTE key[20];
	memset(key, 0x11, 20) ;
	hmac_sha1.HMAC_SHA1((BYTE*)test,strlen(test),key,sizeof(key),digest);
	for(int i=0;i<=19;i++){
		printf("%d:%x\t",i+1,digest[i]);
	}

	unsigned char test[3] = {'1','2','3'};
	cout<<base64_encode(test,3).c_str();
	*/
	return buf;
}

wstring UTF8ToUnicode( const string& str )
{
 int  len = 0;
 len = str.length();
 int  unicodeLen = ::MultiByteToWideChar( CP_UTF8,
            0,
            str.c_str(),
            -1,
            NULL,
            0 ); 
 wchar_t *  pUnicode; 
 pUnicode = new  wchar_t[unicodeLen+1]; 
 memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t)); 
 ::MultiByteToWideChar( CP_UTF8,
         0,
         str.c_str(),
         -1,
         (LPWSTR)pUnicode,
         unicodeLen ); 
 wstring  rt; 
 rt = ( wchar_t* )pUnicode;
 delete  pUnicode;
   
 return  rt; 
}

string UnicodeToUTF8( const wstring& str )
{
 char*     pElementText;
 int    iTextLen;
 // wide char to multi char
 iTextLen = WideCharToMultiByte( CP_UTF8,
         0,
         str.c_str(),
         -1,
         NULL,
         0,
         NULL,
         NULL );
 pElementText = new char[iTextLen + 1];
 memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
 ::WideCharToMultiByte( CP_UTF8,
         0,
         str.c_str(),
         -1,
         pElementText,
         iTextLen,
         NULL,
         NULL );
 string strText;
 strText = pElementText;
 delete[] pElementText;
 return strText;
}

std::string ws2s(const std::wstring& ws)
{
    std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";
    setlocale(LC_ALL, "chs");
    const wchar_t* _Source = ws.c_str();
    size_t _Dsize = 2 * ws.size() + 1;
    char *_Dest = new char[_Dsize];
    memset(_Dest,0,_Dsize);
    wcstombs(_Dest,_Source,_Dsize);
    std::string result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, curLocale.c_str());
    return result;
}

std::wstring s2ws(const std::string& s)
{
    setlocale(LC_ALL, "chs"); 
    const char* _Source = s.c_str();
    size_t _Dsize = s.size() + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest,_Source,_Dsize);
    std::wstring result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, "C");
    return result;
}
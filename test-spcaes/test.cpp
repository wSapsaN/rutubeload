#include <curl/curl.h>
#include <iostream>

using namespace std;

int main(void)
{
  CURL *curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, "http://10.10.10.2");
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 1500);

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    int status_code = 200;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);

    if(res != CURLE_OK)
    {     
      fprintf(stderr, "\n%s\n",
              curl_easy_strerror(res));
      
      // if (curl_easy_strerror(res))
    }

    cout << endl << status_code << endl;

  }

  curl_global_cleanup();

  return 0;
}
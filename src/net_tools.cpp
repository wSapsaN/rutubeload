#include "net_tools.hpp"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

std::string parser_m3u(std::string json)
{
  // search "m3u8"
  // return links to chunks

  bool flag = 0, link_flag = 0;
  std::string link;
  std::string tmp;
  for (size_t i = 0; i < json.size(); i++)
  {
    if (tmp == "\"m3u8")
    {
      if (flag) i+=4;

      if (json[i] == 'h' || link_flag)
      {
        link_flag = 1;
        if (json[i] == '"') break;
        link += json[i];
      }

      flag = 0;
    }

    if ((json[i] == '"' && json[i+1] == 'm' && json[i+2] == '3') || flag)
    {
      tmp += json[i];
      flag = 1;
    }
    
  }
  
  return link;
}

std::string requests(std::string url)
{
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 1500);

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    if(res != CURLE_OK)
    {     
      fprintf(stderr, "%s\n%s\n",
              curl_easy_strerror(res), url.c_str());
      exit(-1);
    }

  }

  curl_global_cleanup();

  return readBuffer;
  // std::cout << parser_m3u(readBuffer) << std::endl;
}
#include "net_tools.hpp"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

std::string parser_m3u(std::string json)
{
  // search "m3u8"
  // return links to chunks

  bool flag = 1, link_flag = 0;
  std::string link;
  std::string tmp;
  for (size_t i = 0; i < json.size(); i++)
  {

    if (json[i] == '"' && json[i+1] == 'm' && json[i+2] == '3')
    {
      if (flag)
      {
        for (size_t j = 0; j < 5; j++) {
          tmp+=json[i+j];
        }
      }
      
    }

    if (tmp == "\"m3u8")
    {
      std::cout << "Success playlist" << std::endl;
      flag = 0;
      
      int count = 8;
      while (1)
      {
        if (json[i+count] == '"') break;
        if (json[i+count] == '\\')
        {
          count += 6;
          link += "&";
        }
        
        link += json[i+count++];
      }
      
      return link;
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
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 5000);

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    if(res != CURLE_OK)
    {     
      fprintf(stderr, "\n%s\n%s\n",
              curl_easy_strerror(res), url.c_str());
      
      exit(-1);
    }

  }

  curl_global_cleanup();

  return readBuffer;
}

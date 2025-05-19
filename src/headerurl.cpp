#include "headerurl.hpp"

UrlsSP::UrlsSP(std::string url) {
  
  int count_slash = 0;
  for (size_t i = 0; i < url.size(); i++)
  {
    if (count_slash == 4 && url[i] != '/') id_video += url[i];
    if (url[i] == '/') count_slash++;
  }

  if (count_slash < 5) exit(-1);
}

void UrlsSP::stdout_id() { std::cout << id_video << std::endl; }

std::string UrlsSP::api_url() {
  id_video += tail;
  head += id_video;
  
  return head;
}

URL::URL(std::string url)
{
  bool flag = 0;
  std::string tmp = "";
  for (size_t i = 0; i < url.size(); i++)
  {
    if (url[i] == '#') {
      flag = 1;

      if (tmp != "") {
        urls.push_back(tmp);
        tmp = "";
      }
    }

    if (url[i] == '\n') {
      flag = 0;
      continue;
    }
    
    if (flag) continue;
    
    tmp += url[i];
  }
  
}

void URL::printer() {
  for (size_t i = 0; i < urls.size(); i++)
  {
    std::cout << "vector " << urls[i] << std::endl;
  }
}


int URL::count_charset(std::string line, char ch) {
  int counter = 0;
  for (size_t i = 0; i < line.size(); i++)
  {
    if (ch == line[i]) counter++;
  }
  
  return counter;
}


std::string URL::pop_afterCHarBYnum(char ch, unsigned int position, std::string line) {
  std::string tmp;
  unsigned    coincidence = 0;

  if (position > line.size()) std::cout << "Error [position > urls.size]\n";
  
  for (size_t i = 0; i < line.size(); i++)
  {
    if (line[i] == ch) coincidence++;
    if (coincidence < position) tmp += line[i];
  }
  
  return tmp;
}

std::vector<std::string> URL::total_linkTOchunk(std::string const baseLink) {
  std::vector<std::string> totaLink;
  std::string              tmp = "";

  for (size_t i = 0; i < urls.size(); i++)
  {
    tmp += baseLink;
    tmp += "/";
    tmp += urls[i];
  
    totaLink.push_back(tmp);
    tmp = "";
  }
  
  return totaLink;
}

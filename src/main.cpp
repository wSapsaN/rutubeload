#include <iostream>
#include <fstream>
#include <cstring>

#include "headerurl.hpp"
#include "net_tools.hpp"
#include "progress_bar.hpp"

bool check_link(std::string link)
{
  std::string equal = "https://rutube.ru/video/", tmp = "";

  if (link.size() < equal.size()) return 1;

  for (size_t i = 0; i < equal.size(); i++)
  {
    tmp += link[i];
    if (equal == tmp)
    {
      return 0;
    }
  }

  return 1;
}

void help()
{
  std::cout << "\n\t\tExample call: app <url> <filename>" << std::endl;
  std::cout << "\t\tЕсли наименование файла отсутствует то подставляется 'file.ts'" << std::endl;
  std::cout << std::endl;
}

std::string resolution(std::string res)
{
  // функция которая сортирует отдельно разрешение и ссылки по разным векторам
  // на разрешение, в которых уже по запросу отдаются чанки

  std::vector<std::string> quality;
  std::vector<std::string> link;

  unsigned j = 0, select;
  bool flagl = 0, flagr = 0;
  std::string tmp;
  for (size_t i = 0; i < res.size(); i++)
  {
    if (res[i] == 'h' || flagl)
    {
      flagl = 1;
      
      if (res[i] == '\n')
      {
        flagl = 0;
        link.push_back(tmp);
        tmp = "";
        continue;
      }

      tmp += res[i];
    }

    if ((res[i] == ',' && res[i+1] == 'R') || flagr)
    {
      flagr = 1;
      j = i+12;
    
      if (res[j] == '\n')
      {
        flagr = 0;
        quality.push_back(tmp);
        tmp = "";
        continue;
      }

      tmp += res[j];
      j++;
    }
  }
  
  std::cout << "Select line: " << std::endl; // выбираем одно из доступных качеств
  for (size_t i = 0; i < quality.size(); i++)
  {
    std::cout << "[" << i << "]" << " " << quality[i] << " " << link[i] << std::endl;
  }
  std::cout << std::endl;

  while (1)
  {
    std::cout << "Select resolution: ";
    std::cin >> select;

    if (select >= link.size())
    {
      std::cout << "\rThe selected resolution does not exist." << std::endl;
      std::cout << "Try again or exit via Ctrl+C." << std::endl;
      
      continue;
    }
    
    return link[select]; // возвращаем ссылку которая ведет на чанки
  }
}

void run(
  std::string link,
  std::string filename
)
{
  // ссылка на видео, в "поделиться" береться ссылка и отправляется программе
  // UrlsSP url("https://rutube.ru/video/a74cc290c346028ad2a3889b146814d1/?r=wd"); 
  UrlsSP url(link);
  
  std::string m3u = requests(url.api_url()); // здесь мы получаем список json
  std::string link_to = parser_m3u(m3u); // потом мы вытягиваем ссылку по ключу m3u8
  
  // в ссылке плейлиста другие ссылки, которые указывают на качество.
  // После выбора качества отдаються ссылки на чанки по запросу
  std::string res = requests(link_to); 
  std::string chunksLink = resolution(res); // разделяем ссылки и не нужные строки, в конце выбираем
  // качество и возвращаем одну ссылку.

  std::string chunks = requests(chunksLink); // здесь хранятся все чанки выбранного качества

  URL setupCHUNKlink(chunks); // сортируем не нужное

  int last_positionTrigger = setupCHUNKlink.count_charset(chunksLink, '/'); // считаем по слешу
  std::string result = setupCHUNKlink.pop_afterCHarBYnum('/', last_positionTrigger, chunksLink); // обрезаем не нужное

  std::vector<std::string> done_link = setupCHUNKlink.total_linkTOchunk(result);

  ProgressOptional poptional;

  int count_timeout = 0;
  int size_links = done_link.size();
  std::ofstream out(filename, std::ios::app);
  for (size_t i = 0; i < size_links; i++)
  {
    std::string data = requests(done_link[i]);
    
    if (out.is_open()) out << data;
    // std::cout << "Download " << i+1 << " of " << done_link.size() << std::endl;
    // progress(size_links, (i+1), poptional);
  }

  out.close();
  
  std::cout << "\nData saved to " << filename << std::endl;
}

int main(int argc, char* argv[])
{
  if (argc == 1 || std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")
  {
    help();
    exit(0);
  }

  if (argc > 3)
  {
    std::cout << "Утилита принемает только два параметра." << std::endl;
    help();
    exit(-1);
  }

  std::string link = argv[1];
  std::string filename = "file.ts";
  if (argv[2]) {
    filename = argv[2];
    filename += ".ts";
  }

  if (check_link(link)) {
    std::cout << "Wrong url - " << link << std::endl;
    exit(0);
  }

  run(link, filename);

  return 0;
}

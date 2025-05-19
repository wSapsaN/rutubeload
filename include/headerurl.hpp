#include <iostream>
#include "general_inc.hpp"

class UrlsSP {
  // Класс который работает с изначальной сылкой, её можно получить в "поделиться" 
private:
  std::string head = "https://rutube.ru/api/play/options/"; 
  std::string tail = "/?no_404=true";
  std::string id_video;

public:
  UrlsSP(std::string);

  std::string api_url();

  void stdout_id();

};

class URL {
  // Класс для работы с конечными ссылками.
  // Конструктор вытаскивает хвосты ссылок чанков, которые потом будут подставляться
  // в конец обрезанной по последнему слешу ссылки которую мы выбрали (когда выбирали качество)
private:
  URL(const URL&); // запрет конструктора копирования

  std::vector<std::string> urls; // здесь хранятся хвосты чанков

public:
  URL(std::string); // конструкотр принемает исключительно массив символов string чанков.
  int count_charset(std::string, char); // считает количество элементов в масстве.

  void printer(); // вывод вектора (костыль)

  std::string pop_afterCHarBYnum(char, unsigned int, std::string); // функция прекращает запись после
  // указаноого символа в его позиции и возвращает строку.
  // Это нужно чтобы убрать лишний в выборе качества и подставить вместо него хвост на чанк.

  std::vector<std::string> total_linkTOchunk(std::string const);

};
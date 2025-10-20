#include <progress_bar.hpp>

using namespace std;

unsigned int prosent(int const a, int const b) { return (b*100)/a; } // функция для вычесления процента

ProgressOptional::ProgressOptional()
{ add_point(); }

ProgressOptional::ProgressOptional(const std::string new_line)
{
  if (new_line.size() > 20)
  {
    std::cerr << "Limit exceeded: 20" << std::endl;
    exit(-1);
  }

  delete this->line;
  this->line = nullptr;

  line = new string;

  size_t i = 0;
  for (i; i < (new_line.size()+33); i++)
  {
    this->line += new_line[i];
  }
  this->line[i] = ' ';
  this->line->push_back('[');
  this->line->push_back('>');

  this->start_len = this->line->size();

  add_point();
}

ProgressOptional::~ProgressOptional()
{
  delete line;
  line = nullptr;
}

void ProgressOptional::add_point()
{
  string points = ""; // переменная в которой храним точки для конкатенации с переменной line

  size_t add_pointer = 0;
  for (add_pointer; add_pointer < this->num_point; add_pointer++)
  { points.push_back('.'); } // набиваем переменную символами
  points[add_pointer-1] = ']'; // завершаем.

  for (size_t i = 0; i < points.size(); i++)
  { this->line->push_back(points[i]); }
}

const int ProgressOptional::get_start_len()
{ return start_len; }

void progress(int const total_num_size, int const fin_size, ProgressOptional& optional)
{
  unsigned int a = prosent(total_num_size, fin_size);          // имзеряет процент пройденного от общего числа процесса
  unsigned int b = prosent((optional.num_point-1), optional.cprogress); // измеряет текующее положение в процентом соотношении
  
  // Если переменная а содержит больший процент чем b то заменяем, делаем шаг и выводим процесс.
  if (a > b)
  {
    const int start_len = optional.get_start_len();
    for (size_t i = 0; i < (a-b) && optional.cprogress < (optional.num_point-1); i++) // Заменяем символы с разницей между a и b
    {
      optional.line[0][optional.cprogress + start_len] = '=';
      optional.cprogress++;
      optional.line[0][optional.cprogress + start_len] = '>'; // направление процесса
    }
  }
  
  cout << *optional.line << " " << a << "%" << flush; // вывод
}


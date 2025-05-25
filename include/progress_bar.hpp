// #include <thread>
#include <general_inc.hpp>

// #define START_LINE  12  // индекс с которого пойдет замена точек
// #define NUM_POINTSE 32  // число точек
// #define NUM_SIZE    100 // Длина процесса // Должна определяться другим процессом а не дерктивой define

struct ProgressOptional
{
public:
  int cprogress = 0;

  ~ProgressOptional();

  ProgressOptional();
  ProgressOptional(const std::string);

  const int get_start_len();

private:
  std::string *line = new std::string("\rProgress: [>");
  unsigned int start_len = 12;
  unsigned int num_point = 32;

  ProgressOptional(const ProgressOptional &);

  void add_point();

  friend void progress(int const, int const, ProgressOptional&);
};

void progress(int const, int const, ProgressOptional&);
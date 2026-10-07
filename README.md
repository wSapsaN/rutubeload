# rutubeload

Этот код поможет вам скачать видео с rutube, запуск кода предполагает, что у вас ОС Linux.
Ему на вход первым параметром передается ссылка на видео, после чего он запускает свои внутренние механизмы по работе с этим видео.
Здесь все просто, берется плейлист, в котором хранятся чанки и уже тянутся чанки и записываются в .ts файл.

# Сборка

Перед тем как собирать приложение вам надо установить curl либу: libcurl4-openssl-dev

```bash
# создаем директорию в которой будет хранится сборка
mkdir build
cd build

cmake ../
make
```

Launch:
```bash
./rutubeload -h # you receive instruction
./rutubeload <LINK> # if file doesn't define, the application itself creates "file.ts"
./rutubeload <LINK> <FILENAME> # define filename without extension
```

Можно также добавить в переменную PATH путь до rutubeload или через сим линк закинуть его в тот же /usr/local/bin/.

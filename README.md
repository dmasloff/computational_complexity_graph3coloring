# computational_complexity_graph3coloring

Реализация алгоритма Юджена Лоулера для проверки графа на 3-раскрашиваемость за время
$\mathcal{O}((\sqrt[3]{3} + \varepsilon)^n)\sim\mathcal{O}(1.4422^n)$ для графа на $n$ вершинах.

TeX-файлы со статьей доступны в директории `/tex`, скомпилированный файл можно найти в корне - `article.pdf`, также статью можно найти в Overleaf по [ссылке](https://www.overleaf.com/read/sfxkrdzkzhnq#48e713).

### Тесты

В проекте реализованы тесты на основе фреймворка [GTest](https://github.com/google/googletest), которые можно запустить из
корня следующей последовательностью команд.

```shell
mkdir build
cd build
cmake ..
make test_graph
./bin/test_graph
```
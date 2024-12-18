# computational_complexity_graph3coloring

Реализация алгоритма Юджена Лоулера для проверки графа на 3-раскрашиваемость за время
$\mathcal{O}((\sqrt[3]{3} + \varepsilon)^n)\sim\mathcal{O}(1.4422^n)$ для графа на $n$ вершинах.

TeX-файлы со статьей доступны в директории `/tex`, скомпилированный файл можно найти в корне - `article.pdf`, также статью можно найти в Overleaf по [ссылке](https://www.overleaf.com/read/sfxkrdzkzhnq#48e713).

### Тесты

В проекте реализованы тесты на основе фреймворка [Google Test](https://github.com/google/googletest), которые можно запустить из
корня следующей последовательностью команд.

```shell
mkdir -p build
cmake -S . -B build
make -C build test_graph
./build/bin/test_graph
```

### Бенчмарк

Также в проекте есть бенчмарки, позволяющие оценить время работы алгоритма на графах из класса $G(n, p)$ - случайных графах в модели Эрдеша-Реньи. В тестах используется константа $p\in\{\frac{1}{4}, \frac{1}{2}, \frac{3}{4}\}$.
Для бенчмарков использован фреймворк
[Google Benchmark](https://github.com/google/benchmark), запуск из корня можно осуществить с помощью последовательности команд:

```shell
mkdir -p build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
make -C build profile_graph
./build/bin/profile_graph
```

Для информативности бенчмарков рекомендуется собирать их в Release версии, поэтому инструкция немного отличает от сборки тестов. Статистику, использованную для построения графиков следует искать в директории `/statistics`.

Чтобы запустить подсчёт среднего числа максимальных антиклик при разной плотности графа рекомендуется рассмотреть файл
`/benchmarks/anticlique_number_distribution.cpp`, там есть элементы, которые можно кастомизировать под свои нужды.
Запуск аналогично осуществляется последовательностью команд.

```shell
mkdir -p build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
make -C build run_anticlique_distribution
./build/bin/run_anticlique_distribution
```

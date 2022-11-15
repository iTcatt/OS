## Задание
Составить программу на языке Си, обрабатывающую данные в многопоточном режиме. При
обработки использовать стандартные средства создания потоков операционной системы
(Windows/Unix). Ограничение потоков должно быть задано ключом запуска вашей программы.

## Вариант 
Есть набор 128 битных чисел, записанных в шестнадцатеричном представлении,
хранящихся в файле. Необходимо посчитать их среднее арифметическое. Округлить
результат до целых. Количество чисел, обрабатывающихся в потоке, задавать ключом.

## Как использовать 
Ввод данных происходит через аргументы командной строки. На вход подается имя файла, количество потоков и количество чисел, которые обрабатывает поток.

Пример запуска: 
```c
./parent test.txt 4 2
```
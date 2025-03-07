Этот проект представляет собой библиотеку для работы с матрицами, написанную на языке программирования C. Он включает в себя набор функций для выполнения различных математических операций над матрицами, таких как создание, удаление, сложение, вычитание, умножение, транспонирование, вычисление определителя, обратной матрицы и других операций. Библиотека предназначена для использования в научных и инженерных расчетах, где требуется работа с матрицами. Вот подробное описание основных компонентов проекта:

### Файлы исходного кода:

- **my_matrix.h**: Заголовочный файл, содержащий объявления структур данных и функций, используемых в библиотеке. Определяет структуру `matrix_t` для представления матрицы и перечисление `result_code` для возврата кодов ошибок. Также включает прототипы функций для работы с матрицами.

- **my_create_matrix.c**: Реализует функцию для создания матрицы заданного размера. Выделяет память для матрицы и инициализирует ее нулями.

- **my_remove_matrix.c**: Освобождает память, выделенную под матрицу, и сбрасывает ее размеры до нуля.

- **my_help.c**: Содержит вспомогательные функции для проверки матриц на корректность (например, на наличие NULL, на размеры, на бесконечность и NaN значения, на нулевые строки или столбцы).

- **my_eq_matrix.c**: Содержит функцию для сравнения двух матриц на равенство с учетом заданной точности.

- **my_sum_matrix.c**: Реализует функцию сложения двух матриц.

- **my_sub_matrix.c**: Реализует функцию вычитания одной матрицы из другой.

- **my_mult_number.c**: Умножает матрицу на число.

- **my_mult_matrix.c**: Умножает две матрицы.

- **my_transpose.c**: Транспонирует матрицу (переставляет строки и столбцы местами).

- **my_inverse_matrix.c**: Вычисляет обратную матрицу к данной.

- **my_calc_complements.c**: Вычисляет матрицу алгебраических дополнений.

- **my_determinant.c**: Вычисляет определитель матрицы.

- **all_test_matrix.c**: Содержит тесты для функций библиотеки, использует фреймворк для тестирования.

### Основные функции:

- **Создание и удаление матриц**: Функции `my_create_matrix` и `my_remove_matrix` позволяют создавать и удалять матрицы соответственно. Создание матрицы включает выделение памяти для двумерного массива, а удаление - освобождение этой памяти.

- **Операции над матрицами**: Функции `my_sum_matrix`, `my_sub_matrix`, `my_mult_number`, `my_mult_matrix` и `my_transpose` выполняют базовые арифметические операции: сложение, вычитание, умножение на число и транспонирование.

- **Вычисление определителя и обратной матрицы**: `my_determinant` и `my_inverse_matrix` вычисляют определитель матрицы и ее обратную матрицу соответственно. Обратная матрица вычисляется через алгебраические дополнения и транспонирование.

- **Вспомогательные функции**: В `my_help.c` находятся функции для проверки матриц на корректность, такие как `my_size_error`, `my_null_matrix`, `my_chec_size`, `my_regional`, `my_null_line`, которые проверяют матрицы на соответствие условиям (размеры больше 0, не NULL, не содержат бесконечности или NaN, не содержат нулевых строк или столбцов).

- **Тестирование**: В `all_test_matrix.c` находятся тесты для проверки корректности работы функций библиотеки. Тесты проверяют различные сценарии использования функций, включая некорректные входные данные и граничные условия.

### Структура проекта:

Проект организован модульно, с каждой функцией в отдельном файле исходного кода и соответствующим заголовочным файле. Это облегчает поддержку и развитие кода, позволяя легко добавлять новые функции и модифицировать существующие без влияния на остальную часть проекта.

### Примеры использования:

Для создания матрицы размером 3x3 и заполнения ее значениями:
```c
matrix_t matrix;
my_create_matrix(3, 3, &matrix);
my_fill_matrix(&matrix, "1 2 3 4 5 6 7 8 9");
```

Для сложения двух матриц:
```c
matrix_t matrix1, matrix2, result;
my_create_matrix(3, 3, &matrix1);
my_create_matrix(3, 3, &matrix2);
my_fill_matrix(&matrix1, "1 2 3 4 5 6 7 8 9");
my_fill_matrix(&matrix2, "9 8 7 6 5 4 3 2 1");
my_sum_matrix(&matrix1, &matrix2, &result);
```

Для транспонирования матрицы:
```c
matrix_t matrix, result;
my_create_matrix(3, 3, &matrix);
my_fill_matrix(&matrix, "1 2 3 4 5 6 7 8 9");
my_transpose(&matrix, &result);
```

### Тестирование:

Тесты в `all_test_matrix.c` используют фреймворк для проверки корректности работы функций. Например, тест на создание матрицы проверяет, что матрица создается с правильными размерами и не содержит NULL. Тесты для операций, таких как сложение и вычитание, проверяют корректность результатов на различных входных данных, включая граничные условия.

### Сборка и тестирование:

Для сборки проекта используется Makefile, который компилирует исходные файлы в исполняемый файл или библиотеку. Для запуска тестов используется команда `make test`, которая компилирует тесты и запускает их.

### Применение:

Библиотека может быть использована в любых проектах, где требуется работа с матрицами, например, в научных расчетах, графике, физических моделях, где необходимы операции линейной алгебры.
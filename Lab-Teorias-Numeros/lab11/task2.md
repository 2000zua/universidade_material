Примеры чисел с разным числом итераций в методе Ферма

Минимальное число итераций

Числа, представимые как разность двух квадратов с x \approx \sqrt{n}, раскладываются быстро.

Пример: n = 15

x = ceil(sqrt(15)) = 4

y² = 4² - 15 = 1 \Rightarrow y = 1

Множители: (4 + 1) * (4 - 1) = 5 * 3

Разложение найдено за 1 итерацию.

Максимальное число итераций

Простые числа требуют полного перебора, так как x² - n никогда не будет полным квадратом.

Пример: n = 97 (простое число)

x = ceil(sqrt(97)) = 10

y² = 10² - 97 = 3, y² = 11² - 97 = 24, …

Метод продолжает увеличивать x, но не найдёт разложения.

Требуется много итераций без успеха.

Среднее число итераций

Составные числа с далеко расположенными множителями требуют больше итераций.

Пример: n = 899 (множители 29 и 31)

x = ceil(sqrt(899)) = 30

y² = 30² - 899 = 1, y = 1

Множители: (30 + 1) * (30 - 1) = 31 * 29

Разложение найдено за несколько итераций.


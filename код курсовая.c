#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>

int is_defined(double x) {
    if (x >= -1 && x < 1 && fabs(x - 1.0) < 1e-9)
        return 0;
    return 1;
}

double calculate_function(double x, int *ok) {
    *ok = 1;

    if (!is_defined(x)) {
        *ok = 0;
        return 0.0;
    }

    if (x < -1) {
        return sinh(x);
    } else if (x >= -1 && x < 1) {
        return (x * x * x - 1) / (x - 1);
    } else {
        double sum = 0.0;
        for (int n = 0; n <= 11; n++) {
            sum += pow(-1, n) * pow(x, n) / sqrt(n * n + 4);
        }
        return sum;
    }
}

void calculate_value() {
    double x;
    int ok;
    printf("Введите x: ");
    scanf("%lf", &x);

    double result = calculate_function(x, &ok);
    if (!ok) {
        printf("Ошибка! Функция не определена в этой точке.\n");
    } else {
        printf("f(%.5lf) = %.5lf\n", x, result);
    }
}

void build_table() {
    double start, step;
    int count;
    printf("Введите начало интервала: ");
    scanf("%lf", &start);
    printf("Введите шаг: ");
    scanf("%lf", &step);
    printf("Введите количество отсчетов: ");
    scanf("%d", &count);

    printf("|    x    |   f(x)   |\n");
    printf("|---------|----------|\n");

    for (int i = 0; i < count; i++) {
        double x = start + i * step;
        int ok;
        double fx = calculate_function(x, &ok);
        if (ok)
            printf("| %7.3lf | %8.3lf |\n", x, fx);
        else
            printf("| %7.3lf |   error |\n", x);
    }
}

void find_extremum() {
    double a, b, step;
    printf("Введите начало отрезка: ");
    scanf("%lf", &a);
    printf("Введите конец отрезка: ");
    scanf("%lf", &b);
    printf("Введите шаг: ");
    scanf("%lf", &step);

    double min = 0, max = 0;
    int first = 1;

    for (double x = a; x <= b; x += step) {
        int ok;
        double fx = calculate_function(x, &ok);
        if (!ok) continue;

        if (first) {
            min = max = fx;
            first = 0;
        } else {
            if (fx < min) min = fx;
            if (fx > max) max = fx;
        }
    }

    if (first) {
        printf("Нет допустимых значений на отрезке.\n");
    } else {
        printf("Минимум: %.5lf\n", min);
        printf("Максимум: %.5lf\n", max);
    }
}

void find_x_by_y() {
    double y, eps;
    printf("Введите Y: ");
    scanf("%lf", &y);
    printf("Введите точность: ");
    scanf("%lf", &eps);

    for (double x = -10; x <= 10; x += eps) {
        int ok;
        double fx = calculate_function(x, &ok);
        if (ok && fabs(fx - y) < eps) {
            printf("Найдено x ≈ %.5lf\n", x);
            return;
        }
    }
    printf("Значение не найдено.\n");
}

void derivative_at_point() {
    double x, h;
    printf("Введите x: ");
    scanf("%lf", &x);
    printf("Введите h: ");
    scanf("%lf", &h);

    int ok1, ok2;
    double f1 = calculate_function(x, &ok1);
    double f2 = calculate_function(x + h, &ok2);

    if (!ok1 || !ok2) {
        printf("Ошибка! Производная не может быть вычислена.\n");
    } else {
        printf("f'(x) ≈ %.5lf\n", (f2 - f1) / h);
    }
}

void menu() {
    printf("\nГлавное меню:\n");
    printf("1. Значение функции в точке\n");
    printf("2. Таблица значений\n");
    printf("3. Поиск минимума/максимума\n");
    printf("4. Поиск X по Y\n");
    printf("5. Производная в точке\n");
    printf("0. Выход\n");
    printf("Выбор: ");
}

int main() {
    setlocale(LC_CTYPE, "RUS");
    int choice;
    do {
        menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: calculate_value(); break;
            case 2: build_table(); break;
            case 3: find_extremum(); break;
            case 4: find_x_by_y(); break;
            case 5: derivative_at_point(); break;
            case 0: printf("Выход из программы.\n"); break;
            default: printf("Неверный пункт меню.\n");
        }
    } while (choice != 0);

    return 0;
}

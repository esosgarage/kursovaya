/*
* Главный модуль: обеспечивает цикл работы программы
* и выбор операций через меню
*/

#include <stdio.h>
#include <locale.h>
#include "ui_handlers.h"

int main() {
	int choice;

	setlocale(LC_CTYPE, "RUS");

	do {
		printf("\nАвтор КП: Дементьева Анна\n");
printf("\n--- МЕНЮ ---\n");
		printf("1. Значение\n2. Таблица\n3. Экстремумы\n");
		printf("4. Поиск X по Y\n5. Производная\n0. Выход\n");
		printf("Выбор: ");

		if (scanf("%d", &choice) != 1) break;

		switch (choice) {
		case 1: ui_calc_value(); break;
		case 2: ui_build_table(); break;
		case 3: ui_find_extrema(); break;
		case 4: ui_find_x_by_y(); break;
		case 5: ui_derivative(); break;
		case 0: printf("Завершение...\n"); break;
		default: printf("Ошибка ввода.\n"); break;
		}
	} while (choice != 0);

	return 0;
}

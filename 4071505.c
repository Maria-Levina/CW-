#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <string.h>
#define size 5
#define string 50

int read_file(char filename[], char names[size][string], float scores[size][size]);/*чтение из файла*/
float resultsf(float scores[size][size], int str);/*подсчет результатов*/
int bubbleSort(float sfp[], int id[], int n);/*сортировка пузырьком*/
void print_table_1(char names[size][string], float scores[size][size], int id[size]);/*печать исходной таблицы*/
void print_table_2(char names[size][string], float scores[size][size], float results[size], int id[size]);/*печать результирующей таблицы*/
int ShellSort(float res[size], int id[size], int n);

int main()
{
	system("chcp 1251");
	system("cls");
	char file_name[string];/*название файла*/
	float scores[size][size];/*массив с результатами*/
	char names[size][string];/*массив с именами участников*/
	int id[size];/*массив идентификаторов игроков*/
	float results[size];/*массив для сумм очков участников*/
	printf("Введите название файла и его формат:");
	scanf("%s", &file_name);
	read_file(file_name, names, scores);
	printf("*******Приветствуем!********");
	int action1 = 0;
	while (action1 != 5)
	{

		for (int i = 0; i < size; i++)
		{
			results[i] = resultsf(scores, i);
			id[i] = i;
		}
		int action2 = 0;
		printf("\n*****Турнир по шахматам*****\n\n");
		printf("Меню:\n1. Распечатать исходную таблицу турнира;\n2. Вывести результирующую таблицу турнира;\n3. Поиск участника по заданному критерию;\n4. Изменить исходные данные;\n5. Выход.\n\n");
		printf("Ответ:");
		scanf_s("%d", &action1);
		printf("\n");
		switch (action1)
		{
		case 1: /*вывод исходной таблицы*/
		{
			print_table_1(names, scores, id);
			break;
		}
		case 2: /*вывод результирующей таблицы*/
		{
			ShellSort(results, id, size);
			print_table_2(names, scores, results, id);
			break;
		}
		case 3: /*поиск участника по критериям*/
		{
			int answer = 0, n;
			ShellSort(results, id, size);
			printf("Выберите критерий:\n1. Лучший игрок.\n2. Худший игрок.\n3. Игроки, набравшие более n баллов.\n4. Игроки, набравшие менее n баллов.\n5. Выход в меню.");
			printf("\nОтвет:");
			scanf_s("%d", &answer);
			switch (answer)
			{
			case 1:
			{
				printf("\nЛучший игрок - %s (%.1f очков)\n", names[id[0]], results[0]);
				break;
			}
			case 2:
			{
				printf("\nХудший игрок - %s (%.1f очков)\n", names[id[size - 1]], results[size - 1]);
				break;
			}
			case 3:
			{
				printf("\nВведите число n:");
				scanf_s("%d", &n);
				for (int i = 0; i < size; i++)
				{
					if (results[i] >= n) printf("%d. %s - %.1f\n", id[i]+1, names[id[i]], results[i]);
				}
				break;
			}
			case 4:
			{
				printf("\nВведите число n:");
				scanf_s("%d", &n);
				for (int i = 0; i < size; i++)
				{
					if (results[i] <= n) printf("%d. %s - %.1f\n", id[i] + 1, names[id[i]], results[i]);
				}
				break;
			}
			case 5: break;
			default:
			{
				printf("Неизвестная команда\n");
				break;
			}
			}
			break;
		}
		case 4:/*изменение данных*/
		{
			int id1, id2, act;
			printf("Что бы Вы хотели поменять?\n");
			printf("1. Имя участника;\n2. Результат.\nОтвет:");
			scanf_s("%d", &act);
			switch (act)
			{
			case 1:
			{
				printf("\nВведите номер участника:");
				scanf_s("%d", &id1);
				char new_name[50];
				printf("\nВведите новое имя участника: ");
				scanf("%s", &names[id1-1]);
				printf("\nНовое имя участника - %s", names[id1 - 1]);
				break;
			}
			case 2:
			{
				printf("\nВведите через пробел строку и столбец результата: ");
				scanf_s("%d %d", &id1, &id2);
				printf("\nВведите новый результат: ");
				scanf_s("%f", &scores[id1-1][id2-1]);
				printf("\nУстановлен результат - %.1f", scores[id1-1][id2-1]);
				break;
			}
			}
			break;
		}
		case 5:break;/*выход из программы*/
		default:
		{
			printf("Неизвестная программа\n");
			break;
		}
		}
		if (action1 != 5)
		{
			printf("\nПродолжить? Да - 1, нет - любой другой символ\nОтвет:");
			scanf("%d", &action2);
			getchar();
			if (action2 != 1) break;
			printf("\n");
		}
		else break;
		
	}
	
}

int read_file(char filename[], char names[size][string], float scores[size][size])
{
	FILE* in;
	in = fopen(filename, "r");
	int n = 0;
	printf("Открытие файла:");
	if (in == NULL) /*проверка открытия файла*/
	{
		perror("не удалось открыть файл.\nОшибка");
		exit(0);
	}
	else printf("выполнено.\n\n");
	fseek(in, 0, SEEK_SET);
	for (int i = 0; i < size; i++)/*чтение данных*/
	{
		fscanf(in, "%s ", &names[i]);
		fscanf(in, " %5f ", &scores[i][0]);
		fscanf(in, " %5f ", &scores[i][1]);
		fscanf(in, " %5f ", &scores[i][2]);
		fscanf(in, " %5f ", &scores[i][3]);
		fscanf(in, " %5f ", &scores[i][4]);
		fscanf(in, " %5f\n", &scores[i][5]);
	}
	fclose(in);
	return 1;
}

void print_table_1(char names[size][string], float scores[size][size], int id[size])
{
	printf("Участ-ки\\Встречи |");
	for (int i = 0; i < size; i++)/*печать номеров встреч*/
	{
		printf("%5d|", i + 1);
	}
	printf("\n");
	for (int i = 0; i < size; i++)/*печать имен участников и их результатов*/
	{
		printf("%d. %13s |", i + 1, names[i]);
		for (int j = 0; j < size; j++)
		{
			if (j == id[i]) printf("  -  |");
			else printf("%4.1f |", scores[i][j]);
		}
		printf("\n");
	}
}

float resultsf(float scores[size][size], int str)
{
	float res = 0;
	for (int j = 0; j < size; j++)/*подсчет сумм очков для одного игрока*/
	{
		res += scores[str][j];
	}
	return res;
}

int ShellSort(float res[size], int id[size], int n)
{
	int i, j, step, temp_id;
	float temp;
	if (res != NULL)/*если массив не пуст*/
	{
		for (step = n / 2; step > 0; step /= 2) /*выбор шага*/
		{
			for (i = step; i < n; i++)/*проход по массиву с шагом step, начиная с половины массива*/
			{
				temp = res[i];
				temp_id = id[i];
				for (j = i; j >= step; j -= step)/*сортировка, если текущий элемент больше элемента, находящегося на step единиц сзади*/
				{
					if (temp > res[j - step])
					{
						res[j] = res[j - step];
						id[j] = id[j - step];
					}
					else
						break;
				}
				res[j] = temp;
				id[j] = temp_id;
			}
		}
		return 1;
	}
	else
	{
		perror("Сортировка не прошла. Ошибка:");
		return 0;
	}
}

void print_table_2(char names[size][string], float scores[size][size], float results[size], int id[size])
{
	printf("Участ-ки\\Встречи |");
	for (int i = 0; i < size; i++)/*печать номеров встреч*/
	{
		printf("%5d|", i + 1);
	}
	printf("Сумма | Место |\n");
	for (int i = 0; i < size; i++)/*печать имен участников и их результатов*/
	{
		printf("%d. %13s |",i+1, names[id[i]]);
		for (int j = 0; j < size; j++)
		{
			if (j == id[i]) printf("  -  |");
			else printf("%4.1f |", scores[id[i]][j]);
		}
		printf(" %4.1f | %5d |", results[i], i+1);/*вывод суммы очков и ранжирование участника*/
		printf("\n");
	}
}
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <string.h>
#define size 5
#define string 50

int read_file(char filename[], char names[size][string], float scores[size][size]);/*������ �� �����*/
float resultsf(float scores[size][size], int str);/*������� �����������*/
int bubbleSort(float sfp[], int id[], int n);/*���������� ���������*/
void print_table_1(char names[size][string], float scores[size][size], int id[size]);/*������ �������� �������*/
void print_table_2(char names[size][string], float scores[size][size], float results[size], int id[size]);/*������ �������������� �������*/
int ShellSort(float res[size], int id[size], int n);

int main()
{
	system("chcp 1251");
	system("cls");
	char file_name[string];/*�������� �����*/
	float scores[size][size];/*������ � ������������*/
	char names[size][string];/*������ � ������� ����������*/
	int id[size];/*������ ��������������� �������*/
	float results[size];/*������ ��� ���� ����� ����������*/
	printf("������� �������� ����� � ��� ������:");
	scanf("%s", &file_name);
	read_file(file_name, names, scores);
	printf("*******������������!********");
	int action1 = 0;
	while (action1 != 5)
	{

		for (int i = 0; i < size; i++)
		{
			results[i] = resultsf(scores, i);
			id[i] = i;
		}
		int action2 = 0;
		printf("\n*****������ �� ��������*****\n\n");
		printf("����:\n1. ����������� �������� ������� �������;\n2. ������� �������������� ������� �������;\n3. ����� ��������� �� ��������� ��������;\n4. �������� �������� ������;\n5. �����.\n\n");
		printf("�����:");
		scanf_s("%d", &action1);
		printf("\n");
		switch (action1)
		{
		case 1: /*����� �������� �������*/
		{
			print_table_1(names, scores, id);
			break;
		}
		case 2: /*����� �������������� �������*/
		{
			ShellSort(results, id, size);
			print_table_2(names, scores, results, id);
			break;
		}
		case 3: /*����� ��������� �� ���������*/
		{
			int answer = 0, n;
			ShellSort(results, id, size);
			printf("�������� ��������:\n1. ������ �����.\n2. ������ �����.\n3. ������, ��������� ����� n ������.\n4. ������, ��������� ����� n ������.\n5. ����� � ����.");
			printf("\n�����:");
			scanf_s("%d", &answer);
			switch (answer)
			{
			case 1:
			{
				printf("\n������ ����� - %s (%.1f �����)\n", names[id[0]], results[0]);
				break;
			}
			case 2:
			{
				printf("\n������ ����� - %s (%.1f �����)\n", names[id[size - 1]], results[size - 1]);
				break;
			}
			case 3:
			{
				printf("\n������� ����� n:");
				scanf_s("%d", &n);
				for (int i = 0; i < size; i++)
				{
					if (results[i] >= n) printf("%d. %s - %.1f\n", id[i]+1, names[id[i]], results[i]);
				}
				break;
			}
			case 4:
			{
				printf("\n������� ����� n:");
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
				printf("����������� �������\n");
				break;
			}
			}
			break;
		}
		case 4:/*��������� ������*/
		{
			int id1, id2, act;
			printf("��� �� �� ������ ��������?\n");
			printf("1. ��� ���������;\n2. ���������.\n�����:");
			scanf_s("%d", &act);
			switch (act)
			{
			case 1:
			{
				printf("\n������� ����� ���������:");
				scanf_s("%d", &id1);
				char new_name[50];
				printf("\n������� ����� ��� ���������: ");
				scanf("%s", &names[id1-1]);
				printf("\n����� ��� ��������� - %s", names[id1 - 1]);
				break;
			}
			case 2:
			{
				printf("\n������� ����� ������ ������ � ������� ����������: ");
				scanf_s("%d %d", &id1, &id2);
				printf("\n������� ����� ���������: ");
				scanf_s("%f", &scores[id1-1][id2-1]);
				printf("\n���������� ��������� - %.1f", scores[id1-1][id2-1]);
				break;
			}
			}
			break;
		}
		case 5:break;/*����� �� ���������*/
		default:
		{
			printf("����������� ���������\n");
			break;
		}
		}
		if (action1 != 5)
		{
			printf("\n����������? �� - 1, ��� - ����� ������ ������\n�����:");
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
	printf("�������� �����:");
	if (in == NULL) /*�������� �������� �����*/
	{
		perror("�� ������� ������� ����.\n������");
		exit(0);
	}
	else printf("���������.\n\n");
	fseek(in, 0, SEEK_SET);
	for (int i = 0; i < size; i++)/*������ ������*/
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
	printf("�����-��\\������� |");
	for (int i = 0; i < size; i++)/*������ ������� ������*/
	{
		printf("%5d|", i + 1);
	}
	printf("\n");
	for (int i = 0; i < size; i++)/*������ ���� ���������� � �� �����������*/
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
	for (int j = 0; j < size; j++)/*������� ���� ����� ��� ������ ������*/
	{
		res += scores[str][j];
	}
	return res;
}

int ShellSort(float res[size], int id[size], int n)
{
	int i, j, step, temp_id;
	float temp;
	if (res != NULL)/*���� ������ �� ����*/
	{
		for (step = n / 2; step > 0; step /= 2) /*����� ����*/
		{
			for (i = step; i < n; i++)/*������ �� ������� � ����� step, ������� � �������� �������*/
			{
				temp = res[i];
				temp_id = id[i];
				for (j = i; j >= step; j -= step)/*����������, ���� ������� ������� ������ ��������, ������������ �� step ������ �����*/
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
		perror("���������� �� ������. ������:");
		return 0;
	}
}

void print_table_2(char names[size][string], float scores[size][size], float results[size], int id[size])
{
	printf("�����-��\\������� |");
	for (int i = 0; i < size; i++)/*������ ������� ������*/
	{
		printf("%5d|", i + 1);
	}
	printf("����� | ����� |\n");
	for (int i = 0; i < size; i++)/*������ ���� ���������� � �� �����������*/
	{
		printf("%d. %13s |",i+1, names[id[i]]);
		for (int j = 0; j < size; j++)
		{
			if (j == id[i]) printf("  -  |");
			else printf("%4.1f |", scores[id[i]][j]);
		}
		printf(" %4.1f | %5d |", results[i], i+1);/*����� ����� ����� � ������������ ���������*/
		printf("\n");
	}
}
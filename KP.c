#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
#include <stddef.h>
#include <stdlib.h>
#define LEN 100

struct Denrozhd
{
	char name[20];
	char surname[20];
	char cathegory[20];
	int day;
	int month;
	int year;

};

typedef struct Denrozhd DR;

void input(DR* dr, int i);
void write(DR* dr, int i);
int read(DR* dr);
void output(DR dr);
int* search_name(DR* dr, int max, char* name_cathegory, int month_poisk, int* index);
int* search_data(DR* dr, int max, int day, int month, int* index);
DR* sort(DR* dr, DR* dr2, int data_file, int year);
int compare_year(const void* av, const void* bv);

void main()
{
	setlocale(LC_ALL, "RUS");
	system("chcp 1251");

	int z, data_file;
	DR* dr = NULL;

	do
	{
		puts("Ввод данных - 1");
		puts("Вывод данных - 2");
		puts("Поиск по категории - 3");
		puts("Сортировка - 4");
		puts("Выход - 5");
		scanf("%d", &z);

		switch (z)
		{
		case 1:
		{
			int k, str=0;
			printf("Введите количество записей\n");
			scanf("%d", &k);

			FILE* ptr_file = fopen("kp.txt", "r");
			while (!feof(ptr_file))
				if (fgetc(ptr_file) == '\n') str++;
			str = str / 6;
			dr = (DR*)malloc((str + 1+k) * sizeof(DR));

			data_file = read(dr);

			for (int i = data_file; i < data_file + k; i++)
			{
				input(dr, i);
				write(dr, i);
			}
			break;
		}
		case 2:
		{
			int str = 0;
			FILE* ptr_file = fopen("kp.txt", "r");
			while (!feof(ptr_file))
				if (fgetc(ptr_file) == '\n') str++;
					str = str / 6;
			dr = (DR*)malloc((str + 1) * sizeof(DR));
			data_file = read(dr);
			for (int i = 0; i < data_file; i++)
			{
				output(dr[i]);
				printf("\n");
			}
		break; 
		}
			case 3:
			{
				data_file = read(dr);
				int z2, *index=malloc(data_file*sizeof(int));

				printf("Выберите критерий поиска\n");
				printf("По категории и месяцу - 1\n");
				printf("По месяцу и дню рождения - 2\n");
				scanf("%d", &z2);

				if (z2 == 1)
				{
					char cathegory_poisk[LEN];
					int month_poisk;

					printf("Введите категорию:\n");
					scanf("%s", cathegory_poisk);

					printf("Введите месяц\n");
					scanf("%d", &month_poisk);

					index = search_name(dr, data_file, cathegory_poisk, month_poisk, index);
					
					for (int i = 0; i < data_file; i++)
						if (index[i] == 1) { 
							output(dr[i]); 
							printf("\n");
						}
				}
				if (z2 == 2)
				{
					int day_f, month_f;
					printf("Введите день, месяц\n");
					scanf("%d %d" , &day_f, &month_f);

					index = search_data(dr, data_file, day_f, month_f, index);

					for (int i = 0; i < data_file; i++)
						if (index[i] == 1) {
							output(dr[i]);
							printf("\n");
						}
				}
				break; 
			}
			case 4:
			{
				DR* dr2;
				int year;
				printf("Введите текущий год\n");
				scanf("%d", &year);

				data_file = read(dr);

				dr2 = (DR*)malloc(sizeof(DR));
				dr2=sort(dr, dr2, data_file, year);

				for (int i = 0; i < data_file; i++)
				{
					output(dr2[i]);
					printf("Возраст на %d год:   %d\n", year, year - dr2[i].year);
					printf("\n");
				}
			break; 
			}
		}
	} while (z!=5);
}


void input(DR* dr, int i)
{
	printf("Введите имя:");
	scanf("%s", dr[i].name);

	printf("Введите фамилию:");
	scanf("%s", dr[i].surname);

	printf("Введите Категорию:");
	scanf("%s", dr[i].cathegory);

	printf("Введите день, месяц, год:");
	scanf("%d", &dr[i].day);
		if (dr[i].day < 0 || dr[i].day>31) 
			printf("Недопустимое значение (максимальное кол-во дней в месяце - 31)\n");

	scanf("%d", &dr[i].month);
		if (dr[i].day < 0 || dr[i].day>12) 
			printf("Недопустимое значение ( кол-во месяцев в году - 12)\n");

	scanf("%d", &dr[i].year);
}

void write(DR* dr, int i)
{
	FILE* ptr_file;

	if (i == 0) { 
		ptr_file = fopen("kp.txt", "w+");
		/*fprintf(ptr_file, "---------------------------------------------------------------------\n");
		fprintf(ptr_file, "|| Номер || Имя || Фамилия || Категория || Дата ||\n");
		fprintf(ptr_file, "---------------------------------------------------------------------\n");*/
	} else  ptr_file = fopen("kp.txt", "a");

	fprintf(ptr_file, "\n%s\n", dr[i].name);
	fprintf(ptr_file, "%s\n", dr[i].surname);
	fprintf(ptr_file, "%s\n", dr[i].cathegory);
	fprintf(ptr_file, "%d\n", dr[i].day);
	fprintf(ptr_file, "%d\n", dr[i].month);
	fprintf(ptr_file, "%d", dr[i].year);
	
	fclose(ptr_file);
}

int read(DR* dr)
{
	FILE* ptr_file=fopen("kp.txt", "rt");
	int i = 0;

	while (!feof(ptr_file))
	{
		fscanf(ptr_file, "\n%s\n", dr[i].name);
		fscanf(ptr_file, "%s\n", dr[i].surname);
		fscanf(ptr_file, "%s\n", dr[i].cathegory);
		fscanf(ptr_file, "%d\n", &dr[i].day);
		fscanf(ptr_file, "%d\n", &dr[i].month);
		fscanf(ptr_file, "%d", &dr[i].year);
		i++;
	}
	if (dr[i].name == NULL) return 0;
	return i;
}

void output(DR dr)
{
	printf("Имя:           %s\n", dr.name);
	printf("Фамилия        %s\n", dr.surname);
	printf("Категория:     %s\n", dr.cathegory);
	printf("Дата:          %d/%d/%d\n", dr.day, dr.month, dr.year);
}

int* search_name(DR* dr, int max, char* cathegory_poisk, int month, int* index)
{
	for (int i = 0; i < max; i++)
		if (strcmp(dr[i].cathegory, cathegory_poisk) == 0 && dr[i].month==month) index[i] = 1;
			else index[i] = 0;

	return index;
}

int* search_data(DR* dr, int max, int day, int month_poisk, int* index)
{
	for (int i = 0; i < max; i++)
		if (dr[i].day == day && dr[i].month == month_poisk) index[i] = 1;
			else index[i] = 0;
	
	return index;
}

//DR* sort(DR* dr2, DR* dr, int data_file)      На вский случай оставил тут
//{
//	for (int i = 0; i < data_file; i++)
//		dr[i] = dr[i];
//
//	DR sort;
//	printf("Введите текущий год\n");
//	int nowyear;
//	scanf("%d", &nowyear);
//	int left = 0, right = data_file - 1; // левая и правая границы сортируемой области массива
//	int flag = 1; // флаг наличия перемещений
//	while ((left < right) && flag > 0)
//	{
//		flag = 0;
//		for (int i = left; i < right; i++) //двигаемся слева направо
//		{
//			if (nowyear - dr[i].year < nowyear - dr[i + 1].year) // если следующий элемент меньше текущего,
//			{ // меняем их местами
//				double t = dr[i].year;
//				dr[i].year = dr[i + 1].year;
//				dr[i + 1].year = t;
//				flag = 1; // перемещения в этом цикле были
//			}
//		}
//		right--; // сдвигаем правую границу на предыдущий элемент
//		for (int i = right; i > left; i--) //двигаемся справа налево
//		{
//			if (nowyear - dr[i - 1].year < nowyear - dr[i].year) // если предыдущий элемент больше текущего,
//			{ // меняем их местами
//				double t = dr[i].year;
//				dr[i].year = dr[i - 1].year;
//				dr[i - 1].year = t;
//				flag = 1; // перемещения в этом цикле были
//			}
//		}
//		left++; // сдвигаем левую границу на следующий элемент
//	}
//	printf("\nСортировка завершена\n");
//	return dr;
//}   

DR* sort(DR* dr, DR* dr2, int data_file, int year)
{
	for (int i = 0; i < data_file; i++)
		dr2[i] = dr[i];

	qsort(dr2, data_file, sizeof(DR), compare_year);
	return dr2;
}

int compare_year(const void* av, const void* bv)
{
	const DR* a = av, * b = bv;
	if (a->year > b->year)return 1;
	if (a->year < b->year)return -1;
	if (a->month > b->month)return 1;
	if (a->month < b->month)return -1;
	if (a->day > b->day)return 1;
	if (a->day < b->day)return -1;
	return 0;
}

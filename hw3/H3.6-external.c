#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

const size_t str_size = 10002;

int cmp(const void* a, const void* b)
{
	return strcmp((char*)a, (char*)b);
}

size_t sort_chunks(size_t chunk_size)
{
	FILE* fin = fopen("input.txt", "r");
	FILE* fout = fopen("output.txt", "w");
	size_t file_size = 0;
	char str[str_size];
	char chunk[chunk_size][str_size];
	bool eof = false;
	while (true)
	{
		size_t size = 0;
		for (size_t i = 0; i < chunk_size; i++)
		{
			if (fgets(str, str_size, fin) != NULL)
			{
				strcpy(chunk[i], str);
				size++;
			}
			else
			{
				eof = true;
				break;
			}
		}
		qsort(chunk, size, str_size, cmp);
		for (size_t i = 0; i < size; i++)
		{
			fputs(chunk[i], fout);
		}
		file_size += size;
		if (eof) break;
	}
	fclose(fin);
	fclose(fout);
	return file_size;
}

void partition(size_t series_size)
{
	FILE* tape[2];
	tape[0] = fopen("tape0.txt", "w");
    tape[1] = fopen("tape1.txt", "w");
	FILE* fout = fopen("output.txt", "r");
	char str[str_size];
	for (size_t i = 0; fgets(str, str_size, fout) != NULL; i++)
	{
		fputs(str, tape[i % (series_size << 1) >= series_size]);
	}
	fclose(tape[0]);
	fclose(tape[1]);
	fclose(fout);
}

void merge(size_t series_size, size_t file_size)
{
	FILE* tape[2];
	tape[0] = fopen("tape0.txt", "r");
    tape[1] = fopen("tape1.txt", "r");
	FILE* fout = fopen("output.txt", "w");
	size_t done = 0;
	char str0[str_size], str1[str_size];
	char* p0 = fgets(str0, str_size, tape[0]);
	char* p1 = fgets(str1, str_size, tape[1]);
	while (true)
	{
		if (p0 == NULL && p1 == NULL) break;
		while (done + (series_size << 1) < file_size)
		{
			size_t i = 0, j = 0;
			while (i < series_size && j < series_size)
			{
				if (strcmp(str0, str1) < 0)
				{
					fputs(str0, fout);
					p0 = fgets(str0, str_size, tape[0]);
					i++;
				}
				else
				{
					fputs(str1, fout);
					p1 = fgets(str1, str_size, tape[1]);
					j++;
				}
				done++;
			}
			while (i < series_size)
			{
				fputs(str0, fout);
				p0 = fgets(str0, str_size, tape[0]);
				i++;
				done++;
			}
			while (j < series_size)
			{
				fputs(str1, fout);
				p1 = fgets(str1, str_size, tape[1]);
				j++;
				done++;
			}
		}
		if (p1 == NULL || (p0 != NULL && strcmp(str0, str1) < 0))
		{
			fputs(str0, fout);
			p0 = fgets(str0, str_size, tape[0]);
		}
		else
		{
			fputs(str1, fout);
			p1 = fgets(str1, str_size, tape[1]);
		}
	}
	fclose(tape[0]);
    fclose(tape[1]);
	fclose(fout);
}

int main()
{
	const size_t chunk_size = 16;
	size_t series_size = chunk_size;
	size_t file_size = sort_chunks(chunk_size);
	while (series_size < file_size)
	{
		partition(series_size);
		merge(series_size, file_size);
		series_size <<= 1;
	}
    return 0;
}
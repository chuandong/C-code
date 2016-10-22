#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>

#define NUM_MAX	1000
#define ARRY_NAME "number"

#define FILE_NAME ARRY_NAME
#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

int lower2upper(char *str);
int create_code(int maxnum);
int create_header(int maxnum);

int main(int argc, const char **argv)
{
	int maxnum;

	if (argc != 2) {
		fprintf(stderr, "invalid argument ! give a number !\n");
		return -1;
	}

	maxnum = atoi(argv[1]);
	create_code(maxnum);
	create_header(maxnum);

	return 0;
}

int lower2upper(char *str)
{
	while (*str != '\0') {
		if (*str >= 'a' && *str <= 'z')
			*str -= 32;
		str++;
	}

	return 0;
}

int create_header(int maxnum)
{
	FILE *fp = NULL;
	char h_name[128];
	char h_sign[128];
	char buff[128];
	char *p;

	strcpy(h_name, FILE_NAME);
	strcat(h_name, ".h");
	
	strcpy(buff, FILE_NAME);
	lower2upper(buff);
	strcpy(h_sign, "__");
	strcat(h_sign, buff);
	strcat(h_sign, "_H__");

	if (NULL == (fp = fopen(h_name, "w+")))
		error_exit("fopen");
	
	fprintf(fp, "#ifndef %s\n", h_sign);
	fprintf(fp, "#define %s\n", h_sign);
	fprintf(fp, "\n");
	fprintf(fp, "#define MAXNUM %d\n", maxnum);
	fprintf(fp, "extern int %s[];\n", ARRY_NAME);
	fprintf(fp, "\n");
	fprintf(fp, "#endif /* %s */\n", h_sign);

	fclose(fp);

	return 0;
}

int create_code(int maxnum)
{
	int i;
	FILE *fp = NULL;
	char name[128] = FILE_NAME;
	char align[64];
	int n;

	n = maxnum;
	while (n /= 10)
		i++;
	sprintf(align, "%%%dd", i);
	strcat(align, ", ");

	strcat(name, ".c");
	if (NULL == (fp = fopen(name, "w+")))
		error_exit("fopen");

	fprintf(fp, "int %s[%d] = {", ARRY_NAME, maxnum);
	for (i = 0; i < maxnum; i++) {
		if (!(i % 10))
			fputs("\n\t", fp);
		fprintf(fp, align, rand() % maxnum);
	}
	fprintf(fp, "\n};\n");

	fclose(fp);

	return 0;
}

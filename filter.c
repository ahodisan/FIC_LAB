#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
	FILE *f;
	char line[256];
	char line2[256];
	char func_name[256];
	int arith=0, mov=0, jump=0, other=0;
	if(argc != 3)
	{
		printf("Usage: %s file function_name\n", argv[0]);
		exit(1);
	}
	strcpy(func_name, argv[2]);
	strcat(func_name, ":");
	
	f=fopen(argv[1], "rt");
	if(f == NULL)
	{
		printf("Error at opening the file\n");
		exit(2);
	}
	
	/*
	while(fgets(line, sizeof(line), f))
	{
		printf("%s", line);
	}
	*/
	while(fgets(line, sizeof(line), f))
	{
		if(strstr(line, func_name) != 0)
		{
			while(fgets(line2, sizeof(line2), f))
			{
				if(strstr(line2, ".cfi") == 0 && strstr(line2, ".LFB0:") == 0)
				{
					if(strstr(line2, ".LFE0:") != 0)
						break;
					
					if(strstr(line2, "addl") != 0 || strstr(line2, "imull") != 0 || strstr(line2, "subl") != 0)
						arith++;
					else if(strstr(line2, "movq") != 0 || strstr(line2, "movl") != 0)
						mov++;
					else if(strstr(line2, "jmp") != 0)
						jump++;
					else 
						other++;
				}
			}
			break;
		}	
	}
	printf("Arith: %d\nMov: %d\nJump: %d\nOther: %d\n", arith, mov, jump, other);
	
	fclose(f);
	
	return 0;
}


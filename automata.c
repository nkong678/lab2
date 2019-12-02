#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void cellTable(const char *num,const char *filename)
{
	int generations;
	generations = atoi(num);

	int array [5][5];
	FILE *fptr;
	FILE *fptr1;
	//create output file name
	char *output;
	int len = 0;
	//get the length of the filename for malloc
	for (int i = 0; filename[i] != '\0'; i++)
		len++;
	//allocate space based on initial file name
	output = (char *) malloc(len + 4);
	for (int i = 0; i < len; i++)
	{
		output[i] = filename[i];
	}
	output[len] = '.';
	output[len + 1] = 'o';
	output[len + 2] = 'u';
	output[len + 3] = 't';
	//read in initial table values to array
	fptr = fopen (filename, "r");
	if (fptr == NULL)
	{
		printf("%s%s%s\n","File ", filename," did not open" );
	}
	else
	{
		while (!feof(fptr))
		{
			for (int a = 0; a < 5; a++)
			{
				for (int b = 0; b < 5; b++)
				{
					fscanf(fptr,"%d",&array[a][b]);
				}
			}
		}
	}
	fclose(fptr);
	int newgen [5][5] = {0};
	for (int i = 0;i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			newgen[i][j] = array[i][j];
	}
	//counter for adjacent live cells
	int counter;
	//for each generation
	for (int i = 0; i < generations; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				counter = 0;
				//decide whether or not to update cell status
				//top row
				if (j == 0)
				{
					//topleft corner
					if (k == 0)
					{
						if (array[j+1][k] == 1)
							counter++;
						if (array[j][k+1] == 1)
							counter++;
						if (array[j+1][k+1] == 1)
							counter++;
					}
					// topright corner
					else if (k == 4)
					{
						if (array[j+1][k] == 1)
							counter++;
						if (array[j][k-1] == 1)
							counter++;
						if (array[j+1][k-1] == 1)
							counter++;

					}
					//top middle
					else
					{
						if (array[j+1][k] == 1)
							counter++;
						if (array[j][k-1] == 1)
							counter++;
						if (array[j+1][k-1] == 1)
							counter++;
						if (array[j][k+1] == 1)
							counter++;
						if (array[j+1][k+1] == 1)
							counter++;
					}
				}
				//same but bottom
				else if (j == 4)
				{
					if (k == 0)
					{
						if (array[j-1][k] == 1)
							counter++;
						if (array[j][k+1] == 1)
							counter++;
						if (array[j-1][k+1] == 1)
							counter++;
					}
					else if (k == 4)
					{
						if (array[j-1][k] == 1)
							counter++;
						if (array[j][k-1] == 1)
							counter++;
						if (array[j-1][k-1] == 1)
							counter++;
					}
					else
					{
						if (array[j-1][k] == 1)
							counter++;
						if (array[j][k-1] == 1)
							counter++;
						if (array[j-1][k-1] == 1)
							counter++;	
						if (array[j][k+1] == 1)
							counter++;
						if (array[j-1][k+1] == 1)
							counter++;					
					}
				}
				//left side (corners already checked)
				else if (k == 0)
				{
					if (array[j-1][k] == 1)
						counter++;
					if (array[j+1][k] == 1)
						counter++;
					if (array[j][k+1] == 1)
						counter++;
					if (array[j+1][k+1] == 1)
						counter++;
					if (array[j-1][k+1] == 1)
						counter++;
				}
				// right side (corners already checked)
				else if (k == 4)
				{
					if (array[j-1][k] == 1)
						counter++;
					if (array[j+1][k] == 1)
						counter++;
					if (array[j][k-1] == 1)
						counter++;
					if (array[j+1][k-1] == 1)
						counter++;
					if (array[j-1][k-1] == 1)
						counter++;		
				}
				//middle
				else
				{
					if (array[j-1][k] == 1)
						counter++;
					if (array[j+1][k] == 1)
						counter++;
					if (array[j][k-1] == 1)
						counter++;
					if (array[j+1][k-1] == 1)
						counter++;
					if (array[j-1][k-1] == 1)
						counter++;	
					if (array[j][k+1] == 1)
						counter++;
					if (array[j+1][k+1] == 1)
						counter++;
					if (array[j-1][k+1] == 1)
						counter++;						
				}
				if (array[j][k] == 0)
				{
					if (counter == 3)
						newgen[j][k] = 1;
				}
				else if (array[j][k] == 1)
				{
					if (counter != 2 && counter != 3)
						newgen[j][k] = 0;
				}
			}
		}
		//update the array to the next generation
		for (int i = 0;i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
				array[i][j] = newgen[i][j];
		}
	}
	fptr1 = fopen(output, "w");
	for (int i = 0; i < 5; i ++)
	{
		for (int j = 0; j < 5; j++)
		{
			fprintf(fptr1, "%d%s", newgen[i][j], " ");
		}
		fprintf(fptr1, "%s\n", "");
	}
	fclose(fptr1);
	free(output);
}
int main(int argc, char const *argv[])
{
cellTable(argv[1], argv[2]);
return 0;
}
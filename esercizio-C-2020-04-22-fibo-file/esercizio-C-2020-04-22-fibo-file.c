#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>

unsigned long fibonacci(unsigned int n){

	unsigned long fn =0;
	unsigned long fn_1 = 1;
	unsigned long fn_2 = 0;

	for(int i=0; i<n; i++){

		if(i==0)
			fn = 0;
		if(i==1)
			fn=1;
		else{

		fn = (fn_1 + fn_2);

		fn_2 = fn_1;
		fn_1 = fn;
		}
	}

	return fn;

}

unsigned long * fibonacci_array(unsigned int n){

	unsigned long * array;

	array = calloc(n+1, sizeof(unsigned long));

	for(int i=0; i<=n; i++){

		array[i] = fibonacci(i);

	}

	return array;

}


void swap_int(unsigned long *x, unsigned long *y) {
	int t = *x;
	*x = *y;
	*y = t;
}
unsigned long * reverse_int(unsigned long * array, unsigned int i, unsigned int j)
{
	while (i < j)
		swap_int(&array[i++], &array[--j]);

	return array;
}

unsigned long * complete_reverse_int(unsigned long * array, unsigned int array_len) {
	return reverse_int(array, 0, array_len);
}

void bubble_sort(unsigned long * array, unsigned int caselle_array) {

	int count = 0;

	for(int i=1; i<caselle_array; i++){
	if(array[i-1]>array[i]){
			swap_int(&array[i-1], &array[i]);
			count++;
	}
	if(i == caselle_array-1 && count>0){
		count =0;
		i=0;
	}

}
}
#define num 40

int main(int argc, char *argv[]){

	//unsigned int num = 40;

	unsigned long * fibonacci_result = fibonacci_array(num-1);	// fibonacci(39) = 63245986

	char * file_name;

	file_name = "fibonacci.txt";
	printf("scrivo nel file %s\n", file_name);

	int fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);

	if (fd == -1) { // errore!

		perror("open()");
		exit(EXIT_FAILURE);
	}

	for(int i=0; i<num; i++){

		char * result;

		result = calloc(10, sizeof(char));

		unsigned long number = fibonacci_result[i];

		snprintf(result,10,"%lu",number);

		int res = write(fd, result, strlen(result)+1);
		// write restituisce il numero di bytes che ha scritto
		// in caso di errore, restuisce -1

		if (res == -1) {
					perror("write()");
					exit(EXIT_FAILURE);
				}

		res = write(fd, "\n", strlen("\n"));

		if (res == -1) {
			perror("write()");
			exit(EXIT_FAILURE);
		}
	}

	// close file

	if (close(fd) == -1) {
		perror("close");
		exit(EXIT_FAILURE);
	}

	printf("bye!\n");

	return 0;

}

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main() {
	FILE *f = fopen("flag.enc", "rb");
	
	if (f == NULL) {
		printf("Error while opening the flag file .. \n");
		return 1;
	}

	fseek(f, 0, 2);
	int offset = ftell(f) - 4, seed;
	fseek(f, 0, 0);
	void *buffer = malloc(offset);	
	// Get seed value
	if (fread(&seed, sizeof(int), 1, f) == 0) {
		printf("Error reading seed .. \n");
		return 1;
	}
	
	// Get encrypted flag
	if (fread(buffer, offset, 1, f) == 0) {
		printf("Error reading buffer .. \n");
		return 1;
	}
	
	fclose(f);
	printf("seed = %d\n", seed);

	// Get flag
	srand(seed);
	int i, rnd_1, rnd_2;
	
	for(i=0; i<offset; i++) {
		rnd_1 = rand(); 
		rnd_2 = rand(); 
		rnd_2 = rnd_2 & 7;
		*(unsigned char *)((long)buffer + i) = *(unsigned char *)((long)buffer + i) >> rnd_2 | *(unsigned char *)((long)buffer + i) << 8 - rnd_2;
		*(unsigned char *)((long)buffer + i) = *(unsigned char *)((long)buffer + i) ^ rnd_1;
	}

	printf("Flag: %s\nLength: %d\n", ((unsigned char*)buffer), offset);
	free(buffer);
	return 0;
}


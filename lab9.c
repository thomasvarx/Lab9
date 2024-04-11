#include <stdio.h>
#include <stdlib.h> 
// RecordType
struct RecordType
{
	int	id;
	char name;
	int	order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType data;
	struct  HashType *next;
	 
};

// Compute the hash function
int hash(int x)
{
	return x % 10;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		struct HashType* curr = &pHashArray[i];
		printf("Index %d -> ", i);
		while (curr != NULL)
		{
			printf("%d %c %d -> ", curr->data.id, curr->data.name, curr->data.order);
			curr = curr->next;
		}
		printf("\n");
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);

	struct HashType hashTable[10]; // Assuming the hash table size is fixed to 10
	// Initialize hash table
	for (int i = 0; i < 10; ++i) {
		hashTable[i].next = NULL;
	}
    // Insert records into hash table
    for (int i = 0; i < recordSz; i++)
    {
        int index = hash(pRecords[i].id);
        struct HashType *newNode = (struct HashType *)malloc(sizeof(struct HashType));
        newNode->data = pRecords[i];
        newNode->next = hashTable[index].next;
        hashTable[index].next = newNode;
    }

    // Display records in hash table
    displayRecordsInHash(hashTable, 10); // Assuming the hash table size is fixed to 10

    // Free dynamically allocated memory for records
    free(pRecords);
	return 0;
}
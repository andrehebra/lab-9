#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType data;
	struct HashType* next;
};

// Compute the hash function
int hash(struct HashType** head, struct HashType* value)
{
	struct HashType* temp = *head;
	struct HashType* temp2 = *head;

	if (*head == NULL) {
		*head = value;
		return 0;
	}

	while (temp2 != NULL) {
		temp = temp2;
		temp2 = temp2->next;
		
	}

	temp->next = value;
	return 0;
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
void displayRecordsInHash(struct HashType *pHashArray[], int hashSz)
{
	int i;

	
	for (i=0;i<hashSz;++i)
	{

		if (pHashArray[i] == NULL) {

		} else {
			printf("index %2d", i);

			while (pHashArray[i] != NULL) {
				printf(" -> %5d, %c, %2d", pHashArray[i]->data.id, pHashArray[i]->data.name, pHashArray[i]->data.order);
				pHashArray[i] = pHashArray[i]->next;
			}

			printf("\n");
		}

		while (pHashArray[i] != NULL) {

		}

		
		
		
	}
	
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;
	
	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

	

	int tableSz = 15;
	int currentIndex;

	struct HashType* hashtable[15];

	struct HashType* temp = malloc(sizeof(struct HashType));
	temp = NULL;

	for (int i = 0; i < tableSz; i++) {
		hashtable[i] = temp;
		//hashtable[i] = NULL;
	}

	for (int i = 0; i < recordSz; i++) {

		currentIndex = pRecords[i].id % tableSz;
		
		struct HashType *record = malloc(sizeof(struct HashType));

		record->data.id = pRecords[i].id;
		record->data.name = pRecords[i].name;
		record->data.order = pRecords[i].order;
		record->next = NULL;

		hash(&hashtable[currentIndex], record);

	}
	

	displayRecordsInHash(hashtable, tableSz);

	return 0;
}
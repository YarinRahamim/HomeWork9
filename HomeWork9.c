#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* verylong;

//Exercise 1
int isIncluded(char *S1, char *S2);
//Exercise 2
int isPermutation(char *S1, char *S2);
//Exercise 3
void removeDups(char *S);
//Exercise 4
void minimizeString(char *S);
//Exercise 5
int isPolidromPermutation(char *S);
//Exercise 6
char *charsToRemoveForPolidromPermutation(char *S, int *sizePtr);
//Exercise 7
int myStrcmpi(char *S1, char *S2);
//Exercise 8
char *subString(char *S, int length, int index);
//Exercise 9
verylong add_verylong(verylong v1, verylong v2);
//Exercise 10
void removeChar(char *S, char *toRemove, int n);


void main() { }

//Exercise 1
int isIncluded(char *S1, char *S2)
{
	char count[26] = { 0 };
	int i;
	for (i = 0; S2[i]; i++)
		count[S2[i] - 'a']++;
	for (i = 0; S1[i]; i++) {
		count[S1[i] - 'a']--;
		if (count[S1[i] - 'a'] < 0)
			return 0;
	}
	return 1;
}
//Exercise 2
int isPermutation(char *S1, char *S2)
{
	char count[26] = { 0 };
	int i;
	if (strlen(S1) != strlen(S2))
		return 0;
	for (i = 0; S2[i]; i++) {
		count[S1[i] - 'a']--;
		count[S2[i] - 'a']++;
	}
	for (i = 0; i < 26; i++)
		if (count[i] != 0)
			return 0;
	return 1;
}
//Exercise 3
void removeDups(char *S)
{
	int i, j;
	for (i = 1, j = 1; S[i]; i++)
		if (S[i] != S[j - 1])
			S[j++] = S[i];
	S[j] = '\0';
}
//Exercise 4
void minimizeString(char *S)
{
	int i, j, count = 1;
	for (i = 0, j = 0; S[i]; i++) {
		if (S[i] != S[i + 1]) {
			S[j++] = S[i];
			if (count > 1) {
				S[j++] = count + '0';
			}
			count = 1;
		}
		else
			count++;
	}
	S[j] = '\0';
}
//Exercise 5
int isPolidromPermutation(char *S)
{
	int count[26] = { 0 };
	int i, numOfOdds = 0;
	for (i = 0; S[i]; i++)
		count[S[i] - 'a']++;
	for (i = 0; i < 26; i++) {
		if (count[i] % 2) {
			numOfOdds++;
			if (numOfOdds > 1)
				return 0;
		}
	}
	return 1;
}
//Exercise 6
char *charsToRemoveForPolidromPermutation(char *S, int *sizePtr)
{
	char *arr = (char*)malloc(strlen(S));
	int count[26] = { 0 };
	int i, flag = 0;
	for (i = 0; S[i]; i++)
		count[S[i] - 'a']++;
	*sizePtr = 0;
	for (i = 0; i < 26; i++) {
		if (count[i] % 2) {
			if (flag != 1)
				flag = 1;
			else
				arr[(*sizePtr)++] = i + 'a';
		}
	}
	return arr;
}
//Exercise 7
int myStrcmpi(char *S1, char *S2)
{
	int i, d1, d2;
	for (i = 0; S1[i] && S2[i]; i++) {
		if (S1[i] >= 'A' && S1[i] <= 'Z') d1 = S1[i] - 'A';
		else	d1 = S1[i] - 'a';
		if (S2[i] >= 'A' && S2[i] <= 'Z') d2 = S2[i] - 'A';
		else	d2 = S2[i] - 'a';
		if (d1 != d2)
			return 0;
	}
	if (S1[i] != S2[i])
		return 0;
	return 1;
}
//Exercise 8
char *subString(char *S, int length, int index)
{
	char *newS;
	int len = strlen(S), i;
	if (index >= len || length > len || index + length > len)
		return NULL;
	newS = (char*)malloc(length + 1);
	for (i = 0; i < length; index++, i++)
		newS[i] = S[index];
	newS[i] = '\0';
	return newS;
}
//Exercise 9

int getDigit(verylong number, int idx)
{
	if (idx >= 0)
		return number[idx] - '0';
	return 0;
}

verylong shiftNumber(verylong number)
{
	int i = 1;
	while (number[i] != '\0')
		number[i - 1] = number[i++];
	number[i - 1] = '\0';
	number = realloc(number, i * sizeof(char));
	assert(number);
	return number;
}

verylong add_verylong(verylong vl1, verylong vl2)
{
	int i = 0, sum = 0;
	int len1 = strlen(vl1);
	int len2 = strlen(vl2);
	int size = ((len1 > len2) ? len1 : len2) + 1;					//max length of the result (without '\0')
	verylong result = (verylong)calloc(size + 1, sizeof(char));		//using calloc intiallize the array with value '\0' 
	assert(result);
	result[size] = '\0';

	for (i = size - 1; i > 0; i--)
	{
		sum += getDigit(vl1, --len1) + getDigit(vl2, --len2);
		result[i] = sum % 10 + '0';
		sum /= 10;
	}

	if (sum > 0)
		result[0] = sum + '0';
	else
		result = shiftNumber(result);

	return result;
}
//Exercise 10
void removeChar(char *S, char *toRemove, int n)
{
	int count[52] = { 0 };
	int i, j;

	for (i = 0; i < n; i++) {
		if (toRemove[i] >= 'A' && toRemove[i] <= 'Z')
			count[2 * (toRemove[i] - 'A')] = 1;
		else
			count[2 * (toRemove[i] - 'a') + 1] = 1;
	}

	for (i = 0, j = 0; S[i]; i++) {
		if (S[i] >= 'A' && S[i] <= 'Z' && count[2 * (S[i] - 'A')] == 0 ||
			S[i] >= 'a' && S[i] <= 'z' && count[2 * (S[i] - 'a') + 1] == 0)
			S[j++] = S[i];
	}
	S[j] = '\0';
}
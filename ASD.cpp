// main idea of program: E = A ⋃ B ⋃ C ⋂ D

#include <iostream>

using namespace std;

struct Set {
	char element;
	Set* next;

	Set(char e, Set* n = nullptr) : element(e), next(n) { }
	~Set() { delete next; }
};

/*----------------------------------------------------------
					   ARRAY FUNCTIONS
 --------------------------------------------------------*/

bool IsInArray(char* set, char element) {
	for (int i = 0; set[i]; ++i)
		if (element == set[i])
			return true;
	return false;
}

void getSet(char* set, char setName) {			// НЕОБХОДИМО
	cout << "Enter set " << setName << " : ";	// ОБЯЗАТЕЛЬНО
	cin >> set;									// ЗАМЕНИТЬ
}

void makeArraySet(char* A, char* B, char* C, char* D) {

	const int NumOfDigits = 10;
	char E[NumOfDigits + 1] = {};
	int size = 0;

	for (int i = 0; A[i]; ++i)
		if (!(IsInArray(E, A[i])))
			E[size++] = A[i];

	for (int i = 0; B[i]; ++i)
		if (!(IsInArray(E, B[i])))
			E[size++] = B[i];

	for (int i = 0; C[i]; ++i)
		if (IsInArray(D, C[i]))
			if (!(IsInArray(E, C[i])))
				E[size++] = C[i];

	cout << "The set E was made like array: " << E << endl;
}

/*----------------------------------------------------------
						LIST FUNCTIONS
 --------------------------------------------------------*/

Set* ConversionToList(char* S) {
	Set* LS = nullptr;
	Set* node = nullptr;
	for (int i = 0; S[i] != '\0'; ++i) {
		if (!LS) {
			node = new Set(S[i]);
			LS = node;
		}
		else {
			node->next = new Set(S[i]);
			node = node->next;
		}
	}
	return LS;
}

bool IsInList(Set* LS, char& element) {
	for (Set* p = LS; p; p = p->next)
		if (element == p->element)
			return true;
	return false;
}

void PrintList(Set* LS) {
	cout << "The set E was made like list: ";
	for (Set* p = LS; p; p = p->next) {
		cout << p->element;
	}
	cout << endl;
}

void makeListSet(char* A, char* B, char* C, char* D) {

	Set* LA = ConversionToList(A),
		* LB = ConversionToList(B),
		* LC = ConversionToList(C),
		* LD = ConversionToList(D),
		* LE = nullptr,
		* node = nullptr;

	for (Set* p = LA; p; p = p->next)
		if (!(IsInList(LE, p->element))) {
			if (!LE) {
				node = new Set(p->element);
				LE = node;
			}
			else {
				node->next = new Set(p->element);
				node = node->next;
			}
		}

	for (Set* p = LB; p; p = p->next)
		if (!(IsInList(LE, p->element))) {
			if (!LE) {
				node = new Set(p->element);
				LE = node;
			}
			else {
				node->next = new Set(p->element);
				node = node->next;
			}
		}

	for (Set* p = LC; p; p = p->next)
		if (IsInList(LD, p->element))
			if (!(IsInList(LE, p->element))) {
				if (!LE) {
					node = new Set(p->element);
					LE = node;
				}
				else {
					node->next = new Set(p->element);
					node = node->next;
				}
			}

	PrintList(LE);
	delete LA;
	delete LB;
	delete LC;
	delete LD;
	delete LE;
}

/*----------------------------------------------------------
					 BITS VECTOR FUNCTIONS
 --------------------------------------------------------*/

void ConversionToBitsVector(char* S, char* bS) {
	for (int i = 0; S[i]; ++i)
		bS[S[i] - '0'] = 1;
}

void ReverseFromBitsVector(char* bS) {
	const int NumOfDigits = 10;
	char S[NumOfDigits + 1] = {};
	for (int i = 0, k = 0; i < NumOfDigits; ++i)
		if (bS[i])
			S[k++] = i + '0';
	cout << S << endl;
}

void makeBitsVectorSet(char* A, char* B, char* C, char* D) {

	const int NumOfDigits = 10;

	char bA[NumOfDigits + 1] = {},
		bB[NumOfDigits + 1] = {},
		bC[NumOfDigits + 1] = {},
		bD[NumOfDigits + 1] = {},
		bE[NumOfDigits + 1] = {};

	ConversionToBitsVector(A, bA);
	ConversionToBitsVector(B, bB);
	ConversionToBitsVector(C, bC);
	ConversionToBitsVector(D, bD);

	for (int i = 0; i < NumOfDigits; ++i)
		bE[i] = bA[i] || bB[i] || (bD[i] && bC[i]);

	cout << "The set E was made like bits vector: ";
	ReverseFromBitsVector(bE);
}

/*----------------------------------------------------------
				   MACHINE WORD FUNCTIONS
----------------------------------------------------------*/

short ConversionToMachineWord(char* S) {
	short wS = 0;
	for (int i = 0; S[i]; ++i)
		wS |= (1 << (S[i] - '0'));
	return wS;
}

void ReverseFromMachineWord(short wS) {
	const int NumOfDigits = 10;
	char S[NumOfDigits + 1] = {};
	for (int i = 0, k = 0; i < NumOfDigits; ++i)
		if ((wS >> i) & 1)
			S[k++] = i + '0';
	cout << S << endl;
}

void makeMachineWordSet(char* A, char* B, char* C, char* D) {

	short wA = ConversionToMachineWord(A),
		wB = ConversionToMachineWord(B),
		wC = ConversionToMachineWord(C),
		wD = ConversionToMachineWord(D),
		wE = 0;

	wE = wA | wB | (wC & wD);

	cout << "The set E was made like machine word: ";
	ReverseFromMachineWord(wE);
}

/*----------------------------------------------------------
						  MAIN
 --------------------------------------------------------*/

int main() {

	const int NumOfDigits = 10;

	char A[NumOfDigits + 1] = {},
		B[NumOfDigits + 1] = {},
		C[NumOfDigits + 1] = {},
		D[NumOfDigits + 1] = {};

	getSet(A, 'A');
	getSet(B, 'B');
	getSet(C, 'C');
	getSet(D, 'D');

	makeArraySet(A, B, C, D);
	makeListSet(A, B, C, D);
	makeBitsVectorSet(A, B, C, D);
	makeMachineWordSet(A, B, C, D);

	return 0;
}

// Ответы на вопросы 1.1.2.:
// 		1) 11 байт - 10 байт для цифр, 1 байт для нуль терминатора
// 		2) Нет ?
// 		3) O((nA+nB+nC*nD)*nE)
// 		4) O((nA+nB+nC*nD)*nE). Алгоритм нельзя считать оптимальным
// 		
// Ответы на вопросы 1.2.2.:
// 		1) O(nA+nB+nC+nD+nE) ?
// 		2) O(nA+nB+nC+nD) ?
// 		3) Нет. Результат от этого не изменится
// 		4) Если мощность множества слишком велика (возможно бесконена),
// 		   то данный способ не применим

// main idea of program: E = A ⋃ B ⋃ C ⋂ D

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

const int repeats = 1000000;		// кол-во повторений
const int number_of_digits = 10;	// мощность универсума

// односвязный список
struct List {
	char element;
	List* next;

	List(char e, List* n = nullptr) : element(e), next(n) { }
	~List() { delete next; }
};

// функция обмена значений
inline void Swap(char& x, char& y) {
	char tmp = x;
	x = y;
	y = tmp;
}

/*----------------------------------------------------------
					   ARRAY FUNCTIONS
  ----------------------------------------------------------*/

  // проверка наличия элемента в множестве
bool IsInArray(char S[], char element) {
	for (int i = 0; S[i]; ++i)
		if (element == S[i])
			return true;
	return false;
}

// представление множества E набором элементов массива
clock_t makeArraySet(char A[], char B[], char C[], char D[]) {

	char E[number_of_digits + 1] = {};

	clock_t start = clock();
	for (int i = 0; i < repeats; ++i) {
		int size = 0;
		// E := A
		for (int i = 0; A[i]; ++i)
			E[size++] = A[i];
		// E := E ⋃ B
		for (int i = 0; B[i]; ++i)
			if (!(IsInArray(E, B[i])))
				E[size++] = B[i];
		// E := E ⋃ C ⋂ D
		for (int i = 0; C[i]; ++i)
			if (IsInArray(D, C[i]))
				if (!(IsInArray(E, C[i])))
					E[size++] = C[i];
	}
	clock_t end = clock();

	cout << "The set E was made like array: " << E;
	cout << setw(18) << "Time: " << end - start << '\n';
	return end - start;
}

/*----------------------------------------------------------
						LIST FUNCTIONS
  ----------------------------------------------------------*/

  // преобразование массива в список
List* ConversionToList(char S[]) {
	List* LS = nullptr;
	for (int i = 0; S[i]; ++i) {
		LS = new List(S[i], LS);
	}
	return LS;
}

// проверка наличия элемента в множестве
bool IsInList(List* LS, char element) {
	for (List* p = LS; p; p = p->next)
		if (element == p->element)
			return true;
	return false;
}

// вывод списка
void PrintList(List* LS) {
	cout << "The set E was made like list: ";
	for (List* p = LS; p; p = p->next) {
		cout << p->element;
	}
}

// представление множества E набором элементов спсика
clock_t makeListSet(char A[], char B[], char C[], char D[]) {

	List
		* LA = ConversionToList(A),
		* LB = ConversionToList(B),
		* LC = ConversionToList(C),
		* LD = ConversionToList(D),
		* LE = nullptr;

	clock_t start = clock();
	for (int i = 0; i < repeats; ++i) {
		delete LE;
		LE = nullptr;

		// E := A
		for (List* p = LA; p; p = p->next)
			LE = new List(p->element, LE);
		// E := E ⋃ B
		for (List* p = LB; p; p = p->next)
			if (!(IsInList(LE, p->element)))
				LE = new List(p->element, LE);
		// E := E ⋃ C ⋂ D
		for (List* p = LC; p; p = p->next)
			if (IsInList(LD, p->element))
				if (!(IsInList(LE, p->element)))
					LE = new List(p->element, LE);
	}
	clock_t end = clock();

	PrintList(LE);
	cout << setw(19) << "Time: " << end - start << '\n';

	delete LA;
	delete LB;
	delete LC;
	delete LD;
	delete LE;

	return end - start;
}

/*----------------------------------------------------------
					 BITS VECTOR FUNCTIONS
  ----------------------------------------------------------*/

  // преобразование массива в вектор битов
void ConversionToBitsVector(char S[], char bS[]) {
	for (int i = 0; S[i]; ++i)
		bS[S[i] - '0'] = 1;
}

// преобразование вектора битов в массив
void ReverseFromBitsVector(char bS[], char S[]) {
	for (int i = 0, k = 0; i < number_of_digits; ++i)
		if (bS[i])
			S[k++] = i + '0';
}

// представление множества E вектором битов
clock_t makeBitsVectorSet(char A[], char B[], char C[], char D[]) {

	char
		bA[number_of_digits + 1] = {},
		bB[number_of_digits + 1] = {},
		bC[number_of_digits + 1] = {},
		bD[number_of_digits + 1] = {},
		bE[number_of_digits + 1] = {},
		E[number_of_digits + 1] = {};

	ConversionToBitsVector(A, bA);
	ConversionToBitsVector(B, bB);
	ConversionToBitsVector(C, bC);
	ConversionToBitsVector(D, bD);

	clock_t start = clock();
	for (int i = 0; i < repeats; ++i) {
		// E := A ⋃ B ⋃ C ⋂ D
		for (int i = 0; i < number_of_digits; ++i)
			bE[i] = bA[i] || bB[i] || (bD[i] && bC[i]);
	}
	clock_t end = clock();
	ReverseFromBitsVector(bE, E);

	cout << "The set E was made like bits vector: " << E
		<< setw(12) << "Time: " << end - start << '\n';

	return end - start;
}

/*----------------------------------------------------------
				   MACHINE WORD FUNCTIONS
  ----------------------------------------------------------*/

  // преобразование массива в машинное слово
short ConversionToMachineWord(char S[]) {
	short wS = 0;
	for (int i = 0; S[i]; ++i)
		wS |= (1 << (S[i] - '0'));
	return wS;
}

// преобразование машинного слова в массив
void ReverseFromMachineWord(short wS, char S[]) {
	for (int i = 0, k = 0; i < number_of_digits; ++i)
		if ((wS >> i) & 1)
			S[k++] = i + '0';
}

// представление множества E в виде машинного слова
clock_t makeMachineWordSet(char A[], char B[], char C[], char D[]) {

	char E[number_of_digits + 1] = {};
	short
		wA = ConversionToMachineWord(A),
		wB = ConversionToMachineWord(B),
		wC = ConversionToMachineWord(C),
		wD = ConversionToMachineWord(D),
		wE = 0;

	clock_t start = clock();
	for (int i = 0; i < repeats; ++i) {
		wE = 0;
		// E := A ⋃ B ⋃ C ⋂ D
		wE = wA | wB | (wC & wD);
	}
	clock_t end = clock();
	ReverseFromMachineWord(wE, E);

	cout << "The set E was made like machine word: " << E
		<< setw(11) << "Time: " << end - start << '\n';

	return end - start;
}

/*----------------------------------------------------------
						 GENERATORS
  ----------------------------------------------------------*/

  // генерация множества случайной мощности как машинного слова
void RandomPowerGenerationMW(char S[]) {
	short wS = rand() % 1023;
	ReverseFromMachineWord(wS, S);
}

// генерация множества случайной мощности как вектора битов
void RandomPowerGenerationBV(char S[]) {
	char bS[number_of_digits + 1] = {};
	for (int i = 0; i < number_of_digits; ++i)
		bS[i] = rand() % 2;
	ReverseFromBitsVector(bS, S);
}

// генерация множества случайной мощности как набора эд-ов массива
void RandomPowerGenerationArray(char S[]) {
	int k = 0;
	for (int i = 0; i < number_of_digits; ++i)
		if (rand() % 2)
			S[k++] = i + '0';
	S[k] = 0;
}

// генерация случайного множества заданной мощности
void SpecifiedPowerGenerationArray(char S[], int power) {
	char X[number_of_digits + 1] = {};
	for (int i = 0; i < number_of_digits; ++i)
		X[i] = i + '0';

	for (int i = 0; i < power; ++i) {
		int p = rand() % (number_of_digits - i);
		if (p) Swap(X[i + p], X[i]);
	}

	for (int i = 0; i < power; ++i)
		S[i] = X[i];
}

/*----------------------------------------------------------
						  MAIN
  ----------------------------------------------------------*/

int main() {
	srand(time(nullptr));
	ofstream output("C:\\Users\\Dangeon Master\\Documents\\My Work\\results.txt");
	if (output) {
		clock_t programStart = clock();
		for (int i = 0; i <= number_of_digits; ++i) {
			char
				A[number_of_digits + 1] = {},
				B[number_of_digits + 1] = {},
				C[number_of_digits + 1] = {},
				D[number_of_digits + 1] = {};

			// rand() % (number_of_digits + 1)
			SpecifiedPowerGenerationArray(A, i);
			SpecifiedPowerGenerationArray(B, i);
			SpecifiedPowerGenerationArray(C, i);
			SpecifiedPowerGenerationArray(D, i);
			cout << "Set A: " << A << '\n';
			cout << "Set B: " << B << '\n';
			cout << "Set C: " << C << '\n';
			cout << "Set D: " << D << "\n\n";

			clock_t
				array_time = makeArraySet(A, B, C, D),
				list_lime = makeListSet(A, B, C, D),
				bits_vector_time = makeBitsVectorSet(A, B, C, D),
				machine_word_time = makeMachineWordSet(A, B, C, D);


			output << "Power: " << i << '\n'
				<< array_time << "; "
				<< list_lime << "; "
				<< bits_vector_time << "; "
				<< machine_word_time << '\n' << endl;

			cout << "--------------------------------------------" << endl;
		}
		clock_t programEnd = clock();
		cout << "\nTotal time: " << programEnd - programStart;
	}
	else {
		cout << "Can't open the file";
	}

	return 0;
}

#include <stdio.h>
#include <string.h>

typedef int (*profession)(char*) ;
struct person {
	char*	 name;
	int	 age;
	profession func;
};



struct familyTree {
   	 int nMembers;
   	 struct person p[2];

   	 struct familyTree* 	next;
};

typedef struct person Person_t;
typedef struct familyTree FamilyTree_t;

int Refua(char* name)   { printf("%s. I'm a doctor\n", name);		return 0; }
int Handasa(char* name) { printf("%s. I'm an engineer\n", name);  return 0; }
int Makhsevim(char* name) { printf("%s. I'm a programmer\n", name);  return 0; }

FamilyTree_t Halakhmi = { 2, "Ilan", 28, Refua, "Gilad", 26, Handasa, 0};
FamilyTree_t Buchler  = { 2, "Rita", 38, Makhsevim, "Brian", 30, Refua, 0};

void DoIt(FamilyTree_t* ftPtr, char* name) {
	int i;
	for (i = 0; i<2; i++)
		if (!strcmp(ftPtr -> p [i]. name, name))		
			(ftPtr -> p)[i] . func(name);
}

int main() {
	DoIt(&Halakhmi , "Ilan");
	DoIt(&Buchler  , "Rita");
	DoIt(&Halakhmi , "Gilad");
	DoIt(&Buchler  , "Brian");
	return 1;
}

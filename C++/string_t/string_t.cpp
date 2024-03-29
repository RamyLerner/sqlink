#include <string.h>
#include "string_t.h"
#include <iostream>
#include <ctype.h>

int String_t::numOfStrings = 0;
int String_t::caseSens = 1;
size_t String_t::defaultCapacity = 16;

String_t::String_t()
{
	numOfStrings++;
	string = createEmpty();
	length = 0;
	capacity = defaultCapacity;
}

String_t::String_t(const char *s)
{
	if (!s)
	{
		string = createEmpty();
		length = 0;
		capacity = defaultCapacity;
	}
	else
	{
		string = createFrom(s);
		length = strlen(s);
		capacity = find2power(length);
	}
	numOfStrings++;
}

String_t::String_t(const String_t &st)
{
	setString(st.string);
	numOfStrings++;
}

String_t::~String_t()
{
	delete[] string;
	numOfStrings--;
}

String_t &String_t::operator=(const String_t &st)
{
	if (this != &st)
	{
		setString(st.string);
	}
	return *this;
}

void String_t::setString(const char *s)
{

	unsigned int len;
	if (!s)
	{
		string = createEmpty();
		length = 0;
	}
	else
	{
		len = strlen(s);
		if (len + 1 > capacity)
		{
			delete[] string;
			string = createFrom(s);
			capacity = len + 1;
		}
		else
			strcpy(string, s);

		length = len;
	}
}

int String_t::compareString(const String_t &st) const
{
	int res;
	if (caseSens)
		res = strcmp(string, st.string);
	else
		res = strcasecmp(string, st.string);
	if (!res)
		return 0;
	return res < 0 ? 1 : 2;
}

void String_t::toLowerString()
{
	int i = 0;
	while (string[i])
	{
		string[i] = tolower(string[i]);
		i++;
	}
}

void String_t::toUpperString()
{
	int i = 0;
	while (string[i])
	{
		string[i] = toupper(string[i]);
		i++;
	}
}

void String_t::appendAndSet(const char *s1, const char *s2)
{
	int len1 = strlen(s1), len2 = strlen(s2);
	char* temp = new char[len1 + len2 + 1];
	strcpy(temp, s1);
	strcat(temp, s2);
	setString(temp);
	delete[] temp;
}

String_t &String_t::prepend(const char *raw)
{
	appendAndSet(raw, string);
	return *this;
}

String_t &String_t::prepend(const String_t &st)
{
	return prepend(st.string);
}

String_t &String_t::operator+=(const char *raw)
{
	appendAndSet(string, raw);
	return *this;
}

String_t &String_t::operator+=(const String_t &st)
{
	return *this += st.string;
}

bool String_t::operator<(const String_t &st) const
{
	return compareString(st) == 1;
}

bool String_t::operator>(const String_t &st) const
{
	return compareString(st) == 2;
}

bool String_t::operator<=(const String_t &st) const
{
	return compareString(st) != 2;
}

bool String_t::operator>=(const String_t &st) const
{
	return compareString(st) != 1;
}

bool String_t::operator==(const String_t &st) const
{
	return compareString(st) == 0;
}

bool String_t::operator!=(const String_t &st) const
{
	return compareString(st) != 0;
}

char &String_t::operator[](size_t index)
{
	return index >= length ? string[length] : string[index];
}

char String_t::operator[](size_t index) const
{
	return index >= length ? 0 : string[index];
}

String_t& String_t::operator() (int start, unsigned int len) const{
	String_t* st;
	if (start < 0 || start+len >= length){
		st = new String_t();
		return *st;
	}
		
	char* raw = new char[len + 1];
	strncpy(raw, string + start, len);
	raw[len] = '\0';
	st = new String_t(raw);
	delete[] raw;
	return *st;
}

bool String_t::contains(const String_t &st) const
{
	return strstr(string, st.string);
}

std::ostream &operator<<(std::ostream &os, const String_t &st)
{
	os << st.getString();
	return os;
}

std::istream& operator>>(std::istream& is, String_t& st){
	char raw[STR_MAX_SIZE];
	is >> raw;
	st.setString(raw);
	return is;
}

void String_t::printString() const
{
	std::cout << *this;
}

int String_t::firstOcc(char c) const
{
	char* res = strchr(string, c);
	return res ? res - string : -1;
}

int String_t::lastOcc(char c) const
{
	char* res = strrchr(string, c);
	return res ? res - string : -1;
}

char *String_t::createEmpty()
{
	char *s = new char[defaultCapacity];
	s[0] = '\0';
	return s;
}

//allocates a new string from a given raw
//result to be assigned to s1.string
//NO OBJECT CREATED!!!
char *String_t::createFrom(const char *s)
{
	if (!s)
		return createEmpty();
	char *temp = new char[find2power(strlen(s) + 1)];
	strcpy(temp, s);
	return temp;
}

unsigned int String_t::find2power(unsigned int num)
{
	unsigned int base2 = 1;
	while (base2 < num)
		base2 *= 2;
	return base2;
}

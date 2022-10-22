#include "inf_int.h"

// 
// to be filled by students
//
// example :
//
// bool operator==(const inf_int& a , const inf_int& b)
// {
//     // we assume 0 is always positive.
//     if ( (strcmp(a.digits , b.digits)==0) && a.thesign==b.thesign )
//         return true;
//     return false;
// }
//

inf_int::inf_int() {
	this->length = 1;
	this->thesign = true;
	this->digits = new char[2];
	this->digits[0] = '0';
	this->digits[1] = '\0';
}

inf_int::inf_int(int n) {
	char buffer[100];

	if (n < 0) {
		this->thesign = false;
		n = -n;
	}
	else {
		this->thesign = true;
	}

	int i = 0;
	while (n > 0)
	{
		buffer[i] = n % 10 + '0';
		n /= 10;
		i++;
	}

	if (i == 0) {
		new (this) inf_int();
	}
	else {
		buffer[i] = '\0';

		this->digits = new char[i + 1];
		this->length = i;
		strcpy(this->digits, buffer);
	}
}

inf_int::inf_int(const char* str) {
	if (str[0] == '-') {
		this->thesign = false;
	}
	else {
		this->thesign = true;
	}

	int strLen = sizeof(str) / sizeof(char);
	int i = 0;
	if (this->thesign == false) {
		for (; i < strLen-1; i++) {
			this->digits[i] = str[strLen - 1 - i];
		}
	}
	else {
		for (; i < strLen; i++) {
			this->digits[i] = str[strLen - 1 - i];
		}
	}
	this->length = i + 1;
}

inf_int::inf_int(const inf_int& ex_inf_int) {
	this->digits = new char[ex_inf_int.length + 1];

	strcpy(this->digits, ex_inf_int.digits);
	this->length = ex_inf_int.length;
	this->thesign = ex_inf_int.thesign;
}

inf_int::~inf_int() {
	delete digits;
}

inf_int& inf_int::operator=(const inf_int& ex_inf_int)
{
	if (this->digits) {
		delete this->digits;		// �̹� ���ڿ��� ���� ��� ����.
	}
	this->digits = new char[ex_inf_int.length + 1];

	strcpy(this->digits, ex_inf_int.digits);
	this->length = ex_inf_int.length;
	this->thesign = ex_inf_int.thesign;

	return *this;
}

bool operator==(const inf_int& a, const inf_int& b)
{
	// we assume 0 is always positive.
	if ((strcmp(a.digits, b.digits) == 0) && a.thesign == b.thesign)	// ��ȣ�� ����, ������ ��ġ�ؾ���.
		return true;
	return false;
}

bool operator!=(const inf_int& a, const inf_int& b)
{
	return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b)
{
	// to be filled
	// ���밪 ��
	// �� �� ����� ��� ���� ���� ���� �״�� return
	// �� �� ������ ��� ���� ���� ���� �����Ͽ� return
	// ��ȣ�� �ٸ� ���, a�� ����� ��� b�� ����, a�� ������ ��� b�� ����̱⿡ a�� ��ȣ�������� ��ȯ�ϸ� ��
	if (a == b) {
		return false;
	}
	
	if (a.thesign && b.thesign) {
		return absLess(a, b);
	}
	else if (!a.thesign && !b.thesign) {
		return !absLess(a, b);
	}
	else {
		return a.thesign;
	}
}

bool operator<(const inf_int& a, const inf_int& b)
{
	if (operator>(a, b) || operator==(a, b)) {
		return false;
	}
	else {
		return true;
	}
}

inf_int operator+(const inf_int& a, const inf_int& b)
{
	inf_int c;
	unsigned int i;

	if (a.thesign == b.thesign) {	// ������ ��ȣ�� ���� ��� + �����ڷ� ����
		for (i = 0; i < a.length; i++) {
			c.Add(a.digits[i], i + 1);
		}
		for (i = 0; i < b.length; i++) {
			c.Add(b.digits[i], i + 1);
		}

		c.thesign = a.thesign;
		
		return c;
	}
	else {	// ������ ��ȣ�� �ٸ� ��� - �����ڷ� ����
		c = b;
		c.thesign = a.thesign;

		return a - c;
	}
}

inf_int operator-(const inf_int& a, const inf_int& b)
{
	// to be filled
	inf_int c,d;
	unsigned int i;

	if (a.thesign != b.thesign) {	// if thesign is different, unify thesign and +
		d = b;
		d.thesign = a.thesign;
		c = a + d;
		return c;
	}
	else {	// if thesign is same, substitute absolute value and decide thesign. always substitute from bigger to smaller number
		if (absLess(a, b)) {
			if (a.thesign) {
				c.thesign = false;
			}
			else {
				c.thesign = true;
			}
			for (i = 0; i < b.length; i++) {
				c.Add(b.digits[i], i + 1);
			}
			for (i = 0; i < a.length; i++) {
				c.Sub(a.digits[i], i + 1);
			}
		}
		else if (strcmp(a.digits, b.digits)) {
			c = inf_int();
		}
		else {
			if (a.thesign) {
				c.thesign = true;
			}
			else {
				c.thesign = false;
			}
			for (i = 0; i < a.length; i++) {
				c.Add(a.digits[i], i + 1);
			}
			for (i = 0; i < b.length; i++) {
				c.Sub(b.digits[i], i + 1);
			}
		}

		return c;
	}


}

inf_int operator*(const inf_int& a, const inf_int& b)
{
	// to be filled
	inf_int c;
	if (isZero(a) || isZero(b)) {
		c = inf_int();
		return c;
	}
	if (a.thesign == b.thesign) {
		c.thesign = true;
	}
	else {
		c.thesign = false;
	}
	c.length = a.length + b.length;
	c.digits = new char[c.length + 1];
	
	for (unsigned int i = 0; i < a.length; i++) {
		for (unsigned int j = 0; j < b.length; j++) {
			if (c.digits[i + j] != '0') c.digits[i + j] = '0';
			int n = (a.digits[i] - '0') * (b.digits[j] - '0') + c.digits[i + j];
			c.digits[i + j] = n % 10;
			c.digits[i + j + 1] += n / 10;
		}
	}
	for (unsigned int i = 0; i < c.length; i++) {
		c.digits[i] += '0';
	}
	if (c.digits[c.length-1] == '0') {
		c.digits = (char*)realloc(c.digits, c.length);
		c.digits[c.length - 1] = '\0';
		c.length -= 1;
	}
	else {
		c.digits[c.length] = '\0';
	}
	return c;
}


ostream& operator<<(ostream& out, const inf_int& a)
{
	int i;

	if (a.thesign == false) {
		out << '-';
	}
	for (i = a.length - 1; i >= 0; i--) {
		out << a.digits[i];
	}
	return out;
}

void inf_int::Add(const char num, const unsigned int index)	// a�� index �ڸ����� n�� ���Ѵ�. 0<=n<=9, ex) a�� 391�϶�, Add(a, 2, 2)�� ����� 411
{
	if (this->length < index) {
		this->digits = (char*)realloc(this->digits, index + 1);

		if (this->digits == NULL) {		// �Ҵ� ���� ����ó��
			cout << "Memory reallocation failed, the program will terminate." << endl;

			exit(0);
		}

		this->length = index;					// ���� ����
		this->digits[this->length] = '\0';	// �ι��� ����
	}

	if (this->digits[index - 1] < '0') {	// ���� ���� '0'���� ���� �ƽ�Ű���� ��� 0���� ä��. �������� �ʾҴ� ���ο� �ڸ����� ��� �߻�
		this->digits[index - 1] = '0';
	}

	this->digits[index - 1] += num - '0';	// �� ����


	if (this->digits[index - 1] > '9') {	// �ڸ��ø��� �߻��� ���
		this->digits[index - 1] -= 10;	// ���� �ڸ������� (�ƽ�Ű��) 10�� ����
		Add('1', index + 1);			// ���ڸ��� 1�� ���Ѵ�
	}
}

void inf_int::Sub(const char num, const unsigned int index) {// substitute num at index of a
	// �׻� ���밪�� �� ū �Ϳ��� ���� ���� ���Ƿ� �ǿ�����(RHS)�� �ε����� ���̸� �Ѿ ���� ����.

	if (this->digits[index - 1] < '0') {	// ���� ���� '0'���� ���� �ƽ�Ű���� ��� 0���� ä��. �������� �ʾҴ� ���ο� �ڸ����� ��� �߻�
		this->digits[index - 1] = '0';
	}

	this->digits[index - 1] -= num + '0';	// �� ����. 0-9�� ���� ���� ���ϰ� ���̽� �� '0'�� ���Ѵ�.


	if (this->digits[index - 1] < '0') {	// �ڸ������� �߻��� ���
		this->digits[index - 1] += 10;	// ���� �ڸ������� (�ƽ�Ű��) 10�� ���ϰ�
		Sub('1', index + 1);			// ���ڸ��� 1�� ����
	}

	if (this->digits[index - 1] == '0' && index == this->length) {
		// ���� ū �ڸ����� ���ڰ� ���� ��Ȳ���� �� ���
		this->digits = (char*)realloc(this->digits, index);
		if (this->digits == NULL) {		// �Ҵ� ���� ����ó��
			cout << "Memory reallocation failed, the program will terminate." << endl;

			exit(0);
		}
		this->length -= 1;
		this->digits[this->length] = '\0';
	}
}

bool isZero(const inf_int& a) {
	if (a.length != 1) return false;
	if (a.thesign != true) return false;
	if (a.digits[a.length - 1] != '0') return false;
	return true;
}

bool absLess(const inf_int& a, const inf_int& b) {
	if (a.length < b.length) {
		return true;
	}
	else if (a.length > b.length) {
		return false;
	}
	else {
		for (int i = 0; i < a.length; i++)
		{
			if (a.digits[i] > b.digits[i]) {
				return false;
			}
			else {
				continue;
			}
		}
		if (strcmp(a.digits, b.digits)) return false;
		return true;
	}
}
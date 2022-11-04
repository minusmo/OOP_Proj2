#include "inf_int.h"
#include <stdlib.h>

using namespace std;

void test();
int main()
{
	inf_int a, e;
	inf_int b(100);
	inf_int c("321111111111122222222222233333333333444444444445555555555");
	inf_int d("123451987651234572749499923455022211");
	inf_int f=d;
	inf_int g(f);

	// cin >> g ;   // not required
	a=b*c;
	// e=g/f;       // not required
	b=c-d;

	if (f==d) {
		cout << "a : " << a << endl;
		cout << "b : " << b << endl;
		cout << "c : " << c << endl;
		cout << "d : " << d << endl;
		// cout << "e : " << e << endl;
		cout << "f : " << f << endl;
		// cout << "g : " << g << endl;
	}

	cout << endl;
	cout << "More tests" << endl;
	test();

	char input;
	cout << "To close this prompt, enter anything: ";
	cin >> input;

	return 0;
}

void test() {
	inf_int a("111");
	inf_int b("2");
	inf_int c(0);
	inf_int d(3);
	inf_int e(-2);
	inf_int f(-0);
	inf_int g(-100);
	inf_int h("-111");
	inf_int i(-1111);
	cout << "111 + 2: " << a + b << endl;
	cout << "111 * 2: " << a * b << endl;
	cout << "111 - 2: "  << a - b << endl;
	cout << "2 + 111: " << b + a << endl;
	cout << "2 * 111: " << b * a << endl;
	cout << "2 - 111: " << b - a << endl;
	cout << "2 * 0: " << b * f << endl;
	cout << "0 * 3: " << c * d << endl;
	cout << "0 * -111: " << c * h << endl;
	cout << "0 + -100: " << f + g << endl;
	cout << "0 + 3: " << c + d << endl;
	cout << "111 + -111: " << a + h << endl;
	cout << "111 * -111: " << a * h << endl;
	cout << "111 - -111: " << a - h << endl;
	cout << "111 + 111: " << a + a << endl;
	cout << "2 + -111: " << b + h << endl;
	cout << "-100 + -111: " << g + h << endl;
	cout << "-100 - -111: " << g - h << endl;
	cout << "-100 * -111: " << g * h << endl;
	cout << "-2 + 111: " << e + a << endl;
	cout << "-2 - 3: " << e - d << endl;
	cout << "111 + -2: " << a + e << endl;
	cout << "3 + -1111: " << d + i << endl;
	cout << "3 * -111: " << d * h << endl;
	cout << "3 - -111: " << d - h << endl;
	cout << "-111 + 2: " << h + b << endl;
	cout << "0 + 0: " << c + c << endl;
	cout << "0 * 0: " << c * f << endl;
	cout << "0 - 0: " << c - f << endl;
}
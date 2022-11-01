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

	test();

	return 0;
}

void test() {
	// more tests
	inf_int h("345");
	inf_int i("1111111111111111111111111111111111111111111111111111");
	inf_int j("333333333333333333333333");
	inf_int k("73755");
	inf_int l("25555555555551111");
	inf_int m("21111111111");

	cout << "More tests" << endl;
	cout << h - i << endl;
	cout << j * k << endl;
	cout << l + m << endl;
}
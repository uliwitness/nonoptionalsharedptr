#include <iostream>
#include "nonoptional_shared_ptr.hpp"

class Bar {
public:
	explicit Bar(int n) : _num(n) {}

	void print() const { std::cout << "Bar::_num = " << _num << std::endl; }

	int _num;
};

class Foo {
public:
	explicit Foo(const nonoptional_shared_ptr<Bar>& p) : _neverNull(p) {}

	void print() { _neverNull->print(); }

protected:
	nonoptional_shared_ptr<Bar> _neverNull;
};

int main(int argc, const char** argv) {
	std::shared_ptr<Bar> bar = std::make_shared<Bar>(42);
	std::shared_ptr<Foo> dest;

	if_nonnullptr<Bar>(bar,
					  [&dest](const nonoptional_shared_ptr<Bar>& p) {
						  dest = std::make_shared<Foo>(p);
					  },
					  [](){
						  std::cerr << "Error!" << std::endl;
					  });

	dest->print();

	nonoptional_shared_ptr<Foo> dest2 = make_nonoptional_shared<Foo>(make_nonoptional_shared<Bar>(55));
	dest2->print();

	std::shared_ptr<Foo> possiblyOptionalAgain = dest2;

	return EXIT_SUCCESS;
}
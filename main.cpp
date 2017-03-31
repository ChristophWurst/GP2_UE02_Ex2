/*
 * The MIT License
 *
 * Copyright 2017 Christoph Wurst <christoph@winzerhof-wurst.at>.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <cstdlib>
#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix.hpp>

using namespace std;
namespace qi = boost::spirit::qi;

struct print_functor {

	void operator()(int const &i) const {
		cout << i << endl;
	}
};

/**
 * expr = term *( '+' term | '-' term )
 * term = fact *( '*' fact | '/' fact )
 * fact = double | '(' expr ')'
 */
template<typename Iterator>
struct simple_calc_grammar : qi::grammar<Iterator, qi::space_type> {

	simple_calc_grammar() : simple_calc_grammar::base_type(expr) {
		expr = term >> *('+' >> term | '-' >> term);
		term = fact >> *('*' >> fact | '/' >> fact);
		fact = qi::double_ | '(' >> expr >> ')';
	}

	qi::rule<Iterator, qi::space_type> expr, term, fact;
};

/*
 * 
 */
int main(int argc, char** argv) {
	string input;
	int output;

	getline(cin, input);
	auto begin = input.begin();

	simple_calc_grammar<decltype(begin) > grammar;
	bool success = qi::phrase_parse(input.begin()
		input.end(),
		grammar,
		qi::space);

	if (success) {
		cout << "Matched. Result=" << output << endl;
	} else {
		cout << "Error!" << endl;
	}

	return 0;
}


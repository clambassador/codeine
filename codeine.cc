#include "codeine.h"

#include "ib/csv_table.h"

#include <string>

using namespace ib;
using namespace minibus;
using namespace std;

namespace codeine {

CSVTable CodeineDriver::_table;
vector<string> CodeineDriver::_headers;

}  // namespace codeine

int main(int argc, char** argv) {
	if (argc != 2) {
		Logger::error("USAGE: % csv_file", argv[0]);
		return 0;
	}
	if (!codeine::CodeineDriver::load(argv[1])) {
		Logger::error("Unable to initialize csv file.");
		return 0;
	}
        initscr();
	start_color();
	keypad(stdscr, true);
	noecho();
	cbreak();
	codeine::CodeineDriver cd;
	cd.start();
	cd.wait();

	codeine::CodeineDriver::save(argv[1]);
}

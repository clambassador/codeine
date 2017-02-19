#ifndef __CODEINE__CODEINE__H__
#define __CODEINE__CODEINE__H__

#include <future>
#include <memory>
#include <string>
#include <vector>

#include "ib/csv_table.h"
#include "minibus/driver/minibus_driver.h"
#include "minibus/widgets/close_on_key.h"
#include "minibus/widgets/list_select.h"
#include "minibus/widgets/text.h"

using namespace ib;
using namespace minibus;
using namespace std;

namespace codeine {

class CodeineDriver : public MinibusDriver {
public:
	CodeineDriver(IDisplay* display,
		      IInput* input) : MinibusDriver(display, input) {
		build();
	}
	CodeineDriver() : MinibusDriver() {
		build();
	}

	virtual ~CodeineDriver() {
	}


	virtual void build() {
		_ls = new ListSelect(_headers);

		_tx = new Text("");
		_shortcut = new CloseOnKey(_tx, '0', '1');
		add_state_widget(new CloseOnKey(_ls));
		loop_state_widget(_shortcut);
	}

	static bool load(const string& csv_file) {
		_table.load(csv_file);
		_headers = _table.headers();
		return !_headers.empty();
	}

	static bool save(const string& csv_file) {
		return _table.save(csv_file);
	}

protected:
	virtual void setup_text() {
		cout << "setup" << endl;
		while (_pos < _column.size()) {
		cout << _pos << endl;
			if (_entry_to_result.count(_column[_pos])) {
				_result.push_back(
				    _entry_to_result[_column[_pos]]);
				++_pos;
			} else {
				_tx->set_text(_column[_pos]);
				return;
			}
		}
		_table.project(_column_number, _result);
		_cur_state = -1;
	}

	virtual void after_keypress(const Key& key, int state) {}
	virtual void after_close(const Key& key, int state) {
		if (state == STATE_SELECT) {
			_column_number = _ls->get_selected_pos().get();
			_column = _table.project(_column_number);
			_pos = 0;
			setup_text();
		}
		if (state == STATE_WORK) {
			assert(key.key() == '0' || key.key() == '1');
			_result.push_back((key.key() == '0' ? "0" : "1"));
			_entry_to_result[_column[_pos]] = _result.back();

			++_pos;
			setup_text();
		}
	}

	static CSVTable _table;
	static vector<string> _headers;

	vector<string> _column;
	ListSelect* _ls;
	Text* _tx;
	CloseOnKey* _shortcut;
	size_t _column_number;
	size_t _pos;
	map<string, string> _entry_to_result;
	vector<string> _result;

	enum {
		STATE_SELECT = 0,
		STATE_WORK
	};
};

}  // namespace codeine

#endif  // __CODEINE__CODEINE__H__

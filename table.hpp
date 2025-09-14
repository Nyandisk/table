#pragma once
#include <iostream>
#include <string>
#include <vector>
struct Column {
	std::string header;
	std::vector<std::string> values;
	inline static int calculateWidth(const Column& c) {
		int longest = c.header.size();
		for (const auto& v : c.values) {
			if (v.size() > longest) longest = v.size();
		}
		return longest + 2; // 2 for space padding
	}
	inline static int calculateHeight(const Column& c) {
		return (c.values.size() + 1) * 2 - 1; // -1 for bottom 
	}
};

class Table {
	std::vector<Column> m_columns;
	inline int tableWidth() const {
		int width = 1; // starting line
		for (const auto& col : m_columns) {
			width += Column::calculateWidth(col) + 1;
		}
		// width includes separator so no need for another +1
		return width;
	}
	inline const Column* tallestColumn() const {
		int tallest = 0;
		const Column* tallestCol{};
		for (const auto& col : m_columns) {
			int h = Column::calculateHeight(col);
			if (h > tallest) {
				tallest = h;
				tallestCol = &col;
			}
		}
		return tallestCol;
	}
	inline std::string line() const {
		std::string result = "+";

		for (const auto& col : m_columns) {
			result += std::string(Column::calculateWidth(col), '-') + '+';
		}

		return result;
	}
public:
	inline void render() {
		int w = tableWidth();

		std::cout << line() << '\n';
		for (size_t i = 0; i < tallestColumn()->values.size() + 1; i++) {
			for (const auto& col : m_columns) {
				std::string value;
				if (i == 0) {
					value = col.header;
				}
				else {
					value = (i - 1) < col.values.size() ? col.values[i - 1] : "";
				}
				int padding = Column::calculateWidth(col) - value.size() - 2; // padding
				std::cout << "| " << value << std::string(padding, ' ') << " ";
			}
			std::cout << "|";
			if (i == 0) std::cout << '\n' << line();
			std::cout << '\n';
		}
		std::cout << line() << '\n';
	}
	inline const std::vector<Column>& columns() const {
		return m_columns;
	}
	inline void add(const Column& col) {
		m_columns.push_back(col);
	}
	inline void add(const std::string header, const std::vector<std::string>& col) {
		m_columns.emplace_back(header, col);
	}
};
#pragma once

class Field {
public:
	Field(int line_max_length, int cell_size);

	~Field();

	void draw();

private:
	int mLineMaxLength = 1024;
	int mCellSize = 0;
};
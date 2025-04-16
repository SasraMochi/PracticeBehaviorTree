#pragma once

#include <vector>
#include "Composite.h"

class Sequence : public CompositeNodeBase {
public:
	Sequence(BlackBoard* black_board);

	~Sequence();

	void reset() override;

public:
	virtual NodeResult tick() override;

	void node_increment();

private:
	// ���ݓ������Ă���m�[�h�ԍ�
	int mRunningNodeIndex{ 0 };
};
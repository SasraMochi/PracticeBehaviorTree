#pragma once

#include <string>
#include <unordered_map>
#include <any>

class BlackBoard {
public:
	// �v�f���Z�b�g
	template<typename T>
	void SetValue(const std::string& key, const T& value);

	// �v�f���擾
	template<typename T>
	T GetValue(const std::string& key) const;

	// �L�[�����邩�`�F�b�N
	bool HasKey(const std::string& key) const;

private:
	std::unordered_map<std::string, std::any> data_;
};
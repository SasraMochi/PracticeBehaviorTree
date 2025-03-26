#pragma once

#include <string>
#include <unordered_map>
#include <any>

class BlackBoard {
public:
	// 要素をセット
	template<typename T>
	void SetValue(const std::string& key, const T& value);

	// 要素を取得
	template<typename T>
	T GetValue(const std::string& key) const;

	// キーがあるかチェック
	bool HasKey(const std::string& key) const;

private:
	std::unordered_map<std::string, std::any> data_;
};
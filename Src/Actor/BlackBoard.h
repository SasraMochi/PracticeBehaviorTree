#pragma once

#include <string>
#include <unordered_map>
#include <any>
#include <iostream>

class BlackBoard {
public:
	// 要素をセット
	template<typename T>
	void SetValue(const std::string& key, const T& value) {
		data_[key] = value;
	}

	// 要素を取得
	template<typename T>
	T GetValue(const std::string& key) const {
		auto it = data_.find(key);
		if (it != data_.end()) {
			return std::any_cast<T>(it->second);
		}

		throw std::runtime_error("キーが見つかりませんでした： " + key);
	}

	// キーがあるかチェック
	bool HasKey(const std::string& key) const;

private:
	std::unordered_map<std::string, std::any> data_;
};
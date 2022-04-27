﻿/// <summary>
/// バイナリファイルを扱うクラス
/// </summary>
#pragma once

#include <memory>

class BinaryFile
{
protected:

	// データ
	std::unique_ptr<char[]> mData;

	// サイズ
	unsigned int mSize;

public:

	// ファイル名を指定してロード
	static BinaryFile LoadFile(const wchar_t* fileName);

	BinaryFile();

	// ムーブコンストラクタ
	BinaryFile(BinaryFile&& in);

	// アクセサ
	const char* GetData() { return mData.get(); }
	const unsigned int& GetSize() { return mSize; }
};

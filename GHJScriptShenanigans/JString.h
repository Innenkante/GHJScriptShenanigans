#pragma once
class JString
{
private:
	std::wstring jsWString;
	std::string jsString;

	JsValueRef jsValue;
public:
	JString(JsValueRef jsValue);

	JString(std::string jsString);

	JString(std::wstring jsWString);

	std::string AsString() const;

	std::wstring AsWString() const;

	const char* ToCharArray() const;

	const wchar_t* ToWCharArray() const;

	JsValueRef AsJsValue() const;
};
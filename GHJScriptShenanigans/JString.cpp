#include "stdafx.h"
#include "JString.h"

JString::JString(JsValueRef jsValue)
{
	this->jsValue = jsValue;

	JsValueRef tmpString;
	JsConvertValueToString(jsValue, &tmpString);

	const wchar_t* tmpArrayForString;
	size_t tmpArrayLength;

	JsStringToPointer(tmpString, &tmpArrayForString, &tmpArrayLength);

	jsWString = std::wstring(tmpArrayForString);

	jsString = std::string(jsWString.begin(), jsWString.end());
}

JString::JString(std::string jsString)
{
	this->jsString = jsString;
	jsWString = std::wstring(jsString.begin(), jsString.end());

	JsValueRef tmp;
	JsPointerToString(this->jsWString.c_str(), this->jsWString.length(), &tmp);
	JsConvertValueToString(tmp, &jsValue);
}

JString::JString(std::wstring jsWString)
{
	this->jsWString = jsWString;
	jsString = std::string(jsWString.begin(), jsWString.end());

	JsValueRef tmp;
	JsPointerToString(this->jsWString.c_str(), this->jsWString.length(), &tmp);
	JsConvertValueToString(tmp, &jsValue);
}

std::string JString::AsString() const
{
	return jsString;
}

std::wstring JString::AsWString() const
{
	return jsWString;
}

const char* JString::ToCharArray() const
{
	return jsString.c_str();
}

const wchar_t* JString::ToWCharArray() const
{
	return jsWString.c_str();
}

JsValueRef JString::AsJsValue() const
{
	return jsValue;
}

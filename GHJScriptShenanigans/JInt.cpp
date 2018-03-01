#include "stdafx.h"
#include "JInt.h"


JInt::JInt(JsValueRef jsValue)
{
	this->jsValue = jsValue;

	JsValueRef jsTmp;
	JsConvertValueToNumber(jsValue, &jsTmp);
	JsNumberToInt(jsTmp, &jsInt);
}

JInt::JInt(int jsInt)
{
	this->jsInt = jsInt;

	JsIntToNumber(jsInt, &jsValue);
}

JsValueRef JInt::AsJsValue() const
{
	return jsValue;
}

int JInt::AsInt() const
{
	return jsInt;
}

#include "stdafx.h"
#include "JFloat.h"


JFloat::JFloat(JsValueRef jsValue)
{
	this->jsValue = jsValue;

	JsValueRef jsTmp;
	JsConvertValueToNumber(jsValue, &jsTmp);
	double tmp;
	JsNumberToDouble(jsTmp, &tmp);
	jsFloat = static_cast<float>(tmp);
}

JFloat::JFloat(float jsFloat)
{
	this->jsFloat = jsFloat;

	JsDoubleToNumber(static_cast<double>(jsFloat), &jsValue);
	
}

JsValueRef JFloat::AsJsValue() const
{
	return jsValue;
}

float JFloat::AsFloat() const
{
	return jsFloat;
}

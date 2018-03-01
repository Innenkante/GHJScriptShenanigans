#pragma once
class JInt
{
private:
	JsValueRef jsValue;
	int jsInt;

public:
	JInt(JsValueRef jsValue);


	JInt(int jsInt);

	JsValueRef AsJsValue() const;

	int AsInt() const;
};
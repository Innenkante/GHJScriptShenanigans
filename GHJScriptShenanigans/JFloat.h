#pragma once
#pragma once
class JFloat
{
private:
	JsValueRef jsValue;
	float jsFloat;

public:
	JFloat(JsValueRef jsValue);


	JFloat(float jsFloat);

	JsValueRef AsJsValue() const;

	float AsFloat() const;
};
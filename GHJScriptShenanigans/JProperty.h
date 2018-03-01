#pragma once
#include "ChakraCore.h"
class JProperty
{
private:
	JsValueRef value;
	std::string name;
public:
	JProperty(std::string name, JsValueRef value);
	void AttachTo(JsValueRef object) const;
};
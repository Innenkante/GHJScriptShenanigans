#pragma once
#include "JProperty.h"
#include <vector>

class JObject
{
private:
	std::vector<JProperty> properties;
	JsValueRef objectRef;
public:
	JObject(std::vector<JProperty> properties);
	JsValueRef AsJsValue() const;
};

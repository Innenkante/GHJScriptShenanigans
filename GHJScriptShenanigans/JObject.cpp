#include "stdafx.h"
#include "JObject.h"

JObject::JObject(std::vector<JProperty> properties)
{
	this->properties = properties;
	JsCreateObject(&objectRef);
}

JsValueRef JObject::AsJsValue() const
{
	for(auto &property : properties)
	{
		property.AttachTo(objectRef);
	}

	return objectRef;
}


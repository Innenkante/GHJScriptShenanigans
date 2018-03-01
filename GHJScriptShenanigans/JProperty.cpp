#include "stdafx.h"
#include "JProperty.h"

JProperty::JProperty(std::string name, JsValueRef value)
{
	this->name = name;
	this->value = value;
}

void JProperty::AttachTo(JsValueRef object) const
{
	JsPropertyIdRef propertyRef;
	JsCreatePropertyId(name.c_str(), name.length(), &propertyRef);
	JsSetProperty(object, propertyRef, value, true);
}

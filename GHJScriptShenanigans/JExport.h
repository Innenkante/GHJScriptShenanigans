#pragma once
#include "string"
template<typename T> class JExport
{
private:
	std::string objectName;
	std::string memberName;
	T value;
public:
	JExport<T>(std::string objectName, std::string functionName, T value);

	void ApplyFunction(JsContextRef context) const;

	void ApplyIntVariable(JsContextRef context) const;
};

template<typename T>
JExport<T>::JExport(std::string objectName, std::string functionName, T value)
{
	this->objectName = objectName;
	this->memberName = functionName;
	this->value = value;
}


template <typename T>
void JExport<T>::ApplyFunction(JsContextRef context) const
{
	JsSetCurrentContext(context);

	JsValueRef objectRef, functionRef, global;
	JsPropertyIdRef objectRefId, functionRefId;
	
	bool objectExists;

	JsGetGlobalObject(&global);
	JsGetPropertyIdFromName(std::wstring(objectName.begin(), objectName.end()).c_str(), &objectRefId);
	JsHasProperty(global, objectRefId, &objectExists);

	if (!objectExists)
	{
		JsCreateObject(&objectRef);
		JsCreatePropertyId(objectName.c_str(), objectName.length(), &objectRefId);
		JsSetProperty(global, objectRefId, objectRef, true);
	}

	JsGetProperty(global, objectRefId, &objectRef);

	JsCreateFunction((JsNativeFunction)value, nullptr, &functionRef);
	JsCreatePropertyId(memberName.c_str(), memberName.length(), &functionRefId);
	JsSetProperty(objectRef, functionRefId, functionRef, true);
}

template<typename T>
void JExport<T>::ApplyIntVariable(JsContextRef context) const
{
	JsSetCurrentContext(context);

	JsValueRef objectRef, global;
	JsPropertyIdRef objectRefId, variableRefId;

	bool objectExists;

	JsGetGlobalObject(&global);
	JsGetPropertyIdFromName(std::wstring(objectName.begin(), objectName.end()).c_str(), &objectRefId);
	JsHasProperty(global, objectRefId, &objectExists);

	if (!objectExists)
	{
		JsCreateObject(&objectRef);
		JsCreatePropertyId(objectName.c_str(), objectName.length(), &objectRefId);
		JsSetProperty(global, objectRefId, objectRef, true);
	}

	JsGetProperty(global, objectRefId, &objectRef);


	JsCreatePropertyId(memberName.c_str(), memberName.length(), &variableRefId);
	JsSetProperty(objectRef, variableRefId, JInt((int)value).AsJsValue(), true);
}
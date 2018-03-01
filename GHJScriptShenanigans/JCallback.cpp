#include "stdafx.h"
#include "JCallback.h"

JCallback::JCallback(std::wstring name)
{
	this->name = name;
}

void JCallback::Call(JsContextRef context, std::vector<JsValueRef> args) const
{
	//MessageBoxA(NULL, "", "", 0);
	JsSetCurrentContext(context);

	JsValueRef global, function;
	JsPropertyIdRef functionRef;

	JsGetGlobalObject(&global);

	JsGetPropertyIdFromName(name.c_str(), &functionRef);

	JsGetProperty(global, functionRef, &function);
	JsCallFunction(function, args.data(), args.size(), NULL);
}


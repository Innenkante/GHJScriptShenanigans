#pragma once
#include "ChakraCore.h"
#include <map>

namespace JExports
{
	extern std::map<int, int*> Fonts;
	extern std::map<int, std::vector<float>> Colors;

	void JInit(JsContextRef context);
	
	JsValueRef CALLBACK JDrawText(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState);

	JsValueRef CALLBACK JDrawShader(JsValueRef callee, bool isConstructCall, JsValueRef * arguments, unsigned short argCount, void * callbackState);

	JsValueRef CALLBACK JGetEntity(JsValueRef callee, bool isConstructCall, JsValueRef * arguments, unsigned short argCount, void * callbackState);

	JsValueRef CALLBACK JWorldToScreen(JsValueRef callee, bool isConstructCall, JsValueRef * arguments, unsigned short argCount, void * callbackState);

	JsValueRef CALLBACK JGetLocalPlayerId(JsValueRef callee, bool isConstructCall, JsValueRef * arguments, unsigned short argCount, void * callbackState);
}

#pragma once
#include <vector>
#include <ChakraCore.h>

class JCallback
{
private:
	std::wstring name;
public:
	JCallback(std::wstring name);

	void Call(JsContextRef context, std::vector<JsValueRef> args) const;
};

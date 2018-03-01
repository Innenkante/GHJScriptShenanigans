#include "stdafx.h"
#include "JExports.h"

std::map<int, int*> JExports::Fonts;
std::map<int, std::vector<float>> JExports::Colors;

Native::GetScreenMatrixNative GetScreenMatrix = reinterpret_cast<Native::GetScreenMatrixNative>(0x004B6350);
Native::WorldToScreenNative WorldToScreen = reinterpret_cast<Native::WorldToScreenNative>(0x004E5FC0);

Native::AddCmdDrawTextNative AddCmdDrawText = reinterpret_cast<Native::AddCmdDrawTextNative>(0x0042C970);
Native::DrawRotatedPictureNative DrawRotatedPicture = reinterpret_cast<Native::DrawRotatedPictureNative>(0x0042F420);

Native::RegisterFontNative RegisterFont = reinterpret_cast<Native::RegisterFontNative>(0x004FB960);
Native::RegisterShaderNative RegisterShader = reinterpret_cast<Native::RegisterShaderNative>(0x0041B6B0);

void JExports::JInit(JsContextRef context)
{
	JExport<JsNativeFunction>("mw3", "drawText", JDrawText).ApplyFunction(context);
	JExport<JsNativeFunction>("mw3", "drawShader", JDrawShader).ApplyFunction(context);
	JExport<JsNativeFunction>("mw3", "getEntity", JGetEntity).ApplyFunction(context);
	JExport<JsNativeFunction>("mw3", "worldToScreen", JWorldToScreen).ApplyFunction(context);
	JExport<JsNativeFunction>("mw3", "getLocalPlayerId", JGetLocalPlayerId).ApplyFunction(context);


	std::vector<std::string> fonts = {
		"smallDevFont",
		"bigDevFont",
		"consoleFont",
		"bigFont",
		"smallFont",
		"boldFont",
		"normalFont",
		"extraBigFont",
		"objectiveFont"
	};

	std::vector<JExport<int>> exportedFonts;
	std::vector<JExport<int>> exportedColors;

	exportedColors.push_back(JExport<int>("mw3", "whiteColor", 0));
	exportedColors.push_back(JExport<int>("mw3", "blackColor", 1));
	exportedColors.push_back(JExport<int>("mw3", "redColor", 2));
	exportedColors.push_back(JExport<int>("mw3", "greenColor", 3));
	exportedColors.push_back(JExport<int>("mw3", "blueColor", 4));

	Colors.insert(std::pair<int, std::vector<float>>(0, { 1.f,1.f,1.f,1.f }));
	Colors.insert(std::pair<int, std::vector<float>> {1, { 0.f,0.f,0.f,1.f }});
	Colors.insert(std::pair<int, std::vector<float>> {2, { 1.f,0.f,0.f,1.f }});
	Colors.insert(std::pair<int, std::vector<float>> {3, { 0.f,1.f,0.f,1.f }});
	Colors.insert(std::pair<int, std::vector<float>> {4, { 0.f,0.f,1.f,1.f }});

	for (auto &exportedColor : exportedColors)
		exportedColor.ApplyIntVariable(context);

	for (int i = 0; i < 8; i++)
	{
		Fonts.insert(std::pair<int, int*>(i, RegisterFont(("fonts/" + fonts[i]).c_str())));
		exportedFonts.push_back(JExport<int>("mw3", fonts[i], i));
	}

	for (auto &exportedFont : exportedFonts)
		exportedFont.ApplyIntVariable(context);
}

JsValueRef CALLBACK JExports::JDrawText(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
{
	//MessageBoxA(NULL, "ExportedDraw called", "", 0);

	auto text = JString(arguments[1]);
	auto x = JFloat(arguments[2]).AsFloat();
	auto y = JFloat(arguments[3]).AsFloat();
	auto font = JInt(arguments[4]).AsInt();
	auto color = JInt(arguments[5]).AsInt();

	AddCmdDrawText(text.ToCharArray(), 0x7FFFFFFF, Fonts[font], x, y, 1, 1, 0, Colors[color].data(), 0);

	return JS_INVALID_REFERENCE;
}

JsValueRef CALLBACK JExports::JDrawShader(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
{
	auto shader = JString(arguments[1]);
	auto x = JFloat(arguments[2]).AsFloat();
	auto y = JFloat(arguments[3]).AsFloat();
	auto w = JFloat(arguments[4]).AsFloat();
	auto h = JFloat(arguments[5]).AsFloat();
	auto color = JInt(arguments[6]).AsInt();

	DrawRotatedPicture(GetScreenMatrix(), x, y, w, h, 0, Colors[color].data(), RegisterShader(shader.ToCharArray()));

	return JS_INVALID_REFERENCE;
}

JsValueRef CALLBACK JExports::JGetEntity(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
{
	//MessageBoxA(NULL, "GetEntityCallled", "", 0);
	auto id = JInt(arguments[1]).AsInt();

	auto entity = reinterpret_cast<Native::Entity*>(0x00A08630 + id * 0x1F8);
	auto client = reinterpret_cast<Native::Client*>(0x009FC748 + id * 0x560);

	const auto valid = client->Valid && entity->Valid;
	const auto alive = entity->Alive & 0x01;
	const auto team = client->Team;
	const auto x = entity->Origin.X;
	const auto y = entity->Origin.Y;
	const auto z = entity->Origin.Z;

	//if (valid)
	//{
		//char buffer[256];
		//sprintf_s(buffer, "%i \n %s \n %i \n %i \n %i \n %i \n %i \n", valid, name, alive, team, x, y, z);
		//MessageBoxA(NULL, buffer, "", 0);
	//}

	if (valid)
	{
		return JObject
		({
			JProperty("valid",JInt(valid).AsJsValue()),
			JProperty("alive",JInt(alive).AsJsValue()),
			JProperty("team",JInt(team).AsJsValue()),
			JProperty("x",JFloat(x).AsJsValue()),
			JProperty("y",JFloat(y).AsJsValue()),
			JProperty("z",JFloat(z).AsJsValue()),
		}).AsJsValue();
	}

	return JObject({ JProperty("valid",JInt(valid).AsJsValue()) }).AsJsValue();

	//return JS_INVALID_REFERENCE;
}

JsValueRef CALLBACK JExports::JWorldToScreen(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
{
	float vector[3] = { JFloat(arguments[1]).AsFloat(), JFloat(arguments[2]).AsFloat(), JFloat(arguments[3]).AsFloat() };
	float screen[2];

	WorldToScreen(0, GetScreenMatrix(), vector, screen);

	return JObject
	({
		JProperty("x",JFloat(screen[0]).AsJsValue()),
		JProperty("y",JFloat(screen[1]).AsJsValue())
	}).AsJsValue();
}

JsValueRef CALLBACK JExports::JGetLocalPlayerId(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argCount, void* callbackState)
{
	auto cg = reinterpret_cast<Native::CG*>(0x008FF100);

	return JInt(cg->ClientNumber).AsJsValue();
}

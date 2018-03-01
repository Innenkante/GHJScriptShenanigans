#pragma once
namespace Native
{
	class Vector3D
	{
	public:
		float X, Y, Z;
	};

	class Entity
	{
	public:
		char _0x0000[0x2];
		short Valid;
		char _0x0004[0x10];
		Vector3D Origin;
		Vector3D Angles;
		char _0x002C[0x3C];
		int Flags;
		char _0x006C[0xC];
		Vector3D OldOrigin;
		char _0x0084[0x18];
		Vector3D OldAngles;
		char _0x00A8[0x28];
		int ClientNumber;
		short Type;
		char _0x00D6[0x12];
		Vector3D NewOrigin;
		char _0x00F4[0x1C];
		Vector3D NewAngles;
		char _0x011C[0x7C];
		BYTE WeaponID;
		char _0x0199[0x37];
		int Alive;
		char _0x01D4[0x24];
	};

	class Client
	{
	public:
		int ClientNumber; //0x0000 
		int Valid; //0x0004 
		char _0x0008[4];
		char Name[16]; //0x000C 
		int Team; //0x001C 
		int Team_2; //0x0020 
		int Rank; //0x0024 
		char _0x0028[16];
		int Perk; //0x0038 
		char _0x003C[8];
		int Score; //0x0044 
		char _0x0048[8];
		char BodyName[32]; //0x0050 
		char _0x0070[32];
		char HeadName[32]; //0x0090 
		char _0x00B0[992];
		BYTE IsStanding; //0x0490 
		BYTE IsWalking; //0x0491 
		BYTE IsSprinting; //0x0492 
		char _0x0493[13];
		int IsAttacking; //0x04A0 
		char _0x04A4[4];
		int IsZooming; //0x04A8 
		char _0x04AC[68];
		int WeaponNumber1; //0x04F0 
		char _0x04F4[24];
		int WeaponNumber2; //0x050C 
		char _0x0510[80];
	};

	class ScreenMatrix
	{
	public:
		char matrix[0x6C];
	};


	class CG
	{
	public:
		int ServerTime;
		int PlayerState;
		int StaminaTimer;
		unsigned short PlayerStance;
		char _0x000E[0x2];
		int IsIngame;
		char _0x0014[0x4];
		int iVelocity;
		float Origin[3];
		float Velocity[3];
		char _0x0034[0x2C];
		float RefViewAngleY;
		float RefViewAngleX;
		char _0x0068[0xE8];
		int ClientNumber;
		char _0x0154[0x4];
		float ViewAngleY;
		float ViewAngleX;
		char _0x0160[0x3C];
		int Health;
		char _0x01A0[0x1C];
		int MaxEntities;
		char _0x01C0[0x44];
		int AdvancedUAV;
	};


	void *DetourFunction(BYTE * src, const BYTE * dst, const int len);

	using GetScreenMatrixNative = ScreenMatrix* (__cdecl*)();
	using WorldToScreenNative = bool(__cdecl*)(int a1, ScreenMatrix* s, float vector[3], float* position);

	using RegisterFontNative = int*(__cdecl*)(const char* font);
	using RegisterShaderNative = int*(__cdecl*)(const char* shader);

	using AddCmdDrawTextNative = char*(__cdecl*)(const char* text, int numChars, int* font, float x, float y, float xScale, float yScale, float angle, float color[4], int stlyeText);
	using DrawRotatedPictureNative = int(__cdecl*)(ScreenMatrix* matrix, float x, float y, float width, float height, float angle, float color[4], int* shader);


}


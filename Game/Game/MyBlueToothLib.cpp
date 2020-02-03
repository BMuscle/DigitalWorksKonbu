#include "MyBlueToothLib.h"
#include <WinSock2.h>
#include <algorithm>
#include <ws2bth.h>
#include <SetupAPI.h>

// 指定した名前のポート名を見つける
bool MyBlueToothLib::SearchPort(const std::string& searchname, std::string& portname)
{
	// COMデバイスが登録されているところ
	const std::string findKey = "SYSTEM\\CurrentControlSet\\services\\BTHPORT\\Parameters\\Devices";

	DWORD dwResult;

	std::string strFolderID;

	////// レジストリから指定した名前を持つポートのフォルダ名を取得する

	// フォルダキー（サブキー）を開く
	HKEY hFolderKey;
	dwResult = RegOpenKeyExA(HKEY_LOCAL_MACHINE, findKey.c_str(), 0, KEY_READ, &hFolderKey);
	if (dwResult != ERROR_SUCCESS) {
		return false;
	}

	FILETIME ftLastWriteTime;
	char folder[1024];

	// フォルダーの列挙
	for (DWORD dwIndex = 0; ; dwIndex++) {
		DWORD folderSz = sizeof(folder) / sizeof(char);
		// 列挙
		dwResult = RegEnumKeyExA(hFolderKey, dwIndex, folder, &folderSz, NULL, NULL, NULL, &ftLastWriteTime);
		if (dwResult == ERROR_NO_MORE_ITEMS) break;
		if (dwResult != ERROR_SUCCESS) continue;

		// 取得された→folder

		// その下のNameエンティティを調べる
		char namePath[1024];
		DWORD namePathSz = sizeof(namePath) / sizeof(char);

		strcpy_s(namePath, namePathSz, folder);

		HKEY hNameEntKey;
		dwResult = RegOpenKeyExA(hFolderKey, namePath, 0, KEY_READ, &hNameEntKey);
		if (dwResult != ERROR_SUCCESS) {
			continue;
		}

		DWORD dwType;
		char lpData[1024];
		DWORD dwDataSize = sizeof(lpData) / sizeof(char);
		dwResult = RegQueryValueEx(hNameEntKey, TEXT("Name"), 0, &dwType, (LPBYTE)lpData, &dwDataSize);
		RegCloseKey(hNameEntKey);

		if (dwResult != ERROR_SUCCESS) {
			continue;
		}
		lpData[dwDataSize] = '\0';

		// 値のチェック
		if (strcmp(lpData, searchname.c_str()) == 0) { /// ここ文字数見たほうがいいかも TODO:
			char searchID[512];
			sprintf_s(searchID, 512, "&%s_", folder);
			strFolderID = std::string(searchID);
			std::transform(strFolderID.begin(), strFolderID.end(), strFolderID.begin(), std::toupper);
			break;
		}
	}
	RegCloseKey(hFolderKey);

	if (strFolderID == "") return false;

	////// デバイス情報から、フォルダ名をキーにCOMポート名をひっぱる

	// デバイス情報取得 COMPORT
	HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_COMPORT, NULL, NULL, (DIGCF_PRESENT | DIGCF_DEVICEINTERFACE));

	SP_DEVINFO_DATA deviceInfoData = { sizeof(SP_DEVINFO_DATA) };
	for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &deviceInfoData); ++i) {
		char buffer[512];
		DWORD buflen = 0;
		SetupDiGetDeviceInstanceIdA(hDevInfo, &deviceInfoData, (char*)buffer, sizeof(buffer), &buflen);
		std::string strBuffer = std::string(buffer);
		if (strBuffer.find(strFolderID) == std::string::npos) continue;

		// 発見
		//// COMポート番号を取得
		HKEY tmp_key = SetupDiOpenDevRegKey(hDevInfo, &deviceInfoData, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_QUERY_VALUE);
		if (!tmp_key) {
			return false;
		}
		char name[256];
		DWORD type = 0;
		DWORD size = sizeof(name);
		RegQueryValueExA(tmp_key, "PortName", NULL, &type, (LPBYTE)name, &size);
		portname = std::string(name);
		return true;
	}
	return false;
}
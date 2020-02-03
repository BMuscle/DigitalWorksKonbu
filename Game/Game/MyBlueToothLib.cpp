#include "MyBlueToothLib.h"
#include <WinSock2.h>
#include <algorithm>
#include <ws2bth.h>
#include <SetupAPI.h>

// �w�肵�����O�̃|�[�g����������
bool MyBlueToothLib::SearchPort(const std::string& searchname, std::string& portname)
{
	// COM�f�o�C�X���o�^����Ă���Ƃ���
	const std::string findKey = "SYSTEM\\CurrentControlSet\\services\\BTHPORT\\Parameters\\Devices";

	DWORD dwResult;

	std::string strFolderID;

	////// ���W�X�g������w�肵�����O�����|�[�g�̃t�H���_�����擾����

	// �t�H���_�L�[�i�T�u�L�[�j���J��
	HKEY hFolderKey;
	dwResult = RegOpenKeyExA(HKEY_LOCAL_MACHINE, findKey.c_str(), 0, KEY_READ, &hFolderKey);
	if (dwResult != ERROR_SUCCESS) {
		return false;
	}

	FILETIME ftLastWriteTime;
	char folder[1024];

	// �t�H���_�[�̗�
	for (DWORD dwIndex = 0; ; dwIndex++) {
		DWORD folderSz = sizeof(folder) / sizeof(char);
		// ��
		dwResult = RegEnumKeyExA(hFolderKey, dwIndex, folder, &folderSz, NULL, NULL, NULL, &ftLastWriteTime);
		if (dwResult == ERROR_NO_MORE_ITEMS) break;
		if (dwResult != ERROR_SUCCESS) continue;

		// �擾���ꂽ��folder

		// ���̉���Name�G���e�B�e�B�𒲂ׂ�
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

		// �l�̃`�F�b�N
		if (strcmp(lpData, searchname.c_str()) == 0) { /// ���������������ق����������� TODO:
			char searchID[512];
			sprintf_s(searchID, 512, "&%s_", folder);
			strFolderID = std::string(searchID);
			std::transform(strFolderID.begin(), strFolderID.end(), strFolderID.begin(), std::toupper);
			break;
		}
	}
	RegCloseKey(hFolderKey);

	if (strFolderID == "") return false;

	////// �f�o�C�X��񂩂�A�t�H���_�����L�[��COM�|�[�g�����Ђ��ς�

	// �f�o�C�X���擾 COMPORT
	HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_COMPORT, NULL, NULL, (DIGCF_PRESENT | DIGCF_DEVICEINTERFACE));

	SP_DEVINFO_DATA deviceInfoData = { sizeof(SP_DEVINFO_DATA) };
	for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &deviceInfoData); ++i) {
		char buffer[512];
		DWORD buflen = 0;
		SetupDiGetDeviceInstanceIdA(hDevInfo, &deviceInfoData, (char*)buffer, sizeof(buffer), &buflen);
		std::string strBuffer = std::string(buffer);
		if (strBuffer.find(strFolderID) == std::string::npos) continue;

		// ����
		//// COM�|�[�g�ԍ����擾
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
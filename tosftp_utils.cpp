#include "tosftp_utils.h"

void deleteSpacesFromString(wchar_t* str)
{
	size_t len = wcslen(str);
	for (unsigned int i = 0; i < len; i++) { // Deleting from the beginning
		if (str[i] != L' ') {
			break;
		}
		deleteCharFromString(str, 0);
		len--;
	}

	for (int i = len - 1; i >= 0; i--) { // Deleting from the end
		if (str[i] != L' ') {
			break;
		}
		deleteCharFromString(str, i);
		len--;
	}

	for (unsigned int i = len - 1; i > 0; i--) { // Deleting before ","
		if (str[i - 1] == L' ' && str[i] == L',') {
			deleteCharFromString(str, i - 1);
			len--;
		}
	}

	for (unsigned int i = 1; i < len; ) { // Deleting after ","
		if (str[i - 1] == L',' && str[i] == L' ') {
			deleteCharFromString(str, i);
			len--;
		}
		else {
			i++;
		}
	}
}


bool isEmptyString(wchar_t* str, bool comma_is_empty_char)
{
	for (unsigned int i = 0; i < wcslen(str); i++) {
		if (str[i] != L' ' && str[i] != L'\r' && str[i] != L'\n') {
			return false;
		}
		if( str[i] == L',' && !comma_is_empty_char) {
			return false;
		}
	}
	return true;
}


void deleteCharFromString(wchar_t* str, int pos)
{
	size_t len = wcslen(str);

	for (unsigned int i = pos + 1; i < len; i++) {
		str[i - 1] = str[i];
	}
	str[len - 1] = L'\x0';
}


void substituteCharInString(wchar_t*str, wchar_t charToFind, wchar_t charToReplaceWith)
{
	for (unsigned int i = 0; i < wcslen(str); i++) {
		if (str[i] == charToFind) {
			str[i] = charToReplaceWith;
		}
	}
}



wchar_t *getPtrToFileName(wchar_t* path)
{
	wchar_t *ptr = &path[0];

	size_t len = wcslen(path);
	for (int i = len - 2; i >= 0; i--) { // Starting from the end...
		if ( (path[i] == L'\\' || path[i] == L'/') && (path[i+1] != L'\\' && path[i+1] != L'/') ) {
			ptr = &path[i+1];
			break;
		}
	}
	return ptr;
}


void appendDirectoryNameWithEndingSlash(wchar_t *dirName, wchar_t slash)
{
	int dirNameLen = wcslen(dirName);
	if (dirNameLen > 0) {
		if (dirName[dirNameLen - 1] != slash) {
			dirName[dirNameLen] = slash;
			dirName[dirNameLen + 1] = L'\x0';
		}
	}
}


void toLower( wchar_t *s ) {
	for( int i = 0 ; i < wcslen(s) ; i++ ) {
		s[i] = towlower(s[i]);
	}
}


int decrypt(char *src, char *dst1b) {
	static wchar_t dst[PROFILE_STRING_BUFFER + 1];
	const char *xorkey1b= "_23ken08SPIDER1970&%_23ken08SPIDER1970&%\0";
	int xorkey1bLen = strlen(xorkey1b);
	wchar_t *xorkey = (wchar_t *)xorkey1b;
	int xorkeyLen = (xorkey1bLen-1)/2;

	int passwordLength = strlen(src);
	if (passwordLength % 4) {
		return -1;
	}

	char symbolBuffer[5];
	symbolBuffer[4] = '\x0';
	
	for (int iSrc = 0, iDst = 0; iSrc < passwordLength ; iSrc += 4, iDst++) {
		symbolBuffer[0] = src[iSrc + 0];
		symbolBuffer[1] = src[iSrc + 1];
		symbolBuffer[2] = src[iSrc + 2];
		symbolBuffer[3] = src[iSrc + 3];
		unsigned short dec;
		int status = sscanf(symbolBuffer, "%hx", &dec);
		//cout << symbolBuffer << ", dec=" << dec << endl;
		if (status != 1) {
			return -1;
		}
		if( iDst < xorkeyLen ) {
			dst[iDst] = (wchar_t)(dec ^ (unsigned short)xorkey[iDst]);			
		} else {
			dst[iDst] = (wchar_t)(dec);						
		}
	}
	dst[passwordLength/4] = L'\x0';
	
	char default_char = '?';
	WideCharToMultiByte(CP_ACP, 0, dst, -1, dst1b, PROFILE_STRING_BUFFER, &default_char, NULL);
	return 0;
}

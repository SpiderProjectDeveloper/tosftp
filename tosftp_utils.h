#ifndef __TOSFTP
#define __TOSFTP

	void deleteSpacesFromString(wchar_t* str);
	bool isEmptyString(wchar_t* str, bool comma_is_empty_char=false);
	void deleteCharFromString(wchar_t* str, int pos);
	void substituteCharInString(wchar_t*str, wchar_t charToFind, wchar_t charToReplaceWith);
	wchar_t *getPtrToFileName(wchar_t* path);
	void appendDirectoryNameWithEndingSlash(wchar_t *dirName, wchar_t slash);
	void toLower( wchar_t *s );
	int decrypt(char *src, char *dst1b);

#endif
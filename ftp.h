// File transfer via SSH
#ifndef __FTP_H
#define __FTP_H

#define FTP_ERROR_Ok 0
#define FTP_ERROR -1

#define FTP_ERROR_FAILED_TO_OPEN_INTERNET	-100
#define FTP_ERROR_FAILED_TO_CONNECT		-101

#define FTP_ERROR_TOO_LONG_CREDENTIALS		-150

#define FTP_ERROR_FAILED_TO_READ_LOCAL		-200
#define FTP_ERROR_FAILED_TO_READ_REMOTE		-201
#define FTP_ERROR_FAILED_TO_WRITE_LOCAL		-202
#define FTP_ERROR_FAILED_TO_WRITE_REMOTE	-203
#define FTP_ERROR_FAILED_TO_WRITE_REMOTE_DUE_TO_SUBDIR_ERROR 				-204

#define FTP_ERROR_FAILED_TO_DELETE_REMOTE	-300

// Uploads a file to a server. Returns negative value if failed, 0 if ok.
// The connection credentials must be set earlier...
int ftpUpload(char *srcFileName,					// A file to transfer to a server
	char *dstFileName, 								// A name for the file when it is stored at the server
	char *dstDirectory, 							// A directory to transfer the file into. For Linux servers starts with '/'
	bool createDstDirIfNotExists);

// Downloads a file from a server. Returns negative value if failed, 0 if ok.
// The connection credentials must be set earlier...
int ftpDownload( char *dstFileName, 				// A file name to save the downloaded file under 
	char *srcFileName, 								// A file to download
	char *srcDirectory); 							// The directory to find the file at the server

int ftpDelete(char *dstFileName, 
	char *dstDirectory );

int ftpDir( char *dstFileMask,       // A file mask to read the list of files with
	char *dstDirectory, 				// A directory to read the list of files from  
	std::string &dest ); 				// The list of files, comma separated
	
// Test is a file exists at a server. "1" - yes, "0" - no, "-1" - error.
// The connection credentials must be set earlier...
int ftpTest( char *fileName, 					// A file name to test
	char *directory, 							// A server directory to test in
  	unsigned long int *size );					// If not NULL receives the size of file in bytes

// 
int ftpSetCredentials(char *server, char *user, char *password, int);

int ftpInit( void ); // Must be called before doing anything else...

void ftpClose( bool resetErrors=true ); // Must be called when all transfers are finished...

int ftpGetLastError( int *ftpErrorCode, 		// 
	DWORD *winInetErrorCode, 						//
	char *winInetErrorText );						//

#endif

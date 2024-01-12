// File transfer via SSH
#ifndef __SFTP_H
#define __SFTP_H

#define SFTP_ERROR_Ok 0
#define SFTP_ERROR -1

#define SFTP_ERROR_FAILED_TO_CREATE_SSH_SESSION		-100
#define SFTP_ERROR_FAILED_TO_CONNECT			-101
#define SFTP_ERROR_FAILED_TO_AUTHORIZE			-102
#define SFTP_ERROR_FAILED_TO_CREATE_SFTP_SESSION	-103

#define SFTP_ERROR_TOO_LONG_CREDENTIALS		-150

#define SFTP_ERROR_FAILED_TO_READ_LOCAL		-200
#define SFTP_ERROR_FAILED_TO_READ_REMOTE	-201
#define SFTP_ERROR_FAILED_TO_WRITE_LOCAL	-202
#define SFTP_ERROR_FAILED_TO_WRITE_REMOTE	-203
#define SFTP_ERROR_FAILED_TO_WRITE_REMOTE_DUE_TO_SUBDIR_ERROR 				-204

#define SFTP_ERROR_FAILED_TO_DELETE_REMOTE	-300

// Uploads a file to a server. Returns negative value if failed, 0 if ok.
// The connection credentials must be set earlier...
int sftpUpload( char *srcFileName,					// A file to transfer to a server
	char *dstFileName, 						// A name for the file when it is stored at the server
	char *dstDirectory, 						// A directory to transfer the file into. For Linux servers starts with '/'
	bool createDstDirIfNotExists);					// Create destination directory if not exists
// Downloads a file from a server. Returns negative value if failed, 0 if ok.
// The connection credentials must be set earlier...
int sftpDownload( char *dstFileName, 				// A file name to save the downloaded file under 
	char *srcFileName, 								// A file to download
	char *srcDirectory); 							// The directory to find the file at the server

int sftpDir( char *dstFileMask,       // A file mask to read the list of files with
	char *dstDirectory, 				// A directory to read the list of files from  
	std::string &dest ); 				// The list of files, comma separated

int sftpDelete(char *dstFileName, 
	char *dstDirectory);
	
	// Test is a file exists at a server. "1" - yes, "0" - no, "-1" - error.
// The connection credentials must be set earlier...
int sftpTest( char *fileName, 					// A file name to test
	char *directory, 							// A server directory to test in
  	unsigned long int *size );					// If not NULL receives the size of file in bytes
				// If not NULL, will be assigned with a size of the file in bytes

// 
int sftpSetCredentials(char *server, char *user, char *password, int port);

int sftpInit( void ); // Must be called before doing anything else...

void sftpClose( bool resetErrors=true ); // Must be called when all transfers are finished...

int sftpGetLastError( int *sftpErrorCode, 		// 
	int *sshErrorCode, 						//
	char *sshErrorText );						//

#endif

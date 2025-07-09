/*
===========================================================================

Doom 3 GPL Source Code
Copyright (C) 1999-2011 id Software LLC, a ZeniMax Media company. 

This file is part of the Doom 3 GPL Source Code (?Doom 3 Source Code?).  

Doom 3 Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/

#include "../idlib/precompiled.h"
#include "../sys/sys_local.h"
#pragma hdrstop

#include "TypeInfoGen.h"

#define SOURCE_CODE_BASE_FOLDER			"neo"

idSession *			session = NULL;
idDeclManager *		declManager = NULL;
idEventLoop *		eventLoop = NULL;

int idEventLoop::JournalLevel( void ) const { return 0; }

/*
==============================================================

	idCommon

==============================================================
*/

#define STDIO_PRINT( pre, post )	\
	va_list argptr;					\
	va_start( argptr, fmt );		\
	printf( pre );					\
	vprintf( fmt, argptr );			\
	printf( post );					\
	va_end( argptr )


class idCommonLocal : public idCommon {
public:
							idCommonLocal( void ) {}

	virtual void			Init(int argc, const char* const* argv, const char* cmdline) {}
	virtual void			Shutdown( void ) {}
	virtual bool		  IsShuttingDown() const { return false; }
	virtual	void			CreateMainMenu() {}
	virtual void			Quit( void ) {}
	virtual bool			IsInitialized( void ) const { return true; }
	virtual void			Frame( void ) {}
	virtual void			UpdateScreen(bool captureToImage) {}
	virtual void			UpdateLevelLoadPacifier() {}
	virtual void			StartupVariable(const char* match) {}
	virtual void			GUIFrame( bool execCmd, bool network  ) {}
	virtual void			Async( void ) {}
	virtual void			StartupVariable( const char *match, bool once ) {}
	virtual void			InitTool( const toolFlag_t tool, const idDict *dict ) {}
	virtual void			ActivateTool( bool active ) {}
	virtual void			WriteConfigToFile( const char *filename ) {}
	virtual void			WriteFlaggedCVarsToFile( const char *filename, int flags, const char *setCmd ) {}
	virtual void			BeginRedirect( char *buffer, int buffersize, void (*flush)( const char * ) ) {}
	virtual void			EndRedirect( void ) {}
	virtual void			SetRefreshOnPrint( bool set ) {}
	virtual void			Printf( const char *fmt, ... ) { STDIO_PRINT( "", "" ); }
	virtual void			VPrintf( const char *fmt, va_list arg ) { vprintf( fmt, arg ); }
	virtual void			DPrintf( const char *fmt, ... ) { /*STDIO_PRINT( "", "" );*/ }
	virtual void			Warning( const char *fmt, ... ) { STDIO_PRINT( "WARNING: ", "\n" ); }
	virtual void			DWarning( const char *fmt, ...) { /*STDIO_PRINT( "WARNING: ", "\n" );*/ }
	virtual void			PrintWarnings( void ) {}
	virtual void			ClearWarnings( const char *reason ) {}
	virtual void			Error( const char *fmt, ... ) { STDIO_PRINT( "ERROR: ", "\n" ); exit(0); }
	virtual void			FatalError( const char *fmt, ... ) { STDIO_PRINT( "FATAL ERROR: ", "\n" ); exit(0); }
	virtual const idLangDict *GetLanguageDict() { return NULL; }
	virtual const char *	KeysFromBinding( const char *bind ) { return NULL; }
	virtual const char *	BindingFromKey( const char *key ) { return NULL; }
	virtual int				ButtonState( int key ) { return 0; }
	virtual int				KeyState( int key ) { return 0; }
	virtual bool				IsMultiplayer() { return false; }
	virtual bool				IsServer() { return false; }
	virtual bool				IsClient() { return false; }
	virtual bool				GetConsoleUsed() { return false; }
	virtual int					GetSnapRate() { return -1; }
	virtual void				NetReceiveReliable(int peer, int type, idBitMsg& msg) {}
	virtual void				NetReceiveSnapshot(class idSnapShot& ss) {}
	virtual void				NetReceiveUsercmds(int peer, idBitMsg& msg) {}
	virtual	bool				ProcessEvent(const sysEvent_t* event) { return false; }
	virtual bool				LoadGame(const char* saveName) { return false; }
	virtual bool				SaveGame(const char* saveName) { return false; }
	virtual idDemoFile* ReadDemo() { return NULL; }
	virtual idDemoFile* WriteDemo() { return NULL; }
	virtual idGame* Game() { return NULL; }
	virtual idRenderWorld* RW() { return NULL; }
	virtual idSoundWorld* SW() { return NULL; }
	virtual idSoundWorld* MenuSW() { return NULL; }
	virtual idSession* Session() { return NULL; }
	virtual idCommonDialog& Dialog() { return idCommonDialog(); }
	virtual void				OnSaveCompleted(idSaveLoadParms& parms) {}
	virtual void				OnLoadCompleted(idSaveLoadParms& parms) {}
	virtual void				OnLoadFilesCompleted(idSaveLoadParms& parms) {}
	virtual void				OnEnumerationCompleted(idSaveLoadParms& parms) {}
	virtual void				OnDeleteCompleted(idSaveLoadParms& parms) {}
	virtual void				TriggerScreenWipe(const char* _wipeMaterial, bool hold) {}
	virtual void				OnStartHosting(idMatchParameters& parms) {}
	virtual int					GetGameFrame() { return -1; }
	virtual void				LaunchExternalTitle(int titleIndex, int device, const lobbyConnectInfo_t* const connectInfo) {}
	virtual void				InitializeMPMapsModes() {}
	virtual const idStrList& GetModeList() const { return {}; }
	virtual const idStrList& GetModeDisplayList() const { return {}; }
	virtual const idList<mpMap_t>& GetMapList() const { return {}; }
	virtual void				ResetPlayerInput(int playerIndex) {}
	virtual bool				JapaneseCensorship() const { return false; }
	virtual void				QueueShowShell() {}
	virtual currentGame_t		GetCurrentGame() const { return {}; }
	virtual void				SwitchToGame(currentGame_t newGame) {}
};

idCVar com_developer( "developer", "0", CVAR_BOOL|CVAR_SYSTEM, "developer mode" );

idCommonLocal		commonLocal;
idCommon *			common = &commonLocal;

/*
==============================================================

	idSys

==============================================================
*/

void			Sys_Mkdir( const char *path ) {}
ID_TIME_T			Sys_FileTimeStamp( FILE *fp ) { return 0; }

#ifdef _WIN32

#include <io.h>
#include <direct.h>

const char *Sys_Cwd( void ) {
	static char cwd[1024];

	_getcwd( cwd, sizeof( cwd ) - 1 );
	cwd[sizeof( cwd ) - 1] = 0;

	/*int i = idStr::FindText( cwd, CD_BASEDIR, false );
	if ( i >= 0 ) {
		cwd[i + strlen( CD_BASEDIR )] = '\0';
	}*/

	return cwd;
}

const char *Sys_DefaultCDPath( void ) {
	return "";
}

const char *Sys_DefaultBasePath( void ) {
	return Sys_Cwd();
}

const char *Sys_DefaultSavePath( void ) {
	return cvarSystem->GetCVarString( "fs_basepath" );
}

const char *Sys_EXEPath( void ) {
	return "";
}

int Sys_ListFiles( const char *directory, const char *extension, idStrList &list ) {
	idStr		search;
	struct _finddata_t findinfo;
	int			findhandle;
	int			flag;

	if ( !extension) {
		extension = "";
	}

	// passing a slash as extension will find directories
	if ( extension[0] == '/' && extension[1] == 0 ) {
		extension = "";
		flag = 0;
	} else {
		flag = _A_SUBDIR;
	}

	sprintf( search, "%s\\*%s", directory, extension );

	// search
	list.Clear();

	findhandle = _findfirst( search, &findinfo );
	if ( findhandle == -1 ) {
		return -1;
	}

	do {
		if ( flag ^ ( findinfo.attrib & _A_SUBDIR ) ) {
			list.Append( findinfo.name );
		}
	} while ( _findnext( findhandle, &findinfo ) != -1 );

	_findclose( findhandle );

	return list.Num();
}

#else

const char *	Sys_DefaultCDPath( void ) { return ""; }
const char *	Sys_DefaultBasePath( void ) { return ""; }
const char *	Sys_DefaultSavePath( void ) { return ""; }
int				Sys_ListFiles( const char *directory, const char *extension, idStrList &list ) { return 0; }

#endif

/*
==============
idSysLocal stub
==============
*/
void			idSysLocal::DebugPrintf( const char *fmt, ... ) {}
void			idSysLocal::DebugVPrintf( const char *fmt, va_list arg ) {}

double			idSysLocal::GetClockTicks( void ) { return 0.0; }
double			idSysLocal::ClockTicksPerSecond( void ) { return 1.0; }
cpuid_t			idSysLocal::GetProcessorId( void ) { return (cpuid_t)0; }
const char *	idSysLocal::GetProcessorString( void ) { return ""; }
const char *	idSysLocal::FPU_GetState( void ) { return ""; }
bool			idSysLocal::FPU_StackIsEmpty( void ) { return true; }
void			idSysLocal::FPU_SetFTZ( bool enable ) {}
void			idSysLocal::FPU_SetDAZ( bool enable ) {}

bool			idSysLocal::LockMemory( void *ptr, int bytes ) { return false; }
bool			idSysLocal::UnlockMemory( void *ptr, int bytes ) { return false; }

void			idSysLocal::GetCallStack( address_t *callStack, const int callStackSize ) { memset( callStack, 0, callStackSize * sizeof( callStack[0] ) ); }
const char *	idSysLocal::GetCallStackStr( const address_t *callStack, const int callStackSize ) { return ""; }
const char *	idSysLocal::GetCallStackCurStr( int depth ) { return ""; }
void			idSysLocal::ShutdownSymbols( void ) {}

int				idSysLocal::DLL_Load( const char *dllName ) { return 0; }
void *			idSysLocal::DLL_GetProcAddress( int dllHandle, const char *procName ) { return NULL; }
void			idSysLocal::DLL_Unload( int dllHandle ) { }
void			idSysLocal::DLL_GetFileName( const char *baseName, char *dllName, int maxLength ) { }

sysEvent_t		idSysLocal::GenerateMouseButtonEvent( int button, bool down ) { sysEvent_t ev; memset( &ev, 0, sizeof( ev ) ); return ev; }
sysEvent_t		idSysLocal::GenerateMouseMoveEvent( int deltax, int deltay ) { sysEvent_t ev; memset( &ev, 0, sizeof( ev ) ); return ev; }

void			idSysLocal::OpenURL( const char *url, bool quit ) { }
void			idSysLocal::StartProcess( const char *exeName, bool quit ) { }

void			idSysLocal::FPU_EnableExceptions( int exceptions ) { }

idSysLocal		sysLocal;
idSys *			sys = &sysLocal;

// Various stubs

idCVar com_productionMode("com_productionMode", "0", CVAR_SYSTEM | CVAR_BOOL, "0 - no special behavior, 1 - building a production build, 2 - running a production build");

sysFolder_t Sys_IsFolder(const char* path) {
	struct _stat buffer;
	if (_stat(path, &buffer) < 0) {
		return FOLDER_ERROR;
	}
	return (buffer.st_mode & _S_IFDIR) != 0 ? FOLDER_YES : FOLDER_NO;
}

bool Sys_Rmdir(const char* path) {
	return _rmdir(path) == 0;
}

ID_TIME_T Sys_FileTimeStamp(idFileHandle fp) {
	FILETIME writeTime;
	GetFileTime(fp, NULL, NULL, &writeTime);

	/*
		FILETIME = number of 100-nanosecond ticks since midnight
		1 Jan 1601 UTC. time_t = number of 1-second ticks since
		midnight 1 Jan 1970 UTC. To translate, we subtract a
		FILETIME representation of midnight, 1 Jan 1970 from the
		time in question and divide by the number of 100-ns ticks
		in one second.
	*/

	SYSTEMTIME base_st = {
		1970,   // wYear
		1,      // wMonth
		0,      // wDayOfWeek
		1,      // wDay
		0,      // wHour
		0,      // wMinute
		0,      // wSecond
		0       // wMilliseconds
	};

	FILETIME base_ft;
	SystemTimeToFileTime(&base_st, &base_ft);

	LARGE_INTEGER itime;
	itime.QuadPart = reinterpret_cast<LARGE_INTEGER&>(writeTime).QuadPart;
	itime.QuadPart -= reinterpret_cast<LARGE_INTEGER&>(base_ft).QuadPart;
	itime.QuadPart /= 10000000LL;
	return itime.QuadPart;
}

const char* sysLanguageNames[] = {
	ID_LANG_ENGLISH, ID_LANG_FRENCH, ID_LANG_ITALIAN, ID_LANG_GERMAN, ID_LANG_SPANISH, ID_LANG_JAPANESE, NULL
};

const int numLanguages = sizeof(sysLanguageNames) / sizeof sysLanguageNames[0] - 1;

int Sys_NumLangs() {
	return numLanguages;
}

// get language name by index
const char* Sys_Lang(int idx) {
	if (idx >= 0 && idx < numLanguages) {
		return sysLanguageNames[idx];
	}
	return "";
}

/*
==============================================================

	main

==============================================================
*/

int main( int argc, char** argv ) {
	idStr fileName, sourcePath;
	idTypeInfoGen *generator;

	idLib::common = common;
	idLib::cvarSystem = cvarSystem;
	idLib::fileSystem = fileSystem;
	idLib::sys = sys;

	idLib::Init();
	cmdSystem->Init();
	cvarSystem->Init();
	idCVar::RegisterStaticVars();
	fileSystem->Init();

	generator = new idTypeInfoGen;

	if ( argc > 1 ) {
		sourcePath = idStr( "../" SOURCE_CODE_BASE_FOLDER "/" ) + argv[1];
	} else {
		sourcePath = "../" SOURCE_CODE_BASE_FOLDER "/game";
	}

	if ( argc > 2 ) {
		fileName = idStr( "../" SOURCE_CODE_BASE_FOLDER "/" ) + argv[2];
	} else {
		fileName = "../" SOURCE_CODE_BASE_FOLDER "/game/gamesys/GameTypeInfo.h";
	}

	if ( argc > 3 ) {
		for ( int i = 3; i < argc; i++ ) {
			generator->AddDefine( argv[i] );
		}
	} else {
		generator->AddDefine( "__cplusplus" );
		generator->AddDefine( "GAME_DLL" );
		generator->AddDefine( "ID_TYPEINFO" );
	}

	generator->CreateTypeInfo( sourcePath );
	generator->WriteTypeInfo( fileName );

	delete generator;

	fileName.Clear();
	sourcePath.Clear();

	fileSystem->Shutdown( false );
	cvarSystem->Shutdown();
	cmdSystem->Shutdown();
	idLib::ShutDown();

	return 0;
}

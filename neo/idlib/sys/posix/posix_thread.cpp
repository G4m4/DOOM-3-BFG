/*
===========================================================================

Doom 3 BFG Edition GPL Source Code
Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company. 

This file is part of the Doom 3 BFG Edition GPL Source Code ("Doom 3 BFG Edition Source Code").  

Doom 3 BFG Edition Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 BFG Edition Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 BFG Edition Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 BFG Edition Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 BFG Edition Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/
#pragma hdrstop
#include "../../precompiled.h"

/*
================================================================================================
================================================================================================
*/

/*
========================
Sys_SetThreadName
========================
*/
void Sys_SetThreadName( uintptr_t threadID, const char * name ) {
#if defined(ID_PC_LINUX)
	pthread_setname_np(threadID, name);
#elif defined(ID_MAC)
  // MacOS only allows to set the name for the current thread
  if(threadID == Sys_GetCurrentThreadID()) {
    pthread_setname_np(name);
  }
#else
#error Unknown platform!
#endif
}

/*
========================
Sys_SetCurrentThreadName
========================
*/
void Sys_SetCurrentThreadName( const char * name ) {
	Sys_SetThreadName( Sys_GetCurrentThreadID(), name );
}

/*
========================
Sys_Createthread
========================
*/
uintptr_t Sys_CreateThread( xthread_t function, void *parms, xthreadPriority priority, const char *name, core_t core, int stackSize, bool suspended ) {

	pthread_attr_t attr;
	pthread_attr_init( &attr );
	

	if( pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE ) != 0 )
	{
		idLib::common->FatalError( "ERROR: pthread_attr_setdetachstate %s failed\n", name );
		return 0;
	}
	if( pthread_attr_setstacksize( &attr, stackSize ) != 0 )
	{
		idLib::common->FatalError( "ERROR: pthread_attr_setstacksize %s failed\n", name );
		return 0;
	}
#if defined(ID_PC_LINUX)
	// Thanks to https://eli.thegreenplace.net/2016/c11-threads-affinity-and-hyperthreading/
	if(core != CORE_ANY) {
		cpu_set_t cpuset;
		CPU_ZERO(&cpuset);
		CPU_SET((int)core, &cpuset);
		if( pthread_attr_setaffinity_np(&attr, sizeof(cpuset), &cpuset) != 0 )
		{
			idLib::common->FatalError( "ERROR: pthread_attr_setaffinity_np %s failed\n", name );
			return 0;
		}
	}

	uintptr_t handle;
	if( pthread_create( &handle, &attr, function, parms ) != 0 )
	{
		idLib::common->FatalError( "ERROR: pthread_create %s failed\n", name );
		return ( uintptr_t )0;
	}
#elif defined(ID_MAC)
  // On MacOS thread affinity is set through a specific API
  // https://developer.apple.com/library/archive/releasenotes/Performance/RN-AffinityAPI/index.html
  // TODO

	uintptr_t handle;
  pthread_t underlying_handle;
	if( pthread_create( &underlying_handle, &attr, function, parms ) != 0 )
	{
		idLib::common->FatalError( "ERROR: pthread_create %s failed\n", name );
		return ( uintptr_t )0;
	}
  handle = (uintptr_t)underlying_handle;
#else
#error Unknown platform!
#endif

	pthread_attr_destroy( &attr );

	Sys_SetThreadName( handle, name );

	// TODO
	// if ( priority == THREAD_HIGHEST ) {
	// 	pthread_setschedprio( handle, THREAD_PRIORITY_HIGHEST );		//  we better sleep enough to do this
	// } else if ( priority == THREAD_ABOVE_NORMAL ) {
	// 	pthread_setschedprio( handle, THREAD_PRIORITY_ABOVE_NORMAL );
	// } else if ( priority == THREAD_BELOW_NORMAL ) {
	// 	pthread_setschedprio( handle, THREAD_PRIORITY_BELOW_NORMAL );
	// } else if ( priority == THREAD_LOWEST ) {
	// 	pthread_setschedprio( handle, THREAD_PRIORITY_LOWEST );
	// }

	return (uintptr_t)handle;
}


/*
========================
Sys_GetCurrentThreadID
========================
*/
uintptr_t Sys_GetCurrentThreadID() {
#if defined (ID_PC_LINUX)
	pthread_self();
#elif defined(ID_MAC)
	(uintptr_t)pthread_self();
#else
#error Unknown platform!
#endif
}

/*
========================
Sys_DestroyThread
========================
*/
void Sys_DestroyThread( uintptr_t threadHandle ) {
	if ( threadHandle == 0 ) {
		return;
	}
#if defined (ID_PC_LINUX)
	pthread_cancel(threadHandle);
#elif defined(ID_MAC)
	pthread_cancel((pthread_t)threadHandle);
#else
#error Unknown platform!
#endif
}

/*
========================
Sys_Yield
========================
*/
void Sys_Yield() {
#if defined (ID_PC_LINUX)
	pthread_yield();
#elif defined(ID_MAC)
  sched_yield();
#else
#error Unknown platform!
#endif
}

/*
================================================================================================

	Signal

================================================================================================
*/

/*
========================
Sys_SignalCreate
========================
*/
void Sys_SignalCreate( signalHandle_t & handle, bool manualReset ) {
	if( pthread_mutex_init(&handle.mutex, NULL) != 0 )
	{
		idLib::common->FatalError( "ERROR: pthread_mutex_init failed\n" );
	}
	if( pthread_cond_init(&handle.cond, NULL) != 0 )
	{
		idLib::common->FatalError( "ERROR: pthread_cond_init failed\n" );
	}
}

/*
========================
Sys_SignalDestroy
========================
*/
void Sys_SignalDestroy( signalHandle_t &handle ) {
	if( pthread_cond_destroy(&handle.cond) != 0 )
	{
		idLib::common->FatalError( "ERROR: pthread_cond_destroy failed\n" );
	}
	if( pthread_mutex_destroy(&handle.mutex) != 0 )
	{
		idLib::common->FatalError( "ERROR: pthread_mutex_destroy failed\n" );
	}
}

/*
========================
Sys_SignalRaise
========================
*/
void Sys_SignalRaise( signalHandle_t & handle ) {
	pthread_mutex_lock(&handle.mutex);
	handle.signaled = true;
	pthread_cond_signal( &handle.cond );
	pthread_mutex_unlock(&handle.mutex);
}

/*
========================
Sys_SignalClear
========================
*/
void Sys_SignalClear( signalHandle_t & handle ) {
	pthread_mutex_lock(&handle.mutex);
	handle.signaled = false;
	pthread_mutex_unlock(&handle.mutex);
}

/*
========================
Sys_SignalWait
========================
*/
bool Sys_SignalWait( signalHandle_t & handle, int timeout ) {

	// Code from Dark Mod
	
	int status;
	pthread_mutex_lock( &handle.mutex );
	if( handle.signaled ) // there is a signal that hasn't been used yet
	{
		if( ! handle.manualReset ) // for auto-mode only one thread may be released - this one.
		{
			handle.signaled = false;
		}	
		status = 0; // success!
	}
	else // we'll have to wait for a signal
	{
		++handle.waiting;
		if( timeout == idSysSignal::WAIT_INFINITE )
		{
			status = pthread_cond_wait( &handle.cond, &handle.mutex );
		}
		else
		{
			timespec ts;
			
			clock_gettime( CLOCK_REALTIME, &ts );
			
			// DG: handle timeouts > 1s better
			ts.tv_nsec += ( timeout % 1000 ) * 1000000; // millisec to nanosec
			ts.tv_sec  += timeout / 1000;
			if( ts.tv_nsec >= 1000000000 ) // nanoseconds are more than one second
			{
				ts.tv_nsec -= 1000000000; // remove one second in nanoseconds
				ts.tv_sec += 1; // add one second to seconds
			}
			// DG end
			status = pthread_cond_timedwait( &handle.cond, &handle.mutex, &ts );
		}
		--handle.waiting;
	}

	pthread_mutex_unlock( &handle.mutex );
	
	assert( status == 0 || ( timeout != idSysSignal::WAIT_INFINITE && status == ETIMEDOUT ) );
	
	return ( status == 0 );
}

/*
================================================================================================

	Mutex

================================================================================================
*/

/*
========================
Sys_MutexCreate
========================
*/
void Sys_MutexCreate( mutexHandle_t & handle ) {
	if( pthread_mutex_init(&handle, NULL) != 0 )
	{
		idLib::common->FatalError( "ERROR: pthread_mutex_init failed\n" );
	}
}

/*
========================
Sys_MutexDestroy
========================
*/
void Sys_MutexDestroy( mutexHandle_t & handle ) {
	if( pthread_mutex_destroy(&handle) != 0 )
	{
		idLib::common->FatalError( "ERROR: pthread_mutex_destroy failed\n" );
	}
}

/*
========================
Sys_MutexLock
========================
*/
bool Sys_MutexLock( mutexHandle_t & handle, bool blocking ) {
	if ( pthread_mutex_trylock( &handle ) != 0 ) {
		if ( !blocking ) {
			return false;
		}
		pthread_mutex_lock( &handle );
	}
	return true;
}

/*
========================
Sys_MutexUnlock
========================
*/
void Sys_MutexUnlock( mutexHandle_t & handle ) {
	pthread_mutex_unlock( & handle );
}

/*
================================================================================================

	Interlocked Integer

================================================================================================
*/

/*
========================
Sys_InterlockedIncrement
========================
*/
interlockedInt_t Sys_InterlockedIncrement( interlockedInt_t & value ) {
	return __sync_add_and_fetch( &value, 1 );
}

/*
========================
Sys_InterlockedDecrement
========================
*/
interlockedInt_t Sys_InterlockedDecrement( interlockedInt_t & value ) {
	return __sync_sub_and_fetch( &value, 1 );
}

/*
========================
Sys_InterlockedAdd
========================
*/
interlockedInt_t Sys_InterlockedAdd( interlockedInt_t & value, interlockedInt_t i ) {
	return __sync_add_and_fetch( &value, i );
}

/*
========================
Sys_InterlockedSub
========================
*/
interlockedInt_t Sys_InterlockedSub( interlockedInt_t & value, interlockedInt_t i ) {
	return __sync_sub_and_fetch( &value, i );
}

/*
========================
Sys_InterlockedExchange
========================
*/
interlockedInt_t Sys_InterlockedExchange( interlockedInt_t & value, interlockedInt_t exchange ) {
	return __sync_val_compare_and_swap( &value, value, exchange );
}

/*
========================
Sys_InterlockedCompareExchange
========================
*/
interlockedInt_t Sys_InterlockedCompareExchange( interlockedInt_t & value, interlockedInt_t comparand, interlockedInt_t exchange ) {
	return __sync_val_compare_and_swap( &value, comparand, exchange );
}

/*
================================================================================================

	Interlocked Pointer

================================================================================================
*/

/*
========================
Sys_InterlockedExchangePointer
========================
*/
void *Sys_InterlockedExchangePointer( void *& ptr, void * exchange ) {
	return __sync_val_compare_and_swap( &ptr, ptr, exchange );
}

/*
========================
Sys_InterlockedCompareExchangePointer
========================
*/
void * Sys_InterlockedCompareExchangePointer( void * & ptr, void * comparand, void * exchange ) {
	return __sync_val_compare_and_swap( &ptr, comparand, exchange );
}

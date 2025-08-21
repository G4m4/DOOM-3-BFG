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
#include "../../idlib/precompiled.h"
#include "stub_localuser.h"

extern idCVar stub_userPersistent;
extern idCVar stub_userOnline;
extern idCVar stub_isInParty;
extern idCVar stub_partyCount;

/*
========================
idLocalUserStub::Init
========================
*/
void idLocalUserStub::Init( int inputDevice_, const char * gamertag_, int numLocalUsers ) {
	if ( numLocalUsers == 1 ) {  // Check for 1, since this is now incremented before we get in here
		// This is the master user
		gamertag = gamertag_;
	} else {
		// On steam, we need to generate a name based off the master user for split-screen users.
		// We use the number of users on the system to generate the name rather than the device
		// number so that it is always consistently "username (2)" for the second player.
		gamertag.Format( "%s (%i)", gamertag_, numLocalUsers );
	}

	inputDevice = inputDevice_;
}

/*
========================
idLocalUserStub::IsProfileReady
========================
*/
bool idLocalUserStub::IsProfileReady() const {
#ifdef _DEBUG
	return stub_userPersistent.GetBool();
#else
	return true;
#endif
}

/*
========================
idLocalUserStub::IsOnline
========================
*/
bool idLocalUserStub::IsOnline() const {
#ifdef _DEBUG
	return stub_userOnline.GetBool();
#else
	return true;
#endif
}

/*
========================
idLocalUserStub::IsInParty
========================
*/
bool idLocalUserStub::IsInParty() const {
#ifdef _DEBUG
	return stub_isInParty.GetBool();
#else
	return false;
#endif
}

/*
========================
idLocalUserStub::GetPartyCount
========================
*/
int idLocalUserStub::GetPartyCount() const {
	// TODO: Implement
#ifdef _DEBUG
	return stub_partyCount.GetInteger();
#else
	return 0;
#endif
}

/*
========================
idLocalUserStub::VerifyUserState
========================
*/
bool idLocalUserStub::VerifyUserState( stubUserState_t & state ) {

	if ( state.inputDevice != inputDevice ) {
		return false;
	}
	return true;
}

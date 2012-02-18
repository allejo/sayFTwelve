/*
Copyright (c) 2011 Vladimir Jimenez
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Author:
Vlad Jimenez (allejo)

Description:
Will automatically kick any player who mentions F12 or some variation of it.

Slash Commands:
N/A

License:
BSD

Version:
1.0 [Codename: Initial Release]
*/

#include "bzfsAPI.h"
#include "plugin_utils.h"

class sayFTwelve : public bz_Plugin
{
	virtual const char* Name (){return "Say F12 See What Happens";}
	virtual void Init ( const char* config);
	virtual void Event(bz_EventData *eventData);
	virtual void Cleanup ();
};

std::string wordList[] = {"f12","f 12","f 1 2","alt+f4","f twelve","f one two","alt+f four","alt + f 4","alt + f4"};

BZ_PLUGIN(sayFTwelve);

void sayFTwelve::Init ( const char* /*commandLine*/ )
{
	Register(bz_eRawChatMessageEvent);
	bz_debugMessage(4,"sayFTwelve plugin loaded");
}

void sayFTwelve::Cleanup(void)
{
	Flush();
	bz_debugMessage(4,"sayFTwelve plugin loaded");
}

void sayFTwelve::Event(bz_EventData *eventData)
{
	switch (eventData->eventType)
	{
		case bz_eRawChatMessageEvent:
		{
			bz_ChatEventData_V1* chat = (bz_ChatEventData_V1*)eventData;
			bz_BasePlayerRecord *chatPlayer = bz_getPlayerByIndex(chat->from);
			
			std::string myChat = bz_tolower(chat->message.c_str());
			
			for (int n=0;n<(sizeof(wordList)/sizeof(wordList[0]));n++)
			{
			    if(myChat.find(wordList[n])!=-1)
				{
					bz_kickUser(chat->from,"There we go, I pressed F12 for you.",1);
					bz_sendTextMessagef(BZ_SERVER,BZ_ALLUSERS,"HUMILIATION! %s was kicked for saying \'%s\'",chatPlayer->callsign.c_str(),myChat.c_str());
				}
			}
			
			bz_freePlayerRecord(chatPlayer);
		}
		break;
		
		default:break; //really? WTF?!
	}
}

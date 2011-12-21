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

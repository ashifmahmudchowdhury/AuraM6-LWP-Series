
/*
    LWP Conter Test

    SPARKtech
    Ashif Mahmud Chowdhury
    www.freelancer.com/u/SPARKtechBD
    sparktech_bd@outlook.com

*/

#include "kernel.h"
#include "widget.h"
#include "button.h"
#include "label.h"
#include "window.h"

#include "LWP.H"

l_ulong AppVersion	= ULONG_ID(0,0,0,1);
char AppName[]		= "Counter";
l_uid	nUID		= "app:counter";
l_uid NeededLibs[]	= { "label","button","window", "" };

#define BTN_START 0x4274
#define BTN_STOP 0x4275
#define MAX_LWP_ID 256

PLabel Counter1;
PLabel Counter2;
PLabel Counter3;
PButton Button1;
PButton Button2;
PButton Button3;

l_bool IsCounter1Start = false;
l_bool IsCounter2Start = false;
l_bool IsCounter3Start = false;

int lwpids[MAX_LWP_ID] = {0};

void (*proc)(void *param);

void Count1(void *param);
void Count2(void *param);
void Count3(void *param);
l_bool AppEventHandler(PWidget o, PEvent Event);


void Count3(void *param)
{
	volatile l_long i = 0;
	volatile l_long val = 100;

	DebugMessage("Counter (LWP): Count3 started...");

	while(1)
	{
		val += 1;
		LabelSetText(Counter3,"%d", val);

		for (i = 0;  i < 5000; i++)
		{
			lwpYield();				// manual context switching
		}
	}
}

void Count2(void *param)
{
	volatile l_long i = 0;
	volatile l_long val = 100;

	DebugMessage("Counter (LWP): Count2 started...");

	while(1)
	{
		val += 1;
		LabelSetText(Counter2,"%d", val);

		for (i = 0;  i < 5000; i++)
		{
			lwpYield();				// manual context switching
		}
	}
}


void Count1(void *param)
{
	volatile l_long i = 0;
	volatile l_long val = 100;

	DebugMessage("Counter (LWP): Count1 started...");

	while(1)
	{
		val += 1;
		LabelSetText(Counter1,"%d", val);

		for (i = 0;  i < 5000; i++)
		{
			lwpYield(); 			// manual context switching
		}
	}
}

l_bool AppEventHandler(PWidget o, PEvent Event)
{
	l_int id = 0;

	if (Event->Type == EV_MESSAGE)
	{
		switch (Event->Message)
		{
			case BTN_START:
			{
				l_text Start = (char*)strdup("START");
				l_text Stop = (char*)strdup("STOP");
				switch ((int)BUTTON(o)->MessageExtra)
				{
				case 1:
					id = 0;
					proc = Count1;
					break;
				case 2:
					id = 1;
					proc = Count2;
					break;
				case 3:
					id = 2;
					proc = Count3;
					break;
				default:
					break;
				}
				if (!strcmp(BUTTON(o)->Caption, Start))
				{
					ButtonSetCaption(BUTTON(o), Stop);
					if (lwpids[id] == 0)
					{
						lwpids[id] = lwpSpawn(proc, NULL, 1024 * 256, 1, 1);
						if (!lwpids[id])
						{
							DebugMessage("Counter (LWP): Failed to create LWP Threading on Counter %d.", id + 1);
							MessageBox(&Me, "Counter (LWP)", "Failed to create LWP Threading on Counter.", MBB_OK);
							break;
						}
						else
						{
							DebugMessage("Counter (LWP): LWP Thread id: %d has been created for Counter %d...", lwpids[id], id + 1);
						}
						lwpYield();	// manual context switching
					}
					else
					{
						lwpThreadResume(lwpids[id]);
					}

				}
				else
				{
					ButtonSetCaption(BUTTON(o), Start);
					lwpThreadSuspend(lwpids[id]);
				}
				free(Start);
				free(Stop);
				
				return true;
			}
			break;
		
			default:
				break;
		}
	}
    return false;
}

l_int Main (int argc, l_text *argv)
{
    PWindow w = 0;
    PButton b = 0;

    TRect r;

	int offset = 50;

	memset(lwpids, 0, sizeof(int) * MAX_LWP_ID);

    RectAssign(&r, 0, 0, 400, 280);
    w = CreateWindow(&Me, r, "Counter (LWP)", WF_CAPTION | WF_FRAME | WF_MINIMIZE | WF_CENTERED );
    WIDGET(w)->AppEvHdl = &AppEventHandler;
    InsertWidget(WIDGET(DeskTop), WIDGET(w));
    WidgetPreCenter(WIDGET(w));

    WidgetSize(&r, offset, 50, 75, 20);
    Counter1 = CreateLabel(&Me, r, "0");
    WIDGET(Counter1)->BackgroundColor = makecol(250, 250, 250);
    InsertWidget(WIDGET(w), WIDGET(Counter1));

    WidgetSize(&r, 95 + offset, 50, 75, 20);
    Counter2 = CreateLabel(&Me, r, "0");
    WIDGET(Counter2)->BackgroundColor = makecol(250, 250, 250);
    InsertWidget(WIDGET(w), WIDGET(Counter2));

    WidgetSize(&r, 180 + offset, 50, 75, 20);
    Counter3 = CreateLabel(&Me, r, "0");
    WIDGET(Counter3)->BackgroundColor = makecol(250, 250, 250);
    InsertWidget(WIDGET(w), WIDGET(Counter3));

    WidgetSize(&r, offset, 100, 75, 50);
    Button1 = CreateButton(&Me, r, "START", BTN_START);
	WIDGET(Button1)->AppEvHdl = &AppEventHandler;
	Button1->MessageExtra = (void*)1;
    InsertWidget(WIDGET(w), WIDGET(Button1));

    WidgetSize(&r, 95 + offset, 100, 75, 50);
    Button2 = CreateButton(&Me, r, "START", BTN_START);
	WIDGET(Button2)->AppEvHdl = &AppEventHandler;
	Button2->MessageExtra = (void*)2;
    InsertWidget(WIDGET(w), WIDGET(Button2)); 
    
    WidgetSize(&r, 180 + offset, 100, 75, 50);
    Button3 = CreateButton(&Me, r, "START", BTN_START);
	WIDGET(Button3)->AppEvHdl = &AppEventHandler;
	Button3->MessageExtra = (void*)3;
    InsertWidget(WIDGET(w), WIDGET(Button3));

    WidgetDrawAll(WIDGET(w));
    

    return true;
}

void Close (void)
{
	/* TODO */
	
	/* This Close event is not working in AuraM6 on Window Close */
	
	DebugMessage("Counter (LWP): Closing Counter Application...");
	
	/* 	Must be stop all counters before closing the app window */

	/* 	Must be Kill or Suspend the LWP threads before closing the Application,
		because we have to free all the resources used by LWP */
	

}


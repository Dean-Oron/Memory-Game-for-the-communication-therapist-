#include "bass.h"
#include <utility.h>
#include "toolbox.h"
#include <cvirte.h>
#include <userint.h>
#include <ansi_c.h>
#include "Memory_Game.h"

typedef  struct
{
	char firstName[70], lastName[70],id[10], address[20],phone[12],parent[12];
	double age;
	int  male, female, score;
} details ;

details  info;

static int panel_1, panel_2,panel_3, panel_4, panel_5,panel_6,panel_7;

char scores[100][100];
static const char snd_folder[] = "Sounds\\";
static const char snd_suffix[] = ".mp3";
char pic_path1[100],pic_path2[100],pic_path3[100],pic_path4[100], snd_path[70],first[];
FILE *score_file;
int Time, flag=0;
int i,c,d,s, counter=10, width, height;
int A=0;
int bmp[425];
int report_bitmap;
int  bg_bitmap,memory_bitmap,noWorries_bitmap;
int makom_hituh, ofen_hituh,koliut,taam,izur;
char pics_path[30];
int s_game, m_game;
//int maxQuestion  =30;
int right_ans[30], counter_ans=0,right=0, chosen_words[400], counter_chosen=0;

int returnAnswerIndex=-1;

HSTREAM snd_open, snd_applause, snd_wrong,snd_wrong_ans, snd_correct;
HSTREAM sounds[425];

void initialize()
{
	GetCtrlAttribute (panel_2, PANEL_2_CANVAS, ATTR_WIDTH, &width);
	GetCtrlAttribute (panel_2, PANEL_2_CANVAS, ATTR_HEIGHT, &height);

	BASS_Init( -1,44100, 0,0,NULL);
	snd_open = BASS_StreamCreateFile(FALSE,"Sounds\\Open_Song.mp3",0,0,0);
	snd_applause =  BASS_StreamCreateFile(FALSE,"Sounds\\applause.mp3",0,0,0);
	snd_wrong =  BASS_StreamCreateFile(FALSE,"Sounds\\wrong.mp3",0,0,0);
	snd_wrong_ans= BASS_StreamCreateFile(FALSE,"Sounds\\Wrong Answer Sound Effect.mp3",0,0,0);
	snd_correct= BASS_StreamCreateFile(FALSE,"Sounds\\Correct-answer.mp3",0,0,0);

	GetBitmapFromFile ("Words_Pictures\\background.jpg", &bg_bitmap);
	GetBitmapFromFile ("Words_Pictures\\Memory.png", &memory_bitmap);
	GetBitmapFromFile ("Words_Pictures\\No worries mate.png", &noWorries_bitmap);
	SetPanelSize (panel_1, 700, 1000);
	SetPanelSize (panel_2, 700, 1000);
	SetPanelSize (panel_3, 700, 1000);
	info.score=0;

	int pic_counter=1;
	for(int i=1 ; i<=384 ; i++)
	{
		sprintf(pics_path,"Words_Pictures\\%d.PNG",i);
		GetBitmapFromFile (pics_path, &bmp[i]);
	}

	for(i=1; i<=192; i++)
	{
		for(int j=1; j<=2; j++)
		{
			if(j==1)
				SetTableCellVal (panel_6, PANEL_6_WORDS_TABLE, MakePoint(j,i),bmp[pic_counter]);
			else
				SetTableCellVal (panel_6, PANEL_6_WORDS_TABLE, MakePoint(j,i),bmp[pic_counter+1]);

		}
		pic_counter=pic_counter+2;
	}

	BASS_ChannelPlay(snd_open,TRUE);

	CanvasDrawBitmap (panel_2, PANEL_2_CANVAS, bg_bitmap, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);

	for(i=1 ; i<=424 ;  i++)
	{
		//Creating sound files path strings array

		sprintf(snd_path, "%s%d%s",snd_folder,i,snd_suffix);

		//Initialize sound files to HSTREAM variables!
		sounds[i] = BASS_StreamCreateFile(FALSE,snd_path,0,0,0);
	}

}

void terminate()
{

	BASS_StreamFree(snd_open);
	BASS_StreamFree(snd_applause);

	for(i=1; i<424; i++)
		BASS_StreamFree(sounds[i]);
}



int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panel_1 = LoadPanel (0, "Memory_Game.uir", PANEL)) < 0)
		return -1;
	if ((panel_2 = LoadPanel (0, "Memory_Game.uir", PANEL_2)) < 0)
		return -1;
	if ((panel_3 = LoadPanel (0, "Memory_Game.uir", PANEL_3)) < 0)
		return -1;
	if ((panel_4 = LoadPanel (0, "Memory_Game.uir", PANEL_4)) < 0)
		return -1;
	if ((panel_5 = LoadPanel (0, "Memory_Game.uir", PANEL_5)) < 0)
		return -1;
	if ((panel_6 = LoadPanel (0, "Memory_Game.uir", PANEL_6)) < 0)
		return -1;

	if ((panel_7 = LoadPanel (0, "Memory_Game.uir", PANEL_7)) < 0)
		return -1;

	srand(time(0));
	initialize();
	SetPanelAttribute (panel_1, ATTR_LEFT, VAL_AUTO_CENTER);
	SetPanelAttribute (panel_2, ATTR_TOP, VAL_AUTO_CENTER);
	DisplayPanel (panel_1);
	RunUserInterface ();
	terminate();
	DiscardPanel (panel_1);
	DiscardPanel (panel_2);
	DiscardPanel (panel_3);
	DiscardPanel (panel_4);
	DiscardPanel (panel_5);
	DiscardPanel (panel_6);

	return 0;
}

void SaveScore()
{

	score_file = fopen("scores.txt", "a");

	fprintf(score_file, "%s\t%s\t%d\n",info.firstName,info.lastName,info.score);

	fclose(score_file);

}

void LoadScore()
{

	FILE *fp;
	char line[100];
	fp = fopen("scores.txt","r");
	int score_counter =0;
	int i, d;
	while (fgets (line, 99, fp) != NULL)
	{
		strncpy(scores[score_counter],line,100);
		score_counter++;
	}

	//Insertion Sorting  (Like we demonstrated in class :) )

	int cur_score =0, prev_score=0;

	int score1;

	char fname[10], lname[10],tmps[100];
	for(i=20; i>=0; i--)
	{
		d=i;
		sscanf(scores[d], "%s\t%s\t%d", fname, lname, &cur_score);

		if (d<20)
			sscanf(scores[d+1], "%s\t%s\t%d", fname, lname, &prev_score);

		while(d<20   &&  cur_score<prev_score)
		{
			strncpy(tmps , scores[d],100);
			strncpy(scores[d],scores[d+1],100);
			strncpy(scores[d+1],tmps,100);
			d++;
			sscanf(scores[d], "%s\t%s\t%d", fname, lname, &cur_score);
			if (scores[d+1][0]==0)
				prev_score =0;
			else
				sscanf(scores[d+1], "%s\t%s\t%d", fname, lname, &prev_score);
		}

	}
	for ( int f=0; f<6; f++)
	{
		sscanf(scores[f]	, "%s\t%s\t%d", fname, lname, &score1)  ;
		sprintf(scores[f], "%s %s score: %d",fname,lname,score1)  ;
	}

	SetCtrlVal (panel_7, PANEL_7_STRING, scores[0]);

	SetCtrlVal (panel_7, PANEL_7_STRING_2, scores[1]);

	SetCtrlVal (panel_7, PANEL_7_STRING_3, scores[2]);

	SetCtrlVal (panel_7, PANEL_7_STRING_4, scores[3]);

	SetCtrlVal (panel_7, PANEL_7_STRING_5, scores[4]);

	SetCtrlVal (panel_7, PANEL_7_STRING_6, scores[5]);


}

int CVICALLBACK exit_panel_1 (int panel, int event, void *callbackData,
							  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
	}
	return 0;
}
int CVICALLBACK exit_panel_2 (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SaveScore();
			LoadScore();
			HidePanel (panel_2);
			SetCtrlAttribute (panel_2, PANEL_2_TIMER, ATTR_ENABLED, 0);

			BASS_ChannelStop(snd_applause);
			BASS_ChannelStop(snd_wrong);
			s_game=0;
			m_game=0;
			BASS_ChannelPlay(snd_open,TRUE);
			info.score=0;

			break;
	}
	return 0;
}
int CVICALLBACK exit_Panel_2 (int panel, int event, void *callbackData,
							  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			SaveScore();
			LoadScore();
			HidePanel (panel_2);
			SetCtrlAttribute (panel_2, PANEL_2_TIMER, ATTR_ENABLED, 0);

			BASS_ChannelStop(snd_applause);
			BASS_ChannelStop(snd_wrong);
			s_game=0;
			m_game=0;
			BASS_ChannelPlay(snd_open,TRUE);
			info.score=0;


			break;
	}
	return 0;
}

int CVICALLBACK exit_panel_3 (int panel, int event, void *callbackData,
							  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			HidePanel (panel_3);
			break;
	}
	return 0;
}

int CVICALLBACK exit_panel_4 (int panel, int event, void *callbackData,
							  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			HidePanel (panel_4);

			break;
	}
	return 0;
}
int CVICALLBACK exit_panel_5 (int panel, int event, void *callbackData,
							  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			HidePanel (panel_5);
			break;
	}
	return 0;
}

int CVICALLBACK exit_panel_6 (int panel, int event, void *callbackData,
							  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			HidePanel (panel_6);

			break;
	}
	return 0;
}

int CVICALLBACK exit_panel_7 (int panel, int event, void *callbackData,
							  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			HidePanel (panel_7);
			break;
	}
	return 0;
}


void Choose_Audio()
{
	int tmp;


// Not in memory game or in memory game buy not in return phase
	counter=10;
	if (s_game ==1 || (m_game ==1 && returnAnswerIndex==-1 ) )
	{
		if(counter_chosen!=0)
		{
			tmp=1+rand()%counter_chosen;
			s=chosen_words[tmp];
		}
		else
			s=1+rand()%384;

		BASS_ChannelPlay(sounds[s],TRUE);
	}
	//in MG and in return phase and not in the end of return phase

	else if(m_game!=0  && returnAnswerIndex!=-1)
	{
		//in memory game and return phase
		s =right_ans[returnAnswerIndex] ;
	}

}
void Choose_Random_Location()
{
	A=1+rand()%4;

	c=1+rand()%384;
	d=1+rand()%384;

	//pic_path1 is the correct answer
	sprintf(pic_path1,"Words_Pictures\\%d.png",s);
	sprintf(pic_path3,"Words_Pictures\\%d.png",c);
	sprintf(pic_path4,"Words_Pictures\\%d.png",d);

	//minimal pair path file
	if(s%2==0)
		sprintf(pic_path2,"Words_Pictures\\%d.png",s-1);

	if(s%2==1)

		sprintf(pic_path2,"Words_Pictures\\%d.png",s+1);



	if(A==1)
	{
		SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_1, ATTR_IMAGE_FILE, pic_path1);
		SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_2, ATTR_IMAGE_FILE, pic_path4);
		SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_3, ATTR_IMAGE_FILE, pic_path3);
		SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_4, ATTR_IMAGE_FILE, pic_path2);
	}
	if(A==2)
	{
		SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_1, ATTR_IMAGE_FILE, pic_path2);
		SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_2, ATTR_IMAGE_FILE, pic_path1);
		SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_3, ATTR_IMAGE_FILE, pic_path3);
		SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_4, ATTR_IMAGE_FILE, pic_path4);
	}
	if(A==3)
	{
		SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_1, ATTR_IMAGE_FILE, pic_path3);
		SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_2, ATTR_IMAGE_FILE, pic_path2);
		SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_3, ATTR_IMAGE_FILE, pic_path1);
		SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_4, ATTR_IMAGE_FILE, pic_path4);
	}
	if(A==4)
	{
		SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_1, ATTR_IMAGE_FILE, pic_path4);
		SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_2, ATTR_IMAGE_FILE, pic_path2);
		SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_3, ATTR_IMAGE_FILE, pic_path3);
		SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_4, ATTR_IMAGE_FILE, pic_path1);
	}
	//Make picture controls visible again
	SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_1, ATTR_VISIBLE, 1);
	SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_2, ATTR_VISIBLE, 1);
	SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_3, ATTR_VISIBLE, 1);
	SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_4, ATTR_VISIBLE, 1);
}


void Analysis()
{

	if (s<=118)
		makom_hituh++;

	if(s>118  && s<=192)
		ofen_hituh++;

	if (s>192  &&  s<=296)
		koliut++ ;

	if (s>296  &&  s<366)
		izur++ ;

	if (s>366  &&  s<380)
		taam++ ;

}

int CVICALLBACK Choosing_func (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	int answer1,answer2,answer3,answer4;
	switch (event)
	{
		case EVENT_COMMIT:

			counter=10;

			GetCtrlVal (panel_2, PANEL_2_PICTUREBUTTON_1, &answer1);
			GetCtrlVal (panel_2, PANEL_2_PICTUREBUTTON_2, &answer2);
			GetCtrlVal (panel_2, PANEL_2_PICTUREBUTTON_3, &answer3);
			GetCtrlVal (panel_2, PANEL_2_PICTUREBUTTON_4, &answer4);

			//answer was right!!!
			if(  (A==1 && answer1==1) ||  (A==2 && answer2==1)  ||   (A==3 && answer3==1)  || (A==4 && answer4==1)   )
			{
				if (s_game==1)
					BASS_ChannelPlay(snd_applause,TRUE);

				//if in MG
				if (m_game==1  )
				{
					//Reach to end of return phase
					if (returnAnswerIndex>0 && returnAnswerIndex+1==counter_ans )
					{
						BASS_ChannelPlay(snd_correct,TRUE);
						info.score++;
						returnAnswerIndex=-1;
					}
					else

						if (returnAnswerIndex==-1 )
						{
							//not in return phase
							BASS_ChannelPlay(snd_applause,TRUE);
							right_ans[counter_ans]=s;
							counter_ans++;


							//Return phase start only after the second correct answer!
							if   (counter_ans>1 )
							{
								//start the return phase

								returnAnswerIndex++;
							}
						}
					//	in return phase
						else
						{
							returnAnswerIndex++;
							BASS_ChannelPlay(snd_correct,TRUE);
							info.score++;
						}
				}

			}


			// Wrong answer was chosen.

			else
			{
				// In return phase
				if (returnAnswerIndex!=-1)

				{
					SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_1, ATTR_VISIBLE, 0);
					SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_2, ATTR_VISIBLE, 0);
					SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_3, ATTR_VISIBLE, 0);
					SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_4, ATTR_VISIBLE, 0);
					CanvasDrawBitmap (panel_2, PANEL_2_CANVAS, noWorries_bitmap, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
					ProcessSystemEvents();


					BASS_ChannelPlay(snd_wrong_ans,TRUE);


					Delay(3);

				}

				else

				{
					// Not in return phase
					Analysis();
					BASS_ChannelPlay(snd_wrong,TRUE);

					CanvasDrawBitmap (panel_2, PANEL_2_CANVAS, noWorries_bitmap, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
					SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_1, ATTR_VISIBLE, 0);
					SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_2, ATTR_VISIBLE, 0);
					SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_3, ATTR_VISIBLE, 0);
					SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_4, ATTR_VISIBLE, 0);


				}

				returnAnswerIndex=-1;

				for (int i = 0; i< 30; i++)
					right_ans[i]=0;

				counter_ans=0;

			}

			answer1=0;
			answer2=0;
			answer3=0;
			answer4=0;

			SetCtrlVal (panel_2, PANEL_2_PICTUREBUTTON_1, answer1);
			SetCtrlVal (panel_2, PANEL_2_PICTUREBUTTON_2, answer2);
			SetCtrlVal (panel_2, PANEL_2_PICTUREBUTTON_3, answer3);
			SetCtrlVal (panel_2, PANEL_2_PICTUREBUTTON_4, answer4);
			ProcessSystemEvents();
			Delay(1);


			//in memory game and returm phase
			if (m_game==1  &&  returnAnswerIndex!=-1)

				CanvasDrawBitmap (panel_2, PANEL_2_CANVAS, memory_bitmap, VAL_ENTIRE_OBJECT, MakeRect (0, 0, 150, 1000));


			BASS_ChannelStop(snd_applause);
			BASS_ChannelStop(snd_wrong);



			if (returnAnswerIndex==-1)
				CanvasDrawBitmap (panel_2, PANEL_2_CANVAS, bg_bitmap, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);


			Choose_Audio();
			Choose_Random_Location();
			//SetCtrlAttribute (panel_2, PANEL_2_TIMER_2, ATTR_ENABLED, 1);




			break;
	}
	return 0;

}

// Start Game from menu

void CVICALLBACK Start_Game (int menuBar, int menuItem, void *callbackData,
							 int panel)
{
	s_game=1;
	counter=10;

	SetCtrlAttribute (panel_2, PANEL_2_TIMER, ATTR_ENABLED, 1);

	SetPanelAttribute (panel_2, ATTR_LEFT, VAL_AUTO_CENTER);
	DisplayPanel (panel_2);

	BASS_ChannelStop(snd_open);
	Choose_Audio();
	Choose_Random_Location();
}

//Start game from control

int CVICALLBACK StartGame_func (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_1, PANEL_START_GAME_BUTTON, &s_game);
			counter=10;

			SetCtrlAttribute (panel_2, PANEL_2_TIMER, ATTR_ENABLED, 1);

			SetPanelAttribute (panel_2, ATTR_LEFT, VAL_AUTO_CENTER);
			DisplayPanel (panel_2);

			BASS_ChannelStop(snd_open);
			Choose_Audio();
			Choose_Random_Location();

			break;
	}
	return 0;
}

int CVICALLBACK StartMemoryGame (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel_1, PANEL_MEMORY_GAME_BUTTON, &m_game);
			SetCtrlAttribute (panel_2, PANEL_2_TIMER, ATTR_ENABLED, 1);
			SetCtrlVal (panel_2, PANEL_2_NUMERIC, counter);
			counter=10;

			m_game=1;

			SetPanelAttribute (panel_2, ATTR_LEFT, VAL_AUTO_CENTER);
			DisplayPanel (panel_2);

			BASS_ChannelStop(snd_open);
			Choose_Audio();
			Choose_Random_Location();

			break;
	}
	return 0;
}

void CVICALLBACK About_func (int menuBar, int menuItem, void *callbackData,
							 int panel)
{
	DisplayPanel (panel_5);
}

void CVICALLBACK Help_Func (int menuBar, int menuItem, void *callbackData,
							int panel)
{
}

void CVICALLBACK Demo_func (int menuBar, int menuItem, void *callbackData,
							int panel)
{

 OpenDocumentInDefaultViewer ("Demo.wmv", VAL_NO_ZOOM);
 BASS_ChannelSetAttribute(snd_open,BASS_ATTRIB_VOL,0);
}

void CVICALLBACK Help_func (int menuBar, int menuItem, void *callbackData,
							int panel)
{
	OpenDocumentInDefaultViewer ("Instructions.pdf", VAL_MAXIMIZE);
}

void CVICALLBACK Mute_func (int menuBar, int menuItem, void *callbackData,
							int panel)
{

	BASS_ChannelSetAttribute(snd_open,BASS_ATTRIB_VOL,0);
}

void CVICALLBACK Unmute_func (int menuBar, int menuItem, void *callbackData,
							  int panel)
{
	BASS_ChannelSetAttribute(snd_open,BASS_ATTRIB_VOL,1);
}


void CVICALLBACK Report_func (int menuBar, int menuItem, void *callbackData,
							  int panel)
{
	SetCtrlAttribute (panel_2, PANEL_2_TIMER, ATTR_ENABLED, 0);
	PlotRectangle (panel_3, PANEL_3_GRAPH, 8, 0, 12, makom_hituh, VAL_RED, VAL_RED);
	PlotRectangle (panel_3, PANEL_3_GRAPH, 18, 0, 22, ofen_hituh, VAL_RED, VAL_GREEN);
	PlotRectangle (panel_3, PANEL_3_GRAPH, 28, 0, 32, koliut, VAL_RED, VAL_MAGENTA);
	PlotRectangle (panel_3, PANEL_3_GRAPH, 38, 0, 42, izur, VAL_RED, VAL_BLUE);
	PlotRectangle (panel_3, PANEL_3_GRAPH, 48, 0, 52, taam, VAL_RED, VAL_BLACK);
	SetPlotAttribute (panel_3, PANEL_3_GRAPH, 1, ATTR_PLOT_LG_TEXT, "Makom Hituh");
	SetPlotAttribute (panel_3, PANEL_3_GRAPH, 2, ATTR_PLOT_LG_TEXT, "Ofen Hituh");
	SetPlotAttribute (panel_3, PANEL_3_GRAPH, 3, ATTR_PLOT_LG_TEXT, "Koliut");
	SetPlotAttribute (panel_3, PANEL_3_GRAPH, 4, ATTR_PLOT_LG_TEXT, "Izur");
	SetPlotAttribute (panel_3, PANEL_3_GRAPH, 5, ATTR_PLOT_LG_TEXT, "Taam");

	SetCtrlVal (panel_3, PANEL_3_FIRST_NAME, info.firstName);
	SetCtrlVal (panel_3, PANEL_3_LAST_NAME, info.lastName);
	SetCtrlVal (panel_3, PANEL_3_ID, info.id);
	SetCtrlVal (panel_3, PANEL_3_AGE, info.age);
	SetCtrlVal (panel_3, PANEL_3_ADDRESS, info.address);
	SetCtrlVal (panel_3, PANEL_3_PHONE, info.phone);
	SetCtrlVal (panel_3, PANEL_3_PARENT, info.parent);

	GetPanelDisplayBitmap (panel_3, VAL_FULL_PANEL, VAL_ENTIRE_OBJECT, &report_bitmap);

	SaveBitmapToJPEGFile (report_bitmap, "Report.jpg" ,0, 100);

	LaunchExecutable ("jpeg2pdf Report.jpg -o Report.pdf");

	OpenDocumentInDefaultViewer ("Report.pdf", VAL_NO_ZOOM);
}

int CVICALLBACK tick_1 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

			if(counter<0)
			{
				//time out = the player did not answered - like wrong answer
				//if in MG reset right answers array
				CanvasDrawBitmap (panel_2, PANEL_2_CANVAS, noWorries_bitmap, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
				BASS_ChannelPlay(snd_wrong_ans,TRUE);
				SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_1, ATTR_VISIBLE, 0);
				SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_2, ATTR_VISIBLE, 0);
				SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_3, ATTR_VISIBLE, 0);
				SetCtrlAttribute (panel_2, PANEL_2_PICTUREBUTTON_4, ATTR_VISIBLE, 0);
				ProcessSystemEvents();

				Delay(4);

				CanvasDrawBitmap (panel_2, PANEL_2_CANVAS, bg_bitmap, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);


				if (m_game==1)
				{
					returnAnswerIndex=-1;
					counter_ans=0;

					for (int t = 0; t< 30; t++)
						right_ans[t]=0;

				}



				Choose_Audio();
				Choose_Random_Location();

			}

			SetCtrlVal (panel_2, PANEL_2_NUMERIC, counter);
			
			counter--;
			Time++;

			break;
	}
	return 0;
}



int CVICALLBACK details_func (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			DisplayPanel (panel_4);

			break;
	}
	return 0;
}

int CVICALLBACK approve_information (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			HidePanel (panel_4);

			GetCtrlVal (panel_4, PANEL_4_FIRST_NAME,info.firstName);
			GetCtrlVal (panel_4, PANEL_4_LAST_NAME,info.lastName);
			GetCtrlVal (panel_4, PANEL_4_ID,info.id);
			GetCtrlVal (panel_4, PANEL_4_AGE, &info.age);
			GetCtrlVal (panel_4, PANEL_4_FEMALE, &info.female);
			GetCtrlVal (panel_4, PANEL_4_MALE, &info.male);
			GetCtrlVal (panel_4, PANEL_4_ADDRESS, info.address);
			GetCtrlVal (panel_4, PANEL_4_PHONE, info.phone);
			GetCtrlVal (panel_4, PANEL_4_PARENT, info.parent);


			break;
	}
	return 0;
}


int CVICALLBACK Report_Func (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{

	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panel_2, PANEL_2_TIMER, ATTR_ENABLED, 0);
			//DisplayPanel (panel_3);


			PlotRectangle (panel_3, PANEL_3_GRAPH, 8, 0, 12, makom_hituh, VAL_RED, VAL_RED);
			PlotRectangle (panel_3, PANEL_3_GRAPH, 18, 0, 22, ofen_hituh, VAL_RED, VAL_GREEN);
			PlotRectangle (panel_3, PANEL_3_GRAPH, 28, 0, 32, koliut, VAL_RED, VAL_MAGENTA);
			PlotRectangle (panel_3, PANEL_3_GRAPH, 38, 0, 42, izur, VAL_RED, VAL_BLUE);
			PlotRectangle (panel_3, PANEL_3_GRAPH, 48, 0, 52, taam, VAL_RED, VAL_BLACK);
			SetPlotAttribute (panel_3, PANEL_3_GRAPH, 1, ATTR_PLOT_LG_TEXT, "Makom Hituh");
			SetPlotAttribute (panel_3, PANEL_3_GRAPH, 2, ATTR_PLOT_LG_TEXT, "Ofen Hituh");
			SetPlotAttribute (panel_3, PANEL_3_GRAPH, 3, ATTR_PLOT_LG_TEXT, "Koliut");
			SetPlotAttribute (panel_3, PANEL_3_GRAPH, 4, ATTR_PLOT_LG_TEXT, "Izur");
			SetPlotAttribute (panel_3, PANEL_3_GRAPH, 5, ATTR_PLOT_LG_TEXT, "Taam");

			SetCtrlVal (panel_3, PANEL_3_FIRST_NAME, info.firstName);
			SetCtrlVal (panel_3, PANEL_3_LAST_NAME, info.lastName);
			SetCtrlVal (panel_3, PANEL_3_ID, info.id);
			SetCtrlVal (panel_3, PANEL_3_AGE, info.age);
			SetCtrlVal (panel_3, PANEL_3_ADDRESS, info.address);
			SetCtrlVal (panel_3, PANEL_3_PHONE, info.phone);
			SetCtrlVal (panel_3, PANEL_3_PARENT, info.parent);

			GetPanelDisplayBitmap (panel_3, VAL_FULL_PANEL, VAL_ENTIRE_OBJECT, &report_bitmap);

			SaveBitmapToJPEGFile (report_bitmap, "Report.jpg" ,0, 100);

			LaunchExecutable ("jpeg2pdf Report.jpg -o Report.pdf");

			OpenDocumentInDefaultViewer ("Report.pdf", VAL_NO_ZOOM);



			break;
	}
	return 0;
}

int CVICALLBACK UploadImg_func (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	int FileStatus;
	char filename[300];
	switch (event)
	{
		case EVENT_COMMIT:

			FileStatus=FileSelectPopup ("", "*.*", "", "Please Select a Picture", VAL_LOAD_BUTTON, 0, 0, 1, 0, filename);

			if(filename!=NULL)

				DisplayImageFile (panel_3, PANEL_3_PICTURE, filename);

			break;
	}
	return 0;
}



int CVICALLBACK plot_graph_func (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			DisplayPanel (panel_3);
			SetCtrlAttribute (panel_2, PANEL_2_TIMER, ATTR_ENABLED, 0);
			PlotRectangle (panel_3, PANEL_3_GRAPH, 8, 0, 12, makom_hituh, VAL_RED, VAL_RED);
			PlotRectangle (panel_3, PANEL_3_GRAPH, 18, 0, 22, ofen_hituh, VAL_RED, VAL_GREEN);
			PlotRectangle (panel_3, PANEL_3_GRAPH, 28, 0, 32, koliut, VAL_RED, VAL_MAGENTA);
			PlotRectangle (panel_3, PANEL_3_GRAPH, 38, 0, 42, izur, VAL_RED, VAL_BLUE);
			PlotRectangle (panel_3, PANEL_3_GRAPH, 48, 0, 52, taam, VAL_RED, VAL_BLACK);
			SetPlotAttribute (panel_3, PANEL_3_GRAPH, 1, ATTR_PLOT_LG_TEXT, "Makom Hituh");
			SetPlotAttribute (panel_3, PANEL_3_GRAPH, 2, ATTR_PLOT_LG_TEXT, "Ofen Hituh");
			SetPlotAttribute (panel_3, PANEL_3_GRAPH, 3, ATTR_PLOT_LG_TEXT, "Koliut");
			SetPlotAttribute (panel_3, PANEL_3_GRAPH, 4, ATTR_PLOT_LG_TEXT, "Izur");
			SetPlotAttribute (panel_3, PANEL_3_GRAPH, 5, ATTR_PLOT_LG_TEXT, "Taam");

			SetCtrlVal (panel_3, PANEL_3_FIRST_NAME, info.firstName);
			SetCtrlVal (panel_3, PANEL_3_LAST_NAME, info.lastName);
			SetCtrlVal (panel_3, PANEL_3_ID, info.id);
			SetCtrlVal (panel_3, PANEL_3_AGE, info.age);
			SetCtrlVal (panel_3, PANEL_3_ADDRESS, info.address);
			SetCtrlVal (panel_3, PANEL_3_PHONE, info.phone);
			SetCtrlVal (panel_3, PANEL_3_PARENT, info.parent);

			break;
	}
	return 0;
}

// Exit from command button


void CVICALLBACK Costumize_func (int menuBar, int menuItem, void *callbackData,
								 int panel)
{
	int forest_bmp;
	DisplayPanel (panel_6);
	GetBitmapFromFile ("Words_Pictures\\forest.jpg", &forest_bmp);
	CanvasDrawBitmap (panel_6, PANEL_6_CANVAS, forest_bmp, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);

}


int CVICALLBACK table_func (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	Point cell;


	switch (event)
	{
		case EVENT_LEFT_CLICK:
			counter_chosen++;
			GetTableCellFromPoint (panel_6, PANEL_6_WORDS_TABLE, MakePoint(eventData2,eventData1), &cell);
			SetCtrlVal (panel_6, PANEL_6_NUMERIC, cell.x);
			SetCtrlVal (panel_6, PANEL_6_NUMERIC_2, cell.y);
			BASS_ChannelSetAttribute(snd_open, BASS_ATTRIB_VOL, 0.2);

			SetTableCellVal (panel_6, PANEL_6_WORDS_TABLE, MakePoint (cell.x, cell.y),bmp[0] );

			if(cell.x==1)
			{
				SetTableCellVal (panel_6, PANEL_6_WORDS_TABLE, MakePoint (cell.x+1, cell.y),bmp[0] );
				SetTableCellVal (panel_6, PANEL_6_WORDS_TABLE, MakePoint (cell.x+2, cell.y),bmp[(cell.y)*2-1] );
				SetTableCellVal (panel_6, PANEL_6_WORDS_TABLE, MakePoint (cell.x+3, cell.y),bmp[(cell.y)*2]);
			}

			else
			{
				SetTableCellVal (panel_6, PANEL_6_WORDS_TABLE, MakePoint (cell.x-1, cell.y),bmp[0] );
				SetTableCellVal (panel_6, PANEL_6_WORDS_TABLE, MakePoint (cell.x+1, cell.y),bmp[(cell.y)*2-1] );
				SetTableCellVal (panel_6, PANEL_6_WORDS_TABLE, MakePoint (cell.x+2, cell.y),bmp[(cell.y)*2] );

			}

			BASS_ChannelPlay(sounds[cell.y*2-1],TRUE);
			Delay(0.7);
			BASS_ChannelPlay(sounds[cell.y*2],TRUE);
			BASS_ChannelSetAttribute(snd_open, BASS_ATTRIB_VOL,1);

			if (cell.x==1)
				chosen_words[counter_chosen]= cell.y*2-1;
			else
				chosen_words[counter_chosen]= cell.y*2;

			break;
	}
	return 0;
}

int CVICALLBACK leader_func (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			LoadScore();
			DisplayPanel (panel_7);

			break;
	}
	return 0;
}


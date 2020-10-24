/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: exit_panel_1 */
#define  PANEL_START_GAME_BUTTON          2       /* control type: pictButton, callback function: StartGame_func */
#define  PANEL_PICTURE                    3       /* control type: picture, callback function: (none) */
#define  PANEL_MEMORY_GAME_BUTTON         4       /* control type: pictButton, callback function: StartMemoryGame */
#define  PANEL_COMMANDBUTTON              5       /* control type: command, callback function: details_func */
#define  PANEL_PLOT                       6       /* control type: command, callback function: Report_Func */
#define  PANEL_PLOT_GRAPH                 7       /* control type: command, callback function: plot_graph_func */
#define  PANEL_COMMANDBUTTON_2            8       /* control type: command, callback function: leader_func */

#define  PANEL_2                          2       /* callback function: exit_Panel_2 */
#define  PANEL_2_NUMERIC                  2       /* control type: numeric, callback function: (none) */
#define  PANEL_2_CANVAS                   3       /* control type: canvas, callback function: (none) */
#define  PANEL_2_MEMORY_GAME_BUTTON       4       /* control type: pictButton, callback function: exit_panel_2 */
#define  PANEL_2_PICTUREBUTTON_4          5       /* control type: pictButton, callback function: Choosing_func */
#define  PANEL_2_PICTUREBUTTON_1          6       /* control type: pictButton, callback function: Choosing_func */
#define  PANEL_2_PICTUREBUTTON_2          7       /* control type: pictButton, callback function: Choosing_func */
#define  PANEL_2_PICTUREBUTTON_3          8       /* control type: pictButton, callback function: Choosing_func */
#define  PANEL_2_TIMER                    9       /* control type: timer, callback function: tick_1 */

#define  PANEL_3                          3       /* callback function: exit_panel_3 */
#define  PANEL_3_FIRST_NAME               2       /* control type: string, callback function: (none) */
#define  PANEL_3_LAST_NAME                3       /* control type: string, callback function: (none) */
#define  PANEL_3_ID                       4       /* control type: string, callback function: (none) */
#define  PANEL_3_ADDRESS                  5       /* control type: string, callback function: (none) */
#define  PANEL_3_PHONE                    6       /* control type: string, callback function: (none) */
#define  PANEL_3_AGE                      7       /* control type: numeric, callback function: (none) */
#define  PANEL_3_PARENT                   8       /* control type: string, callback function: (none) */
#define  PANEL_3_GRAPH                    9       /* control type: graph, callback function: (none) */
#define  PANEL_3_PICTURE                  10      /* control type: picture, callback function: (none) */

#define  PANEL_4                          4       /* callback function: exit_panel_4 */
#define  PANEL_4_FIRST_NAME               2       /* control type: string, callback function: (none) */
#define  PANEL_4_LAST_NAME                3       /* control type: string, callback function: (none) */
#define  PANEL_4_ID                       4       /* control type: string, callback function: (none) */
#define  PANEL_4_ADDRESS                  5       /* control type: string, callback function: (none) */
#define  PANEL_4_PHONE                    6       /* control type: string, callback function: (none) */
#define  PANEL_4_AGE                      7       /* control type: numeric, callback function: (none) */
#define  PANEL_4_FEMALE                   8       /* control type: radioButton, callback function: (none) */
#define  PANEL_4_MALE                     9       /* control type: radioButton, callback function: (none) */
#define  PANEL_4_PARENT                   10      /* control type: string, callback function: (none) */
#define  PANEL_4_CLOSE_INFO               11      /* control type: command, callback function: approve_information */
#define  PANEL_4_UPLOAD_IMAGE             12      /* control type: command, callback function: UploadImg_func */

#define  PANEL_5                          5       /* callback function: exit_panel_5 */
#define  PANEL_5_PICTURE                  2       /* control type: picture, callback function: (none) */
#define  PANEL_5_TEXTMSG_2                3       /* control type: textMsg, callback function: (none) */
#define  PANEL_5_TEXTMSG                  4       /* control type: textMsg, callback function: (none) */

#define  PANEL_6                          6       /* callback function: exit_panel_6 */
#define  PANEL_6_NUMERIC_2                2       /* control type: numeric, callback function: (none) */
#define  PANEL_6_NUMERIC                  3       /* control type: numeric, callback function: (none) */
#define  PANEL_6_WORDS_TABLE              4       /* control type: table, callback function: table_func */
#define  PANEL_6_PICTURE_2                5       /* control type: picture, callback function: (none) */
#define  PANEL_6_PICTURE_3                6       /* control type: picture, callback function: (none) */
#define  PANEL_6_PICTURE_5                7       /* control type: picture, callback function: (none) */
#define  PANEL_6_PICTURE_4                8       /* control type: picture, callback function: (none) */
#define  PANEL_6_CANVAS                   9       /* control type: canvas, callback function: (none) */
#define  PANEL_6_PICTURE                  10      /* control type: picture, callback function: (none) */

#define  PANEL_7                          7       /* callback function: exit_panel_7 */
#define  PANEL_7_STRING_6                 2       /* control type: string, callback function: (none) */
#define  PANEL_7_STRING_5                 3       /* control type: string, callback function: (none) */
#define  PANEL_7_STRING_4                 4       /* control type: string, callback function: (none) */
#define  PANEL_7_STRING_3                 5       /* control type: string, callback function: (none) */
#define  PANEL_7_STRING_2                 6       /* control type: string, callback function: (none) */
#define  PANEL_7_STRING                   7       /* control type: string, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_OPTIONS                  2
#define  MENUBAR_OPTIONS_STARTPLA         3       /* callback function: Start_Game */
#define  MENUBAR_OPTIONS_REPORT           4       /* callback function: Report_func */
#define  MENUBAR_OPTIONS_COSTUMIZE        5       /* callback function: Costumize_func */
#define  MENUBAR_HELP                     6
#define  MENUBAR_HELP_HELP                7       /* callback function: Help_func */
#define  MENUBAR_DEMO                     8
#define  MENUBAR_DEMO_DEMO                9       /* callback function: Demo_func */
#define  MENUBAR_MUTE                     10
#define  MENUBAR_MUTE_MUTE                11      /* callback function: Mute_func */
#define  MENUBAR_MUTE_UNMUTE              12      /* callback function: Unmute_func */
#define  MENUBAR_ABOUT                    13
#define  MENUBAR_ABOUT_ABOUT              14      /* callback function: About_func */


     /* Callback Prototypes: */

void CVICALLBACK About_func(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK approve_information(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Choosing_func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Costumize_func(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK Demo_func(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK details_func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK exit_panel_1(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK exit_Panel_2(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK exit_panel_3(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK exit_panel_4(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK exit_panel_5(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK exit_panel_6(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK exit_panel_7(int panel, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Help_func(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK leader_func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Mute_func(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK plot_graph_func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Report_func(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK Start_Game(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK StartGame_func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartMemoryGame(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK table_func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK tick_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Unmute_func(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK UploadImg_func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif

/***************************************************************
 * Name:      ais_readers_manager_gui_wxwidgetsMain.h
 * Purpose:   Defines Application Frame
 * Author:    Bojan (Bojan)
 * Created:   2018-08-29
 * Copyright: Bojan (Bojan)
 * License:
 **************************************************************/

#ifndef AIS_READERS_MANAGER_GUI_WXWIDGETSMAIN_H
#define AIS_READERS_MANAGER_GUI_WXWIDGETSMAIN_H

//(*Headers(ais_readers_manager_gui_wxwidgetsFrame)
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class ais_readers_manager_gui_wxwidgetsFrame: public wxFrame
{
    public:

        ais_readers_manager_gui_wxwidgetsFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~ais_readers_manager_gui_wxwidgetsFrame();

        void DoAsyncExec(const wxString& cmd);
        bool started;
        long pid;
        bool child_process_created;
        wxString shell_output;

        wxTextOutputStream *to_write;

    private:

        //(*Handlers(ais_readers_manager_gui_wxwidgetsFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnbStartClick(wxCommandEvent& event);
        void OnbReadWhitelistFromDBClick(wxCommandEvent& event);
        void OnbReadBlacklistFromDBClick(wxCommandEvent& event);
        void OnbReadWhitelistFromReaderClick(wxCommandEvent& event);
        void OnbReadBlacklistFromReaderClick(wxCommandEvent& event);
        void OnbGetLogsClick(wxCommandEvent& event);
        void OnbSendAllLogsClick(wxCommandEvent& event);
        void OnbSetTimeToDevicesClick(wxCommandEvent& event);
        void OnbGetTimeFromDevicesClick(wxCommandEvent& event);
        void OnbGetLogsByTimeClick(wxCommandEvent& event);
        void OnbGetLogsByIndexClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(ais_readers_manager_gui_wxwidgetsFrame)
        static const long ID_BUTTON12;
        static const long ID_TEXTCTRL7;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_BUTTON5;
        static const long ID_BUTTON6;
        static const long ID_BUTTON7;
        static const long ID_BUTTON8;
        static const long ID_BUTTON9;
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL2;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRL3;
        static const long ID_BUTTON10;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL4;
        static const long ID_STATICTEXT4;
        static const long ID_TEXTCTRL5;
        static const long ID_BUTTON11;
        static const long ID_TEXTCTRL6;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(ais_readers_manager_gui_wxwidgetsFrame)
        wxButton* bReadBlacklistFromReader;
        wxButton* bGetTimeFromDevices;
        wxStatusBar* StatusBar1;
        wxTextCtrl* tStartTime;
        wxButton* bSendAllLogs;
        wxTextCtrl* tEndTime;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxButton* bReadWhitelistFromDB;
        wxButton* bStart;
        wxStaticText* StaticText4;
        wxStaticText* StaticText2;
        wxButton* bGetLogs;
        wxButton* bSetTimeToDevices;
        wxTextCtrl* tStartIndex;
        wxButton* bGetLogsByIndex;
        wxTextCtrl* tEndIndex;
        wxButton* bReadWhitelistFromReader;
        wxButton* bReadBlacklistFromDB;
        wxTextCtrl* tLogger;
        wxButton* bGetLogsByTime;
        wxTextCtrl* tStatus;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // AIS_READERS_MANAGER_GUI_WXWIDGETSMAIN_H

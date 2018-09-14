/***************************************************************
 * Name:      ais_readers_manager_gui_wxwidgetsMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Bojan (Bojan)
 * Created:   2018-08-29
 * Copyright: Bojan (Bojan)
 * License:
 **************************************************************/

#include "ais_readers_manager_gui_wxwidgetsMain.h"
#include <wx/msgdlg.h>
//#include "NotificationIcon.h"
#include <wx/utils.h>
#include <wx/wx.h>
#include <wx/process.h>
#include <wx/sstream.h>
#include <wx/txtstrm.h>
#include <wx/app.h>
#include <wx/textentry.h>
#include <wx/textdlg.h>

#include <iostream>
#include <streambuf>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include<unistd.h>
#include<fcntl.h>


using namespace std;





//(*InternalHeaders(ais_readers_manager_gui_wxwidgetsFrame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(ais_readers_manager_gui_wxwidgetsFrame)
const long ais_readers_manager_gui_wxwidgetsFrame::ID_STATICTEXT1 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON1 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON13 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON2 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON3 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON4 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON5 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON6 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON7 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON8 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON9 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON10 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_STATICTEXT2 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_TEXTCTRL1 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_STATICTEXT3 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_TEXTCTRL2 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON11 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_STATICTEXT4 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_TEXTCTRL3 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_STATICTEXT5 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_TEXTCTRL4 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON12 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_TEXTCTRL5 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::idMenuQuit = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::idMenuAbout = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_STATUSBAR1 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_TIMER1 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_TIMER2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ais_readers_manager_gui_wxwidgetsFrame,wxFrame)
    //(*EventTable(ais_readers_manager_gui_wxwidgetsFrame)
    //*)
END_EVENT_TABLE()

ais_readers_manager_gui_wxwidgetsFrame::ais_readers_manager_gui_wxwidgetsFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(ais_readers_manager_gui_wxwidgetsFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer6;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxStaticBoxSizer* StaticBoxSizer2;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxStaticBoxSizer* StaticBoxSizer4;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, wxEmptyString);
    StaticBoxSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("AIS READERS MANAGER GUI"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(18,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    StaticBoxSizer1->Add(StaticText1, 0, wxALL|wxALIGN_TOP, 2);
    StaticBoxSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(StaticBoxSizer1, 0, wxALL|wxEXPAND, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Application"));
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    bStart = new wxButton(this, ID_BUTTON1, _("START"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer2->Add(bStart, 0, wxALL|wxEXPAND, 2);
    BoxSizer2->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    bClear = new wxButton(this, ID_BUTTON13, _("CLEAR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON13"));
    BoxSizer2->Add(bClear, 0, wxALL|wxEXPAND, 2);
    BoxSizer2->Add(0,0,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    bStop = new wxButton(this, ID_BUTTON2, _("STOP"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer2->Add(bStop, 0, wxALL|wxEXPAND, 2);
    StaticBoxSizer2->Add(BoxSizer2, 0, wxALL|wxEXPAND, 2);
    BoxSizer1->Add(StaticBoxSizer2, 0, wxALL|wxEXPAND, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("Commands"));
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    bReadWhitelistFromDB = new wxButton(this, ID_BUTTON3, _("Read whitelist from DB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BoxSizer3->Add(bReadWhitelistFromDB, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    bReadWhitelistFromReader = new wxButton(this, ID_BUTTON4, _("Read whitelist from reader"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    BoxSizer3->Add(bReadWhitelistFromReader, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    bGetLogs = new wxButton(this, ID_BUTTON5, _("Get logs"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    BoxSizer3->Add(bGetLogs, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    bSendAllLogs = new wxButton(this, ID_BUTTON6, _("Send all logs"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    BoxSizer3->Add(bSendAllLogs, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticBoxSizer3->Add(BoxSizer3, 0, wxALL|wxEXPAND, 2);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    bReadBlacklistFromDB = new wxButton(this, ID_BUTTON7, _("Read blacklist from DB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    BoxSizer4->Add(bReadBlacklistFromDB, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    bReadBlacklistFromReader = new wxButton(this, ID_BUTTON8, _("Read blacklist from reader"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
    BoxSizer4->Add(bReadBlacklistFromReader, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    bGetTimeFromDevices = new wxButton(this, ID_BUTTON9, _("Get time from devices"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
    BoxSizer4->Add(bGetTimeFromDevices, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    bSetTimeToDevices = new wxButton(this, ID_BUTTON10, _("Set time to devices"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
    BoxSizer4->Add(bSetTimeToDevices, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticBoxSizer3->Add(BoxSizer4, 0, wxALL|wxEXPAND, 2);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Start index :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer5->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    tStartIndex = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    BoxSizer5->Add(tStartIndex, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("End index :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer5->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    tEndIndex = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    BoxSizer5->Add(tEndIndex, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    bGetLogsByIndex = new wxButton(this, ID_BUTTON11, _("Get logs by index"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON11"));
    BoxSizer5->Add(bGetLogsByIndex, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticBoxSizer3->Add(BoxSizer5, 0, wxALL|wxEXPAND, 2);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Time from :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    BoxSizer6->Add(StaticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    tStartTime = new wxTextCtrl(this, ID_TEXTCTRL3, _("hh:mm:ss dd.mm.yyyy"), wxDefaultPosition, wxSize(137,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    BoxSizer6->Add(tStartTime, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Time to :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    BoxSizer6->Add(StaticText5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    tEndTime = new wxTextCtrl(this, ID_TEXTCTRL4, _("hh:mm:ss dd.mm.yyyy"), wxDefaultPosition, wxSize(133,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    BoxSizer6->Add(tEndTime, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    bGetLogsByTime = new wxButton(this, ID_BUTTON12, _("Get logs by time"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON12"));
    BoxSizer6->Add(bGetLogsByTime, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticBoxSizer3->Add(BoxSizer6, 0, wxALL|wxEXPAND, 2);
    BoxSizer1->Add(StaticBoxSizer3, 0, wxALL|wxEXPAND, 5);
    StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Output"));
    tLogger = new wxTextCtrl(this, ID_TEXTCTRL5, wxEmptyString, wxDefaultPosition, wxSize(1061,257), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    wxFont tLoggerFont(12,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    tLogger->SetFont(tLoggerFont);
    StaticBoxSizer4->Add(tLogger, 1, wxALL|wxEXPAND, 5);
    BoxSizer1->Add(StaticBoxSizer4, 1, wxALL|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    readTimer.SetOwner(this, ID_TIMER1);
    readTimer.Start(10, false);
    commandTimer.SetOwner(this, ID_TIMER2);
    commandTimer.Start(500, false);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbStartClick1);
    Connect(ID_BUTTON13,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbClearClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbStopClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbReadWhitelistFromDBClick1);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbReadWhitelistFromReaderClick1);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbGetLogsClick1);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbSendAllLogsClick1);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbReadBlacklistFromDBClick1);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbReadBlacklistFromReaderClick1);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbGetTimeFromDevicesClick1);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbSetTimeToDevicesClick1);
    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbGetLogsByIndexClick1);
    Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbGetLogsByTimeClick1);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnAbout);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnreadTimerTrigger1);
    Connect(ID_TIMER2,wxEVT_TIMER,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OncommandTimerTrigger1);
    //*)
}

ais_readers_manager_gui_wxwidgetsFrame::~ais_readers_manager_gui_wxwidgetsFrame()
{
    //(*Destroy(ais_readers_manager_gui_wxwidgetsFrame)
    //*)

    if (process_started == true)
    {
       wxKill(pid,wxSignal(wxSIGKILL));
    }

}

void ais_readers_manager_gui_wxwidgetsFrame::OnQuit(wxCommandEvent& event)
{
        if (process_started == true)
    {
       wxKill(pid,wxSignal(wxSIGKILL));
    }
    Close();
}

void ais_readers_manager_gui_wxwidgetsFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbStartClick1(wxCommandEvent& event)
{
        wxString shell = "../../shell/bin/Debug/ais_readers-manager-c-php-mysql.exe -gui";

    pproc = new wxProcess(wxPROCESS_REDIRECT);

    pid = wxExecute(shell, wxEXEC_ASYNC, pproc);

        if (!pid)
        {
            tLogger->AppendText(wxT("FAIL: Command: " + shell + " could not be run!\n"));
        }

        pproc->Redirect();

        process_started = true;

        ins = pproc->GetInputStream();
        outs = pproc->GetOutputStream();

        tin = new wxTextInputStream(*ins);
        tout = new wxTextOutputStream(*outs);

}

void ais_readers_manager_gui_wxwidgetsFrame::OnbReadWhitelistFromDBClick1(wxCommandEvent& event)
{
    tout->WriteString("1");
    tout->WriteString("\n");
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbReadWhitelistFromReaderClick1(wxCommandEvent& event)
{
    tout->WriteString("4");
    tout->WriteString("\n");
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbGetLogsClick1(wxCommandEvent& event)
{
    tout->WriteString("3");
    tout->WriteString("\n");
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbSendAllLogsClick1(wxCommandEvent& event)
{
    tout->WriteString("6");
    tout->WriteString("\n");
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbReadBlacklistFromDBClick1(wxCommandEvent& event)
{
    tout->WriteString("2");
    tout->WriteString("\n");
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbReadBlacklistFromReaderClick1(wxCommandEvent& event)
{
    tout->WriteString("5");
    tout->WriteString("\n");
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbGetTimeFromDevicesClick1(wxCommandEvent& event)
{
    tout->WriteString("8");
    tout->WriteString("\n");
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbSetTimeToDevicesClick1(wxCommandEvent& event)
{
    tout->WriteString("7");
    tout->WriteString("\n");
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbGetLogsByTimeClick1(wxCommandEvent& event)
{
    wxString start_time = "";

    wxString end_time = "";


    start_time = tStartTime->GetValue();

    end_time = tEndTime->GetValue();

    //constInput ->Write("T",1);
        tout->WriteString("T");
        tout->WriteString("\n");


    tout->WriteString(start_time);
    tout->WriteString("\n");
    tout->WriteString(end_time);
    tout->WriteString("\n");

    start_time = "";
    end_time = "";
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbGetLogsByIndexClick1(wxCommandEvent& event)
{
        wxString start_index = "";

    wxString end_index = "";

    start_index = tStartIndex->GetValue();

    end_index = tEndIndex->GetValue();

    tout->WriteString("I");
    tout->WriteString("\n");

    tout->WriteString(start_index);
    tout->WriteString("\n");
    tout->WriteString(end_index);
    tout->WriteString("\n");

    start_index = "";

    end_index = "";
}

void ais_readers_manager_gui_wxwidgetsFrame::OncommandTimerTrigger1(wxTimerEvent& event)
{
    if (process_started == true)
    {
        tout->WriteString("0");
    }
}

void ais_readers_manager_gui_wxwidgetsFrame::OnreadTimerTrigger1(wxTimerEvent& event)
{
        if (!ins)
        return;

        wxString oout;
        wxChar line;

        while (ins->CanRead())
        {
            line = tin->GetChar();

                oout << line; //<< "\n";

        }

    *tLogger << oout;
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbStopClick(wxCommandEvent& event)
{
    if (process_started == true)
    {
       wxKill(pid,wxSignal(wxSIGKILL));
    }
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbClearClick(wxCommandEvent& event)
{
    tLogger->Clear();
}

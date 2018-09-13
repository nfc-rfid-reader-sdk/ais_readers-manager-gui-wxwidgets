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


wxString CMD = "0";
wxString last_CMD;
bool halt;

wxProcess * process = new wxProcess(wxPROCESS_REDIRECT);

 wxOutputStream *constInput;

//int COMMAND_FLAG = 0;



//(*InternalHeaders(ais_readers_manager_gui_wxwidgetsFrame)
#include <wx/string.h>
#include <wx/intl.h>
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
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON12 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_TEXTCTRL7 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON2 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON3 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON4 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON5 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON6 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON7 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON8 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON9 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_STATICTEXT1 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_TEXTCTRL2 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_STATICTEXT2 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_TEXTCTRL3 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON10 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_STATICTEXT3 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_TEXTCTRL4 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_STATICTEXT4 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_TEXTCTRL5 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_BUTTON11 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_TEXTCTRL6 = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::idMenuQuit = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::idMenuAbout = wxNewId();
const long ais_readers_manager_gui_wxwidgetsFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ais_readers_manager_gui_wxwidgetsFrame,wxFrame)
    //(*EventTable(ais_readers_manager_gui_wxwidgetsFrame)
    //*)
END_EVENT_TABLE()

ais_readers_manager_gui_wxwidgetsFrame::ais_readers_manager_gui_wxwidgetsFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(ais_readers_manager_gui_wxwidgetsFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxGridSizer* GridSizer1;
    wxMenu* Menu1;
    wxGridSizer* GridSizer3;
    wxGridSizer* GridSizer2;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(1200,500));
    GridSizer1 = new wxGridSizer(3, 1, 125, 0);
    GridSizer2 = new wxGridSizer(5, 4, -50, -852);
    bStart = new wxButton(this, ID_BUTTON12, _("Start"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON12"));
    GridSizer2->Add(bStart, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    tStatus = new wxTextCtrl(this, ID_TEXTCTRL7, wxEmptyString, wxDefaultPosition, wxSize(151,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
    GridSizer2->Add(tStatus, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    GridSizer2->Add(-1,-1,1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    GridSizer2->Add(-1,-1,1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    bReadWhitelistFromDB = new wxButton(this, ID_BUTTON2, _("Read whitelist from DB"), wxDefaultPosition, wxSize(200,30), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    GridSizer2->Add(bReadWhitelistFromDB, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    bReadWhitelistFromReader = new wxButton(this, ID_BUTTON3, _("Read whitelist from reader"), wxDefaultPosition, wxSize(200,30), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    GridSizer2->Add(bReadWhitelistFromReader, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    bGetLogs = new wxButton(this, ID_BUTTON4, _("Get logs"), wxDefaultPosition, wxSize(200,30), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    GridSizer2->Add(bGetLogs, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    bGetTimeFromDevices = new wxButton(this, ID_BUTTON5, _("Get time from devices"), wxDefaultPosition, wxSize(200,30), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    GridSizer2->Add(bGetTimeFromDevices, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    bReadBlacklistFromDB = new wxButton(this, ID_BUTTON6, _("Read blacklist from DB"), wxDefaultPosition, wxSize(200,30), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    GridSizer2->Add(bReadBlacklistFromDB, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    bReadBlacklistFromReader = new wxButton(this, ID_BUTTON7, _("Read blacklist from reader"), wxDefaultPosition, wxSize(200,30), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    GridSizer2->Add(bReadBlacklistFromReader, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    bSendAllLogs = new wxButton(this, ID_BUTTON8, _("Send all logs to DB"), wxDefaultPosition, wxSize(200,30), 0, wxDefaultValidator, _T("ID_BUTTON8"));
    GridSizer2->Add(bSendAllLogs, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    bSetTimeToDevices = new wxButton(this, ID_BUTTON9, _("Set time to devices"), wxDefaultPosition, wxSize(200,30), 0, wxDefaultValidator, _T("ID_BUTTON9"));
    GridSizer2->Add(bSetTimeToDevices, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    GridSizer3 = new wxGridSizer(2, 5, 0, -20);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Start index :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    GridSizer3->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    tStartIndex = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(116,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    GridSizer3->Add(tStartIndex, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("End index :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    GridSizer3->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    tEndIndex = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    GridSizer3->Add(tEndIndex, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP|wxSHAPED, 5);
    bGetLogsByIndex = new wxButton(this, ID_BUTTON10, _("Get logs by index "), wxDefaultPosition, wxSize(200,30), 0, wxDefaultValidator, _T("ID_BUTTON10"));
    GridSizer3->Add(bGetLogsByIndex, 1, wxALL|wxALIGN_RIGHT|wxALIGN_TOP, 5);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Time from :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    GridSizer3->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    tStartTime = new wxTextCtrl(this, ID_TEXTCTRL4, _("hh:mm:ss dd.mm.yyyy"), wxDefaultPosition, wxSize(238,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    GridSizer3->Add(tStartTime, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Time to :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    GridSizer3->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    tEndTime = new wxTextCtrl(this, ID_TEXTCTRL5, _("hh:mm:ss dd.mm.yyyy"), wxDefaultPosition, wxSize(166,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    GridSizer3->Add(tEndTime, 1, wxALL|wxEXPAND, 5);
    bGetLogsByTime = new wxButton(this, ID_BUTTON11, _("Get logs by time"), wxDefaultPosition, wxSize(200,30), 0, wxDefaultValidator, _T("ID_BUTTON11"));
    GridSizer3->Add(bGetLogsByTime, 1, wxALL|wxALIGN_RIGHT|wxALIGN_TOP, 5);
    GridSizer2->Add(GridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(GridSizer2, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    tLogger = new wxTextCtrl(this, ID_TEXTCTRL6, wxEmptyString, wxDefaultPosition, wxSize(1190,400), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL6"));
    GridSizer1->Add(tLogger, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    SetSizer(GridSizer1);
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
    SetSizer(GridSizer1);
    Layout();

    Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbStartClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbReadWhitelistFromDBClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbReadWhitelistFromReaderClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbGetLogsClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbGetTimeFromDevicesClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbReadBlacklistFromDBClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbReadBlacklistFromReaderClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbSendAllLogsClick);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbSetTimeToDevicesClick);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbGetLogsByIndexClick);
    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnbGetLogsByTimeClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ais_readers_manager_gui_wxwidgetsFrame::OnAbout);
    //*)
}

ais_readers_manager_gui_wxwidgetsFrame::~ais_readers_manager_gui_wxwidgetsFrame()
{

    if (started == true)
    {
        process->Kill(pid);
    }
    //(*Destroy(ais_readers_manager_gui_wxwidgetsFrame)
    //*)
}

void ais_readers_manager_gui_wxwidgetsFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void ais_readers_manager_gui_wxwidgetsFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
void ais_readers_manager_gui_wxwidgetsFrame::DoAsyncExec(const wxString& cmd)
{


    string alive = "Alive";

    started = false;

    pid = wxExecute(cmd, wxEXEC_ASYNC, process);

    child_process_created = true;

    process -> Redirect();

    if (!pid)
    {
        wxLogError(wxT("Execution of '%s' failed."), cmd.c_str());

        delete process;
    }

    else
    {
       wxLogStatus(wxT("Process %ld (%s) launched."), pid, cmd.c_str());


            if (process)
            {

                started = true;

                wxInputStream *msg;

                constInput = process ->GetOutputStream();

                msg = process->GetInputStream();

                if (process->Exists(pid))
                    {

                    wxTextInputStream tStream(*msg);

                        //while (tStream.GetChar() > 0)
                        while (true)
                        {

                            Update();

                            wxYield();

                            tLogger->Update();
///*** work in progress***///
                    /*if (last_CMD=="0")
                            {
                    usleep(400*500);
                        halt = true;
                            }
        if (CMD != last_CMD)
        {
            halt = false;
            constInput->Write(CMD.c_str(), CMD.length());
           // constInput->Write("\n", strlen("\n"));
        }

        if (halt==true){
        constInput->Write(CMD.c_str(), CMD.length());
        //constInput->Write("\n", strlen("\n"));
        }*/

 /* constInput->Write(CMD.c_str(), CMD.length());

        tStartIndex->SetValue(CMD);
        usleep(100*500);


/*
 wxString deb="";
tStartTime->SetValue(deb<<constInput->LastWrite());
 deb="";
*/

                                shell_output << tStream.ReadLine();


                                if (shell_output.Matches(alive) || shell_output=="")
                                {
                                    tStatus->SetValue("Process alive!");

                                } else{

                                tLogger->AppendText("\n");
                                tLogger->AppendText(shell_output);

                                }


                            shell_output = "";



                            //last_CMD = CMD;

                            //CMD="0";


                         }

                    }
            }

    }
}


void ais_readers_manager_gui_wxwidgetsFrame::OnbStartClick(wxCommandEvent& event)
{

    wxString shell = "../../shell/bin/Debug/ais_readers-manager-c-php-mysql -gui";

    //wxString shell = "../../shell/bin/Debug/ais_readers-manager-c-php-mysql.exe";

    DoAsyncExec(shell);
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbReadWhitelistFromDBClick(wxCommandEvent& event)
{
    constInput -> Write("1", strlen("1"));

    //CMD = "1";
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbReadBlacklistFromDBClick(wxCommandEvent& event)
{
    //CMD = "2";

    constInput -> Write("2", strlen("2"));
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbReadWhitelistFromReaderClick(wxCommandEvent& event)
{
    //CMD = "4";

    constInput -> Write("4", strlen("4"));
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbReadBlacklistFromReaderClick(wxCommandEvent& event)
{
    constInput -> Write("5", strlen("5"));

    //CMD = "5";
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbGetLogsClick(wxCommandEvent& event)
{
    //CMD = "3";
    constInput -> Write("3", strlen("3"));
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbSendAllLogsClick(wxCommandEvent& event)
{
    //CMD = "6";

    constInput -> Write("6", strlen("6"));
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbSetTimeToDevicesClick(wxCommandEvent& event)
{

    //CMD = "7";

    constInput -> Write("7", strlen("7"));

}

void ais_readers_manager_gui_wxwidgetsFrame::OnbGetTimeFromDevicesClick(wxCommandEvent& event)
{
   // to_write = new wxTextOutputStream(*constInput);
    //CMD = "8";

    //to_write->WriteString(CMD);

    //to_write->PutChar('8');
   //wxSleep(3);
   // to_write->WriteString("\n");

   constInput -> Write("8", strlen("8"));
}

void ais_readers_manager_gui_wxwidgetsFrame::OnbGetLogsByTimeClick(wxCommandEvent& event)
{

    wxString start_time = "";

    wxString end_time = "";


    start_time = tStartTime->GetValue();

    end_time = tEndTime->GetValue();

    constInput ->Write("T",1);

        constInput->Write(start_time,strlen(start_time));

        constInput->Write("\x0D", 1);

        constInput->Write(end_time,strlen(end_time));

        constInput->Write("\x0D", 1);

        start_time = "";

        end_time = "";

}

void ais_readers_manager_gui_wxwidgetsFrame::OnbGetLogsByIndexClick(wxCommandEvent& event)
{


    wxString start_index = "";

    wxString end_index = "";

    start_index = tStartIndex->GetValue();

    end_index = tEndIndex->GetValue();

        constInput ->Write("I",1);

        constInput ->Write(start_index, strlen(start_index));

        constInput ->Write("\x0D", 1);

        constInput ->Write(end_index, strlen(end_index));

        constInput ->Write("\x0D", 1);


}

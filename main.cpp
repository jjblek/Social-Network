#include "SocialNetwork.hpp"
#include <chrono>

using milliseconds = std::chrono::duration<float, std::chrono::milliseconds::period>;
using seconds = std::chrono::duration<float, std::chrono::seconds::period>;
using timer = std::chrono::high_resolution_clock;

char LOG_FILE_NAME[] = "SocialNetwork.log";

int main(int argc, char *argv[]) {

    /** TIMER START **/
    auto start = timer::now();

    std::ifstream inputStream(argv[1], std::ios::in);

    if (argc < 2) {
        std::cout << "This program expects an argument: [input file name]\n";
        exit(1);
    }

    /** PROGRAM OPTIONS **/
    bool withCSS = false, withLog = false;
    std::vector<std::string> args(argv, argv+argc);
    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "-css") withCSS = true;
        else if (args[i] == "-log") withLog = true;
    }

    if (!inputStream.is_open()) {
        std::cout << "Unable to open " << argv[1] << ". Terminating...";
        exit(2);
    }

    inputStream.close();

    /** TIMER START **/
    auto networkStart = timer::now();

    /** CONSTRUCT SOCIAL NETWORK **/
    SocialNetwork network(argv[1]);

    auto networkEnd = timer::now();
    std::cout << "Network constructed in " <<
        milliseconds(networkEnd - networkStart).count() << " ms\n";
    /** TIMER END - SOCIAL NETWORK CONSTRUCTED **/


    /** TIMER START **/
    auto HTMLStart = timer::now();

    /** GENERATE HTML FILES **/
    network.generateHTML(withCSS);

    auto HTMLEnd = timer::now();
    std::cout << "HTML generated in " <<
        milliseconds(HTMLEnd - HTMLStart).count() << " ms\n";
    /** TIMER END - HTML FILES GENERATED **/


    auto end = timer::now();
    if (milliseconds(end - start).count() > 1000) {
        std::cout << "Total Execution Time: "
                  << seconds(end - start).count()
                  << " seconds\n";
    }
    else {
        std::cout << "Total Execution Time: "
                  << milliseconds(end - start).count()
                  << " ms\n";
    }

    /** TIMER END - TOTAL EXECUTION TIME **/

    if (withLog) { /** OUTPUT LOG **/

        auto now = timer::now();

        auto in_time_t = timer::to_time_t(now);

        std::stringstream date;

        date << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");

        bool isEmtpy; // is the file empty?

        std::ifstream file(LOG_FILE_NAME);

        if (file.peek() == std::ifstream::traits_type::eof()) isEmtpy = true;

        else isEmtpy = false;

        std::fstream logFile;

        logFile.open(LOG_FILE_NAME, std::ios_base::app | std::ios_base::out);

        if (isEmtpy) {
            logFile << "# LOGS - Social Network\n"
                       "# LOG PROGRAM EXECUTION TIME\n"
                       "# DATE - TYPE [INFO] : VALUE\n\n";
        }

        logFile << date.str()
                << " - INFO [USERS: " << network.size() << "] [EXECUTION TIME: "
                << milliseconds(end - start).count() << " ms]\n";

        logFile.close();
    }

    /** OPEN THE NETWORK? **/
    char choice;
    std::cout << "Open the Social Network? [Y/N]: ";
    std::cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        std::cout << "\nOpening the Social Network..." << std::endl;
        SocialNetwork::open();
    }

    return 0;
}

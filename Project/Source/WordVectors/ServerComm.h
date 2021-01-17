#include <string>

namespace WordVectors {
    class ServerComm {
        public:
            ServerComm(std::string baseEndpoint);

            std::string makeRequest(std::string url);

            std::string getNearestWord(std::string word);
            std::string getWordAddition(std::string firstWord, std::string secondWord);
            std::string getWordSubtraction(std::string firstWord, std::string secondWord);
            std::string getWordAnalogy(std::string firstWord, std::string comparison, std::string secondWord);

        private:
            std::string analogyEndpoint;
            std::string addEndpoint;
            std::string subtractEndpoint;
            std::string nearestEndpoint;
    };
};
#include <CommandTranslator.h>
#include <JSONThingy.h>

CommandTranslator::CommandTranslator() {
    JSONThingy jt;
    jt.load("EN", *this);
}

void CommandTranslator::registerTranslation(const Invocation& invocationWord, CommandType command) {
    std::string lowerCase = utility::toLower(invocationWord);
    translateMap[lowerCase] = std::move(command);
}

CommandType CommandTranslator::translateMe(const std::string& invocationWord) {
    std::string lowerCase = utility::toLower(invocationWord);
    if(translateMap.find(lowerCase) == translateMap.end()) {
        return CommandType::UNKNOWN;
    }
    return translateMap[lowerCase];
}

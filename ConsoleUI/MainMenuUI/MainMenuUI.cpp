#include "MainMenuUI.h"

// void MainMenuUI::InputHandler(ConsoleUI* consoleUI) {
//     this->_commandMap["test"] = [consoleUI](_Argument args){
//         printf("FUck You!");
//     };
// }

MainMenuUI::MainMenuUI(ConsoleUI* consoleUI) : AConsoleUI("MAINMENU_CONSOLE"), _consoleUI(consoleUI) {
    // this->InputHandler(consoleUI);


    this->_commandMap["screen"] = [consoleUI](_Argument args){
        std::cout << "Inside screen command!" << std::endl;
    };

    this->_commandMap["scheduler-start"] = [consoleUI](_Argument args){
        std::cout << "Inside scheduler-start command!" << std::endl;
    };

    this->_commandMap["scheduler-stop"] = [consoleUI](_Argument args){
        std::cout << "Inside scheduler-stop command!" << std::endl;
    };

    this->_commandMap["process-smi"] = [consoleUI](_Argument args){
        std::cout << "Inside process-smi command!" << std::endl;
    };
    
    this->_commandMap["report-util"] = [consoleUI](_Argument args){
        std::cout << "Inside report-util command!" << std::endl;
    };

}

void MainMenuUI::run() {
    std::string inputString;


    while(!this->_initialized){
        std::cout << ":\\> ";
        std::getline(std::cin, inputString);

        if(inputString == "initialize"){
            Config config = Config();
            this->_active=true;
            this->_initialized=true;
            std::cout<< this->_active << "Initialization finished." << std::endl;

            // std::cout<<std::to_string(config.get_numCpu());
        }
        std::cout<<std::endl;
    }

    system("cls");
    this->openingMessage();
    while (this->_active){
        std::cout << this->_name<<":\\> ";
        std::getline(std::cin, inputString);

        std::string baseCommand = inputString.substr(0, inputString.find(" "));

        if (inputString == "exit"){
            this->stop();
            return;
        }


        if (this->_commandMap.find(baseCommand) == this->_commandMap.end()) 
            std::cout << "Command not found." << std::endl;
        else {
            std::stringstream params(inputString);
            std::vector<std::string> args;
            std::string param;
            while(std::getline(params, param, ' ')) args.push_back(param);

            this->_commandMap[baseCommand](args);
        }
        
    }
}

void MainMenuUI::stop() {
    this->_active = false;
}

void MainMenuUI::openingMessage() {
    std::cout << "-----Process Scheduler-----" << std::endl;
}
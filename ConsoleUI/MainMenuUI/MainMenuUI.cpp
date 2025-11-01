#include "MainMenuUI.h"

MainMenuUI::MainMenuUI(ConsoleUI* consoleUI) : AConsoleUI("MAINMENU_CONSOLE"), _consoleUI(consoleUI) {
    // this->InputHandler(consoleUI);


    this->_commandMap["screen"] = [consoleUI](_Argument args){
        std::cout << "Inside screen command!" << std::endl;

    };

    this->_commandMap["scheduler-start"] = [consoleUI](_Argument args){
        std::cout << "Inside scheduler-start command!" << std::endl;
        
    };
    this->_commandMap["t"] = [consoleUI](_Argument args){

        std::cout << "RUNNING TEST COMMAND" << std::endl;

        // ProcessControlBlock pcb;

        // auto pcb = std::make_unique<ProcessControlBlock>(ProcessControlBlock{ 1,"p1",0,READY});
        ProcessControlBlock pcb = ProcessControlBlock{ 1,"p1",0,READY};

        // Declare inst_1 = Declare();

        // // std::vector<std::unique_ptr<Instruction>> *text;
        std::vector<std::shared_ptr<Instruction>> text;
        // text.emplace_back(std::make_unique<Declare>());

        // Making process and generating instruction
        // Process p1 = Process(pcb, text);
        // p1.generateInstruction();
        // p1.listInstructions();

        // Utilizing CPU and Process
        CPU cpu1 = CPU();
        Process p1 = Process(pcb, text);
        while(!p1.isEmpty()){
            cpu1.CPUExecute(p1.getInstruction().get());
            p1.listInstructions();
            p1.deleteTopInstruction();
            std::cout << "----" << std::endl;
        }
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

    // Remove this after testing
    this->_active = true;
    this->_initialized=true;

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
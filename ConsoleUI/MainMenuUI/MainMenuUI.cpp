#include "./MainMenuUI.h"

MainMenuUI::MainMenuUI(ConsoleUI* consoleUI) : AConsoleUI("MAINMENU_CONSOLE"), _consoleUI(consoleUI) {
    // this->InputHandler(consoleUI);

    this->_commandMap["screen"] = [consoleUI](_Argument args){

        
        if(args.at(1) == "-s"){
            std::cout << args.size() << std::endl;
            if(args.size() == 3 ) {
                if(consoleUI->_scheduler->findProcess(args.at(2)) == nullptr){

                    std::cout <<"Creating process " + args.at(2)<<std::endl;

                    ProcessControlBlock pcb = ProcessControlBlock{69420, "p_" + args.at(2),-1};
                    std::shared_ptr<Process> p = std::make_shared<Process>(pcb );
        
                    p->generateInstruction(1,400);
                    consoleUI->_scheduler->addProcess(p);
                    consoleUI->_scheduler->addToReadyQueue(p);

                    // if scheduler is not active
                    // consoleUI->_scheduler->_CPUList

                    // consoleUI->_scheduler->schedulerTest();
                    // consoleUI->createNewConsole("p_" +args.at(2));
                    // consoleUI->_scheduler->stop();
                //     // if (consoleUI->_scheduler->isRunning())
                }
                else {
                    // consoleUI->_scheduler->schedulerTest();
                    consoleUI->createNewConsole(args.at(2));
                    // consoleUI->_scheduler->stop();
                }
            }
            
        }
        else if(args.at(1) == "-r")
            consoleUI->switchConsole(args.at(2));
        else if(args.at(1) == "-ls")
            // std::cout<< "Implement consoleUI->_scheduler->printStatus()" << std::endl;
            consoleUI->_scheduler->printStatus();
        else {
            std::cout << "Invalid input" << std::endl;
            std::cout << "args.at(0): " << args.at(0) << std::endl;
            std::cout << "args.at(1): " << args.at(1) << std::endl;
            return;
        }
            
    };

    this->_commandMap["scheduler-start"] = [consoleUI](_Argument args){
        consoleUI->_scheduler->schedulerTest();
    };
    this->_commandMap["t"] = [consoleUI](_Argument args){

        std::cout << "RUNNING TEST COMMAND" << std::endl;


    };

    this->_commandMap["scheduler-stop"] = [consoleUI](_Argument args){
        std::cout << "Inside scheduler-stop command!" << std::endl;
        consoleUI->_scheduler->stop();
    };

    this->_commandMap["process-smi"] = [consoleUI](_Argument args){
        std::cout << "Inside process-smi command!" << std::endl;
        consoleUI->_scheduler->processSMI();
    };
    
    this->_commandMap["report-util"] = [consoleUI](_Argument args){
        std::cout << "Inside report-util command!" << std::endl;
        consoleUI->_scheduler->reportUtil();
    };

}

void MainMenuUI::run() {
    std::string inputString;

    // Remove this after testing
    // this->_active = true;
    // this->_initialized=true;

    while(!this->_initialized){
        std::cout << "Input 'initialize' to begin..." << std::endl;
        std::cout << ":\\> ";
        std::getline(std::cin, inputString);

        if(inputString == "initialize"){
            Clock::start(100);
            Config config = Config();
            config.initialize();

            Scheduler::initialize(
                config.get_numCpu(),
                config.get_scheduler(),
                config.get_quantumCycle(),
                config.get_batchProcessFreq(),
                config.get_minIns(),
                config.get_maxIns(),
                config.get_delaysPerExec()
            );

            Scheduler* s= Scheduler::get();
            // std::make_shared<Scheduler> s = Scheduler::get();

            this->_consoleUI->_scheduler = s;

            if(this->_consoleUI->_scheduler == nullptr){
                std::cout << "initialized scheduler is null..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            } 

            std::string sType = config.get_scheduler();
            std::cout << sType << std::endl;
            if (sType == "fcfs"){
                s->runFCFS(config.get_delaysPerExec());
            }
            if (sType == "rr"){
                s->runRR(config.get_delaysPerExec(), config.get_quantumCycle());
            }

            // std::cout<< this->_active << "Initialization finished." << std::endl;
            // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            this->_initialized=true;
            this->_active=true;
            // std::cout<<std::to_string(config.get_numCpu());
        }
        std::cout<<std::endl;
    }

    this->_active=true;
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

void MainMenuUI::display(){
    std::cout << "MainMenuUI" << std::endl;
}

void MainMenuUI::openingMessage() {
    std::cout << "-----Process Scheduler-----" << std::endl;
}
#include "./MainMenuUI.h"


MainMenuUI::MainMenuUI(ConsoleUI* consoleUI) : AConsoleUI("MAINMENU_CONSOLE"), _consoleUI(consoleUI) {

    this->_commandMap["screen"] = [consoleUI](_Argument args){

        
        if(args.at(1) == "-s"){
            // for (std::string s : args){
            //     std::cout << s << std::endl;
            // }
            if(args.size() == 4 ) {
                if(consoleUI->_scheduler->findProcess(args.at(2)) == nullptr){
                    std::cout << "Allocating " << args.at(3) << " bytes of memory to Process " << args.at(2) << std::endl;
                    consoleUI->_scheduler->createProcess(args.at(2), stoi(args.at(3)));
                }

                // consoleUI->_scheduler->schedulerTest();
                consoleUI->createNewConsole(args.at(2));
                // consoleUI->_scheduler->stop();
            }
            
        }
        else if(args.at(1) == "-r")
            consoleUI->switchConsole(args.at(2));
        else if(args.at(1) == "-ls")
            // std::cout<< "Implement consoleUI->_scheduler->printStatus()" << std::endl;
            consoleUI->_scheduler->printStatus();

        else if(args.at(1) == "-c"){

        }
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
    
    this->_commandMap["report-util"] = [consoleUI](_Argument args){
        consoleUI->_scheduler->reportUtil();
    };
    
    this->_commandMap["process-smi"] = [consoleUI](_Argument args) {

        consoleUI->_scheduler->processSMI();
        
        // for (std::shared_ptr<Process> process : consoleUI->_scheduler->getProcesses())
        //     std::cout << process->getName() << "\t" << process->getRequiredMemory() <<std::endl;
        

    };

    this->_commandMap["vmstat"] = [consoleUI](_Argument args) {
        consoleUI->_scheduler->vmstat();
    };
}

void MainMenuUI::run() {
    std::string inputString;

    while(!this->_initialized){
        std::cout << "Input 'initialize' to begin..." << std::endl;
        std::cout << ":\\> ";
        std::getline(std::cin, inputString);

        if(inputString == "initialize"){
            Clock::start(100);
            Config config = Config();
            config.initialize();

            if ( (config.get_minMemPerProc()/config.get_memPerFrame()) != 1 && (config.get_maxMemPerProc()/config.get_memPerFrame()) != 1)
                Process::setRequiredMemory(config.get_minMemPerProc()/config.get_memPerFrame(), config.get_maxMemPerProc()/config.get_memPerFrame());

            Scheduler::initialize(
                config.get_numCpu(),
                config.get_scheduler(),
                config.get_quantumCycle(),
                config.get_batchProcessFreq(),
                config.get_minIns(),
                config.get_maxIns(),
                config.get_delaysPerExec(),
                config.get_maxOverallMem(),
                config.get_memPerFrame(),
                config.get_minMemPerProc(),
                config.get_maxMemPerProc()
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
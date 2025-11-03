#include "ProcessUI.h"

ProcessUI::ProcessUI(std::shared_ptr<Process> process) :
    AConsoleUI(process->getName()),
    _process(process) {}

void ProcessUI::run() {
    if(this->_process->isEmpty()){
        this->_removable = true;
        return;
    }

    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    system("cls");
    this->_active = true;
    if(this->_pastDisplays == "")
        this->display();

    std::string inputString;
    std::string getProcessName = this->_process->getName();

    while(this->_active){
        std::cout << getProcessName << ":\\> ";
        std::getline(std::cin, inputString);

        if (inputString == "exit"){
            this->stop();
            return;
        }

        this->_pastDisplays += getProcessName + ":\\ " + "\n";
        if (inputString == "process-smi"){
            this->display();
            continue;
        }

    }

}

void ProcessUI::stop() {
    std::cout << "Exiting from process: " << this->_process->getName() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    if (this->_process->isEmpty()) this->_removable= true;
    this->_active = false;
}
void ProcessUI::display(){
    std::string out = 
    "Process " + this->_process->getName()+ "\n" +"ID: " + std::to_string(this->_process->getID()) + "\n";

    if(this->_process->getState() == ProcessState::TERMINATED)
        std::cout << this->_process->getName() << " finished successfully"<< std::endl;
    else{
        std::cout << this->_process->getName() << " is " << std::to_string(this->_process->getState())<< std::endl;
        out += "Currently on instruction: " + std::to_string(this->_process->getProgramCounter())+ "\n";
        + "Number of Instructions: " + std::to_string(this->_process->getInstructionSetSize()) + "\n";
    }

    std::cout << out;
    
    this->_pastDisplays += out;
}

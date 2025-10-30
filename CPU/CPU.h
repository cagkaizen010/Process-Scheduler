#ifndef CPU_H
#define CPU_H
class CPU {
    public:

        void setNumCPU(int);
        void setBatchProcessFreq(int);
        void setDelaysPerExec(int);
    private:
        CPU();
        ~CPU() = default;

        int numCPU;
        float batchProcessFreq;
        float delaysPerExec;
};

#endif
#ifndef SIMTYPE_H
#define SIMTYPE_H

class globleSimDataDef
{
public:
    bool simStartFlag;
    bool connectFlag;

    void dataInit();
};

extern globleSimDataDef globleSimData;

#endif // SIMTYPE_H
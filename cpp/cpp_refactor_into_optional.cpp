#include <iostream>
#include <tuple>
#include <optional>

class ObjSelection
{
public:
    bool IsValid() const { return true; }
};

bool CheckSelectionVer1(const ObjSelection &objList, bool *pOutAnyCivilUnits, bool *pOutAnyCombatUnits, int *pOutNumAnimating)
{
    if (!objList.IsValid())
        return false;
    
    // local variables:
    int numCivilUnits = 0;
    int numCombat = 0;
    int numAnimating = 0;
    
    // scan...
    
    // set values:
    if (pOutAnyCivilUnits)
        *pOutAnyCivilUnits = numCivilUnits > 0;
        
    if (pOutAnyCombatUnits)
        *pOutAnyCombatUnits = numCombat > 0;
    
    if (pOutNumAnimating)
        *pOutNumAnimating = numAnimating;
    
    return true;
}

std::tuple<bool, bool, bool, int> CheckSelectionVer2(const ObjSelection &objList)
{
    if (!objList.IsValid())
        return {false, false, false, 0};
    
    // local variables:
    int numCivilUnits = 0;
    int numCombat = 0;
    int numAnimating = 0;
    
    // scan...
    
    return {true, numCivilUnits > 0, numCombat > 0, numAnimating };
}

struct SelectionData
{
    bool anyCivilUnits { false };
    bool anyCombatUnits { false };
    int numAnimating { 0 };
};

std::pair<bool, SelectionData> CheckSelectionVer3(const ObjSelection &objList)
{
    SelectionData out;
    
    if (!objList.IsValid())
        return {false, out};

    
    // scan...
    
    return {true, out};
}

std::optional<SelectionData> CheckSelectionVer4(const ObjSelection &objList)
{   
    if (!objList.IsValid())
        return { };

    SelectionData out;   
    // scan...
    
    return {out};
}

int main()
{
    ObjSelection sel;
    
    bool anyCivilUnits = false;
    bool anyCombatUnits = false;
    int numAnimating = 0;
    if (CheckSelectionVer1(sel, &anyCivilUnits, &anyCombatUnits, &numAnimating))
        std::cout << "ok...\n";
        
    auto [ok, anyCivilVer2, anyCombatVer2, numAnimatingVer2] = CheckSelectionVer2(sel);
    if (ok)
        std::cout << "ok...\n";
        
    auto retV4 = CheckSelectionVer4(sel);
    if (retV4.has_value())
        std::cout << "ok...\n";
}
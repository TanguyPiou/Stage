#pragma once
#include <vector>
#include <string>
class Tortue {
public:

    Tortue(std::string nom, float PV, float pointEndu, int degats, int pos);

    std::string nom() const;
    float PV() const;
    void setPV(float newPV);
    float PE() const;
    void setPE(float newPE);
    int degats() const;
    void setDegats(int degats);
    int pos() const;
    void setPos(int newPos);
    bool tir() const;
    void setTir(bool tir);


private:
    std::string _nom;
    float _PV;
    float _PE;
    int _degats;
    int _pos;
    bool _tir;
};

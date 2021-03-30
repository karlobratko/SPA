#pragma once

#include <ostream>
#include <string>

class Pokemon
{
public:
	Pokemon();

	void SetData(std::string&);
	void SetID(const int);
	void SetName(const std::string&);
	void SetType1(const std::string&);
	void SetType2(const std::string&);
	void SetTotal(const int);
	void SetHP(const int);
	void SetAtk(const int);
	void SetDef(const int);
	void SetSPAtk(const int);
	void SetSPDef(const int);
	void SetSpeed(const int);
	void SetGen(const int);
	void SetIsLegendary(const bool);

	std::string GetName() const;

	double CalculateDMG(const Pokemon&) const;

	Pokemon& Fight(Pokemon&);

	friend std::ostream& operator<<(std::ostream&, const Pokemon&);

private:
	int m_ID;
	char m_Name[30];
	char m_Type1[10];
	char m_Type2[10];
	int m_Total;
	int m_HP;
	int m_Atk;
	int m_Def;
	int m_SPAtk;
	int m_SPDef;
	int m_Speed;
	int m_Gen;
	bool m_IsLegendary;
};


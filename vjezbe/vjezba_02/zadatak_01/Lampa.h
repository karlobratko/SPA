#pragma once

#include <string>
#include <ostream>

class Lampa {
public:
	friend std::ostream& operator<<(std::ostream&, const Lampa&);

	Lampa(const std::string& = "");

	void SetModel(const std::string&);
	void SetProizvodjac(const std::string&);
	void SetSijaliceCount(const int&);
	void SetSnaga(const double&);

	const std::string& GetModel() const;
	const std::string& GetProizvodjac() const;
	const int& GetSijaliceCount() const;
	const double& GetSnaga() const;


private:
	std::string m_Naziv;
	std::string m_Proizvodjac;
	int m_SijaliceCount;
	double m_Snaga;

};


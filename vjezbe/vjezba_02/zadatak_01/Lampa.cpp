#include "Lampa.h"

std::ostream& operator<<(std::ostream& os, const Lampa& lampa) {
  os
    << lampa.m_Naziv << ", "
    << lampa.m_Proizvodjac << ", "
    << lampa.m_SijaliceCount << ", "
    << lampa.m_Snaga;
  return os;
}

Lampa::Lampa(const std::string& p_Naziv) 
  : m_Naziv{ p_Naziv }, m_Proizvodjac{ "" }, m_SijaliceCount{ 0 }, m_Snaga{ 0 } {
}

void Lampa::SetModel(const std::string& p_Model) {
  m_Naziv = p_Model;
}

void Lampa::SetProizvodjac(const std::string& p_Proizvodjac) {
  m_Proizvodjac = p_Proizvodjac;
}

void Lampa::SetSijaliceCount(const int& p_SijaliceCount) {
  m_SijaliceCount = p_SijaliceCount;
}

void Lampa::SetSnaga(const double& p_Snaga) {
  m_Snaga = p_Snaga;
}

const std::string& Lampa::GetModel() const {
  return m_Naziv;
}

const std::string& Lampa::GetProizvodjac() const {
  return m_Proizvodjac;
}

const int& Lampa::GetSijaliceCount() const {
  return m_SijaliceCount;
}

const double& Lampa::GetSnaga() const {
  return m_Snaga;
}

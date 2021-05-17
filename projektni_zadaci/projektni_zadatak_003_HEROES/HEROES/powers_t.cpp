#include "powers_t.h"

#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>

std::array<std::string, 167> powers_t::power_names_{ "Agility","Accelerated Healing","Lantern Power Ring","Dimensional Awareness","Cold Resistance","Durability","Stealth","Energy Absorption","Flight","Danger Sense","Underwater breathing","Marksmanship","Weapons Master","Power Augmentation","Animal Attributes","Longevity","Intelligence","Super Strength","Cryokinesis","Telepathy","Energy Armor","Energy Blasts","Duplication","Size Changing","Density Control","Stamina","Astral Travel","Audio Control","Dexterity","Omnitrix","Super Speed","Possession","Animal Oriented Powers","Weapon - based Powers","Electrokinesis","Darkforce Manipulation","Death Touch","Teleportation","Enhanced Senses","Telekinesis","Energy Beams","Magic","Hyperkinesis","Jump","Clairvoyance","Dimensional Travel","Power Sense","Shapeshifting","Peak Human Condition","Immortality","Camouflage","Element Control","Phasing","Astral Projection","Electrical Transport","Fire Control","Projection","Summoning","Enhanced Memory","Reflexes","Invulnerability","Energy Constructs","Force Fields","Self - Sustenance","Anti - Gravity","Empathy","Power Nullifier","Radiation Control","Psionic Powers","Elasticity","Substance Secretion","Elemental Transmogrification","Technopath / Cyberpath","Photographic Reflexes","Seismic Power","Animation","Precognition","Mind Control","Fire Resistance","Power Absorption","Enhanced Hearing","Nova Force","Insanity","Hypnokinesis","Animal Control","Natural Armor","Intangibility","Enhanced Sight","Molecular Manipulation","Heat Generation","Adaptation","Gliding","Power Suit","Mind Blast","Probability Manipulation","Gravity Control","Regeneration","Light Control","Echolocation","Levitation","Toxinand Disease Control","Banish","Energy Manipulation","Heat Resistance","Natural Weapons","Time Travel","Enhanced Smell","Illusions","Thirstokinesis","Hair Manipulation","Illumination","Omnipotent","Cloaking","Changing Armor","Power Cosmic","Biokinesis","Water Control","Radiation Immunity","Vision - Telescopic","Toxinand Disease Resistance","Spatial Awareness","Energy Resistance","Telepathy Resistance","Molecular Combustion","Omnilingualism","Portal Creation","Magnetism","Mind Control Resistance","Plant Control","Sonar","Sonic Scream","Time Manipulation","Enhanced Touch","Magic Resistance","Invisibility","Sub - Mariner","Radiation Absorption","Intuitive aptitude","Vision - Microscopic","Melting","Wind Control","Super Breath","Wallcrawling","Vision - Night","Vision - Infrared","Grim Reaping","Matter Absorption","The Force","Resurrection","Terrakinesis","Vision - Heat","Vitakinesis","Radar Sense","Qwardian Power Ring","Weather Control","Vision - X - Ray","Vision - Thermal","Web Creation","Reality Warping","Odin Force","Symbiote Costume","Speed Force","Phoenix Force","Molecular Dissipation","Vision - Cryo","Omnipresent","Omniscient" };

powers_t::powers_t(std::string name) : 
  name_{ name } {
}

powers_t::powers_t(const powers_t& other) : 
  name_{ other.name_ },
  flags_{ other.flags_ } {
}

std::string powers_t::get_name() const {
  return name_;
}

bool powers_t::has_power(const std::string& power) const {
  auto it = std::find(std::begin(power_names_), std::end(power_names_), power);
  if (it == std::end(power_names_)) return false;
  return flags_.at(std::distance(std::begin(power_names_), it));
}

bool powers_t::valid_power(const std::string& power) {
  auto it = std::find(std::begin(power_names_), std::end(power_names_), power);
  return it != std::end(power_names_);
}

std::array<bool, 167>* powers_t::operator->() {
  return &flags_;
}

std::istream& operator>>(std::istream& is, powers_t& powers) {
  std::string line{};
  std::getline(is, line);
  if (!is.eof()) {
    std::istringstream iss{ line };
    std::getline(iss, powers.name_, ',');
    std::string temp{};
    for (std::size_t i{ 0 }; i < powers.flags_.size(); ++i) {
      std::getline(iss, temp, ',');
      powers.flags_.at(i) = (temp == "False" ? false : true);
    }
    if (iss.fail()) is.setstate(iss.rdstate());
  }
  else is.setstate(std::ios::eofbit);
  return is;
}

std::ostream& operator<<(std::ostream& os, const powers_t& powers) {
  std::ostringstream oss{};
  std::copy(std::begin(powers.flags_), std::end(powers.flags_), std::ostream_iterator<bool>(oss, ""));
  if (!oss) os.setstate(oss.rdstate());
  else os << oss.str();
  return os;
}

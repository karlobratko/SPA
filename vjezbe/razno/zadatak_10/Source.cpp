#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <iomanip>

const char* file_name_I{ "music.csv" };
const char* file_name_O{ "music_bin.dat" };

class file_except_t : public std::exception {
public:
	file_except_t() noexcept = default;
	~file_except_t() = default;
	virtual const char* what() const noexcept {
		return "FSTREAM::could not open file";
	}
};

class date_t {
public:
	date_t(unsigned year = 0, unsigned month = 0, unsigned day = 0) : 
		year_	{ year	},
		month_{ month },
		day_	{ day		} {
	}
	bool valid() {
		return year_ > 1900 && month_ > 0 && month_ <= 12 && day_ > 0 && day_ <= 31;
	}
	friend std::istream& operator>>(std::istream& is, date_t& date) {
		unsigned year{}, month{}, day{};
		char c{};
		is >> day >> c >> month >> c >> year;
		if (is) {
			date.year_ = year;
			date.month_ = month;
			date.day_ = day;
			if (!date.valid()) is.setstate(std::ios::failbit);
		}
		return is;
	}
	friend std::ostream& operator<<(std::ostream& os, const date_t& date) {
		std::ostringstream oss{};
		oss
			<< std::setw(2) << date.day_															<< " "
			<< std::setw(3) << date.month_names_abbr[date.month_ - 1] << " "
			<< std::setw(4) << date.year_;
		if (!oss) os.setstate(oss.rdstate());
		else os << oss.str();
		return os;
	}

private:
	static const char* month_names_abbr[12];
	unsigned year_, month_, day_;

};

const char* date_t::month_names_abbr[12]{
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

class song_t {
public:
	song_t(const char* artist = "undefined", const char* track = "undefined", date_t date = date_t{}) {
		strcpy_s(artist_, artist);
		strcpy_s(track_, track);
		date_ = date;
	}
	friend std::istream& operator>>(std::istream& is, song_t& song) {
		std::string line{};
		std::getline(is, line);
		if (!is.eof()) {
			std::istringstream iss{ line };
			std::string temp;
			std::getline(iss, temp, ';');
			iss.getline(song.artist_, 90, ';');
			std::getline(iss, temp, ';');
			iss.getline(song.track_, 90, ';');
			iss >> song.date_;
			if (iss.fail()) is.setstate(iss.rdstate());
		}
		else is.setstate(std::ios::eofbit);
		return is;
	}
	friend std::ostream& operator<<(std::ostream& os, const song_t& song) {
		std::ostringstream oss{};
		oss
			<< std::left
			<< std::setw(90) << song.artist_	<< " "
			<< std::setw(90) << song.track_		<< " "
			<< std::setw(15) << song.date_;
		if (!oss) os.setstate(oss.rdstate());
		else os << oss.str();
		return os;
	}

private:
	char artist_[90]{}, track_[90]{};
	date_t date_;

};

int main() {
	try {
		std::fstream file{};
		std::vector<song_t> songs{};
		file.open(file_name_I, std::ios::in);
		if (file.is_open()) {
			std::copy(std::istream_iterator<song_t>(file), std::istream_iterator<song_t>(), std::back_inserter(songs));
			file.close();
		}
		else throw file_except_t{};

		file.open(file_name_O, std::ios::out | std::ios::binary | std::ios::trunc);
		if (file.is_open()) {
			file.write(reinterpret_cast<char*>(songs.data()), sizeof(song_t) * static_cast<__int64>(songs.size()));
			file.close();
		}
		else throw file_except_t{};

		std::vector<song_t> new_songs{};
		file.open(file_name_O, std::ios::in | std::ios::binary);
		if (file.is_open()) {
			file.seekg(0, std::ios::end);
			new_songs.resize(file.tellg() / sizeof(song_t));
			file.seekg(0, std::ios::beg);
			file.read(reinterpret_cast<char*>(new_songs.data()), sizeof(song_t) * static_cast<__int64>(new_songs.size()));
			file.close();
		}
		else throw file_except_t{};

		std::copy(std::begin(new_songs), std::end(new_songs), std::ostream_iterator<song_t>(std::cout, "\n"));
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
		return 1;
	}

	return 0;
}
#include "multimedia_t.h"

#include <sstream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include "json.h"

const std::map<std::uint8_t, std::string> multimedia_t::country_key{
	{ 1,		"India"},
	{ 2,		"United States"},
	{ 3,		"United Kingdom"},
	{ 4,		"Belgium"},
	{ 5,		"Uruguay"},
	{ 6,		"Canada"},
	{ 7,		"France"},
	{ 8,		"Morocco"},
	{ 9,		"China"},
	{ 10,		"Mexico"},
	{ 11,		"Argentina"},
	{ 12,		"Greece"},
	{ 13,		"Switzerland"},
	{ 14,		"Denmark"},
	{ 15,		"Australia"},
	{ 16,		"Brazil"},
	{ 17,		"Germany"},
	{ 18,		"Senegal"},
	{ 19,		"Soviet Union"},
	{ 20,		"Spain"},
	{ 21,		"Hong Kong"},
	{ 22,		"Italy"},
	{ 23,		"Norway"},
	{ 24,		"Ukraine"},
	{ 25,		"South Africa"},
	{ 26,		"Indonesia"},
	{ 27,		"Poland"},
	{ 28,		"Portugal"},
	{ 29,		"Czech Republic"},
	{ 30,		"Malaysia"},
	{ 31,		"Luxembourg"},
	{ 32,		"Austria"},
	{ 33,		"Bulgaria"},
	{ 34,		"West Germany"},
	{ 35,		"United Arab Emirates"},
	{ 36,		"Jordan"},
	{ 37,		"Israel"},
	{ 38,		"Iceland"},
	{ 39,		"Malta"},
	{ 40,		"Sweden"},
	{ 41,		"Ireland"},
	{ 42,		"Russia"},
	{ 43,		"Japan"},
	{ 44,		"Chile"},
	{ 45,		"Netherlands"},
	{ 46,		"New Zealand"},
	{ 47,		"South Korea"},
	{ 48,		"Iran"},
	{ 49,		"Qatar"},
	{ 50,		"Iraq"},
	{ 51,		"Thailand"},
	{ 52,		"Pakistan"},
	{ 53,		"Slovakia"},
	{ 54,		"Cambodia"},
	{ 55,		"Finland"},
	{ 56,		"Colombia"},
	{ 57,		"Botswana"},
	{ 58,		"Taiwan"},
	{ 59,		"Malawi"},
	{ 60,		"Kenya"},
	{ 61,		"Sri Lanka"},
	{ 62,		"Peru"},
	{ 63,		"Singapore"},
	{ 64,		"Croatia"},
	{ 65,		"Slovenia"},
	{ 66,		"Nepal"},
	{ 67,		"Vatican City"},
	{ 68,		"Egypt"},
	{ 69,		"East Germany"},
	{ 70,		"Venezuela"},
	{ 71,		"Namibia"},
	{ 72,		"Cuba"},
	{ 73,		"Hungary"},
	{ 74,		"Azerbaijan"},
	{ 75,		"Nicaragua"},
	{ 76,		"Romania"},
	{ 77,		"Kazakhstan"},
	{ 78,		"Turkey"},
	{ 79,		"Armenia"},
	{ 80,		"Bermuda"},
	{ 81,		"Syria"},
	{ 82,		"Zimbabwe"},
	{ 83,		"United States"},
	{ 84,		"United Kingdom"},
	{ 85,		"Spain"},
	{ 86,		"Bulgaria"},
	{ 87,		"Chile"},
	{ 88,		"Netherlands"},
	{ 90,		"France"},
	{ 91,		"Thailand"},
	{ 92,		"China"},
	{ 93,		"Belgium"},
	{ 94,		"India"},
	{ 95,		"Pakistan"},
	{ 96,		"Canada"},
	{ 97,		"South Korea"},
	{ 98,		"Denmark"},
	{ 99,		"Turkey"},
	{ 100,	"Brazil"},
	{ 101,	"Indonesia"},
	{ 102,	"Ireland"},
	{ 103,	"Hong Kong"},
	{ 104,	"Mexico"},
	{ 105,	"Vietnam"},
	{ 106,	"Nigeria"},
	{ 107,	"Japan"},
	{ 108,	"Norway"},
	{ 109,	"Lebanon" },
	{ 110,	"Philippines" },
	{ 111,	"Serbia" },
	{ 112,	"Cayman Islands" },
	{ 113,	"Saudi Arabia" },
	{ 114,	"Liechtenstein" },
	{ 115,	"Albania" },
	{ 116,  "Samoa" },
	{ 117,	"Ghana" },
	{ 118,	"Guatemala" },
	{ 119,	"Paraguay" },
	{ 120,	"Somalia" },
	{ 121,	"Sudan" },
	{ 122,	"Dominican Republic" },
	{ 123,	"Panama" },
	{ 124,	"Latvia" },
	{ 125,	"Uganda" },
	{ 126,  "Montenegro" },
	{ 127,	"Bangladesh" },
	{ 128,	"Afghanistan" },
	{ 129,	"Georgia" },
	{ 130,	"Mauritius" },
	{ 131,	"Mongolia" },
	{ 132,	"Ecuador" },
	{ 133,	"Kuwait" },
	{ 134,	"Cyprus" },
};
const std::map<std::uint8_t, std::string> multimedia_t::rating_key{
	{1,		"TV-PG"},
	{2,		"TV-MA"},
	{3,		"TV-Y7-FV"},
	{4,		"TV-Y7"},
	{5,		"TV-14"},
	{6,		"R"},
	{7,		"TV-Y"},
	{8,		"NR"},
	{9,		"PG-13"},
	{10,	"TV-G"},
	{11,	"PG"},
	{12,	"G"},
	{13,	"UR"},
	{14,	"NC-17"}
};
const std::map<std::uint8_t, std::string> multimedia_t::genre_key{
	{1 ,"Children & Family Movies" },
	{2 ,"Stand-Up Comedy" },
	{3 ,"Kids' TV" },
	{4 ,"Comedies" },
	{5 ,"Crime TV Shows" },
	{6 ,"International Movies" },
	{7 ,"Docuseries" },
	{8 ,"Action & Adventure" },
	{9 ,"Cult Movies" },
	{10 ,"Documentaries" },
	{11 ,"Horror Movies" },
	{12 ,"Dramas" },
	{13 ,"International TV Shows" },
	{14 ,"Romantic TV Shows" },
	{15 ,"TV Comedies" },
	{16 ,"British TV Shows" },
	{17 ,"Anime Features" },
	{18 ,"Independent Movies" },
	{19 ,"Reality TV" },
	{20 ,"Anime Series" },
	{21 ,"TV Horror" },
	{22 ,"Movies" },
	{23 ,"Stand-Up Comedy & Talk Shows" },
	{24 ,"Thrillers" },
	{25 ,"TV Action & Adventure" },
	{26 ,"Classic Movies" },
	{27 ,"TV Dramas" },
	{28 ,"Music & Musicals" },
	{29 ,"Sci-Fi & Fantasy" },
	{30 ,"TV Shows" },
	{31 ,"Spanish-Language TV Shows" },
	{32 ,"Sports Movies" },
	{33 ,"Classic & Cult TV" },
	{34 ,"Romantic Movies" },
	{35 ,"TV Sci-Fi & Fantasy" },
	{36 ,"Science & Nature TV" },
	{37 ,"Korean TV Shows" },
	{38 ,"Teen TV Shows" },
	{39 ,"LGBTQ Movies" },
	{40 ,"TV Mysteries" },
	{41 ,"TV Thrillers" },
	{42 ,"Faith & Spirituality" },
};

void split_string_by(std::string& str, std::vector<std::string>& vec, const char delim) {
	std::istringstream iss{ str };
	std::string buff{};
	while (std::getline(iss, buff, delim)) {
		vec.emplace_back(buff); iss.get();
	}
}

void value_vec_to_key_vec(std::vector<std::string>& value_vec, std::vector<std::uint8_t>& key_vec, const std::map<std::uint8_t, std::string>& referential_map) {
	if (value_vec.empty()) return;
	std::transform(
		std::begin(value_vec),
		std::end(value_vec),
		std::back_inserter(key_vec),
		[&referential_map](const std::string& value) -> std::uint8_t {
			auto it = std::find_if(
				std::begin(referential_map),
				std::end(referential_map),
				[&value](const std::pair<std::uint8_t, std::string>& pair) {
					return pair.second == value;
				}
			);
			return it->first;
		}
	);
}

void read_quoted_until_delim(std::istringstream& iss, std::string& buff, const char delim) {
	buff.clear();
	iss.get();
	char c{};
	while (true) {
		c = iss.get();
		if (c == '"' && iss.peek() == delim) break;
		else if (c == '"') { buff.push_back('\\'); c = iss.get(); }
		buff.push_back(c);
	}
	iss.get();
}

std::istream& operator>>(std::istream& is, multimedia_t& media) {
	std::string line{};
	std::getline(is, line);
	media = multimedia_t{};
	if (!is.eof()) {
		std::istringstream iss{ line };
		std::string buff{};
		// id - std::uint64_t
		iss >> media.id_; iss.get();

		// type - bool
		std::getline(iss, buff, ',');
		media.type_ = (buff == "Movie" ? true : false);

		// title - std::string
		if (iss.peek() == '"')
			read_quoted_until_delim(iss, media.title_, ',');
		else
			std::getline(iss, media.title_, ',');

		// director - std::vector<std::string>
		if (iss.peek() == '"') {
			read_quoted_until_delim(iss, buff, ',');
			split_string_by(buff, media.director_, ',');
		}
		else {
			std::getline(iss, buff, ',');
			if (!buff.empty()) media.director_.emplace_back(buff);
		}

		// cast - std::vector<std::string>
		if (iss.peek() == '"') {
			read_quoted_until_delim(iss, buff, ',');
			split_string_by(buff, media.cast_, ',');
		}
		else {
			std::getline(iss, buff, ',');
			if (!buff.empty()) media.cast_.emplace_back(buff);
		}
		// country - std::vector<std::uint8_t>

		std::vector<std::string> country_temp{};
		if (iss.peek() == '"') {
			iss.get();
			std::getline(iss, buff, '"'); iss.get();
			split_string_by(buff, country_temp, ',');
		}
		else {
			std::getline(iss, buff, ',');
			if (!buff.empty()) country_temp.emplace_back(buff);
		}
		value_vec_to_key_vec(country_temp, media.country_, multimedia_t::country_key);

		// date - date_t
		if (iss.get() == '"') {
			std::getline(iss, buff, '"'); iss.get();
			std::istringstream iss_date{ buff };
			iss_date >> media.date_;
		}
		else
			media.date_ = date_t{};

		// release - std::uint16_t
		iss >> media.release_; iss.get();

		// rating - std::vector<std::uint8_t>
		std::vector<std::string> rating_temp{};
		if (iss.peek() == '"') {
			iss.get();
			std::getline(iss, buff, '"'); iss.get();
			split_string_by(buff, rating_temp, ',');
		}
		else {
			std::getline(iss, buff, ',');
			if (!buff.empty()) rating_temp.emplace_back(buff);
		}
		value_vec_to_key_vec(rating_temp, media.rating_, multimedia_t::rating_key);

		// duration - std::string
		std::getline(iss, media.duration_, ',');

		// genre - std::vector<std::uint8_t>
		std::vector<std::string> genre_temp{};
		if (iss.peek() == '"') {
			iss.get();
			std::getline(iss, buff, '"'); iss.get();
			split_string_by(buff, genre_temp, ',');
		}
		else {
			std::getline(iss, buff, ',');
			if (!buff.empty()) genre_temp.emplace_back(buff);
		}
		value_vec_to_key_vec(genre_temp, media.genre_, multimedia_t::genre_key);

		// description - std::string
		if (iss.peek() == '"') {
			iss.get();
			std::getline(iss, media.description_, '"');
		}
		else 
			std::getline(iss, media.description_);

		if (iss.fail()) is.setstate(iss.rdstate());
	}
	else is.setstate(std::ios_base::eofbit);
	return is;
}

void stringify_key(std::ostringstream& oss, const std::string& key, const std::int64_t depth) {
	oss << std::string(depth, '\t') << "\"" << key << "\": ";
}

template <typename _Type, typename _Function>
void stringify_vec(std::ostringstream& oss, const std::string& key, _Function function, const std::vector<_Type>& vec, const std::int64_t depth) {
	stringify_key(oss, key, depth);
	if (vec.empty())
		oss << "null,\n";
	else {
		oss << "[\n";
		std::for_each(
			std::begin(vec),
			std::end(vec),
			[&oss, i = 0, &vec, &function](const _Type& value) mutable -> void {
			function(oss, value, i, vec.size());
			++i;
		}
		);
		oss << std::string(depth, '\t') << "],\n";
	}
}

void stringify_integer(std::ostringstream& oss, const std::string& key, const std::uint64_t& value, const std::int64_t depth) {
	stringify_key(oss, key, depth);
	oss << value << ",\n";
}

void stringify_string(std::ostringstream& oss, const std::string& key, const std::string& value, const std::int64_t depth) {
	stringify_key(oss, key, depth);
	oss << "\"" << value << "\",\n";
}

void stringify_date(std::ostringstream& oss, const date_t& date, const std::int64_t depth) {
	stringify_key(oss, "date", depth);
	oss
		<< "{\n"
		<< std::string(depth + 1, '\t') << "\"year\": " << date.get_year() << ",\n"
		<< std::string(depth + 1, '\t') << "\"month\": " << date.get_month() << ",\n"
		<< std::string(depth + 1, '\t') << "\"day\": " << date.get_day() << "\n"
		<< std::string(depth, '\t') << "},\n";
}

std::ostream& operator<<(std::ostream& os, const multimedia_t& media) {
	std::ostringstream oss{};
	oss << "\t{\n";
	stringify_integer(oss, "id", media.id_, 2);
	stringify_string(oss, "type", (media.type_ ? "Movie" : "TV Show"), 2);
	stringify_string(oss, "title", media.title_, 2);
	
	stringify_vec(
		oss, 
		"director",
		[](std::ostringstream& oss, const std::string& director, std::size_t i, std::size_t size) mutable -> void {
			oss
				<< "\t\t\t\"" << director
				<< (i != size - 1 ? "\"," : "\"") << "\n";
		},
		media.director_,
		2
	);

	stringify_vec(
		oss,
		"cast",
		[](std::ostringstream& oss, const std::string& cast, std::size_t i, std::size_t size) mutable -> void {
			oss
				<< "\t\t\t\"" << cast
				<< (i != size - 1 ? "\"," : "\"") << "\n";
		},
		media.cast_,
		2
	);

	stringify_vec(
		oss,
		"country",
		[](std::ostringstream& oss, const std::uint8_t key, std::size_t i, std::size_t size) mutable -> void {
			oss
				<< "\t\t\t\"" << multimedia_t::country_key.at(key)
				<< (i != size - 1 ? "\"," : "\"") << "\n";
		},
		media.country_,
		2
	);

	stringify_date(oss, media.date_, 2);

	stringify_integer(oss, "release", media.release_, 2);

	stringify_vec(
		oss,
		"rating",
		[](std::ostringstream& oss, const std::uint8_t key, std::size_t i, std::size_t size) mutable -> void {
			oss
				<< "\t\t\t\"" << multimedia_t::rating_key.at(key)
				<< (i != size - 1 ? "\"," : "\"") << "\n";
		},
		media.rating_,
		2
	);

	stringify_string(oss, "duration", media.duration_, 2);

	stringify_vec(
		oss,
		"genre",
		[](std::ostringstream& oss, const std::uint8_t key, std::size_t i, std::size_t size) mutable -> void {
			oss
				<< "\t\t\t\"" << multimedia_t::genre_key.at(key)
				<< (i != size - 1 ? "\"," : "\"") << "\n";
		},
		media.genre_,
		2
	);

	stringify_key(oss, "description", 2);
	if (media.description_.empty()) oss << "null\n";
	else oss << "\"" << media.description_ << "\"\n";
	oss << "\t}";

	if (!oss) os.setstate(oss.rdstate());
	else os << oss.str();
	return os;
}

std::string multimedia_t::get_type() const {
	return (type_ ? "Movie" : "TV Show");
}

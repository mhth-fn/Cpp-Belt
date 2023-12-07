#include <iostream>
#include <unordered_map>
#include <utility>
#include <optional>
#include <cmath>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <set>
#include <iomanip>

double PI = 3.1415926535;
double R = 6371000.0;

      
using namespace std;

template <typename EnumType>
optional<EnumType> ConvertEnumTypeFromString(string_view type_str, 
                                unordered_map<string_view, EnumType> str_to_enum_type);

pair<string_view, optional<string_view>> SplitTwoStrict(string_view s, string_view delimiter = " ") {
  const size_t pos = s.find(delimiter);
  if (pos == s.npos) {
    return {s, nullopt};
  } else {
    return {s.substr(0, pos), s.substr(pos + delimiter.length())};
  }
}

pair<string_view, string_view> SplitTwo(string_view s, string_view delimiter = " ") {
  const auto [lhs, rhs_opt] = SplitTwoStrict(s, delimiter);
  return {lhs, rhs_opt.value_or("")};
}

string_view ReadToken(string_view& s, string_view delimiter = " ") {
  const auto [lhs, rhs] = SplitTwo(s, delimiter);
  s = rhs;
  return lhs;
}

int ConvertToInt(string_view str) {
  // use std::from_chars when available to git rid of string copy
  size_t pos;
  const int result = stoi(string(str), &pos);
  if (pos != str.length()) {
    std::stringstream error;
    error << "string " << str << " contains " << (str.length() - pos) << " trailing chars";
    throw invalid_argument(error.str());
  }
  return result;
}


template <typename Number>
Number ReadNumberOnLine(istream& stream) {
  Number number;
  stream >> number;
  string dummy;
  getline(stream, dummy);
  return number;
}
struct Response{
    string Bus = "";
    int stops = 0;
    int unique_stops = 0;
    double length = 0;
  };
struct Coordinates{
    double latitude;
    double longitude;
};

struct Route{
    vector<string> stops_;
    bool is_circled = false;
};

double Spacing(const Coordinates& lhs, const Coordinates& rhs){
  double lon_diff = lhs.longitude > rhs.longitude ? lhs.longitude - rhs.longitude : rhs.longitude - lhs.longitude;
  return acos(sin(lhs.latitude) * sin(rhs.latitude) +
  cos(lhs.latitude) * cos(rhs.latitude) * cos(lon_diff)) * R;
}
using RouteBase = unordered_map<string, Route>;
using StopBase = unordered_map<string, Coordinates>;

class Database{
public:
    friend class DatabaseBuilding; 

struct Request;
using RequestHolder = unique_ptr<Request>;

 struct Request{
  enum class Type{
    BUS
  };

  virtual void ParseFrom(string_view input) = 0;
  static RequestHolder Create(Type type);
  virtual Response Process(const Database& db) = 0;
};

struct BusRequest : public Request{
  void ParseFrom(string_view input) override{
    bus = string(ReadToken(input, "el;jekljfe3^&"));
  }

  Response Process(const Database& db) override{
    auto it = db.routebase_.find(bus);
    if (it != end(db.routebase_)){
      Response res;
      res.Bus = bus;
      const auto& rb = it->second.stops_;
      res.stops = rb.size();
      res.unique_stops = set(rb.begin(), rb.end()).size();
      string_view lhs, rhs;
      for (const auto& item : rb){
        if (lhs.empty()){
          lhs = item;
        } else {
          rhs = item;
          res.length += Spacing(db.stopbase_.at(string(lhs)), db.stopbase_.at(string(rhs)));
          lhs = item;
        }
      }
      if (it->second.is_circled){
        res.length += res.length;
        res.stops = res.stops * 2 - 1;
      }
      return res;
    }
    return {bus, 0, 0, 0};
  }
  string bus = "";
};


const unordered_map<string_view, Request::Type> STR_TO_REQUEST_TYPE = {
    {"Bus", Request::Type::BUS},
};

RequestHolder ParseRequest(string_view request_str) const{
  const auto request_type = ConvertEnumTypeFromString<Request::Type>(ReadToken(request_str), STR_TO_REQUEST_TYPE);
  if (!request_type) {
    return nullptr;
  }
  RequestHolder request = Request::Create(*request_type);
  if (request) {
    request->ParseFrom(request_str);
  };
  return request;
}

vector<RequestHolder> ReadRequests(istream& in_stream = cin) const{
  const size_t request_count = ReadNumberOnLine<size_t>(in_stream);

  vector<RequestHolder> requests;
  requests.reserve(request_count);

  for (size_t i = 0; i < request_count; ++i) {
    string request_str;
    getline(in_stream, request_str);
    if (auto request = ParseRequest(request_str)) {
      requests.push_back(move(request));
    }
  }
  return requests;
}

    const StopBase& GetStopBase() const{
      return stopbase_;
    }

    const RouteBase& GetRouteBase() const{
      return routebase_;
    } 
private:
    Database(StopBase& stopbase, RouteBase& routebase) 
    : stopbase_(move(stopbase)), routebase_(move(routebase)){}

    StopBase stopbase_;
    RouteBase routebase_;
};


enum class DataType{
    BUS,
    STOP
};


const unordered_map<string_view, DataType> STR_TO_DATA_TYPE = {
    {"Bus", DataType::BUS},
    {"Stop", DataType::STOP}
};

template <typename EnumType>
optional<EnumType> ConvertEnumTypeFromString(string_view type_str, 
                                unordered_map<string_view, EnumType> str_to_enum_type);

class DatabaseBuilding{
public:
    DatabaseBuilding& ReadData(istream& in_stream  = cin){
        const size_t data_count = ReadNumberOnLine<size_t>(in_stream);

        for (size_t i = 0; i != data_count; ++i){
            string data_str;
            getline(in_stream, data_str);
            WriteData(data_str);
        }

        return *this;
    }

    Database Build(){
        return Database(stopbase_, routebase_);
    }
private:
    void WriteData(string_view data_str){
      if(const auto datatype = ConvertEnumTypeFromString<DataType>(ReadToken(data_str), STR_TO_DATA_TYPE)){
        ParseData(*datatype, data_str);
      }
    }

    void ParseData(const DataType type, string_view data_str){
        switch (type)
        {
        case DataType::BUS:
            ParseRoute(data_str);
            break;
        case DataType::STOP:
            ParseStop(data_str);
            break; 
        default:
            break;
        }
    }

    void ParseRoute(string_view route){
      string routename = string(ReadToken(route, ": "));
      Route res;
      string delimiter = " - ";
      res.is_circled = true;
      if (route.find(">") != string_view::npos){
        delimiter[1] = '>';
        res.is_circled = false;
      }
      while (!route.empty()){
        res.stops_.push_back(string(ReadToken(route, delimiter)));
      }
      routebase_[routename] = move(res);
    }


    void ParseStop(string_view stop){
      string_view stopname = ReadToken(stop, ": ");
      Coordinates cord = {stod(string(ReadToken(stop))) * M_PI / 180.0, stod(string(ReadToken(stop))) * M_PI / 180.0};
      stopbase_[string(stopname)] = cord;
    }

    StopBase stopbase_;
    RouteBase routebase_;
};

template <typename EnumType>
optional<EnumType> ConvertEnumTypeFromString(string_view type_str, 
                                unordered_map<string_view, EnumType> str_to_enum_type) {
  if (const auto it = str_to_enum_type.find(type_str);
      it != str_to_enum_type.end()) {
    return it->second;
  } else {
    return nullopt;
  }
}

Database::RequestHolder Database::Request::Create(Database::Request::Type type) {
  switch (type) {
    case Request::Type::BUS:
      return make_unique<BusRequest>();
    default:
      return nullptr;
  }
}

void PrintResponses(const vector<Response> responses, ostream& out = cout){
  bool is_first = false;
  for (const auto& response : responses){
    if (is_first){
      out << '\n';
    }
    if (response.length != 0){
      out << "Bus " << response.Bus << ": " << response.stops << " stops on route, "
      << response.unique_stops << " unique stops, " << fixed << std::setprecision(6) << response.length << " route length";
    } else {
      out << "Bus " << response.Bus << ": not found";
    }
    is_first = true;
  }
}

vector<Response> ProcessRequests(const vector<Database::RequestHolder>& requests, const Database& db){
 vector<Response> res;
 for (const auto& request : requests){
   res.push_back(request->Process(db));
 }
 return res;
}
int main(){
  const auto db = DatabaseBuilding()
                 .ReadData()
                 .Build();
  const auto request = db.ReadRequests(); 
  const auto responses = ProcessRequests(request, db);
  PrintResponses(responses);
}
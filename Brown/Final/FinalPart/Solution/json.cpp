#include "json.h"

using namespace std;

namespace Json {

  Document::Document(Node root) : root(move(root)) {
  }

  const Node& Document::GetRoot() const {
    return root;
  }

  Node LoadNode(istream& input);

  Node LoadArray(istream& input) {
    vector<Node> result;

    for (char c; input >> c && c != ']'; ) {
      if (c != ',') {
        input.putback(c);
      }
      result.push_back(LoadNode(input));
    }

    return Node(move(result));
  }

  Node LoadDouble(istream& input) {
    std::string str;
    getline(input, str);
    double result = stod(str);
    // while (isdigit(input.peek())) {
    //   result *= 10;
    //   result += input.get() - '0';
    // }
    return Node(result);
  }

  Node LoadString(istream& input) {
    string line;
    getline(input, line, '"');
    return Node(move(line));
  }

  Node LoadBool(istream& input) {
    std::string str;
    getline(input, str);
    bool bl = false;
    if (str[0] == 't'){
      bl = true;
    }
    return Node(bl);
  }

  Node LoadDict(istream& input) {
    map<string, Node> result;

    for (char c; input >> c && c != '}'; ) {
      if (c == ',') {
        input >> c;
      }

      string key = LoadString(input).AsString();
      input >> c;
      result.emplace(move(key), LoadNode(input));
    }

    return Node(move(result));
  }

  Node LoadNode(istream& input) {
    char c;
    input >> c;

    if (c == '[') {
      return LoadArray(input);
    } else if (c == '{') {
      return LoadDict(input);
    } else if (c == '"') {
      return LoadString(input);
    } else {
      input.putback(c);
      if (input.peek() == 't' || input.peek() == 'f'){
        return LoadBool(input);
      } else {
      return LoadDouble(input);
      }
    }
  }

  Document Load(istream& input) {
    return Document{LoadNode(input)};
  }

}

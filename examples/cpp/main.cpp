#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>
#include <streambuf>
#include "wrapper.hpp"

using namespace std;
using namespace speedreader;

size_t num_passed = 0;
size_t num_failed = 0;

void Assert(bool value, const std::string& message) {
  if (!value) {
    cout << "Failed!" << endl;
    cout << message << endl;
  }
  assert(value);
}

void Check(bool expected_readable,
    std::string expected_transformed,
    const std::string& test_description,
    SpeedReader& reader, const std::string& content, const std::string& url) {
  cout << test_description << "... ";
  
  std::string transformed;
  reader.reset(url.c_str());
  reader.pumpContent(content.c_str());
  bool readable = reader.finalize(&transformed);

  if (expected_readable != readable) {
    num_failed++;
  } else {
    num_passed++;
  }

  assert(expected_readable == readable);
  if (expected_readable) {
    assert(transformed.length() > 0);
    assert(transformed == expected_transformed);
  }
}

const std::string basic =
R"(
"<!DOCTYPE html>
<html>
  <head>
    <title>This is title</title>
  </head>
</html>
"
)";

void TestBasics() {
  SpeedReader reader;
  Check(false, "", "Basic document", reader, basic, "http://example.com/");
}

void TestBbc() {
  std::ifstream t("./examples/data/bbc_1.html");
  std::string doc((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());
  std::ifstream t2("./examples/data/bbc_1_expected.html");
  std::string expected((std::istreambuf_iterator<char>(t2)),
                 std::istreambuf_iterator<char>());
  SpeedReader reader;
  Check(true, expected, "BBC document", reader, doc, "https://www.bbc.com/news/newsbeat-48719919");
}

int main() {
  TestBasics();
  TestBbc();
  cout << num_passed << " passed, " <<
      num_failed << " failed" << endl;
  cout << "Success!";
  return 0;
}

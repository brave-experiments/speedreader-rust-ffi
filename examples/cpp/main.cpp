#include <iostream>
#include <assert.h>
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
  bool readable = reader.process(content, url, &transformed);

  if (expected_readable != readable) {
    num_failed++;
  } else {
    num_passed++;
  }

  assert(expected_readable == readable);
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

int main() {
  TestBasics();
  cout << num_passed << " passed, " <<
      num_failed << " failed" << endl;
  cout << "Success!";
  return 0;
}

#include "base64.h"
#include "blns.h"

#include <cerrno>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <sys/xattr.h>
#include <utility>

constexpr auto base64SampleImage =
    R"(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)";

constexpr auto utf8LoremIpsum =
    R"(चिदंश मुश्किले अर्थपुर्ण पसंद स्थिति आशाआपस सोफ़्टवेर बलवान मानव बनाने वास्तव कार्यसिधान्तो आपके उसके तरहथा। प्राथमिक मजबुत बनाकर करते निर्माण आंतरजाल भाषा बढाता गटकउसि निर्देश विचारशिलता रखति शारिरिक व्रुद्धि प्रोत्साहित करता। उन्हे एकत्रित जानकारी सुस्पश्ट कारन उनका सभीकुछ निरपेक्ष लाभान्वित डाले। संपादक विकेन्द्रियकरण समूह बनाना ध्येय मुखय दिशामे बातसमय व्याख्या
नवंबर अपने संस्था आवश्यक उपलब्ध करता आशाआपस दिनांक बनाने सकती बाजार खयालात ऎसाजीस उनका सुचना गुजरना पुस्तक मुश्किले आजपर ध्येय पुस्तक किएलोग आंतरकार्यक्षमता
आशाआपस असरकारक कर्य करता। जोवे पहेला उपेक्ष समस्याए भेदनक्षमता अतित समजते संस्था प्रमान विकेन्द्रियकरण बढाता द्वारा यन्त्रालय चाहे तकनिकल दर्शाता हार्डवेर आपको सुचना जाता असरकारक अविरोधता लाभान्वित बाजार जिम्मे प्रदान व्यवहार समाजो अतित एसेएवं सोफ़्टवेर अंग्रेजी सीमित गएआप एकएस आवश्यक उसीएक् निरपेक्ष हिंदी
उपलब्ध नयेलिए सामूहिक सादगि सुनत नीचे बनाना ब्रौशर दिनांक पुष्टिकर्ता भारतीय किएलोग केन्द्रित साधन बाटते सभिसमज बिन्दुओ मार्गदर्शन विकास जाएन वर्णन अपने है।अभी प्राप्त स्थापित विकेन्द्रित सुचनाचलचित्र ढांचामात्रुभाषा करती प्राण विभाग मानव असक्षम वैश्विक उपलब्धता और्४५० कार्यसिधान्तो चुनने जाने प्रति प्रमान वर्तमान समस्याए सकता गुजरना निर्देश विश्लेषण बिना होसके देखने स्थिति सोफ़तवेर सकती
ध्वनि रखति पासपाई असक्षम समस्याए बलवान २४भि हमेहो। अमितकुमार भारत संदेश असक्षम निर्देश विकेन्द्रित ऎसाजीस प्रेरना बढाता बिना जिसकी कार्यकर्ता प्रतिबध्दता जैसी विषय बलवान क्षमता अविरोधता हार्डवेर मजबुत संपादक प्रतिबध २४भि भाषए जिम्मे क्षमता। बनाना बनाति कलइस उपलब्ध तकरीबन सुस्पश्ट गएआप अनुवाद वार्तालाप बाटते पहोचने वेबजाल विश्लेषण लगती प्रति क्षमता वर्तमान सुचनाचलचित्र बाधा समाजो मानसिक व्याख्या व्याख्यान सादगि जोवे लचकनहि निर्माता हैं। प्रति
जिवन हमारी संपुर्ण विश्वव्यापि जाने नवंबर खयालात व्याख्यान ढांचा समाज पहोचने अनुवादक शुरुआत पहोचने सामूहिक जाएन संदेश किया भोगोलिक मुश्किले विकासक्षमता औषधिक उन्हे मेमत दोषसके गयेगया प्रौध्योगिकी डाले। असक्षम वातावरण संस्थान लगती जिवन स्थिति परिवहन पासपाई डाले। जाता संसाध अनुवाद वर्णित अमितकुमार उशकी प्रदान निर्माता विश्वव्यापि पुर्व द्वारा मुश्किले विकासक्षमता विशेष मेमत औषधिक गयेगया आंतरजाल जैसे ध्वनि हैं। परिभाषित अमितकुमार समाज वेबजाल आधुनिक सहयोग दारी बाजार बातसमय अधिकांश विकेन्द्रियकरण दिये सहयोग उपलब्ध गयेगया समस्याओ बाधा देखने तरहथा। अनुवाद अन्तरराष्ट्रीयकरन
काम बनाति आधुनिक पहोचाना बनाति सेऔर दोषसके बातसमय सुचनाचलचित्र सीमित वेबजाल हमेहो। समूह संस्थान विकेन्द्रित सेऔर संदेश दिशामे विज्ञान विशेष समूह सिद्धांत करके(विशेष अन्तरराष्ट्रीयकरन जिसकी कर्य द्वारा क्षमता। वहहर सुचना विवरण अन्य हुएआदि दिनांक सम्पर्क रचना बाजार हुआआदी वातावरण माहितीवानीज्य
मजबुत बाधा निर्माण मुश्किले भाषाओ तरहथा। पुर्णता अन्तरराष्ट्रीयकरन सकते किएलोग अधिकांश यन्त्रालय पहोच नवंबर ढांचा बहुत वर्णित विकेन्द्रियकरण जिसकी जागरुक सोफ़तवेर उशकी हमारी वर्ष पुर्णता व्रुद्धि संस्क्रुति बारे प्रति सभिसमज विश्वव्यापि जोवे उदेशीत समस्याए खरिदे पहोचने संपुर्ण प्रव्रुति एवम् बाजार प्राप्त अन्तरराष्ट्रीयकरन पहोच। नीचे विकासक्षमता विकेन्द्रियकरण आंतरकार्यक्षमता प्रति वर्ष मानसिक उसीएक् जैसी जिसकी
प्रति सहायता सम्पर्क प्रतिबध देकर होभर गटकउसि पासपाई भोगोलिक सदस्य रचना उदेशीत पहोचने अंतर्गत विकास मर्यादित केन्द्रित केन्द्रिय लिये बढाता सके। सदस्य पुष्टिकर्ता विकासक्षमता ।क हमारी और्४५० बीसबतेबोध ज्यादा रहारुप परिभाषित आजपर विश्व पहोच। किके सारांश दिनांक हिंदी वहहर लक्ष्य प्रमान ऎसाजीस हमारि एकएस जिम्मे गुजरना प्राधिकरन
सादगि सकते सुविधा मुश्किले अनुकूल पुस्तक सिद्धांत कैसे लेकिन बाजार करेसाथ वातावरण उपयोगकर्ता जाने हमारि एकएस गटकउसि कार्यलय जनित संपादक उपलब्ध विभाजनक्षमता बढाता चिदंश पढने उद्योग आधुनिक वास्तविक मानव एसलिये तकनीकी निर्माण उन्हे सम्पर्क सिद्धांत एवम् खरिदे जाने दिशामे वर्णित विवरण संदेश दोषसके सभीकुछ बेंगलूर सेऔर)";

static int __total_tests = 0;
static int __failed_count = 0;

bool file_exists(const std::string &name) {
  std::ifstream f(name.c_str());
  return f.good();
}

std::string unquote_string(const std::string &s) {
  if (s.size() > 1 && s.front() == '\"' && s[s.size() - 1] == '\"') {
    return s.substr(1, s.size() - 2);
  } else {
    return s;
  }
}

template <typename... Ts> void XTLOG(Ts &&... args) {
  int dummy[] = {0, ((std::cout << args), 0)...};
  static_cast<void>(dummy);
  std::cout << std::endl;
}

void set_xattr(std::string file, std::string name, std::string value,
               int flags) {
  int result = setxattr(file.c_str(), name.c_str(), value.data(), value.size(),
#if defined(__APPLE__)
                        0,
#endif
                        flags);
  if (result == -1) {
    throw std::runtime_error(std::string("Cannot set extended attribute '") +
                             name + "': " + std::strerror(errno));
  }
}

std::string get_xattr(std::string file, std::string name) {
  static char get_xattr_buffer[64 * 1024];
  std::string result;

  int count =
      getxattr(file.c_str(), name.c_str(), (void *)get_xattr_buffer, 64 * 1024
#if defined(__APPLE__)
               ,
               0, 0
#endif
               );
  if (count == -1) {
    throw std::runtime_error(std::string("Cannot get extended attribute '") +
                             name + "': " + std::strerror(errno));
  } else {
    result.assign(get_xattr_buffer, count);
  }
  return result;
}

void EXPECT_XATTR_SET(std::string MSG, std::string F, std::string N,
                      std::string V) {
  __total_tests++;
  try {
    set_xattr(F, N, V, 0);
    auto test_value = unquote_string(V);
    auto xattr = get_xattr(F, N);

    bool is_numeric = false;
    try {
      double numeric_xattr = std::stod(xattr);
      is_numeric = true;
      if (xattr == "NaN")
        is_numeric = false;
    } catch (std::exception &e) {
    }

    if (is_numeric ? (std::stod(test_value) != std::stod(xattr))
                   : (test_value != xattr)) {
      XTLOG(MSG, "...", "Failed -- ", "EXPECTED(", test_value, ") GOT(", xattr,
            ")");
      __failed_count++;
    } else {
      XTLOG(MSG, "...", "OK");
    }
  } catch (std::exception &e) {
    XTLOG(MSG, "...", "Failed -- ", e.what());
    __failed_count++;
  }
}


void EXPECT_XATTR_NOTSET(std::string MSG, std::string F, std::string N,
                         std::string V) {
  {
  __total_tests++;
    try {
      set_xattr(F, N, V, 0);
      auto xattr = get_xattr(F, N);
      if (V != xattr) {
        XTLOG(MSG, "...", "Failed -- ", "EXPECTED(", V, ") GOT(", xattr, ")");
        __failed_count++;
      } else {
        XTLOG(MSG, "...", "Failed -- ", "Attribute set");
        __failed_count++;
      }
    } catch (std::runtime_error &e) {
      XTLOG(MSG, "...", "OK");
    }
  }
}

void EXPECT_XATTR_NOTREPLACED(std::string MSG, std::string F, std::string N,
                              std::string V) {
  __total_tests++;
  try {
    set_xattr(F, N, V, XATTR_REPLACE);
    XTLOG(MSG, "...",
        "Failed -- Attribute should not be created if it didn't exist already");
    __failed_count++;
  } catch (std::runtime_error &e) {
    XTLOG(MSG, "...", "OK");
  }
}

void EXPECT_XATTR_NOTCREATED(std::string MSG, std::string F, std::string N,
                             std::string V) {
  __total_tests++;
  try {
    set_xattr(F, N, V, XATTR_CREATE);
    XTLOG(MSG, "...",
        "Failed -- Attribute should not be set if it existed already");
    __failed_count++;
  } catch (std::runtime_error &e) {
    XTLOG(MSG, "...", "OK");
  }
}

int main(int argc, char **argv) {

  if (argc != 2) {
    XTLOG("Usage:\n", argv[0], "EXISTING_TEST_FILE");
    exit(-1);
  }

  if(!file_exists(argv[1])) {
    XTLOG("File ", argv[1], " does not exist!");
    exit(-1);
  }

  EXPECT_XATTR_SET("Setting attribute string value should work", argv[1],
                   "stringAttribute", "stringValue");

  EXPECT_XATTR_SET("Setting attribute with empty value should work", argv[1],
                   "emptyAttribute", "");

  EXPECT_XATTR_SET(
      "Setting attribute with Json string should be properly escaped", argv[1],
      "jsonInvalidObjectString", "{{{{{}");

  EXPECT_XATTR_SET(
      "Setting attribute with inner quotes string should be properly escaped", argv[1],
      "jsonString", R"(asdasd"adsdas'asdda)");

  EXPECT_XATTR_SET("Setting attribute with Json number value should work",
                   argv[1], "jsonNumberAttribute", "-123.89");

  EXPECT_XATTR_SET("Setting attribute with Json boolean value should work",
                   argv[1], "jsonBooleanAttribute", "true");

  EXPECT_XATTR_SET("Setting attribute with new line characters should work",
                   argv[1], "jsonMultilineAttribute", "\nLINE1\nLINE2\nLINE3");

  EXPECT_XATTR_SET("Setting attribute with unicode characters should work",
                   argv[1], "jsonUnicodeAttribute", "महसुस");

  EXPECT_XATTR_SET("Setting attribute with long unicode text should work",
                   argv[1], "jsonLongUnicodeAttribute", utf8LoremIpsum);

  EXPECT_XATTR_SET("Setting attribute with any characters should work",
                   argv[1], "jsonStringSymbols",
                   R"(!@#O!@O#Y!OI@U!@*!*@"<,...,\t\n\\00\0\0\0?><>:|"|||{:}_!(@)(#*!@*#&!(@#*&£§§§))))``````)");

  EXPECT_XATTR_SET("Setting attribute with just single quotes",
                    argv[1], "justSingleQoutes", R"('')");

  EXPECT_XATTR_SET("Setting attribute with just double quotes",
                    argv[1], "justDoubleQoutes", "\"\"");

  EXPECT_XATTR_SET("Setting attribute with just double quotes",
                    argv[1], "valueInDoubleQoutes", R"("text")");

  EXPECT_XATTR_SET("Setting attribute with complex name",
                    argv[1], R"(%^&*()(*&^%$#$%^&*(/)", "123");

  EXPECT_XATTR_SET("Setting attribute with Json object",
                   argv[1], "jsonObject", R"({"key":1})");

  EXPECT_XATTR_SET("Setting attribute with Json array",
                   argv[1], "jsonObject2", R"([{"key1":1},{"key2":2}])");


  for(int i = 0; i<100; i++) {
  EXPECT_XATTR_SET("Setting the same attribute quickly multiple times should work",
                    argv[1], "volatileAttribute", std::to_string(i));
}


  std::string binaryValue;
  binaryValue += "A";
  binaryValue += (char)0;
  binaryValue += "B";
  binaryValue += (char)0;
  binaryValue += "C";

  EXPECT_XATTR_SET("Setting attribute with binary value should work", argv[1],
                   "binaryAttribute", binaryValue);

  std::string sampleImage;
  base64_decode(std::string(base64SampleImage), sampleImage);
  EXPECT_XATTR_SET("Setting attribute with long binary value should work",
                   argv[1], "gifImage", sampleImage);

  EXPECT_XATTR_NOTSET(
      "Setting string attribute with empty name should not work", argv[1], "",
      "IRRELEVANT");

  EXPECT_XATTR_SET("Setting attribute string value should work", argv[1],
                   "TO_BE_REPLACED", "VALUE");
  EXPECT_XATTR_NOTCREATED("Existing attribute should not be replaced with XATTR_CREATE", argv[1],
                          "TO_BE_REPLACED", "stringValue");
  EXPECT_XATTR_NOTREPLACED("Non existing attributed should not be replaced with XATTR_REPLACE",
                           argv[1], "TO_BE_CREATED", "stringValue");

  //
  // Test Big List of Naughty Strings
  //  https://github.com/minimaxir/big-list-of-naughty-strings
  //
  int i = 0;
  for(auto& naughtyString : big_list_of_naughty_strings) {
    if(naughtyString.length() < 127) {
      if(!naughtyString.empty()
          && naughtyString != "￾"
          && !std::all_of(naughtyString.begin(),naughtyString.end(),isspace)) {
        EXPECT_XATTR_SET("Setting naughty string <<<"+naughtyString+">>> name should work", argv[1],
                       naughtyString, "naughtyString_"+std::to_string(i));
      }
      else {
        EXPECT_XATTR_NOTSET("Setting naughty string <<<"+naughtyString+">>> name should work", argv[1],
                       naughtyString, "naughtyString_"+std::to_string(i));
      }
    }
    EXPECT_XATTR_SET("Setting naughty string <<<"+naughtyString+">>> value should work", argv[1],
                   "naughtyString_"+std::to_string(i++), naughtyString);
  }

  if(__failed_count) {
    XTLOG(__failed_count, " of ", __total_tests, " FAILED");
  }
  else {
     XTLOG("All ", __total_tests, " PASSED");
  }

  return __failed_count > 0;
}